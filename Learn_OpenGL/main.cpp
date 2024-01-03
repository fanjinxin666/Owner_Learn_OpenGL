// Learn_OpenGL.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

//#include <iostream>
//#include <Learn_OpenGL_App/Learn_OpenGL_App.h>
//
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
//
//int main()
//{
//	Learn_OpenGL_App app;
//	app.Initialize(env_model_loading);
//
//	std::cout << "Hello World!\n";
//
//	return 0;
//}
//



#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

const int width = 800;
const int height = 600;

void errorCallback(int error, const char* description) {
	std::cerr << "GLFW Error: " << description << std::endl;
}


void grab_image()
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

	GLubyte* pPixelData = nullptr;
	pPixelData = (GLubyte*)malloc(800 * 600 * 4);

	glReadPixels(0, 0, 800, 600, GL_RGBA, GL_UNSIGNED_BYTE, pPixelData);

	FILE* fp = nullptr;
	fopen_s(&fp, "F:/temp.rgb", "wb");

	if (fp) {
		fwrite(pPixelData, 1, 800 * 600 * 4, fp);
		fclose(fp);
	}

	free(pPixelData);
	pPixelData = nullptr;
}

int main() {
	// 初始化GLFW
	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	// 设置错误回调函数
	glfwSetErrorCallback(errorCallback);

	// 创建窗口
	GLFWwindow* window = glfwCreateWindow(width, height, "Offscreen Rendering", nullptr, nullptr);
	if (!window) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// 设置当前上下文为窗口上下文
	glfwMakeContextCurrent(window);
	// 初始化 GLEW
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	// 创建离屏渲染用的帧缓冲对象和纹理
	GLuint fbo, texture;
	glGenFramebuffers(1, &fbo);
	glGenTextures(1, &texture);

	
	// 设置视口
	glViewport(0, 0, width, height);

	// 绑定帧缓冲对象和纹理
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

	// 检查帧缓冲完整性
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cerr << "Framebuffer is not complete" << std::endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glfwTerminate();
		return -1;
	}

	// 渲染循环
	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// 这里进行你的渲染操作

		//// 读取渲染结果，这里只是简单地输出一些像素值
		//glBindFramebuffer(GL_FRAMEBUFFER, 0);
		////glClear(GL_COLOR_BUFFER_BIT);

		//// 将纹理绘制到窗口
		//glUseProgram(0);
		//glBindTexture(GL_TEXTURE_2D, texture);
		//glBegin(GL_QUADS);
		//glTexCoord2f(0, 0); glVertex2f(-1, -1);
		//glTexCoord2f(1, 0); glVertex2f(1, -1);
		//glTexCoord2f(1, 1); glVertex2f(1, 1);
		//glTexCoord2f(0, 1); glVertex2f(-1, 1);
		//glEnd();

		// 交换缓冲区并处理事件
		glfwSwapBuffers(window);
		glfwPollEvents();

		grab_image();
	}

	// 清理资源
	glDeleteFramebuffers(1, &fbo);
	glDeleteTextures(1, &texture);

	// 关闭窗口和GLFW
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}



