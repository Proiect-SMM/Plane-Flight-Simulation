#include <iostream>
#include "Camera.h"

#pragma comment (lib, "glfw3dll.lib")
#pragma comment (lib, "glew32.lib")
#pragma comment (lib, "OpenGL32.lib")

double deltaTime = 0.0f;	// time between current frame and last frame
double lastFrame = 0.0f;
float g_fKa = 0.5;
float g_fKd = 0.5;
float g_fKs = 0.5;
float g_fn = 1;

const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

Camera* pCamera = nullptr;

//int Run();
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
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
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

//int Run() {
//	//GLFWwindow* window;
//
//	///* Initialize the library */
//	//if (!glfwInit())
//	//	return -1;
//
//	///* Create a windowed mode window and its OpenGL context */
//	//window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
//	//if (!window)
//	//{
//	//	glfwTerminate();
//	//	return -1;
//	//}
//
//	///* Make the window's context current */
//	//glfwMakeContextCurrent(window);
//
//	///* Loop until the user closes the window */
//	//while (!glfwWindowShouldClose(window))
//	//{
//	//	/* Render here */
//	//	glClear(GL_COLOR_BUFFER_BIT);
//
//	//	/* Swap front and back buffers */
//	//	glfwSwapBuffers(window);
//
//	//	/* Poll for and process events */
//	//	glfwPollEvents();
//	//}
//
//	//glfwTerminate();
//	//glfwInit();
//	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	//// glfw window creation
//	//GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "plane-simulation", NULL, NULL);
//	//if (window == NULL) {
//	//	std::cout << "Failed to create GLFW window" << std::endl;
//	//	glfwTerminate();
//	//	return -1;
//	//}
//
//	//glfwMakeContextCurrent(window);
//	//glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//	//glfwSetCursorPosCallback(window, mouse_callback);
//	//glfwSetScrollCallback(window, scroll_callback);
//	//glfwSetKeyCallback(window, key_callback);
//
//	//glewInit();
//	//glEnable(GL_DEPTH_TEST);
//
//	//pCamera = new Camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0, 0.0, 3.0));
//	//while (!glfwWindowShouldClose(window)) {
//	//	// per-frame time logic
//	//	double currentFrame = glfwGetTime();
//	//	deltaTime = currentFrame - lastFrame;
//	//	lastFrame = currentFrame;
//
//	//	// input
//	//	//processInput(window);
//
//	//	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//	//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//	//}
//
//	//delete pCamera;
//
//}