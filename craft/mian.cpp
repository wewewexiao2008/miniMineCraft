/**
* @file main.c
* @author zf
* @date 2017/11/26
* @detail 尝试利用opengl去复刻minecraft
* @TODO 地形生成，能加载minecraft的材质包，解决鼠标漂移问题，破坏方块，方块状态的记录
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
////参数
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

//窗口大小
int WindowWidth = WINDOW_WIDTH;
int WindowHeight = WINDOW_HEIGHT;

float near_sight = 0.35;
float far_sight = 1000;
int scr_w;
int scr_h;
extern float curPos[3];

//相对坐标参数
bool left_forward = true;
bool right_forward = false;
bool look_from_left = true;

//光源太阳
GLfloat s_angle = 0.0f;
GLfloat LightPosition[] = { 0.0f, 0.0f, 0.0f, 1.0f };        //光源位置
GLfloat ambient = 0.1f;
GLfloat LightAmbient[] = { ambient, ambient, ambient, 1.0f };        //环境光
GLfloat diffuse = 0.1f;
GLfloat LightDiffuse[] = { diffuse, diffuse, diffuse, 1.0f };        //漫反射
GLfloat specular = 0.0f;
GLfloat LightSpecular[] = { specular, 0.6f, 0.6f, 1.0f };    //镜面反射

//材料参数
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
* @brief 设置苦力怕
*/
void setCrawler()
{
	for (auto& itr : crawler_arr)
	{
		itr.createCrawler();
	}
}

/**
* @brief 设置火把函数
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
* @brief 显示函数
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


int v_num = 0; //记录点的数量
int vn_num = 0;//记录法线的数量
int f_num = 0; //记录面的数量

GLfloat** vArr; //存放点的二维数组
GLfloat** vnArr;//存放法线的二维数组

int** fvArr; //存放面顶点的二维数组
int** fnArr; //存放面法线的二维数组

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
	{//从指定文件逐行读取
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
	string sline;//每一行
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

		if (sline[0] == 'f') //读取面
		{
			istringstream in(sline);
			GLfloat a;
			in >> s1;//去掉前缀f
			int i, k;
			for (i = 0; i < 3; i++)
			{
				in >> s1;
				//	cout << s1 << endl;
					//取得顶点索引和法线索引
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
	//TODO  可能纹理贴反了
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
* @brief opengl一些初始状态的设定
*/
void init()
{
	///设置为非平滑着色
	glShadeModel(GL_FLAT);
	///开启深度检测
	glEnable(GL_DEPTH_TEST);
	///开启面剔除，取消对那些看不到的面的渲染
	glEnable(GL_CULL_FACE);
	///设置逆时针的为正面
	glFrontFace(GL_CCW);
	///开启颜色混合
	glEnable(GL_BLEND);
	///设置以源颜色的alpha，目标颜色的所有进行混合
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	///开启光照，关闭则物体全是昏暗的
	glEnable(GL_COLOR_MATERIAL);
}

/**
* @brief 刷新
* @TODO   待解决
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
	///每DELAY毫秒调用一下refresh，传入参数为0
	glutTimerFunc(DELAY, refresh, 0);
	///标记当前窗口需要重绘
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

// 鼠标空闲回调函数.......
//void passiveMotion(int x, int y)
//{
//	camera.unname(x, y, scr_w, man);
//}
//
//
//// 鼠标点击函数
//void mouseButton(int button, int state, int x, int y) 
//{
//	camera.mouse_Button(button, state, x, y, scr_h);
//	TexCube *newCube = new TexCube(man.x + 1, man.y, man.z + 1, 1.0f, Stone);
//	newCube->createCube();
//}
//
//// 鼠标移动回调函数
//void mouseMotion(int x, int y) 
//{
//	trackball_ptov(x, y, scr_w, scr_h, curPos);
//	trackMouse();
//	glutPostRedisplay();
//}

// 空闲回调函数
/*
void idle()
{
	// 如果鼠标发生移动，则后面自动转动
	if (redrawContinue) glutPostRedisplay();
}*/

// 键盘输入

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
//// 按键松开
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
* @brief 方块(地图)初始化，加载纹理贴图
*/
void initCube()
{
	///启用2D纹理和材质初始化
	glEnable(GL_TEXTURE_2D);
	///开启深度检测
	glEnable(GL_DEPTH_TEST);
	///纹理参数设置，设置GL_NEAREST速度较快，设置GL_REPEAT使纹理重复
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
	//////////////////////地面//////////////////////////
	cube_mgr.insertCube(TexCube(0, 1, 0, 1.0f, Table));
	//cube_mgr.buildPool(8, 1, 10);
	//cube_mgr.buildPyramid(30, 1, 10);
	//cube_mgr.buildDiamondBuilding(8, 1, 1);
	//种树----
	for (int i = 1; i <= 6; i++)
	{
		cube_mgr.buildTree(1, 1, 4 * i);
		cube_mgr.buildTree(19, 1, 4 * i);
	}
}

// 播放音乐
void music() {
	//    MCI_OPEN_PARMS op;                                     //播放背景音乐
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
* @brief 初始化除方块外的其他物体
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
* @brief main函数
* @param argc:参数数量  *argv[]参数数组
* @return 呵呵呵呵呵呵
*/
int main(int argc, char* argv[])
{
	
	//start 初始窗口设置
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WindowWidth, WindowHeight);
	GLint screenWidth = glutGet(GLUT_SCREEN_WIDTH);
	GLint screenHeight = glutGet(GLUT_SCREEN_HEIGHT);
	glutInitWindowPosition((screenWidth - WindowWidth) / 2, (screenHeight - WindowHeight) / 2);
	glutCreateWindow("我的世界");
	//end	
	init();
	//lastTime = clock();    //启动时首次设定当前时间
	man.setLocation(6, 1, 6);
	//ShowCursor(false);
	initCube();
	initOther();
	glutDisplayFunc(display);
	//窗口大小改变时不改变游戏物体比例
	glutReshapeFunc(reshape);

	//当鼠标移动时，并有没鼠标键按下时的回调函数
	//glutPassiveMotionFunc(passiveMotion);
	//鼠标点击的回调函数
	//glutMouseFunc(mouseButton);
	//当鼠标移动时，鼠标键按下时的回调函数
	//glutMotionFunc(mouseMotion);

	glutMouseFunc(mouseClick); // 鼠标click
	glutPassiveMotionFunc(mouseMove); // 鼠标未按下时的移动

	//键盘按键弹起时的回调函数
	glutKeyboardUpFunc(keyUp);
	//键盘回调函数
	glutKeyboardFunc(keyPress);

	//AABB_list.push_back(floor);
	//AABB_list.push_back(B);
	glutMainLoop();

	system("pause");
	return 0;
}

