#pragma once
#include <iostream>
#include <math.h>
#include <vector>
#include <string>
#include "AABB.h"
#include "CubeManager.h"


#define gravity 1.1f
#define UNIT 10.0f
#define BOX_LENGTH 0.4f
#define horizon_speed 0.15f
#define vertical_speed 0.03f
#define HeroHeight 0.8f
#define min_speed 0.001f
#define max_speed 0.5f
#define eps 0.1f
#define HeadHeight 0.6f
#define GodFactor 20
#define JumpFactor 10

#define PI 3.1415926
#define Far_Factor 0


#define WINDOW_WIDTH 720
#define WINDOW_HEIGHT 600

#define MOUSE_SENSE_X 0.008
#define MOUSE_SENSE_Y 0.003

#define RANGE 10
#define PlaceSpeed 0.25

const float centerX = WINDOW_WIDTH / 2;
const float centerY = WINDOW_HEIGHT / 2;

enum MODE {
	GOD, NORMAL
};

class PhysicsEngine
{
public:
	PhysicsEngine(CubeManager* cm);
	AABB Player_Box;
	MODE mode;

	float omega, theta; // ˮƽ0 360 �����Ƕ�-90 90 �ɵ���
	Vec3 velocity;	// λ������  ���ٶ�

	bool isAir = true;		//�Ƿ��Ϳ�
	Vec3 coordinate;	// ��ԭ��λ�� ���������
	Vec3 focus;	// ע�ӷ��� �����ڵ㱣�ְ뾶����
	bool isW, isS, isA, isD, isUp,isDown; // Keyboard Pressing
	bool isLeft, isRight;
	float accelerUp = 0.f;

	void reset(std::map<std::string,AABB> BoundingBox_list);    // У׼�ٶ� ����
	void UpdateVerticalMotion(std::map<std::string,AABB> Box_list);
	void UpdateHorizentalMotion(std::map<std::string,AABB> Box_list);
	void JumpUpdateVelocity();


	bool fixMouse = false;
	float lastX = centerX;
	float lastY = centerY;
	void MouseMove(int x, int y);
	void FixMouseInWindow(int &x, int &y);
	void AddCube(CubeTex cube);
	void EliminateCube(CubeTex cube);

	CubeManager* cube_manager;
};
