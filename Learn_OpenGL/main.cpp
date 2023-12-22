// Learn_OpenGL.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Learn_OpenGL_App/Learn_OpenGL_App.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <mutex>
#include <condition_variable>
std::mutex                      mutex;
std::condition_variable         condition_var;


int main()
{
	Learn_OpenGL_App app;
	app.Initialize(env_introduce_texture);

	std::cout << "Hello World!\n";

	//std::unique_lock<std::mutex> lck(mutex);
	//condition_var.wait(lck);

	return 0;
}








