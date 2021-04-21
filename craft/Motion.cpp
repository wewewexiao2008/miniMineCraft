#include "Motion.h"
#include<string>
#include <math.h>
using namespace std;
PhysicsEngine::PhysicsEngine(CubeManager* cm) {
	coordinate.set(8,3* HeroHeight,-2 );
	// AABB
	Vec3 min(coordinate.x-BOX_LENGTH,coordinate.y-HeroHeight,coordinate.z-BOX_LENGTH);
	Vec3 max(coordinate.x+BOX_LENGTH,coordinate.y+1.0f,coordinate.z-BOX_LENGTH);

	Player_Box.set(min, max);
	isW = isS = isA = isD = false;
	isAir = false;
	// v,a
	omega = 0;
	theta = 0;
	velocity.set(0, 0, 0);
	cube_manager = cm;
}

void PhysicsEngine::reset(std::map<std::string,AABB> BoundingBox_list) {

	//AABB
	Vec3 min(coordinate.x - BOX_LENGTH, coordinate.y - HeroHeight, coordinate.z - BOX_LENGTH);
	Vec3 max(coordinate.x + BOX_LENGTH, coordinate.y + HeadHeight, coordinate.z + BOX_LENGTH); 
	Player_Box.set(min, max);
	if (isLeft)omega += 5.0f / 180 * PI;
	if (isRight)omega -= 5.0f / 180 * PI;
	UpdateVerticalMotion(BoundingBox_list);
	UpdateHorizentalMotion(BoundingBox_list);
	// focus
	focus.set(coordinate.x + UNIT * cos(omega) * cos(theta), coordinate.y + UNIT * sin(theta), coordinate.z + UNIT * sin(omega) * cos(theta));
	

}
void PhysicsEngine::JumpUpdateVelocity() {
	velocity.y = JumpFactor*vertical_speed;
	
	accelerUp = 0.f;
}
void PhysicsEngine::UpdateHorizentalMotion(std::map<std::string,AABB> Box_list) {
	float angle = omega;
	float v = horizon_speed;
	if (isA && isW) {
		angle = omega - 0.25 * PI;
	}
	else if (isA && isS) {
		angle = omega - 0.75 * PI;
	}
	else if (isD && isW) {
		angle = omega + 0.25 * PI;
	}
	else if (isD && isS) {
		angle = omega + 0.75 * PI;
	}
	else if (isD) {
		angle = omega + 0.5 * PI;
	}
	else if (isW) {
		angle = omega;
	}
	else if (isS) {
		angle = omega + PI;
	}
	else if (isA) {
		angle = omega - 0.5 * PI;
	}
	else {
		v = 0;
	}
	
	velocity.x = v * cos(angle);
	if (velocity.x<min_speed && velocity.x > -min_speed)velocity.x = 0;
	velocity.z = v * sin(angle);
	if (velocity.z<min_speed && velocity.z> -min_speed)velocity.z = 0;
	coordinate.x += velocity.x;
	coordinate.z += velocity.z;
	Vec3 min(coordinate.x - BOX_LENGTH, coordinate.y - HeroHeight, coordinate.z - BOX_LENGTH);
	Vec3 max(coordinate.x + BOX_LENGTH, coordinate.y + HeadHeight, coordinate.z + BOX_LENGTH);
	Player_Box.set(min, max);
	vector<string> vs;
	for (int x = floor(coordinate.x); x <= ceil(coordinate.x); x++) {
		for (int y = floor(coordinate.y); y <= ceil(coordinate.y+HeadHeight); y++) {
			for (int z = floor(coordinate.z); z <= ceil(coordinate.z); z++) {
				string s = to_string(x) + "_" + to_string(y) + "_" + to_string(z);
				vs.push_back(s);
			}
		}
	}
	// 水平碰撞检测
	for (vector<string>::iterator i = vs.begin(); i < vs.end(); i++) {
		if (Box_list[*i].isEmpty())continue;
		//在竖直范围内才进行检测
		if (Box_list[*i]._min.y - eps> Player_Box._max.y || Box_list[*i]._max.y + eps < Player_Box._min.y)continue;
		if (Player_Box.intersects_XZ(Box_list[*i])) {
			Vec3 temp = Box_list[*i].getCenter();
			// 根据中心的相对位置判断碰撞方向XZ
			if (fabs(temp.x - coordinate.x) > fabs(temp.z - coordinate.z)) {
				coordinate.x = coordinate.x<temp.x?(Box_list[*i]._min.x-BOX_LENGTH):(Box_list[*i]._max.x+BOX_LENGTH);

			}
			else {
				coordinate.z = coordinate.z < temp.z ? (Box_list[*i]._min.z - BOX_LENGTH) : (Box_list[*i]._max.z + BOX_LENGTH );

			}
			Vec3 min(coordinate.x - BOX_LENGTH, coordinate.y - HeroHeight, coordinate.z - BOX_LENGTH);
			Vec3 max(coordinate.x + BOX_LENGTH, coordinate.y + HeadHeight, coordinate.z + BOX_LENGTH);
			Player_Box.set(min, max);

		}
	}
}


