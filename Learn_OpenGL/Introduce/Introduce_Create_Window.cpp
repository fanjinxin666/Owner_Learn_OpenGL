
#include "Introduce_Create_Window.h"
#include "windows.h"
#include <glad/glad.h>
#include <GLFW\glfw3.h>


Introduce_Create_Window::Introduce_Create_Window()
{
	// ���庯��ԭ��
	typedef void(*GL_GENBUFFERS) (GLsizei, GLuint*);
	// �ҵ���ȷ�ĺ�������ֵ������ָ��
	GL_GENBUFFERS glGenBuffers = (GL_GENBUFFERS)wglGetProcAddress("glGenBuffers");
	// ���ں������Ա�����������
	GLuint buffer;
	glGenBuffers(1, &buffer);
}

Introduce_Create_Window::~Introduce_Create_Window()
{

}

