#include"TexCube.h"

const GLfloat torch_Ambient[] = { 0.185f, 0.151f, 0.025f, 1.0f };    //环境光
const GLfloat torch_Diffuse[] = { 0.185f, 0.151f, 0.025f, 1.0f };    //漫射光
const GLfloat torch_Specular[] = { 0.625f, 0.625f, 0.425f, 1.0f };    //镜面光
const GLfloat torch_Emission[] = { 0.625f, 0.625f, 0.425f, 1.0f };    //自发光
const GLfloat torch_Position[] = { 0.0f, 0.0f, 0.0f, 1.0f };        //位置
const GLfloat torch_Constant[] = { 0.002f };                        //常量衰减系数
const GLfloat torch_Linear[] = { 0.002f };                        //一次衰减系数
const GLfloat torch_Quadratic[] = { 0.0f };                        //二次衰减系数

TexCube::TexCube(float x, float y, float z, float size, CubeTex tex)
	: Cube()
{
	_x = x;
	_y = y;
	_z = z;
	_size = size;
	type = tex;
	switch (tex)
	{
	case Wood:
		_top = Cube::texWood;
		_bot = Cube::texWood;
		_side = Cube::texWood;
		break;
	case Water:
		_top = Cube::texWater;
		_bot = Cube::texWater;
		_side = Cube::texWater;
		break;
	case Soil:
		_top = Cube::texGrass;
		_bot = Cube::texGrass;
		_side = Cube::texSoil;
		break;
	case Stone:
		_top = Cube::texStone;
		_bot = Cube::texStone;
		_side = Cube::texStone;
		break;
	case RedStone:
		_top = Cube::texRedStone;
		_bot = Cube::texRedStone;
		_side = Cube::texRedStone;
		break;
	case Dirt:
		_top = Cube::texDirt;
		_bot = Cube::texDirt;
		_side = Cube::texDirt;
		break;
	case Brick:
		_top = Cube::texBrick;
		_bot = Cube::texBrick;
		_side = Cube::texBrick;
		break;
	case Table:
		_top = Cube::texTabletop;
		_bot = Cube::texTabletop;
		_side = Cube::texTableside;
		break;
	case Diamond:
		_top = Cube::texDiamond;
		_bot = Cube::texDiamond;
		_side = Cube::texDiamond;
		break;
	case Tnt:
		_top = Cube::texTnttop;
		_bot = Cube::texTnttop;
		_side = Cube::texTntside;
		break;
	case Tree:
		_top = Cube::texTreetop;
		_bot = Cube::texTreetop;
		_side = Cube::texTreeside;
		break;
	case Leaf:
		_top = Cube::texLeaf;
		_bot = Cube::texLeaf;
		_side = Cube::texLeaf;
		break;
	case Bookshelf:
		_top = Cube::texWood;
		_bot = Cube::texWood;
		_side = Cube::texBookshelf;
		break;
	case RedSand:
		_top = Cube::texRedSand;
		_bot = Cube::texRedSand;
		_side = Cube::texRedSand;
		break;
	case Sand:
		_top = Cube::texSand;
		_bot = Cube::texSand;
		_side = Cube::texSand;
		break;
	default:
		break;
	}
}

void TexCube::createCube()
{
	float x = _x;
	float y = _y;
	float z = _z;
	if (type != Light) {
		float size = _size;
		float half = size / 2.0;

		float white[] = { 0.85f, 0.85f, 0.85f, 1.0f };
		float gray[] = { 0.6f, 0.6f, 0.6f, 1.0f };
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, white);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, gray);
		glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 100);

		//底面
		glBindTexture(GL_TEXTURE_2D, _bot);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(x + half, y - half, z - half);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(x + half, y - half, z + half);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(x - half, y - half, z + half);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(x - half, y - half, z - half);
		glEnd();

		//侧面西
		glBindTexture(GL_TEXTURE_2D, _side);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(x + half, y - half, z - half);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(x - half, y - half, z - half);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(x - half, y + half, z - half);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(x + half, y + half, z - half);
		glEnd();

		//侧面东
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(x - half, y - half, z + half);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(x + half, y - half, z + half);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(x + half, y + half, z + half);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(x - half, y + half, z + half);
		glEnd();

		//侧面南
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(x + half, y - half, z + half);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(x + half, y - half, z - half);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(x + half, y + half, z - half);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(x + half, y + half, z + half);
		glEnd();

		//侧面北
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(x - half, y - half, z - half);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(x - half, y - half, z + half);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(x - half, y + half, z + half);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(x - half, y + half, z - half);
		glEnd();

		//顶面
		glBindTexture(GL_TEXTURE_2D, _top);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(x - half, y + half, z - half);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(x - half, y + half, z + half);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(x + half, y + half, z + half);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(x + half, y + half, z - half);
		glEnd();

		glBindTexture(GL_TEXTURE_2D, 0);
	}
	else {
		glLightfv(GL_LIGHT2, GL_AMBIENT, torch_Ambient);
		glLightfv(GL_LIGHT2, GL_DIFFUSE, torch_Diffuse);
		glLightfv(GL_LIGHT2, GL_SPECULAR, torch_Specular);

		glLightfv(GL_LIGHT2, GL_CONSTANT_ATTENUATION, torch_Constant);
		glLightfv(GL_LIGHT2, GL_LINEAR_ATTENUATION, torch_Linear);
		glLightfv(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, torch_Quadratic);

		glPushMatrix();
		glTranslated(x, y, z);
		glColor3f(0.925f, 0.725f, 0.125f);
		glLightfv(GL_LIGHT2, GL_POSITION, torch_Position);
		glMaterialfv(GL_FRONT, GL_EMISSION, torch_Emission);
		glScalef(1.0f, 5.0f, 1.0f);
		glutSolidCube(0.1);
		glPopMatrix();

		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT2);
	}
}

TexCube::~TexCube()
{}