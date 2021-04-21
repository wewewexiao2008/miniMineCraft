#pragma once
#include <iostream>
#include <time.h>
#include<gl\glut.h>

/**
* @brief 光的设置类
*/
class LightMaterial 
{
public:
	LightMaterial();

	void setLight();

	void setTorch(GLfloat x, GLfloat y, GLfloat z);

	void setMaterial(int type);

	void setBackGround();

private:
	GLfloat ***material;
	GLfloat **material0;
	GLfloat **material1;
	GLfloat **material2;
};

