#pragma once

//��ȷ�����ڰ���GLFW��ͷ�ļ�֮ǰ������GLAD��ͷ�ļ���GLAD��ͷ�ļ���������ȷ��OpenGLͷ�ļ�������GL/gl.h����������Ҫ������������OpenGL��ͷ�ļ�֮ǰ����GLAD��
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <Shader/Shader.h>

class Introduce_Shaders
{
public:
	Introduce_Shaders();
	~Introduce_Shaders();

	void processInput(GLFWwindow *window);

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);


	void processEventLoop();
private:
	GLFWwindow* m_pGLWindow = nullptr;

	unsigned int VBO, VAO;

	Shader * m_pOurShader = nullptr;// { "ShaderConfig/1_5_shader.vs", "ShaderConfig/1_5_shader.fs" };

};

