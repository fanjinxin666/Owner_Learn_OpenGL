
#include "Introduce_Create_Window.h"
#include "windows.h"
#include <glad/glad.h>
#include <GLFW\glfw3.h>


Introduce_Create_Window::Introduce_Create_Window()
{
	// 定义函数原型
	typedef void(*GL_GENBUFFERS) (GLsizei, GLuint*);
	// 找到正确的函数并赋值给函数指针
	GL_GENBUFFERS glGenBuffers = (GL_GENBUFFERS)wglGetProcAddress("glGenBuffers");
	// 现在函数可以被正常调用了
	GLuint buffer;
	glGenBuffers(1, &buffer);
}

Introduce_Create_Window::~Introduce_Create_Window()
{

}

