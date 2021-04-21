#pragma once
#include <iostream>
#include <cmath>
#include <gl\glut.h>
#include "Point.h"
#include "Texture.h"

#define BMP_Header_Length 54

class Cube 
{
public:
	Cube();

	Cube(float, float, float, float, GLuint, GLuint, GLuint);

	void createCube();
	
	static void initCubeTexture();

	~Cube();

public:
	float _x, _y, _z, _size;
public:
	static GLuint texRedStone;
	static GLuint texGrass;
	static GLuint texSoil;
	static GLuint texStone;
	static GLuint texWater;
	static GLuint texWood;
	static GLuint texDirt;
	static GLuint texBrick;
	static GLuint texTabletop;
	static GLuint texTableside;
	static GLuint texDiamond;
	static GLuint texTnttop;
	static GLuint texTntside;
	static GLuint texTreetop;
	static GLuint texTreeside;
	static GLuint texLeaf;
	static GLuint texBookshelf;
	static GLuint texRedSand;
	static GLuint texSand;

	//Ìì¿ÕºÐ
	static GLuint texSkybox_back;
	static GLuint texSkybox_front;
	static GLuint texSkybox_down;
	static GLuint texSkybox_up;
	static GLuint texSkybox_right;
	static GLuint texSkybox_left;

protected:
	GLuint _top, _bot, _side;
};


