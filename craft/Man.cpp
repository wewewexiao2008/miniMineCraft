#include "Man.h"

Man::Man()
{
	_ini();
	reset();
}

bool Man::forward(Chunk &world)
{
	float x_temp = x +speed * cos(vangle / 180 * PI);
	float z_temp = z - speed * sin(vangle / 180 * PI);
	float y_temp = y;
	//能向前移动的标志
	bool is_forword = coll_check.is_collision(x_temp, y_temp, z_temp, x_temp - 1,
		y_temp + 2, z_temp - 1, world);
	if (!is_forword)
	{
		move = true;
		x = x_temp;
		z = z_temp;
		return true;
	}
	else
	{
		return false;
	}
}

bool Man::back(Chunk &world)
{
	float x_temp = x - speed * cos(vangle / 180 * PI);
	float z_temp = z + speed * sin(vangle / 180 * PI);
	float y_temp = y;
	//能向前移动的标志
	bool is_forword = coll_check.is_collision(x_temp, y_temp, z_temp, x_temp - 1,
		y_temp + 2, z_temp - 1, world);
	if (!is_forword)
	{
		move = true;
		x = x_temp;
		z = z_temp;
		return true;
	}
	else
	{
		return false;
	}
}

bool Man::left(Chunk & world)
{
	float x_temp = x - speed * sin(vangle / 180 * PI);
	float z_temp = z - speed * cos(vangle / 180 * PI);
	float y_temp = y;
	//能向前移动的标志
	bool is_forword = coll_check.is_collision(x_temp, y_temp, z_temp, x_temp - 1,
		y_temp + 2, z_temp - 1, world);
	if (!is_forword)
	{
		move = true;
		x = x_temp;
		z = z_temp;
		return true;
	}
	else
	{
		return false;
	}
}

bool Man::right(Chunk & world)
{
	float x_temp = x + speed * sin(vangle / 180 * PI);
	float z_temp = z + speed * cos(vangle / 180 * PI);
	float y_temp = y;
	//能向前移动的标志
	bool is_forword = coll_check.is_collision(x_temp, y_temp, z_temp, x_temp - 1,
		y_temp + 2, z_temp - 1, world);
	if (!is_forword)
	{
		move = true;
		x = x_temp;
		z = z_temp;
		return true;
	}
	else
	{
		return false;
	}
}

bool Man::jump()
{
	jumping = true;
	return true;
}

bool Man::is_moving()
{
	return move;
}

void Man::set_move(bool move)
{
	this->move = move;
}

