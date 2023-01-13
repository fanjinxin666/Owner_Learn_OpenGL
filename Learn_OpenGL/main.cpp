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
	app.Initialize(0);
	std::cout << "Hello World!\n";

	//std::unique_lock<std::mutex> lck(mutex);
	//condition_var.wait(lck);

	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件






//class enty
//{
//public:
//	enty() = default;
//public:
//	int test() {
//		std::cout << "111" << std::endl;
//		return 123;
//	}
//
//	std::string getName() 
//	{
//		return this->m_strName;
//	};
//
//private:
//	std::string m_strName;
//};
//
//
//int main() {
//	enty* ptr = NULL;
//	int num = ptr->test();
//	std::cout << "test" << num << std::endl;
//	return 0;
//}