void PhysicsEngine::UpdateVerticalMotion(std::map<std::string,AABB> Box_list) {

	float acceleration = -gravity + accelerUp;//重力+支持力
	if (acceleration != 0)isAir = true;
	velocity.y += acceleration * vertical_speed;//移动
	if (fabs(velocity.y) > max_speed && velocity.y<0)velocity.y = -max_speed;
	float god_speed = 0;
	if (isUp)god_speed += GodFactor * vertical_speed;
	if (isDown)god_speed -= GodFactor * vertical_speed;
	if (mode == NORMAL)coordinate.y += velocity.y;
	else if(mode == GOD) coordinate.y += god_speed;
	Vec3 min(coordinate.x - BOX_LENGTH, coordinate.y - HeroHeight, coordinate.z - BOX_LENGTH);
	Vec3 max(coordinate.x + BOX_LENGTH, coordinate.y + HeadHeight, coordinate.z + BOX_LENGTH);
	Player_Box.set(min, max);
	vector<string> vs;
	for (int x = floor(coordinate.x); x <= ceil(coordinate.x); x++) {
		for (int y = floor(coordinate.y - HeroHeight); y <= ceil(coordinate.y+HeadHeight); y++) {
			for (int z = floor(coordinate.z); z <= ceil(coordinate.z); z++) {
				string s = to_string(x) + "_" + to_string(y) + "_" + to_string(z);
				vs.push_back(s);
			}
		}
	}
	// 竖直碰撞检测
	accelerUp = 0.f;
	for (vector<string>::iterator i = vs.begin(); i < vs.end(); i++) {
		if (Box_list[*i].isEmpty())continue;
		//在XZ范围内才进行检测
		if (!Player_Box.intersects_XZ(Box_list[*i])) {
			continue;
		}
		//if (Player_Box._max.x <= Box_list[*i]._max.x && Player_Box._max.z <= Box_list[*i]._max.z
		//	&& Player_Box._min.x >= Box_list[*i]._min.x && Player_Box._min.z >= Box_list[*i]._min.z) {
		if (Player_Box._min.y  <= Box_list[*i]._max.y && Player_Box._max.y > Box_list[*i]._max.y) {//踩进去
			isAir = false;
			coordinate.y = Box_list[*i]._max.y + HeroHeight;
			accelerUp = gravity;//支持力
			velocity.y = 0.f;
			Vec3 min(coordinate.x - BOX_LENGTH, coordinate.y - HeroHeight, coordinate.z - BOX_LENGTH);
			Vec3 max(coordinate.x + BOX_LENGTH, coordinate.y + HeadHeight, coordinate.z + BOX_LENGTH);
			Player_Box.set(min, max);
			break;
		}
		if (Player_Box._min.y < Box_list[*i]._min.y && Player_Box._max.y >= Box_list[*i]._min.y){//头
			coordinate.y = Box_list[*i]._min.y - HeadHeight;
			velocity.y = 0.f;
			Vec3 min(coordinate.x - BOX_LENGTH, coordinate.y - HeroHeight, coordinate.z - BOX_LENGTH);
			Vec3 max(coordinate.x + BOX_LENGTH, coordinate.y + HeadHeight, coordinate.z + BOX_LENGTH);
			Player_Box.set(min, max);
			break;
		}

	}
	
}

void PhysicsEngine::MouseMove(int x, int y) {
	
	//if (fixMouse)
		//FixMouseInWindow(x, y);

	float dx = x - lastX;
	float dy = y - lastY;

	dx *= MOUSE_SENSE_X;
	dy *= MOUSE_SENSE_Y;

	omega += dx;
	theta -= dy;

	lastX = x;
	lastY = y;
	return;
}