void Man::refresh()
{
	//跳跃函数
	if (jumping == true && y < max_height && falling == false)
	{
		y += jump_speed;
		jump_speed -= 0.05;
		if (jump_speed <= 0)
		{
			falling = true;
			jumping = false;
			jump_speed = 0.3;
		}
	}
	if (falling == true)
	{
		y -= fall_speed;
		fall_speed += 0.05;
		if (y - 0.05 <= ground_height)
		{
			fall_speed = 0.3;
			falling = false;
		}
	}


	// 人
	glPushMatrix();
	glTranslatef(x, y, z);
	glRotatef(vangle, 0, 1, 0);

	////////////////////////////Hair//////////////////////////
	glColor3f(0.0f, 0.0f, 0.0f);
	glPushMatrix();
	glTranslatef( hair.x,  hair.y,  hair.z);
	glScalef( hair_scale.x,  hair_scale.y,  hair_scale.z);
	glutSolidCube(1);
	glPopMatrix();

	///////////////////////////Head////////////////////////////
	// head
	glColor3f(139.0 / 255, 115.0 / 255, 85.0 / 255);
	glPushMatrix();
	glTranslatef( head.x,  head.y,  head.z);
	glScalef( head_scale.x,  head_scale.y,  head_scale.z);
	glutSolidCube(1);
	glPopMatrix();

	// left eye
	glColor3f(0.9f, 0.9f, 0.9f);
	glPushMatrix();
	glTranslatef( eyeL.x,  eyeL.y,  eyeL.z);
	glScalef( eye_scale.x,  eye_scale.y,  eye_scale.z);
	glutSolidCube(1);
	glPopMatrix();

	// right eye
	glColor3f(0.9f, 0.9f, 0.9f);
	glPushMatrix();
	glTranslatef( eyeR.x,  eyeR.y,  eyeR.z);
	glScalef( eye_scale.x,  eye_scale.y,  eye_scale.z);
	glutSolidCube(1);
	glPopMatrix();

	// mouth
	glColor3f(1, 1, 1);
	glPushMatrix();
	glTranslatef( mouth.x,  mouth.y,  mouth.z);
	glScalef( mouth_scale.x,  mouth_scale.y,  mouth_scale.z);
	glutSolidCube(1);
	glPopMatrix();


	///////////////////////////Body////////////////////////////
	glColor3f(0.0f, 206.0 / 255, 209.0 / 255);
	glPushMatrix();
	glTranslatef( body.x,  body.y,  body.z);
	glScalef( body_scale.x,  body_scale.y,  body_scale.z);
	glutSolidCube(1);
	glPopMatrix();

	/////////////////////////Leg/////////////////////////
	//Left leg
	glColor3f(67.0 / 255, 110.0 / 255, 238.0 / 255);
	glPushMatrix();
	glTranslatef( thighL.x, 2 *  thighL.y,  thighL.z);
	glRotatef( ltangle, 0, 0, 1);
	glTranslatef(0, - thighR.y, 0);
	glScalef( thigh_scale.x,  thigh_scale.y,  thigh_scale.z);
	glutSolidCube(1);
	glPopMatrix();

	//Right leg
	glColor3f(67.0 / 255, 110.0 / 255, 238.0 / 255);
	glPushMatrix();
	glTranslatef( thighR.x, 2 *  thighR.y,  thighR.z);
	glRotatef( rtangle, 0, 0, 1);
	glTranslatef(0, - thighR.y, 0);
	glScalef( thigh_scale.x,  thigh_scale.y,  thigh_scale.z);
	glutSolidCube(1);
	glPopMatrix();

	///////////////////////Arm////////////////////////

	//Left Arm
	glColor3f(139.0 / 255, 115.0 / 255, 85.0 / 255);
	glPushMatrix();
	glTranslatef( armL.x,  arm_scale.y / 2 +  armL.y,  armL.z);
	glRotatef( laangle, 0, 0, 1);
	glTranslatef(0, - arm_scale.y / 2, 0);
	glScalef( arm_scale.x,  arm_scale.y,  arm_scale.z);
	glutSolidCube(1);
	glPopMatrix();

	//Right Arm
	glColor3f(139.0 / 255, 115.0 / 255, 85.0 / 255);
	glPushMatrix();
	glTranslatef( armR.x,  arm_scale.y / 2 +  armR.y,  armR.z);
	glRotatef( raangle, 0, 0, 1);
	glTranslatef(0, - arm_scale.y / 2, 0);
	glScalef( arm_scale.x,  arm_scale.y,  arm_scale.z);
	glutSolidCube(1);
	glPopMatrix();

	glPopMatrix();
}

void Man::refresh_ini(int c)
{
	if (is_moving())
	{
		if (ltangle < -60)
		{
			left_forward = false;
		}
		else if ( ltangle > 60)
		{
			left_forward = true;
		}
		if ( rtangle < -60)
		{
			right_forward = false;
		}
		else if ( rtangle > 60)
		{
			right_forward = true;
		}
		if (left_forward)
		{
			 ltangle--;
			 laangle++;
		}
		else
		{
			 ltangle++;
			 laangle--;
		}
		if (right_forward)
		{
			 rtangle--;
			 raangle++;
		}
		else
		{
			 rtangle++;
			 raangle--;
		}
	}
	else
	{
		 raangle = 0;
		 laangle = 0;
		 rtangle = 0;
		 ltangle = 0;
	}
	///每DELAY毫秒调用一下refresh，传入参数为0
	//glutTimerFunc(delay_time,refresh_ini, 0);
	///标记当前窗口需要重绘
	glutPostRedisplay();
}

void Man::_ini()
{
	jumping = false;
	falling = false;
	jump_speed = 0.3;
	fall_speed = 0.3;
	basic_size = 1;
	speed = 0.5;
	vangle = 0;
	ltangle = -60;
	rtangle = -120;
	laangle = -115;
	raangle = -75;
	move = false;
	left_forward = true;
	right_forward = false;
	look_from_left = true;
}
