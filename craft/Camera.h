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
	* @param man:���Ƕ���
	* @brief ÿ���ӽ�ģʽ������ķ�Ӧ
	*/
	void setting_view_person(Man &man);
	/**
	* @brief �ı��ӽ�ģʽ
	*/
	void change_view();

	/**
	* @brief ��ȡ��ǰ�ӽ�ģʽ
	*/
	int get_view_pattern() const;

	/**
	* @brief ....��ʱû�����������������������
	*/
	void unname(int mouse_x, int mouse_y, int scr_w,Man &man);

	/**
	* @brief ���Ҳ����ʱ��װ
	*/
	void mouse_Button(int button, int state, int x, int y, int scr_h);
private:
	enum {GOD, FIRST_PERSON, THIRD_PERSON, BALL};
	/// �������
	Point center = Point(0, 0, 0);
	Point lookAt = Point(5, 5, 5);
	Point cameraAt = Point(5, 5, 5);
	Point godAt = Point(8, 11, -18);

	float last_mm_x = 0;
	float last_mm_y = 0;

	bool reset_god = false;
	int view_person = 0;  // 0 �ϵ��ӽǣ�1 ��һ�˳ƣ�2 �����˳�, ������
	int last_view = 0;
	/// ����flag
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
