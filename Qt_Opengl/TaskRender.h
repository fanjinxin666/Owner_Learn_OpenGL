#pragma once

#include <iostream>
#include <thread>


class TaskRender
{
public:
	TaskRender();
	~TaskRender();

public:
	void Render();

private:
	void thread_render_fun();

private:
	std::thread m_render_handle;

};

