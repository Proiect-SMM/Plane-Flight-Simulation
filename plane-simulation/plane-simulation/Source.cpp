#include <iostream>
#include <glew.h>
#include <glfw3.h>

#include "Camera.h"
#include "Mesh.h"
#include "Shader.h"
#include "Skybox.h"
#include "Model.h"
#include "Terrain.h"

#pragma comment (lib, "glfw3dll.lib")
#pragma comment (lib, "glew32.lib")
#pragma comment (lib, "OpenGL32.lib")

double deltaTime = 0.5f;	// time between current frame and last frame
double lastFrame = 0.5f;

//test
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

Camera* pCamera = nullptr;
Terrain* terrain = nullptr;
void Cleanup();
void processInput(GLFWwindow* window);
void scroll_callback(GLFWwindow* window, double xoffset, double yOffset);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void InitWindow(GLFWwindow* (&window), const std::string& title);

int main(void) {
	GLFWwindow* window;
	InitWindow(window, "Plane-Simulation");

	terrain = new Terrain("terrain/map.jpg");

	glEnable(GL_DEPTH_TEST);

	Shader simpleShader("basic.vs", "basic.fs");

	Skybox skybox;

	Model* airplane = new Model("airplane/airplane.obj");

	pCamera = new Camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0, 100.0, 90.0));


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		processInput(window);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		
		glDepthMask(GL_FALSE);
		skybox.Draw(pCamera);
		glDisable(GL_DEPTH_TEST);
		glDepthMask(GL_TRUE);

		glEnable(GL_DEPTH_TEST);

		simpleShader.Bind();
		simpleShader.SetMat4("projection", pCamera->GetProjectionMatrix());
		simpleShader.SetMat4("view", pCamera->GetViewMatrix());
		glm::mat4 model = glm::scale(glm::mat4(1), glm::vec3(0.01f));
		model = glm::rotate(model, -90.f, {1.0f, 0.0f, 0.0f });
		simpleShader.SetMat4("model", model);
		//const Shader shader = simpleShader;
		airplane->Draw(&simpleShader); 

		model = glm::mat4(0.7f);
		//model= glm::scale(glm::mat4(1), glm::vec3(0.01f,0.01f,0.01f));
		simpleShader.SetMat4("model", model);
		terrain->Render();
		

		//glDrawArrays(GL_TRIANGLES, 0, 3);
		//--stop desenare patrat

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
	Cleanup();

	glfwTerminate();
	return 0;
}
void InitWindow(GLFWwindow* (&window), const std::string& title) {
	/* Initialize the library */
	if (!glfwInit())
		exit(-1);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //setam pe COMPAT ca sa 

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, title.c_str(), NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(-1);
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	//glfwSetKeyCallback(window, key_callback);
	//tip : shader = cod ce ruleaza pe gpu
	//glew poate fi initializat doar dupa un context valid!!!!
	if (glewInit() != GLEW_OK) {
		std::cout << "Error at glew!";
	}

	std::cout << glGetString(GL_VERSION) << "\n";
}

void Cleanup() {
	delete pCamera;
}

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