#include <iostream>
#include "Camera.h"
#include <GL/glew.h>
#include "Shader.h"
#include <glfw3.h>

#pragma comment (lib, "glfw3dll.lib")
#pragma comment (lib, "glew32.lib")
#pragma comment (lib, "OpenGL32.lib")

double deltaTime = 0.0f;	// time between current frame and last frame
double lastFrame = 0.0f;
float g_fKa = 0.5;
float g_fKd = 0.5;
float g_fKs = 0.5;
float g_fn = 1;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Camera* pCamera = nullptr;

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
static unsigned int CompileShader(unsigned int type, const std::string& source);
void scroll_callback(GLFWwindow* window, double xoffset, double yOffset);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main(void) {
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "plane-simulation", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	//tip : shader = cod ce ruleaza pe gpu
	//glew poate fi initializat doar dupa un context valid!!!!
	if (glewInit() != GLEW_OK) {
		std::cout << "Error at glew!";
	}
	
	std::cout << glGetString(GL_VERSION) << "\n";


	float positions[6] = {
		-0.5f, -0.5f,
		 0.0f,  0.5f,
		 0.5f, -0.5f
	};

	unsigned int buffer;
	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW); 
	//static- nu il modificam, dynamic - il modificam si il actualizam la fiecare frame, draw - se actualizeaza la fiecare frame, fara modificare

	//distanta dintre vertex-uri sizeof(float) * 2 este de 2 float-uri, yup
	//0 = de la care se incepe
	// 2 = cate float-uri avem per vertex
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (const void*) 0);

	Shader basicShader("basic.vs", "basic.fs");
	basicShader.Use();
	/*unsigned int shader = CreateShader(vertexShader, fragmentShader);
	glUseProgram(shader);*/
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		//--desenare triunghi
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		//--stop desenare triunghi

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
//
//static unsigned int CompileShader(unsigned int type, const std::string& source) {
//	unsigned int id = glCreateShader(type);
//	const char* src = source.c_str();
//	glShaderSource(id, 1, &src, nullptr);
//	glCompileShader(id);
//	
//	//Error handling
//	int result;
//	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
//	if (result == GL_FALSE) {
//		int length;
//		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
//		char * message = (char*) alloca(length * sizeof(char));
//		glGetShaderInfoLog(id, length, &length, message);
//		std::cout << "Failed to compile shader!" << std::endl;
//		std::cout << message << std::endl;
//		glDeleteShader(id);
//		return 0;
//	}
//
//	return id;
//}
//
//static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
//	unsigned int program = glCreateProgram();
//	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
//	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
//
//	glAttachShader(program, vs);
//	glAttachShader(program, fs);
//	glLinkProgram(program);
//	glValidateProgram(program);
//
//	glDeleteShader(vs);
//	glDeleteShader(fs);
//
//	return program;
//}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	pCamera->Reshape(width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	pCamera->MouseControl((float)xpos, (float)ypos);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yOffset)
{
	pCamera->ProcessMouseScroll((float)yOffset);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_A && action == GLFW_PRESS && g_fKa < 1.0)
	{
		g_fKa += 0.1;
	}
	if (key == GLFW_KEY_Z && action == GLFW_PRESS && g_fKa > 0)
	{
		g_fKa -= 0.1;
	}
	if (key == GLFW_KEY_D && action == GLFW_PRESS && g_fKd > 0)
	{
		g_fKd -= 0.1;
	}
	if (key == GLFW_KEY_C && action == GLFW_PRESS && g_fKd < 1.0)
	{
		g_fKd += 0.1;
	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS && g_fKs > 0)
	{
		g_fKs -= 0.1;
	}
	if (key == GLFW_KEY_X && action == GLFW_PRESS && g_fKs < 1.0)
	{
		g_fKs += 0.1;
	}
	if (key == GLFW_KEY_N && action == GLFW_PRESS && g_fn < 1.0)
	{
		g_fn *= 2;
	}
	if (key == GLFW_KEY_M && action == GLFW_PRESS && g_fn > 0.0)
	{
		g_fn /= 2;
	}
}
