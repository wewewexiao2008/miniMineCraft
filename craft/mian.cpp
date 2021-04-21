/**
* @file main.c
* @author zf
* @date 2017/11/26
* @detail ��������openglȥ����minecraft
* @TODO �������ɣ��ܼ���minecraft�Ĳ��ʰ���������Ư�����⣬�ƻ����飬����״̬�ļ�¼
*/
#define  _CRT_SECURE_NO_WARNINGS
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>

#include "Crawler.h"
//#include "visualBall.h"
#include "CubeManager.h"
#include "LightMaterial.h"
#include "Man.h"
#include "Chunk.h"
#include "coll_dete.h"
#include "Camera.h"
#include "Skybox.h"
#include "Motion.h"
#include "AABB.h"
#include "snapScreen.h"
#include <time.h>
using namespace std;
////����
#define DELAY 12
#define NUM_OF_LINE 32
#define BLOCK_SIZE 1
#define PI 3.1415926535898
#define MAX_CHAR 128
Chunk chunk_test;
Camera camera;
CSkyBox skybox;
time_t cur_time = time(NULL);

CubeManager cube_mgr = CubeManager();
LightMaterial lightMaterial;
vector<Crawler> crawler_arr;

Man man;

vector<Point> torch_arr;

PhysicsEngine player(&cube_mgr);
map<std::string, AABB> AABB_list;

CubeTex nowcube = CubeTex::Wood;
int cubeSelect = 0;

//���ڴ�С
int WindowWidth = WINDOW_WIDTH;
int WindowHeight = WINDOW_HEIGHT;

float near_sight = 0.35;
float far_sight = 1000;
int scr_w;
int scr_h;
extern float curPos[3];

//����������
bool left_forward = true;
bool right_forward = false;
bool look_from_left = true;

//��Դ̫��
GLfloat s_angle = 0.0f;
GLfloat LightPosition[] = { 0.0f, 0.0f, 0.0f, 1.0f };        //��Դλ��
GLfloat ambient = 0.1f;
GLfloat LightAmbient[] = { ambient, ambient, ambient, 1.0f };        //������
GLfloat diffuse = 0.1f;
GLfloat LightDiffuse[] = { diffuse, diffuse, diffuse, 1.0f };        //������
GLfloat specular = 0.0f;
GLfloat LightSpecular[] = { specular, 0.6f, 0.6f, 1.0f };    //���淴��

//���ϲ���
GLfloat matEmissionR, matEmissionG, matEmissionB;
GLfloat MatEmission[] = { matEmissionR, matEmissionG, matEmissionB, 1.0f };
GLfloat matAmbientR, matAmbientG, matAmbientB;
GLfloat MatAmbient[] = { matAmbientR, matAmbientG, matAmbientB, 1.0f };
GLfloat matDiffuseR, matDiffuseG, matDiffuseB;
GLfloat MatDiffuse[] = { matDiffuseR, matDiffuseG, matDiffuseB, 1.0f };
GLfloat matSpecularR, matSpecularG, matSpecularB;
GLfloat MatSpecular[] = { matSpecularR, matSpecularG, matSpecularB, 1.0f };
GLfloat MatShininess;

GLfloat angleTrans = 0.0;

/**
* @brief ���ÿ�����
*/
void setCrawler()
{
	for (auto& itr : crawler_arr)
	{
		itr.createCrawler();
	}
}

/**
* @brief ���û�Ѻ���
*/
void setTorch()
{
	for (auto itr : torch_arr)
	{
		lightMaterial.setTorch(itr.x, itr.y, itr.z);
	}
}

void setSpotLight() {
	GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat position[] = { player.coordinate.x, player.coordinate.y, player.coordinate.z, 1 };
	GLfloat lightDir[] = { player.focus.x, player.focus.y, player.focus.z, 1 };
	GLfloat spotangle = 5 + angleTrans;
	glLightfv(GL_LIGHT3, GL_AMBIENT, white);
	glLightfv(GL_LIGHT3, GL_SPECULAR, white);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT3, GL_POSITION, position);
	glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, lightDir);
	glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, spotangle);
	glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, 2.);
	glEnable(GL_LIGHT3);
}

