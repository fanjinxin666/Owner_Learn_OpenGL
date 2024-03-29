#ifndef SHADER_H
#define SHADER_H


// 包含glad来获取所有的必须OpenGL头文件
#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader
{
public:
	// 构造器读取并构建着色器
	Shader(const char* vertexPath, const char* fragmentPath);
	// 使用/激活程序
	void use();
	// uniform工具函数
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;

	void setMaxtrix(const std::string &name, GLsizei count, GLboolean transpose, const GLfloat *value);

	// 程序ID
	unsigned int ID;
private:
	void checkCompileErrors(unsigned int shader, std::string type);
};

#endif