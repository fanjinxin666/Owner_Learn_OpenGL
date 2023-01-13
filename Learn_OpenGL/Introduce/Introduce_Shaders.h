#pragma once

//请确认是在包含GLFW的头文件之前包含了GLAD的头文件。GLAD的头文件包含了正确的OpenGL头文件（例如GL/gl.h），所以需要在其它依赖于OpenGL的头文件之前包含GLAD。
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