void DrawAll()
{
	glColor3f(1.0f, 1.0f, 1.0f);
	cube_mgr.createAllCube();
	glBindTexture(GL_TEXTURE_2D, 0);
}



/**
* @brief ��ʾ����
*/
static GLfloat scaleFactor = 1.0;
static GLfloat transFactor = 0;
bool isTrans = false;
bool isBigger = true;
void drawSphere(bool isScale) {
	glPushMatrix();  //Sphere
	glColor3f(0.0, 0.0, 1.0);
	glTranslatef(15.0, 2.0, 15.0);
	glRotatef(60, 1.0, 0.0, 0.0);
	if (isScale) {
		glScalef(scaleFactor, scaleFactor, scaleFactor);
		if (scaleFactor > 1.5) {
			isBigger = false;
		}
		if (scaleFactor < 0.5) {
			isBigger = true;
		}
		if (isBigger) {
			scaleFactor += 0.01;
		}
		else {
			scaleFactor -= 0.01;
		}
	}
	glutWireSphere(0.8, 20, 20);
	glPopMatrix();
	return;
}
GLvoid DrawCircleArea(float cx, float cy, float cz, float r, int num_segments)
{
	GLfloat vertex[4];

	const GLfloat delta_angle = 2.0 * PI / num_segments;
	glBegin(GL_TRIANGLE_FAN);

	vertex[0] = cx;
	vertex[1] = cy;
	vertex[2] = cz;
	vertex[3] = 1.0;
	glVertex4fv(vertex);

	//draw the vertex on the contour of the circle   
	for (int i = 0; i < num_segments; i++)
	{
		vertex[0] = std::sin(delta_angle * i) * r + cy;
		vertex[1] = std::cos(delta_angle * i) * r + cx;
		vertex[2] = cz;
		vertex[3] = 1.0;
		glVertex4fv(vertex);
	}

	vertex[0] = 1.0 * r + cx;
	vertex[1] = 0.0 * r + cy;
	vertex[2] = cz;
	vertex[3] = 1.0;
	glVertex4fv(vertex);
	glEnd();
}
void drawCylinder(GLUquadric* quad,
	GLdouble base,
	GLdouble top,
	GLdouble height,
	GLint slices,
	GLint stacks)
{
	glDisable(GL_CULL_FACE);
	glPushMatrix();
	if (isTrans) {
		transFactor += 0.01;
		if (transFactor >= 3.0) {
			isTrans = false;
			transFactor = 0;
		}
	}
	glTranslatef(10, 4, 5 + transFactor);
	glColor3f(84.0 / 255, 0.0, 125.0 / 255.0);
	gluCylinder(quad, base, top, height, slices, stacks);
	glPopMatrix();
	glPushMatrix();
	//top   

	glColor3f(84.0 / 255, 0.0, 125.0 / 255.0);
	glTranslatef(10, 4, 5 + transFactor);
	DrawCircleArea(0, 0, 0 + height, top, slices);
	glPopMatrix();
	glPushMatrix();
	//base   	

	glColor3f(84.0 / 255, 0.0, 125.0 / 255.0);
	glTranslatef(10, 4, 5 + transFactor);
	DrawCircleArea(0, 0, 0, base, slices);
	glPopMatrix();
	glEnable(GL_CULL_FACE);
}


static GLfloat angle = 0.0;
bool isRotate = true;
void drawCone(bool isRotate) {
	if (isRotate) {
		if (angle > 360) {
			angle -= 360;
		}
	}
	else {
		angle += 10;
	}
	glPushMatrix();  //Cone
	glColor3f(0.0, 1.0, 0.0);
	glTranslatef(7.0, 1.8, 7.0);

	glRotatef(angle, 1.0, 0.0, 0.0);
	glutWireCone(0.6, 1, 30, 30);
	glPopMatrix();
	return;
}

bool isScale = false;
GLUquadric* pObj = gluNewQuadric();
const int slice[7] = { 3,4,5,7,9,15,32 };
int choose = 0;
static GLdouble bottom_r = 1.0;

