#pragma once
#include "Point.h"
#include "coll_dete.h"

#define PI 3.1415926535898
/**
* @brief 人物类
* @TODO 以后是不是设置一个生物类的基类，然后主角，村民，苦力怕再去继承呢？？
*/
class Man
{
public:
	///基础大小
	float basic_size;
	///速度
	float speed;
	Point hair_scale, head_scale, thigh_scale, body_scale, arm_scale, eye_scale, mouth_scale;
	Point head, hair, body, thighL, thighR, armL, armR, eyeL, eyeR, mouth;
	//Point* bodyArray[] = { &head, &hair, &body, &thighL, &thighR, &armL, &armR, &eyeL, &eyeR, &mouth };

	float x, y, z;
	float vangle;  // 速度偏角
	float ltangle; // 左腿偏角
	float rtangle;// 右腿偏角
	float laangle;// 左臂偏角
	float raangle; // 右臂偏角
	bool move;


public:
	/// 构造函数
	Man();

	//@TODO 运动相关函数除了碰撞检测。。。还应考虑其他物理检测的扩展（比如重力检测）
	/**
	* @brief 人物向前移动
	* @return 若不可移动则返回false
	*/
	bool forward(Chunk &world);
	/**
	* @brief 人物向后移动
	* @return 若不可移动则返回false
	*/
	bool back(Chunk &world);
	/**
	* @brief 人物向左移动
	* @return 若不可移动则返回false
	*/
	bool left(Chunk &world);
	/**
	* @brief 人物向右移动
	* @return 若不可移动则返回false
	*/
	bool right(Chunk &world);
	
	/**
	* @brief 人物跳跃
	* @return 若不可移动则返回false
	*/
	bool jump();
	
	/**
	* @brief 重置人物大小
	*/
	void resetSize(float new_basic) 
	{
		this->basic_size = new_basic;
		reset();
	}

	/**
	* @brief 是否正在移动
	* @return 正在移动返回true
	*/
	bool is_moving();
	
	/**
	* @brief 改变move标志
	*/
	void set_move(bool move);

	/**
	* @brief 设定人物坐标，也可以设定的初始位置（出生点^_^）
	*/
	void setLocation(float x, float y, float z) 
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	/**
	* @brief 人物刷新函数
	*/
	void refresh();

	/**
	* @brief 重设人物显示参数
	*/
	void reset()
	{
		// 比例控制
		head_scale = Point(0.5, 0.5, 0.75, basic_size);
		body_scale = Point(0.3, 1.25, 0.75, basic_size);
		eye_scale = Point(0.2, 0.2, 0.2, basic_size);
		mouth_scale = Point(0.2, 0.2, 0.5, basic_size);
		hair_scale = Point(head_scale.x, 0.3, head_scale.z, basic_size); // 头发xz与头相同
		thigh_scale = Point(body_scale.x, 1.4, body_scale.z / 2, basic_size); // 腿x与身相同，z为身的一半
		arm_scale = Point(body_scale.x, body_scale.y, 0.3, basic_size); //手臂xy与身相同

																		// 相对位置控制
		head = Point(0, thigh_scale.y + body_scale.y + head_scale.y / 2, 0, basic_size);
		hair = Point(0, thigh_scale.y + body_scale.y + head_scale.y + hair_scale.y / 2, 0, basic_size);
		body = Point(0, thigh_scale.y + body_scale.y / 2, 0, basic_size);
		thighL = Point(0, thigh_scale.y / 2, -thigh_scale.z / 2, basic_size);
		thighR = Point(0, thigh_scale.y / 2, thigh_scale.z / 2, basic_size);
		armL = Point(0, thigh_scale.y + arm_scale.y / 2, -(arm_scale.z + body_scale.z) / 2, basic_size);
		armR = Point(0, thigh_scale.y + arm_scale.y / 2, (arm_scale.z + body_scale.z) / 2, basic_size);
		eyeL = Point(head_scale.x / 2, thigh_scale.y + body_scale.y + head_scale.y / 2, -(eye_scale.z / 2 + 0.1),
			basic_size);
		eyeR = Point(head_scale.x / 2, thigh_scale.y + body_scale.y + head_scale.y / 2, (eye_scale.z / 2 + 0.1),
			basic_size);
		mouth = Point(head_scale.x / 2, thigh_scale.y + body_scale.y + head_scale.y / 2 - 0.1, 0, basic_size);
	}

	/**
	* @brief 人物动画标志刷新
	* @TODO 有问题待定
	*/
	void refresh_ini(int c);
private:
	///碰撞检测类
	Collision coll_check;
	///
	/// 跳跃参数
	bool jumping;
	bool falling;
	float jump_speed;
	float fall_speed;
	const float max_height = 3.0;
	const float ground_height = 1.00;
	const int delay_time = 12;
	///相对坐标参数
	bool left_forward;
	bool right_forward;
	bool look_from_left;

private:
	/**
	* @初始函数
	*/
	void _ini();
};