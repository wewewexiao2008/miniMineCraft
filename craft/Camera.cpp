#include "Camera.h"
#include <iostream>
void Camera::setting_view_person(Man & man)
{
	if (view_person == FIRST_PERSON)
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		cameraAt.x = man.x + 1.3 * cos(man.vangle / 180.0 * PI);
		cameraAt.y = man.y + man.head.y;
		cameraAt.z = man.z - 1.3 * sin(man.vangle / 180.0 * PI);

		lookAt.x = man.x + 5 * cos(man.vangle / 180.0 * PI);
		lookAt.y = man.y + man.hair.y - look_dy;
		lookAt.z = man.z - 5 * sin(man.vangle / 180.0 * PI);
		
		gluLookAt(lookAt.x, cameraAt.y, cameraAt.z,
			lookAt.x, lookAt.y, lookAt.z,
			0.0f, 1.0f, 0.0f);
	}
	else if (view_person == GOD)
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		if (!reset_god)
		{
			cameraAt = godAt;
			lookAt.x = 10;
			lookAt.y = 0;
			lookAt.z = 0;
			reset_god = true;
		}
		std::cout
		<<"c("<< cameraAt.x
		<<","<< cameraAt.y
		<<","<< cameraAt.z
		<<")\nlook("<< lookAt.x
		<<","<< lookAt.y
		<<","<< lookAt.z << ")\n";

		gluLookAt(cameraAt.x, cameraAt.y, cameraAt.z,
			lookAt.x, lookAt.y, lookAt.z,
			0.0f, 1.0f, 0.0f);
	}
	else if (view_person == THIRD_PERSON)
	{
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		cameraAt.x = man.x - 10 * cos(man.vangle / 180.0 * PI);
		cameraAt.y = man.head.y + 10;
		cameraAt.z = man.z + 10 * sin(man.vangle / 180.0 * PI);

		lookAt.x = man.x;
		lookAt.y = man.hair.y;
		lookAt.z = man.z;

		gluLookAt(cameraAt.x, cameraAt.y, cameraAt.z,
			lookAt.x, lookAt.y, lookAt.z,
			0.0f, 1.0f, 0.0f);
	}
	else if (view_person == BALL)
	{
		if (trackballMove)
		{
			glRotatef(angle, axis[0], axis[1], axis[2]);
		}
	}
}

void Camera::change_view()
{
	reset_god = false;
	if (view_person >= 3)
	{
		view_person = 0;
	}
	else
	{
		view_person++;
	}
}

void Camera::unname(int x, int y, int scr_w,Man &man)
{
	float r = 0.06;
	man.vangle -= 0.1 * (x - last_mm_x);

	if (x < r * scr_w && last_mm_x > x)
	{
		x = (1 - r) * scr_w;
		//        SetCursorPos(x, y);
	}
	else if (x > (1 - r) * scr_w && last_mm_x < x)
	{
		x = r * scr_w;
		//        SetCursorPos(x, y);
	}
	if (view_person == FIRST_PERSON)
	{
		look_dy += 0.01 * (y - last_mm_y);
	}
	last_mm_x = x;
	last_mm_y = y;
}

void Camera::mouse_Button(int button, int state, int x, int y,int scr_h)
{
	this->scr_h = scr_h;
	if (button == GLUT_LEFT_BUTTON)
	{
		switch (state)
		{
		case GLUT_DOWN:
			if (view_person == FIRST_PERSON)
			{
				UnProject(x, y, GLUT_LEFT_BUTTON);
			}
			cameraAt.x /= VIEW_SCALE;
			cameraAt.y /= VIEW_SCALE;
			cameraAt.z /= VIEW_SCALE;
			startMotion(x, y);
			break;
		case GLUT_UP:
			stopMotion(x, y);
			break;

		}
	}
	else if (button == GLUT_RIGHT_BUTTON)
	{
		// 视角收缩
		if (state == GLUT_DOWN)
		{
			if (view_person == FIRST_PERSON)
			{
				UnProject(x, y, GLUT_RIGHT_BUTTON);
			}
			cameraAt.x *= VIEW_SCALE;
			cameraAt.y *= VIEW_SCALE;
			cameraAt.z *= VIEW_SCALE;
		}
	}
}

void Camera::UnProject(float mouse_x, float mouse_y, int c)
{
	int x = mouse_x;                /* 屏幕坐标 */
	int y = mouse_y;
	GLint viewport[4];
	GLdouble mvmatrix[16], projmatrix[16];
	GLfloat winx, winy, winz;
	GLdouble posx, posy, posz;

	glPushMatrix();

	//glScalef(0.1, 0.1, 0.1);
	glGetIntegerv(GL_VIEWPORT, viewport);            /* 获取三个矩阵 */
	glGetDoublev(GL_MODELVIEW_MATRIX, mvmatrix);
	glGetDoublev(GL_PROJECTION_MATRIX, projmatrix);

	glPopMatrix();

	winx = x;
	winy = scr_h - y;

	glReadPixels((int)winx, (int)winy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winz);            /* 获取深度 */
	gluUnProject(winx, winy, winz, mvmatrix, projmatrix, viewport, &posx, &posy, &posz);    /* 获取三维坐标 */
	int xx = changePos(posx);
	int yy = changePos(posy);
	int zz = changePos(posz);

	///@TODO 可能与放置物品有关
	/*
	if (c == GLUT_LEFT_BUTTON)
	{
		cube_mgr.insertCube(TexCube(xx, yy, zz, 1.0f, Tnt));
	}
	else
	{
		torch_arr.push_back(Point(xx, yy, zz));
	}
	*/
}