void DrawNowcubeTip(CubeTex now) {
	TexCube n(0, 0, 0, 0, now);
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(0.975, 0.025, 0.0);
	glVertex3f(0.975, 0.135, 0.0);
	glVertex3f(0.865, 0.135, 0.0);
	glVertex3f(0.865, 0.025, 0.0);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, n.GetSide());
	glBegin(GL_QUADS);

	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.97, 0.03, 0.0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.97, 0.13, 0.0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.87, 0.13, 0.0);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.87, 0.03, 0.0);

	glEnd();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
}


int v_num = 0; //��¼�������
int vn_num = 0;//��¼���ߵ�����
int f_num = 0; //��¼�������

GLfloat** vArr; //��ŵ�Ķ�ά����
GLfloat** vnArr;//��ŷ��ߵĶ�ά����

int** fvArr; //����涥��Ķ�ά����
int** fnArr; //����淨�ߵĶ�ά����

string s1;
GLfloat f2, f3, f4;


void getLineNum(const std::string& sFileName)
{
	ifstream infile(sFileName.c_str());
	if (!infile.is_open())	cout << "Error" << endl;
	string sline;
	v_num = vn_num = f_num = 0;
	getline(infile, sline);
	//while(getline(infile,sline))
	while (sline.size() != 0)
	{//��ָ���ļ����ж�ȡ
		if (sline[0] == 'v')
		{
			if (sline[1] == 'n')
				vn_num++;
			else
				v_num++;
		}
		else if (sline[0] == 'f')
			f_num++;
		getline(infile, sline);
	}
	infile.close();
}



int readfile(string addrstr)
{
	vArr = new GLfloat * [v_num];
	for (int i = 0; i < v_num; i++)
	{
		vArr[i] = new GLfloat[3];
	}
	vnArr = new GLfloat * [vn_num];
	for (int i = 0; i < vn_num; i++)
	{
		vnArr[i] = new GLfloat[3];
	}

	fvArr = new int* [f_num];
	fnArr = new int* [f_num];

	for (int i = 0; i < f_num; i++)
	{
		fvArr[i] = new int[3];
		fnArr[i] = new int[3];
	}

	ifstream infile(addrstr.c_str());
	string sline;//ÿһ��
	int ii = 0, jj = 0, kk = 0;

	getline(infile, sline);
	while (sline.size() != 0)
	{
		if (sline[0] == 'v')
		{
			if (sline[1] == 'n')//vn
			{
				istringstream sin(sline);
				sin >> s1 >> f2 >> f3 >> f4;
				vnArr[ii][0] = f2;
				vnArr[ii][1] = f3;
				vnArr[ii][2] = f4;
				ii++;
			}
			else//v
			{
				istringstream sin(sline);
				sin >> s1 >> f2 >> f3 >> f4;
				vArr[jj][0] = f2;
				vArr[jj][1] = f3;
				vArr[jj][2] = f4;
				jj++;
			}
		}

		if (sline[0] == 'f') //��ȡ��
		{
			istringstream in(sline);
			GLfloat a;
			in >> s1;//ȥ��ǰ׺f
			int i, k;
			for (i = 0; i < 3; i++)
			{
				in >> s1;
				//	cout << s1 << endl;
					//ȡ�ö��������ͷ�������
				a = 0;
				a = atoi(s1.c_str());
				//for (k = 0; s1[k] != ' '; k++)
				//{
				//	a = a * 10 + (s1[k] - 48);
				//}
				fvArr[kk][i] = a;
				/*a = 0;
				for (k = k + 2; s1[k]; k++)
				{
					a = a * 10 + (s1[k] - 48);;
				}
				fnArr[kk][i] = a;*/

			}
			kk++;
		}
		getline(infile, sline);
	}
	return 0;
}

int grass = 0;

