#pragma once
#include<vector>
#include"Point.h"
#include"Chunk.h"
/**
* @brief ��ײ��������
*/

class Collision
{
public:
	Collision();

	/**
	* @param a,bΪ��������ԽǶ���
	* @brief ��ײ���,��AABB�㷨
	* @return ������ײʱ����true
	*/
	bool is_collision(Point a, Point b);
	bool is_collision(const float a_x, const float a_y, const float a_z,
		const float b_x, const float b_y, const float b_z, const Chunk &my_chunk);

	/**
	* @brief ����ת������opengl�е������Ӧ��ĳһchunk�е�����
	*/

private:


};

