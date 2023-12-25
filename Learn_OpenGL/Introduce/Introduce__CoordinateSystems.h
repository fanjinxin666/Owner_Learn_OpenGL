#pragma once


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include <Shader/Shader.h>

class Introduce__CoordinateSystems
{
public:
	Introduce__CoordinateSystems();
	~Introduce__CoordinateSystems();

public:
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	void processEventLoop();

private:
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

private:
	static float mixValue;

private:
	GLFWwindow* m_pGLWindow = nullptr;

	unsigned int VBO, VAO, EBO;
	unsigned int texture0;
	unsigned int texture1;

	Shader * m_pOurShader = nullptr;
};