void drawGrass() {
	switch (grass/10) {
	case 0:
		getLineNum("grass1.obj");
		readfile("grass1.obj");
		break;
	case 1:
		getLineNum("grass2.obj");
		readfile("grass2.obj");
		break;
	case 2:
		getLineNum("grass3.obj");
		readfile("grass3.obj");
		break;
	case 3:
		getLineNum("grass4.obj");
		readfile("grass4.obj");
		break;
	case 4:
		getLineNum("grass5.obj");
		readfile("grass5.obj");
		break;
	case 5:
		getLineNum("grass6.obj");
		readfile("grass6.obj");
		break;
	case 6:
		getLineNum("grass7.obj");
		readfile("grass7.obj");
		break;
	case 7:
		getLineNum("grass8.obj");
		readfile("grass8.obj");
		break;
	case 8:
		getLineNum("grass9.obj");
		readfile("grass9.obj");
		break;
	case 9:
		getLineNum("grass10.obj");
		readfile("grass10.obj");
		break;
	}

	glDisable(GL_CULL_FACE);
	glPushMatrix();  //Cone
	glColor3f(0.0, 1.0, 0.0);
	glTranslatef(12.0, 1.0, 7.0);
	glBegin(GL_TRIANGLES);
	//	cout << f_num << endl;
	for (int i = 0; i < f_num; i++)
	{
		glVertex3fv(vArr[fvArr[i][0] - 1]);
		glVertex3fv(vArr[fvArr[i][1] - 1]);
		glVertex3fv(vArr[fvArr[i][2] - 1]);

	}
	grass++;
	if (grass == 100) grass = 0;

	glEnd();
	glPopMatrix();
	glEnable(GL_CULL_FACE);
}

void drawMonkey() {
	getLineNum("monkey.obj");
	readfile("monkey.obj");

	glDisable(GL_CULL_FACE);
//	GLfloat color[] = { 1.0f,1.0f,1.0f };
//	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);
	glPushMatrix();  //Cone
	glColor3f(1.0, 1.0, 0.0);
	glTranslatef(12.0, 1.0, 12.0);
	glBegin(GL_TRIANGLES);
//	cout << f_num << endl;
	for (int i = 0; i < f_num; i++)
	{
		glVertex3fv(vArr[fvArr[i][0] - 1]);
		glVertex3fv(vArr[fvArr[i][1] - 1]);
		glVertex3fv(vArr[fvArr[i][2] - 1]);
	}

	glEnd();
	glPopMatrix();
	glEnable(GL_CULL_FACE);
}

void display()
{
	lightMaterial.setBackGround();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_BLEND);
	lightMaterial.setLight();
	//TODO  ��������������
	skybox.CreateSkyBox(man.x, man.y, man.z, 1.0, 1.0, 1.0);

	glDisable(GL_BLEND);
	lightMaterial.setMaterial(2);

	DrawAll(); // floor()

	lightMaterial.setMaterial(0);
	man.refresh();
	lightMaterial.setMaterial(1);
	setCrawler();
	drawCylinder(pObj, 1.0, 1.0 * bottom_r, 3.0, slice[choose], 5);
	drawCone(isRotate);
	drawGrass();
	drawMonkey();
	drawSphere(isScale);
	glEnable(GL_LIGHTING);
	setTorch();
	setSpotLight();
	//glColor3f(1.0f, 0.0f, 0.0f);
	//glRasterPos2f(0.0f, 0.0f);
	//drawString("Hello, World!");

	//cout << "omega = " << player.omega
	//	<< " c = (" << player.coordinate.x << ","
	//	<< player.coordinate.y << ", "
	//	<< player.coordinate.z << "\n";
	//cout<< " v = (" << player.velocity.x << ",";
	//cout << player.velocity.y << ", " << player.velocity.z << ")\n";

	//cout << "Player min: " << player.Player_Box._min.x << "," << player.Player_Box._min.y << ","
	//	<< player.Player_Box._min.z << endl;
	//cout << "Player max: " << player.Player_Box._max.x << "," << player.Player_Box._max.y << ","
	//	<< player.Player_Box._max.z << endl;

	player.reset(cube_mgr.aabbMap);
	glLoadIdentity();									// Reset The Current Modelview Matrix
	gluLookAt(player.coordinate.x - Far_Factor * player.focus.x,
		player.coordinate.y - Far_Factor * player.focus.y,
		player.coordinate.z - Far_Factor * player.focus.z,
		player.focus.x, player.focus.y, player.focus.z,
		0, 1, 0);

	DrawNowcubeTip(nowcube);/////

	glutSwapBuffers();


	//camera.setting_view_person(man);
}

