#pragma once

//��ȷ�����ڰ���GLFW��ͷ�ļ�֮ǰ������GLAD��ͷ�ļ���GLAD��ͷ�ļ���������ȷ��OpenGLͷ�ļ�������GL/gl.h����������Ҫ������������OpenGL��ͷ�ļ�֮ǰ����GLAD��
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Introduce_Hello_Triangle
{
public:
	Introduce_Hello_Triangle();
	~Introduce_Hello_Triangle();


	void processInput(GLFWwindow *window);
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);


	void processEventLoop();
private:
	GLFWwindow* m_pGLWindow = nullptr;

	unsigned int VBO, VAO, EBO;
	unsigned int shaderProgram;


	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";;


	const char* fragmentShaderSource = "#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n\0";


};

