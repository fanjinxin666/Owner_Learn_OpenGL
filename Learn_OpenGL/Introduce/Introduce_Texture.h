#pragma once

//��ȷ�����ڰ���GLFW��ͷ�ļ�֮ǰ������GLAD��ͷ�ļ���GLAD��ͷ�ļ���������ȷ��OpenGLͷ�ļ�������GL/gl.h����������Ҫ������������OpenGL��ͷ�ļ�֮ǰ����GLAD��
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <Shader/Shader.h>

class Introduce_Texture
{
public:
	Introduce_Texture();
	~Introduce_Texture();
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	void processEventLoop();

private:
	void processInput(GLFWwindow *window);

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
private:
	GLFWwindow* m_pGLWindow = nullptr;

	unsigned int VBO, VAO, EBO;
	unsigned int texture0;
	unsigned int texture1;

	Shader * m_pOurShader = nullptr;// { "ShaderConfig/1_5_shader.vs", "ShaderConfig/1_5_shader.fs" };


	static float mixValue;
};

