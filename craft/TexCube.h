#pragma once
#include "Cube.h"
#define CUBE_NUM 16
enum CubeTex {
	Empty = -1,
	Light = 0,
	Wood = 1,
	Water = 2,
	Soil = 3,
	Stone = 4,
	RedStone = 5,
	Dirt = 6,
	Brick = 7,
	Table = 8,
	Diamond = 9,
	Tnt = 10,
	Tree = 11,
	Leaf = 12,
	Bookshelf = 13,
	RedSand = 14,
	Sand = 15
};

//纹理相关设置
class TexCube : public Cube 
{
public:
	TexCube(float x, float y, float z, float size, CubeTex tex);
	TexCube() {};
	void createCube();
	~TexCube();
	CubeTex type;
	GLuint GetSide() { return _side; }
private:
	GLuint _top;
	GLuint _bot;
	GLuint _side;
};


