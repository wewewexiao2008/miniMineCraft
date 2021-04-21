#define  _CRT_SECURE_NO_WARNINGS
#include"Cube.h"

Cube::Cube(float x, float y, float z, float size, GLuint top, GLuint bot, GLuint side)
	: _x(x), _y(y), _z(z), _size(size), _top(top), _bot(bot), _side(side)
{}

Cube::Cube()
{}

Cube::~Cube()
{}


void Cube::createCube()
{
	float x = _x;
	float y = _y;
	float z = _z;
	float size = _size;
	glBindTexture(GL_TEXTURE_2D, _bot);

	glBegin(GL_QUADS);
	//底面
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x + size, y, z);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(x + size, y, z + size);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(x, y, z + size);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(x, y, z);
	glEnd();

	//侧面西
	glBindTexture(GL_TEXTURE_2D, _side);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(x + size, y, z);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x, y, z);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(x, y + size, z);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(x + size, y + size, z);
	glEnd();

	//侧面东
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(x, y, z + size);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x + size, y, z + size);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(x + size, y + size, z + size);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(x, y + size, z + size);
	glEnd();

	//侧面南
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(x + size, y, z + size);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x + size, y, z);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(x + size, y + size, z);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(x + size, y + size, z + size);
	glEnd();

	//侧面北
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(x, y, z);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x, y, z + size);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(x, y + size, z + size);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(x, y + size, z);
	glEnd();

	//顶面
	glBindTexture(GL_TEXTURE_2D, _top);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(x, y + size, z);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(x, y + size, z + size);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(x + size, y + size, z + size);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(x + size, y + size, z);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, 0);
}

//初始化材质
void Cube::initCubeTexture() 
{
	texRedStone = Texture::load_texture("img/redStone.bmp");
	texGrass = Texture::load_texture("img/grass.bmp");
	texSoil = Texture::load_texture("img/soil.bmp");
	texStone = Texture::load_texture("img/stone.bmp");
	texWater = Texture::load_texture("img/water.bmp");
	texWood = Texture::load_texture("img/wood.bmp");
	texDirt = Texture::load_texture("img/dirt.bmp");;
	texBrick = Texture::load_texture("img/brick.bmp");
	texTabletop = Texture::load_texture("img/tabletop.bmp");
	texTableside = Texture::load_texture("img/tableside1.bmp");
	texDiamond = Texture::load_texture("img/diamond.bmp");
	texTnttop = Texture::load_texture("img/tnttop.bmp");
	texTntside = Texture::load_texture("img/tntside.bmp");
	texTreetop = Texture::load_texture("img/treetop.bmp");
	texTreeside = Texture::load_texture("img/treeside.bmp");
	texLeaf = Texture::load_texture("img/leaf.bmp");
	texBookshelf = Texture::load_texture("img/bookshelf.bmp");
	texRedSand = Texture::load_texture("img/redsand.bmp");
	texSand = Texture::load_texture("img/sand.bmp");
	
	texSkybox_back = Texture::load_texture("img/back.bmp");
	texSkybox_front = Texture::load_texture("img/front.bmp");
	texSkybox_down = Texture::load_texture("img/down.bmp");
	texSkybox_up = Texture::load_texture("img/up.bmp");
	texSkybox_right = Texture::load_texture("img/right.bmp");
	texSkybox_left = Texture::load_texture("img/left.bmp");
}

GLuint Cube::texRedStone = 0;
GLuint Cube::texGrass = 0;
GLuint Cube::texSoil = 0;
GLuint Cube::texStone = 0;
GLuint Cube::texWater = 0;
GLuint Cube::texWood = 0;
GLuint Cube::texDirt = 0;
GLuint Cube::texBrick = 0;
GLuint Cube::texTabletop = 0;
GLuint Cube::texTableside = 0;
GLuint Cube::texDiamond = 0;
GLuint Cube::texTnttop = 0;
GLuint Cube::texTntside = 0;
GLuint Cube::texTreetop = 0;
GLuint Cube::texTreeside = 0;
GLuint Cube::texLeaf = 0;
GLuint Cube::texBookshelf = 0;
GLuint Cube::texRedSand = 0;
GLuint Cube::texSand = 0;
GLuint Cube::texSkybox_back = 0;
GLuint Cube::texSkybox_front = 0;
GLuint Cube::texSkybox_down = 0;
GLuint Cube::texSkybox_up = 0;
GLuint Cube::texSkybox_right = 0;
GLuint Cube::texSkybox_left = 0;