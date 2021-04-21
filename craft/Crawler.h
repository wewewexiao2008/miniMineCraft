#pragma once
#include "Point.h"
#include<cstdio>
#include<iostream>
#include<GL\glut.h>



/**
* @brief ��������
*/
class Crawler
{
public:
	float basic_size;
	float speed;
	Point head_scale, body_scale, foot_scale, eye_scale, mouth_scale;
	Point head, body, foot, eyeL, eyeR, mouth;
	
	float x, y, z;
	int random_t;
	unsigned int count;
	float vangle;    // �ٶ�ƫ��
	bool move;


public:
	// ���캯��
	Crawler();
	
	Crawler(float x, float y, float z);
	
	// ���ÿ����´�С
	void resetSize(float new_basic);
	
	// ���ÿ���������
	void setLocation(float x, float y, float z);
	
	// �ػ������
	void reset();
	void randomMove();
	void createCrawler();
private:
	void _ini();
};