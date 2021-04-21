#pragma once
#include<gl\glut.h>
#include<iostream>
#include<fstream>
#include<string>

#define BMP_Header_Length 54

class Texture
{
public:
	/**
	* @brief 读取纹理并返回对应编号
	* @return 对该纹理分配的编号
	*/
	static GLuint load_texture(const char *file_name);

private:
	/**
	* @brief 判断n是否是2的整数幂
	* @return 是则返回true
	*/
	static bool power_of_two(int n);

};
