#include "Crawler.h"

#define PI 3.1415926535898
using namespace std;

Crawler::Crawler()
{
	_ini();
	reset();
}

Crawler::Crawler(float x, float y, float z)
{
	_ini();
	reset();
	setLocation(x, y, z);
}

void Crawler::resetSize(float new_basic)
{
	this->basic_size = new_basic;
	reset();
}

void Crawler::setLocation(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void Crawler::reset()
{
	// ��������
	head_scale = Point(0.7, 1, 1, basic_size);
	body_scale = Point(0.7, 2, 0.8, basic_size);
	foot_scale = Point(0.7, 0.3, 0.9, basic_size);
	eye_scale = Point(0.2, 0.2, 0.2, basic_size);
	mouth_scale = Point(0.2, 0.2, 0.5, basic_size);

	// ���λ�ÿ���
	foot = Point(0, foot_scale.y / 2, 0, basic_size);
	body = Point(0, foot_scale.y + body_scale.y / 2, 0, basic_size);
	head = Point(0, foot_scale.y + body_scale.y + head_scale.y / 2, 0, basic_size);

	eyeL = Point(head_scale.x / 2, foot_scale.y + body_scale.y + head_scale.y / 2, -(eye_scale.z / 2 + 0.1), basic_size);
	eyeR = Point(head_scale.x / 2, foot_scale.y + body_scale.y + head_scale.y / 2, (eye_scale.z / 2 + 0.1), basic_size);
	mouth = Point(head_scale.x / 2, foot_scale.y + body_scale.y + head_scale.y / 2 - 0.1, 0, basic_size);
}

void Crawler::randomMove()
{
	if (this->count % this->random_t == 0)
	{
		this->random_t = rand() % 10 + 5;
		this->vangle += rand() % 100;
	}
	this->count++;
	this->x += this->speed * cos(this->vangle / 180 * PI);
	this->z -= this->speed * sin(this->vangle / 180 * PI);
}

void Crawler::createCrawler()
{
	randomMove();
	// ������

	glPushMatrix();
	glTranslatef(this->x, this->y, this->z);
	glRotatef(this->vangle, 0, 1, 0);

	///////////////////////////Head////////////////////////////
	// head
	glColor3f(46.0 / 255, 130.0 / 255, 38.0 / 255);
	glPushMatrix();
	glTranslatef(this->head.x, this->head.y, this->head.z);
	glScalef(this->head_scale.x, this->head_scale.y, this->head_scale.z);
	glutSolidCube(1);
	glPopMatrix();

	// left eye
	glColor3f(0, 0, 0);
	glPushMatrix();
	glTranslatef(this->eyeL.x, this->eyeL.y, this->eyeL.z);
	glScalef(this->eye_scale.x, this->eye_scale.y, this->eye_scale.z);
	glutSolidCube(1);
	glPopMatrix();

	// right eye
	glColor3f(0, 0, 0);
	glPushMatrix();
	glTranslatef(this->eyeR.x, this->eyeR.y, this->eyeR.z);
	glScalef(this->eye_scale.x, this->eye_scale.y, this->eye_scale.z);
	glutSolidCube(1);
	glPopMatrix();

	// mouth
	glColor3f(0, 0, 0);
	glPushMatrix();
	glTranslatef(this->mouth.x, this->mouth.y, this->mouth.z);
	glScalef(this->mouth_scale.x, this->mouth_scale.y, this->mouth_scale.z);
	glutSolidCube(1);
	glPopMatrix();


	///////////////////////////Body////////////////////////////
	glColor3f(46.0 / 255, 130.0 / 255, 38.0 / 255);
	glPushMatrix();
	glTranslatef(this->body.x, this->body.y, this->body.z);
	glScalef(this->body_scale.x, this->body_scale.y, this->body_scale.z);
	glutSolidCube(1);
	glPopMatrix();

	/////////////////////////Foot//////////////////////////////
	glColor3f(46.0 / 255, 130.0 / 255, 38.0 / 255);
	glPushMatrix();
	glTranslatef(this->foot.x, this->foot.y, this->foot.z);
	glScalef(this->foot_scale.x, this->foot_scale.y, this->foot_scale.z);
	glutSolidCube(1);
	glPopMatrix();


	glPopMatrix();

}

void Crawler::_ini()
{
	basic_size = 1;
	speed = 0.15;
	random_t = 5;
	count = 0;
	vangle = 0;    // �ٶ�ƫ��
	move = false;

}
