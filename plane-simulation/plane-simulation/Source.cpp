#include <iostream>
#include <GL/glew.h>
#include <glfw3.h>

#include "Camera.h"
#include "Shader.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"

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

void processInput(GLFWwindow* window);
void scroll_callback(GLFWwindow* window, double xoffset, double yOffset);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main(void) {
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //setam pe COMPAT ca sa 

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

	float positions[] = {
		-0.5f, -0.5f, //0 
		 0.5f,  -0.5f, //1
		 0.5f, 0.5f, //2
		 -0.5f, 0.5f //3
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao); //pentru core profile sa avem binding

	VertexBuffer vb(positions, 4 * 2 * sizeof(float));
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (const void*)0); // linia aceasta linkeaza buffer-ul cu vertex array (vao)
	IndexBuffer ib(indices, 6);


	Shader basicShader("basic.vs", "basic.fs");
	basicShader.Use();
	basicShader.SetVec4("u_Color", 1.0f, 1.0f, 0.0f, 1.0f);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		processInput(window);
		glClear(GL_COLOR_BUFFER_BIT);

		//--desenare patrat
		basicShader.SetVec4("u_Color", 0.5f, 1.0f, 0.0f, 1.0f);
		glBindVertexArray(vao);
		ib.Bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		//glDrawArrays(GL_TRIANGLES, 0, 3);
		//--stop desenare patrat

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

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		pCamera->ProcessKeyboard(Camera::FORWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		pCamera->ProcessKeyboard(Camera::BACKWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		pCamera->ProcessKeyboard(Camera::LEFT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		pCamera->ProcessKeyboard(Camera::RIGHT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_PAGE_UP) == GLFW_PRESS)
		pCamera->ProcessKeyboard(Camera::UP, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_PAGE_DOWN) == GLFW_PRESS)
		pCamera->ProcessKeyboard(Camera::DOWN, (float)deltaTime);

	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
		int width, height;
		glfwGetWindowSize(window, &width, &height);
		pCamera->Reset(width, height);

	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	/*if (key == GLFW_KEY_A && action == GLFW_PRESS && g_fKa < 1.0)
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
	}*/
}