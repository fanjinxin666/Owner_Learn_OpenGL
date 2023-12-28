// Learn_OpenGL.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Learn_OpenGL_App/Learn_OpenGL_App.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//#include <mutex>
//#include <condition_variable>
//std::mutex                      mutex;
//std::condition_variable         condition_var;
//
//
//int main()
//{
//	Learn_OpenGL_App app;
//	app.Initialize(env_model_loading);
//
//	std::cout << "Hello World!\n";
//
//	//std::unique_lock<std::mutex> lck(mutex);
//	//condition_var.wait(lck);
//
//	return 0;
//}



#include <GL/glew.h>
#include <iostream>

const int width = 800;
const int height = 600;

int main() {
	// 初始化 GLEW
	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	// 创建离屏渲染用的帧缓冲对象和纹理
	GLuint fbo, texture;
	glGenFramebuffers(1, &fbo);
	glGenTextures(1, &texture);

	// 绑定帧缓冲对象和纹理
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

	// 检查帧缓冲完整性
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cerr << "Framebuffer is not complete" << std::endl;
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		return -1;
	}

	// 渲染到帧缓冲对象
	glViewport(0, 0, width, height);
	glClear(GL_COLOR_BUFFER_BIT);
	// 这里进行你的渲染操作

	// 读取渲染结果，将数据存储在pixels数组中
	unsigned char* pixels = new unsigned char[width * height * 3]; // 3 channels (RGB)
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);

	// 现在pixels数组包含了渲染结果的数据

	// 清理资源
	delete[] pixels;
	glDeleteFramebuffers(1, &fbo);
	glDeleteTextures(1, &texture);

	return 0;
}





