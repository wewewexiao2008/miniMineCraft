#pragma once

/**
* @brief 对结点点的封装，包括重载一些操作
*/
struct Point
{
	float x, y, z;
	Point(float x, float y, float z, float basic_size = 1)
	{
		this->x = x * basic_size;
		this->y = y * basic_size;
		this->z = z * basic_size;
	}
	Point()
	{

	}
	void setPoint(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	Point& operator *=(float e)
	{
		this->x *= e;
		this->y *= e;
		this->z *= e;
		return *this;
	}
	Point& operator *(float e)
	{
		Point p = *this;
		p *= e;
		return p;
	}
};