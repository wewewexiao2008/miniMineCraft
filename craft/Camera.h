#pragma once
#include<iostream>
#include<gl\glut.h>
#include"Point.h"
#include"Man.h"
#include"visualBall.h"

#define VIEW_SCALE 2

class Camera
{
public:
	/**
	* @param man:主角对象
	* @brief 每种视角模式下相机的反应
	*/
	void setting_view_person(Man &man);
	/**
	* @brief 改变视角模式
	*/
	void change_view();

	/**
	* @brief 获取当前视角模式
	*/
	int get_view_pattern() const;

	/**
	* @brief ....暂时没看懂这个函数，叫无名好了
	*/
	void unname(int mouse_x, int mouse_y, int scr_w,Man &man);

	/**
	* @brief 这个也是暂时封装
	*/
	void mouse_Button(int button, int state, int x, int y, int scr_h);
private:
	enum {GOD, FIRST_PERSON, THIRD_PERSON, BALL};
	/// 世界参数
	Point center = Point(0, 0, 0);
	Point lookAt = Point(5, 5, 5);
	Point cameraAt = Point(5, 5, 5);
	Point godAt = Point(8, 11, -18);

	float last_mm_x = 0;
	float last_mm_y = 0;

	bool reset_god = false;
	int view_person = 0;  // 0 上帝视角，1 第一人称，2 第三人称, 虚拟球
	int last_view = 0;
	/// 各种flag
	bool trackingMouse;
	bool redrawContinue;
	bool trackballMove;
	float look_dy;
	int curx, cury;
	float angle, axis[3], trans[3];

	int scr_h;

private:
	void UnProject(float mouse_x, float mouse_y, int c);
	

	int changePos(float pos)
	{
		if (pos < 0)
		{
			return pos - 0.5;
		}
		else
		{
			return pos + 0.5;
		}
	}
};
