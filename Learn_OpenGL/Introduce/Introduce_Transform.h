#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <Shader/Shader.h>

class Introduce_Transform
{
public:
	Introduce_Transform();
	~Introduce_Transform();
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

