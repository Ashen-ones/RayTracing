#include "gltest.h"
#include <iostream>
void gltest::GlfwInit()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

void gltest::GladInit()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
}

void gltest::GlInit()
{
	GlfwInit();
}

GLFWwindow* gltest::CreateWindow()
{
	window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return nullptr;
	}
	glfwMakeContextCurrent(window);

	GladInit();
	return window;
}

void gltest::ReflushWindow(GLFWwindow* window, int width, int height)
{
	std::cout << "Change Window Size" << std::endl;
	glViewport(0, 0, width, height);
}
void gltest::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	ReflushWindow(window, width,height);
}
void gltest::GlEnd()
{
	glDisableVertexAttribArray(0);
	glfwTerminate();
}

void gltest::Tick()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