/**
* @brief openglһЩ��ʼ״̬���趨
*/
void init()
{
	///����Ϊ��ƽ����ɫ
	glShadeModel(GL_FLAT);
	///������ȼ��
	glEnable(GL_DEPTH_TEST);
	///�������޳���ȡ������Щ�������������Ⱦ
	glEnable(GL_CULL_FACE);
	///������ʱ���Ϊ����
	glFrontFace(GL_CCW);
	///������ɫ���
	glEnable(GL_BLEND);
	///������Դ��ɫ��alpha��Ŀ����ɫ�����н��л��
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	///�������գ��ر�������ȫ�ǻ谵��
	glEnable(GL_COLOR_MATERIAL);
}

/**
* @brief ˢ��
* @TODO   �����
*/
void refresh(int c)
{
	if (man.is_moving())
	{
		if (man.ltangle < -60)
		{
			left_forward = false;
		}
		else if (man.ltangle > 60)
		{
			left_forward = true;
		}
		if (man.rtangle < -60)
		{
			right_forward = false;
		}
		else if (man.rtangle > 60)
		{
			right_forward = true;
		}
		if (left_forward)
		{
			man.ltangle--;
			man.laangle++;
		}
		else
		{
			man.ltangle++;
			man.laangle--;
		}
		if (right_forward)
		{
			man.rtangle--;
			man.raangle++;
		}
		else
		{
			man.rtangle++;
			man.raangle--;
		}
	}
	else
	{
		man.raangle = 0;
		man.laangle = 0;
		man.rtangle = 0;
		man.ltangle = 0;
	}
	///ÿDELAY�������һ��refresh���������Ϊ0
	glutTimerFunc(DELAY, refresh, 0);
	///��ǵ�ǰ������Ҫ�ػ�
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	scr_w = w;
	scr_h = h;
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)scr_w / scr_h, near_sight, far_sight);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// �����лص�����.......
//void passiveMotion(int x, int y)
//{
//	camera.unname(x, y, scr_w, man);
//}
//
//
//// ���������
//void mouseButton(int button, int state, int x, int y) 
//{
//	camera.mouse_Button(button, state, x, y, scr_h);
//	TexCube *newCube = new TexCube(man.x + 1, man.y, man.z + 1, 1.0f, Stone);
//	newCube->createCube();
//}
//
//// ����ƶ��ص�����
//void mouseMotion(int x, int y) 
//{
//	trackball_ptov(x, y, scr_w, scr_h, curPos);
//	trackMouse();
//	glutPostRedisplay();
//}

// ���лص�����
/*
void idle()
{
	// �����귢���ƶ���������Զ�ת��
	if (redrawContinue) glutPostRedisplay();
}*/

// ��������

