#pragma once
#include "math.h"
class Vec3 {
public:
	float x, y, z;
	Vec3() {
		x = y = z = 0;
	}
	Vec3(const Vec3& v) {
		x = v.x;
		y = v.y;
		z = v.z;
	}
	Vec3(const float a, const float b, const float c) {
		x = a;
		y = b;
		z = c;
	}
	void set(const float a, const float b, const float c) {
		x = a;
		y = b;
		z = c;
	}
	void set(float a) {
		x = y = z = a;
	}
	void add(const float a, const float b, const float c) {
		x += a;
		y += b;
		z += c;
	}
	void add(const Vec3& v) {
		x += v.x;
		y += v.y;
		z += v.z;
	}
	//float len() {
	//	return sqrt(x * x + y * y + z * z);
	//}
	Vec3 operator+(const Vec3& v) {
		return Vec3(x + v.x, y + v.y, z + v.z);
	}
	Vec3 operator-() {
		return Vec3(-x, -y, -z);
	}
	Vec3 operator-(const Vec3& v) {
		Vec3 temp = -(Vec3)v;
		return *this+temp;
	}
	Vec3 operator*(const float k) {
		return Vec3(x + k, y + k, z + k);
	}

	bool operator>(const Vec3 v) {
		return ((this->x > v.x) || (this->x == v.x && this->y > v.y) || (this->x == v.x && this->y == v.y && this->z > v.z));
	}
	bool operator<(const Vec3 v) {
		return ((this->x < v.x) || (this->x == v.x && this->y < v.y) || (this->x == v.x && this->y == v.y && this->z < v.z));
	}
	bool operator==(const Vec3 v) {
		return ((this->x==v.x) && (this->y==v.y) && (this->z==v.z));
	}
};
class AABB {
public:
	Vec3 _min;
	Vec3 _max;
	//ctor
	AABB() {
		reset();
	}
	AABB(const Vec3& min, const Vec3& max) {
		set(min, max);
	}

	AABB(const AABB& box) {
		set(box._min, box._max);
	}
	void set(const Vec3& min, const Vec3& max) {
		this->_max = max;
		this->_min = min;
	}
	void set(const float& x, const float& y, const float& z, const float& size) {
		this->_min.x = x - size / 2.0;
		this->_min.y = y - size / 2.0;
		this->_min.z = z - size / 2.0;
		this->_max.x = x + size / 2.0;
		this->_max.y = y + size / 2.0;
		this->_max.z = z + size / 2.0;
	}
	void reset() {
		_min.set(99999.0f, 99999.0f, 99999.0f);
		_max.set(-99999.0f, -99999.0f, -99999.0f);
	}
	bool tested = false;
	//判断两个包围盒是否碰撞
	bool intersects_XZ(const AABB& aabb) const;
	//检测坐标信息是否有误
	bool isEmpty() const;
	//由给定点坐标点重新确定最大最小的坐标向量
	void updateMinMax(const Vec3* point, int num);
	//获取包围盒中心点坐标
	Vec3 getCenter();

};
