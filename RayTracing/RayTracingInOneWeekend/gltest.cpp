#include "Gltest.h"
#include <iostream>
Gltest::Gltest()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
}

void Gltest::GladInit()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
}

void Gltest::GlInit()
{

}

GLFWwindow* Gltest::CreateWindow()
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

void Gltest::ReflushWindow(GLFWwindow* window, int width, int height)
{
	std::cout << "Change Window Size" << std::endl;
	glViewport(0, 0, width, height);
}
void Gltest::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	ReflushWindow(window, width,height);
}
void Gltest::GlEnd()
{
	glDisableVertexAttribArray(0);
	glfwTerminate();
}

void Gltest::Tick()
{
	glfwSwapBuffers(window);
	glfwPollEvents();
}