#include <Windows.h>
void PhysicsEngine::FixMouseInWindow(int &x, int &y) {
	if (x > WINDOW_WIDTH / 4 * 3) {
		lastX -= WINDOW_WIDTH / 4;
		x -= WINDOW_WIDTH / 4;
		SetCursorPos(x, y);
	}

	if (y > WINDOW_HEIGHT / 4 * 3) {
		lastY -= WINDOW_WIDTH / 4;
		y -= WINDOW_WIDTH / 4;
		SetCursorPos(x, y);
	}

	if (x < WINDOW_WIDTH / 4) {
		lastX += WINDOW_WIDTH / 4;
		x += WINDOW_WIDTH / 4;
		SetCursorPos(x, y);
	}

	if (y < WINDOW_HEIGHT / 4) {
		lastY += WINDOW_WIDTH / 4;
		y += WINDOW_WIDTH / 4;
		SetCursorPos(x, y);
	}
	
}

void PhysicsEngine::AddCube(CubeTex cube) {
	Vec3 target;
	std::cout << "I'm at position" << coordinate.x << "," << coordinate.y << "," << coordinate.z << std::endl;
	std::cout << "Focus is at towards" << focus.x << "," << focus.y << "," << focus.z << std::endl;

	for (int i = 1; i < RANGE; i++) {
		// - coordinate
		// target = coordinate + (focus - coordinate)*(i * PlaceSpeed);
		// Vec3 pos(round(target.x), round(target.y), round(target.z));
		// int z = round(target.z);
		int x = round(coordinate.x + (focus.x - coordinate.x) * (i * PlaceSpeed));
		int y = round(coordinate.y + (focus.y - coordinate.y) * (i * PlaceSpeed));
		int z = round(coordinate.z + (focus.z - coordinate.z) * (i * PlaceSpeed));

		std::cout << "try to add Cube one before[" << x << "][" << y << "][" << z << "]" << std::endl;

		std::string s = std::to_string(x) + "_" + std::to_string(y) + "_" + std::to_string(z);
		if (cube_manager->isExist(s)) {
			x = round(coordinate.x + (focus.x - coordinate.x) * ((i - 1) * PlaceSpeed));
			y = round(coordinate.y + (focus.y - coordinate.y) * ((i - 1) * PlaceSpeed));
			z = round(coordinate.z + (focus.z - coordinate.z) * ((i - 1) * PlaceSpeed));
			std::cout << "and its befor is [" << x << "][" << y << "][" << z << "]" << std::endl;

			std::string s = std::to_string(x) + "_" + std::to_string(y) + "_" + std::to_string(z);
			if (!cube_manager->isExist(s) && 
				! ( (x == ceil(coordinate.x)) || (y == ceil(coordinate.y)) || (z == ceil(coordinate.z)) )
				) {
				cube_manager->insertCube(TexCube(x, y, z, 1.0f, cube));
				return;
			}
		}
	}
}

void PhysicsEngine::EliminateCube(CubeTex cube) {
	Vec3 target;
	std::cout << "I'm at position" << coordinate.x << "," << coordinate.y << "," << coordinate.z << std::endl;
	std::cout << "Focus is at at" << focus.x << "," << focus.y << "," << focus.z << std::endl;

	for (int i = 1; i < RANGE; i++) {
		// target = coordinate + (focus - coordinate)*(i * PlaceSpeed);
		std::cout << "try to remove Cube at pos[" << round(target.x) << "][" << round(target.y) << "][" << round(target.z) << "]" << std::endl;
		int x = round(coordinate.x + (focus.x - coordinate.x) * (i * PlaceSpeed));
		int y = round(coordinate.y + (focus.y - coordinate.y) * (i * PlaceSpeed));
		int z = round(coordinate.z + (focus.z - coordinate.z) * (i * PlaceSpeed));

		std::string s = std::to_string(x) + "_" + std::to_string(y) + "_" + std::to_string(z);
		if (cube_manager->isExist(s)) {
			cube_manager->deleteCube(TexCube(x, y, z, 1.0f, cube));
			// add elimination animation
			return;
		}
		else {
			std::cout << "when delete in physics engine , not exist" << std::endl;
		}
	}
}