void keyPress(unsigned char k, int x, int y)
{
	switch (k)
	{
	case 'g':
		if (player.mode == NORMAL) {
			player.mode = GOD;
			cout << "OMG!!\n";
		}
		else {
			cout << "SHIT!!\n";
			player.mode = NORMAL;
			player.accelerUp = 0.f;
			player.velocity.y = 0;
		}
		break;
	case 27:
	case 'q': {exit(0); break; }

	case 'A':
	case 'a':
		player.isA = true;
		break;
	case 'D':
	case 'd':
		player.isD = true;
		break;
	case 'W':
	case 'w':
		player.isW = true;
		break;
	case 'S':
	case 's':
		player.isS = true;
		break;
	case ' ':
		if (player.mode == NORMAL) {
			if (!player.isAir) {
				player.JumpUpdateVelocity();
			}
			player.isAir = true;
		}
		else if (player.mode == GOD) {
			player.isUp = true;
		}
		break;
	case 'c':
	case 'C':
		if (player.mode == GOD) {
			player.isDown = true;
		}
		break;
	case '0':
		bottom_r *= 1.1;
		break;
	case '9':
		bottom_r /= 1.1;
		break;
	case '`':
		cubeSelect = (cubeSelect + 1) % CUBE_NUM;
		nowcube = (enum CubeTex)cubeSelect;
		if (nowcube == CubeTex::Light)	cout << "Light Mode" << endl;
		break;
	case ']': {
		angleTrans += 0.2f;
		break;
	}
	case '[': {
		angleTrans -= 0.2f;
		break;
	}
	case ',': {
		ambient -= 0.2;
		diffuse -= 0.2;
		if (ambient < 0.0)
			ambient = 0.1;
		if (diffuse < 0.0)
			diffuse = 0.1;
		break;
	}
	case '.': {
		ambient += 0.2;
		diffuse += 0.2;
		if (ambient > 1.0)
			ambient = 1.0;
		if (diffuse > 1.0)
			diffuse = 1.0;
		break;
	}
	default:
		break;
	}
}
struct tm* ptr;
char str[80];
string s;
void keyUp(unsigned char k, int x, int y) {
	switch (k)
	{
	case 'R':
	case 'r':
		isRotate = !isRotate;
		break;
	case 'H':
	case 'h':
		isTrans = !isTrans;
		break;
	case 'B':
	case 'b':
		isScale = !isScale;
		break;
	case 'A':
	case 'a':
		cout << "A up\n";
		player.isA = false;
		break;
	case 'D':
	case 'd':
		cout << "D up\n";
		player.isD = false;
		break;
	case 'W':
	case 'w':
		cout << "W up\n";
		player.isW = false;
		break;
	case 'S':
	case 's':
		cout << "S up\n";
		player.isS = false;
		break;
	case ' ':
		if (player.mode == GOD) {
			player.isUp = false;
		}
		break;
	case 'c':
	case 'C':
		if (player.mode == GOD) {
			player.isDown = false;
		}
		break;
	case '=':
		choose = (choose + 1) % 7;

		break;
	case '-':
		choose = (choose + 6) % 7;

		break;
	case 't':
		s = "Screenshot_";
		cur_time = time(NULL);
		ptr = localtime(&cur_time);
		strftime(str, 100, "%Y_%m_%d_%H_%M_%S", ptr);
		s += str;
		s += ".bmp";
		if (snapScreen(800, 600, s.c_str()))cout << "Screen shot" << s << endl;
		else cout << "screenshot failed!\n";

		break;
	default:
		break;
	}
}

//void control(unsigned char key, int x, int y) 
//{
//	Collision check;
//	cout << "X:" << man.x << "  Z:" << man.z << endl;
//	switch (key) 
//	{
//	case 'p':
//		cout << man.vangle << endl;
//		break;
//	case 32:
//		man.jump();
//		break;
//	case 'a':
//		man.left(chunk_test);
//		break;
//	case 'd':
//		man.right(chunk_test);
//		break;
//	case 'w':
//		man.forward(chunk_test);
//		break;
//	case 's':
//		man.back(chunk_test);
//		break;
//	case 'h':
//		camera.change_view();
//		break;
//	case 27:
//		exit(0);
//	default:
//		break;
//	}
//
//}
//
//// �����ɿ�
//void controlup(unsigned char key, int x, int y) 
//{
//	switch (key) 
//	{
//	case 'w':
//		man.move = false;
//		break;
//	case 's':
//		man.move = false;
//		break;
//	case 'a':
//		man.move = false;
//		break;
//	case 'd':
//		man.move = false;
//		break;
//	}
//}

