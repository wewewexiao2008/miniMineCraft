#include "AABB.h"
bool AABB::intersects_XZ(const AABB& aabb) const
{	
	if (_min.x > aabb._max.x || _min.y > aabb._max.y || _max.x < aabb._min.x || _max.y < aabb._min.y)return false;
	//就是各轴 互相是否包含，（aabb 包含  当前包围盒）||  （当前的包围盒 包含 aabb）
	return true;
	//return ((_min.x > aabb._min.x && _min.x < aabb._max.x) || (aabb._min.x > _min.x && aabb._min.x < _max.x)) &&
	//	/*((_min.y > aabb._min.y && _min.y < aabb._max.y) || (aabb._min.y >_min.y && aabb._min.y < _max.y)) &&*/
	//	((_min.z > aabb._min.z && _min.z < aabb._max.z) || (aabb._min.z > _min.z && aabb._min.z <_max.z));
}

bool AABB::isEmpty() const
{
	return _min.x > _max.x || _min.y > _max.y || _min.z > _max.z;
}

void AABB::updateMinMax(const Vec3* point, int num)
{
	for (int i = 0; i < num; i++)
	{
		// Leftmost point.
		if (point[i].x < _min.x)
			_min.x = point[i].x;

		// Lowest point.
		if (point[i].y < _min.y)
			_min.y = point[i].y;

		// Farthest point.
		if (point[i].z < _min.z)
			_min.z = point[i].z;

		// Rightmost point.
		if (point[i].x > _max.x)
			_max.x = point[i].x;

		// Highest point.
		if (point[i].y > _max.y)
			_max.y = point[i].y;

		// Nearest point.
		if (point[i].z > _max.z)
			_max.z = point[i].z;
	}
}
//获取包围盒中心点坐标
Vec3 AABB::getCenter()
{
	Vec3 center;
	center.x = 0.5f * (_min.x + _max.x);
	center.y = 0.5f * (_min.y + _max.y);
	center.z = 0.5f * (_min.z + _max.z);
	return center;
}