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
	* @brief ��ȡ�������ض�Ӧ���
	* @return �Ը��������ı��
	*/
	static GLuint load_texture(const char *file_name);

private:
	/**
	* @brief �ж�n�Ƿ���2��������
	* @return ���򷵻�true
	*/
	static bool power_of_two(int n);

};
