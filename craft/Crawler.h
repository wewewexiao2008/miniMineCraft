#pragma once
#include "Point.h"
#include<cstdio>
#include<iostream>
#include<GL\glut.h>



/**
* @brief 苦力怕类
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
	float vangle;    // 速度偏角
	bool move;


public:
	// 构造函数
	Crawler();
	
	Crawler(float x, float y, float z);
	
	// 重置苦力怕大小
	void resetSize(float new_basic);
	
	// 设置苦力怕坐标
	void setLocation(float x, float y, float z);
	
	// 重绘苦力怕
	void reset();
	void randomMove();
	void createCrawler();
private:
	void _ini();
};