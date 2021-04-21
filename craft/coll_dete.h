#pragma once
#include<vector>
#include"Point.h"
#include"Chunk.h"
/**
* @brief 碰撞检测相关类
*/

class Collision
{
public:
	Collision();

	/**
	* @param a,b为物体的两对角顶点
	* @brief 碰撞检测,类AABB算法
	* @return 发生碰撞时返回true
	*/
	bool is_collision(Point a, Point b);
	bool is_collision(const float a_x, const float a_y, const float a_z,
		const float b_x, const float b_y, const float b_z, const Chunk &my_chunk);

	/**
	* @brief 坐标转化，将opengl中的坐标对应到某一chunk中的坐标
	*/

private:


};

