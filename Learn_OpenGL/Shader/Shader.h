#ifndef SHADER_H
#define SHADER_H


// ����glad����ȡ���еı���OpenGLͷ�ļ�
#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


class Shader
{
public:
	

	// ��������ȡ��������ɫ��
	Shader(const char* vertexPath, const char* fragmentPath);
	// ʹ��/�������
	void use();
	// uniform���ߺ���
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string &name, float value) const;

	// ����ID
	unsigned int ID;
private:
	void checkCompileErrors(unsigned int shader, std::string type);

	
};

#endif