/**
* @brief ����(��ͼ)��ʼ��������������ͼ
*/
void initCube()
{
	///����2D����Ͳ��ʳ�ʼ��
	glEnable(GL_TEXTURE_2D);
	///������ȼ��
	glEnable(GL_DEPTH_TEST);
	///����������ã�����GL_NEAREST�ٶȽϿ죬����GL_REPEATʹ�����ظ�
	glTexParameterf(GL_NEAREST, GL_TEXTURE_WRAP_S, GL_REPEAT);
	Cube::initCubeTexture();
	chunk_test.create_chunk(cube_mgr);
	//chunk_test.print_test();

	/*
	int num_cube = 30;

	for (int i = num_cube; i >= (-num_cube); i--)
	{
		for (int j = num_cube; j >= (-num_cube); j--)
		{
			cube_mgr.insertCube(TexCube(i, 0, j, 1.0f, Soil));
		}
	}
	*/
	//////////////////////����//////////////////////////
	cube_mgr.insertCube(TexCube(0, 1, 0, 1.0f, Table));
	//cube_mgr.buildPool(8, 1, 10);
	//cube_mgr.buildPyramid(30, 1, 10);
	//cube_mgr.buildDiamondBuilding(8, 1, 1);
	//����----
	for (int i = 1; i <= 6; i++)
	{
		cube_mgr.buildTree(1, 1, 4 * i);
		cube_mgr.buildTree(19, 1, 4 * i);
	}
}

// ��������
void music() {
	//    MCI_OPEN_PARMS op;                                     //���ű�������
	//    op.dwCallback = NULL;
	//    op.lpstrAlias = NULL;
	//    op.lpstrDeviceType = "MPEGAudio";
	//    op.lpstrElementName = "music.mp3";
	//    op.wDeviceID = NULL;
	//    UINT rs;
	//    rs = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT, (DWORD) & op);
	//    if (rs == 0) {
	//        MCI_PLAY_PARMS pp;
	//        pp.dwCallback = NULL;
	//        pp.dwFrom = 0;
	//        //mciSendCommand(op.wDeviceID, MCI_PLAY, MCI_NOTIFY, (DWORD)&pp);
	//        mciSendCommand(op.wDeviceID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD) & pp);
	//
	//    }
}

/**
* @brief ��ʼ�������������������
*/
void initOther()
{
	refresh(0);
	//for (int i = 0; i < 10; i++)
	//{
	//	crawler_arr.push_back(Crawler(8, 1, -10 - i));
	//}
}

void mouseMove(int x, int y) {
	if (player.fixMouse)
		glutSetCursor(GLUT_CURSOR_NONE);
	else
		glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
	player.MouseMove(x, y);
}

// 

void mouseClick(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		player.AddCube(nowcube);
	}
	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		player.EliminateCube(nowcube);
	}

	return;
}

/**
* @brief main����
* @param argc:��������  *argv[]��������
* @return �ǺǺǺǺǺ�
*/
int main(int argc, char* argv[])
{
	
	//start ��ʼ��������
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WindowWidth, WindowHeight);
	GLint screenWidth = glutGet(GLUT_SCREEN_WIDTH);
	GLint screenHeight = glutGet(GLUT_SCREEN_HEIGHT);
	glutInitWindowPosition((screenWidth - WindowWidth) / 2, (screenHeight - WindowHeight) / 2);
	glutCreateWindow("�ҵ�����");
	//end	
	init();
	//lastTime = clock();    //����ʱ�״��趨��ǰʱ��
	man.setLocation(6, 1, 6);
	//ShowCursor(false);
	initCube();
	initOther();
	glutDisplayFunc(display);
	//���ڴ�С�ı�ʱ���ı���Ϸ�������
	glutReshapeFunc(reshape);

	//������ƶ�ʱ������û��������ʱ�Ļص�����
	//glutPassiveMotionFunc(passiveMotion);
	//������Ļص�����
	//glutMouseFunc(mouseButton);
	//������ƶ�ʱ����������ʱ�Ļص�����
	//glutMotionFunc(mouseMotion);

	glutMouseFunc(mouseClick); // ���click
	glutPassiveMotionFunc(mouseMove); // ���δ����ʱ���ƶ�

	//���̰�������ʱ�Ļص�����
	glutKeyboardUpFunc(keyUp);
	//���̻ص�����
	glutKeyboardFunc(keyPress);

	//AABB_list.push_back(floor);
	//AABB_list.push_back(B);
	glutMainLoop();

	system("pause");
	return 0;
}

