#include "CubeManager.h"
#include "AABB.h"
using namespace std;

bool CubeManager::insertCube(const TexCube &texcube)
{
	//Vec3 pos;
	int x = (int)texcube._x;
	int y = (int)texcube._y;
	int z = (int)texcube._z;
	AABB temp;
	//temp.set(texcube._x, texcube._y, texcube._z, texcube._size);
	temp.set(x, y, z,texcube._size);
	string s = to_string(x) + "_" + to_string(y) + "_" + to_string(z); // debug
	if (isExist(s)) {
		//std::cout << "cannot add new at " << s << std::endl;
		return false;
	}
	else {
		cubeMap[s] = texcube;
		aabbMap[s] = temp;
		//std::cout << "success in adding new at " << s  << " with type " << texcube.type << std::endl;
		return true;
	}
	
}

bool CubeManager::deleteCube(const TexCube &texcube) {
	//Vec3 pos;
	int x = (int)texcube._x;
	int y = (int)texcube._y;
	int z = (int)texcube._z;

	string s = to_string(x) + "_" + to_string(y) + "_" + to_string(z); // debug
	if (isExist(s)) {
		cubeMap.erase(s);
		aabbMap.erase(s);
		//std::cout << "success in deleting " << s  << " with cube type" << texcube.type << std::endl;
		return true;
	}
	else {
		//std::cout << "cannot delete " << s << std::endl;
		return false;
	}
}

void CubeManager::createAllCube()
{

	for (auto it : cubeMap)
	{
		it.second.createCube();
	}
	/*
	//该代码相当于：该好好看书的
	for (auto it = std::begin(cubeMap); it != std::end(cubeMap); it++)
	{
		it.second.createCube();
	}
	*/

}

bool CubeManager::isExist(std::string id) {
	bool res = (cubeMap.find(id) != cubeMap.end());
	//if (res)	std::cout << id << " exists!" << std::endl;
	//else	std::cout << id << "not exists" << std::endl;
	return res;
}


bool CubeManager::isAround(std::string input) {
	int x, y, z;
	int i = 0;
	std::cout << "isAround" << input << std::endl;
	std::string num1;
	while (input[i] != '_' && input[i] != '\0') {
		num1[i] = input[i];
		i++;
	}
	x = atoi(num1.c_str());

	std::string num2;
	int len1 = ++i;
	while (input[i] != '_' && input[i] != '\0') {
		num2[i - len1] = input[i];
		i++;
	}
	y = atoi(num2.c_str());

	std::string num3;
	int len2 = ++i;
	while (input[i] != '\0') {
		num3[i - len2] = input[i];
		i++;
	}
	z = atoi(num3.c_str());

	for (int i = 0; i < 3; i++) 
		for(int k = 0; k<3; k++)
			for (int j = 0; j < 3; j++) {
				int tx, ty, tz;
				switch (i % 3) {
					case 0: tx = x + 1; break;
					case 1: tx = x - 1; break;
					default: break;
				}

				switch (k % 3) {
					case 0: ty = y + 1; break;
					case 1: ty = y - 1; break;
					default: break;
				}

				switch (j % 3) {
					case 0: tz = z + 1; break;
					case 1: tz = z - 1; break;
					default: break;
				}
				if ((tx == x) && (ty == y) && (tz == z)) break;
				std::string around = to_string(tx) + "_" + to_string(ty) + "_" + to_string(tz);
				if (isExist(around))
					return true;
			}
}

void CubeManager::buildPyramid(int x, int y, int z)
{
	for (int n = y; n <= 10; n++) {
		for (int i = x + n; i < 2 * 10 - n; i++) {
			for (int j = z + n; j < 2 * 10 - n; j++) {
				this->insertCube(TexCube(i, n, j, 1.0f, Sand));
			}
		}
	}
	for (int i = y; i < 4 + y; i++) {
		this->insertCube(TexCube(x + 7, i, z, 1.0f, Sand));
	}
	for (int i = y; i < 4 + y; i++) {
		this->insertCube(TexCube(x + 11, i, z, 1.0f, Sand));
	}
	for (int i = x + 8; i <= x + 10; i++) {
		for (int j = y + 3; j <= y + 5; j++) {
			this->insertCube(TexCube(i, j, z, 1.0f, Sand));
		}
	}
	this->insertCube(TexCube(x + 8, y + 4, z, 1.0f, RedSand));
	this->insertCube(TexCube(x + 10, y + 4, z, 1.0f, RedSand));
	this->buildannexBuilding(x, y, z);
	this->buildannexBuilding(x + 14, y, z);
}

void CubeManager::buildannexBuilding(int x, int y, int z) {
	for (int k = y; k < y + 9; k++) {
		for (int i = x; i < x + 5; i++) {
			for (int j = z; j < z + 5; j++) {
				this->insertCube(TexCube(i, k, j, 1.0f, Sand));
			}
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			this->insertCube(TexCube(x + i + 1, y + 9, z + j + 1, 1.0f, Sand));
		}
	}
	this->insertCube(TexCube(x, y + 9, z + 2, 1.0f, Sand));
	this->insertCube(TexCube(x + 2, y + 9, z, 1.0f, Sand));
	this->insertCube(TexCube(x + 2, y + 9, z + 4, 1.0f, Sand));
	this->insertCube(TexCube(x + 4, y + 9, z + 2, 1.0f, Sand));
	this->insertCube(TexCube(x + 2, y + 1, z, 1.0f, RedSand));
	this->insertCube(TexCube(x + 2, y + 2, z, 1.0f, RedSand));
	this->insertCube(TexCube(x + 1, y + 3, z, 1.0f, RedSand));
	this->insertCube(TexCube(x + 3, y + 3, z, 1.0f, RedSand));
	this->insertCube(TexCube(x + 2, y + 4, z, 1.0f, RedSand));
	this->insertCube(TexCube(x + 1, y + 5, z, 1.0f, RedSand));
	this->insertCube(TexCube(x + 3, y + 5, z, 1.0f, RedSand));
	this->insertCube(TexCube(x + 1, y + 6, z, 1.0f, RedSand));
	this->insertCube(TexCube(x + 2, y + 6, z, 1.0f, RedSand));
	this->insertCube(TexCube(x + 3, y + 6, z, 1.0f, RedSand));
}

void CubeManager::buildPool(int x, int y, int z)
{
	int num_cube = 4;
	for (int i = x + 1; i <= x + num_cube; i++) {
		for (int j = z + 1; j <= z + num_cube; j++) {
			this->insertCube(TexCube(i, y, j, 1.0f, Water));
		}
	}

	for (int i = x; i <= x + 1 + num_cube; i++) {
		this->insertCube(TexCube(i, y, z, 1.0f, Soil));
		this->insertCube(TexCube(i, y, z + num_cube + 1, 1.0f, Soil));
	}
	for (int i = z + 1; i <= z + num_cube; i++) {
		this->insertCube(TexCube(x, y, i, 1.0f, Soil));
		this->insertCube(TexCube(x + num_cube + 1, y, i, 1.0f, Soil));
	}
}

void CubeManager::buildTree(int x, int y, int z) {
	for (int i = y; i <= y + 5; i++) {
		this->insertCube(TexCube(x, i, z, 1.0f, Tree));
	}
	for (int n = 3; n > 0; n--) {
		for (int i = x - n; i <= x + n; i++) {
			for (int j = z - n; j <= z + n; j++) {
				this->insertCube(TexCube(i, y + 6 + (3 - n), j, 1.0f, Leaf));
			}
		}
	}
}

void CubeManager::buildDiamondBuilding(int x, int y, int z) {
	for (int k = y; k < y + 9; k++) {
		for (int i = x; i < x + 5; i++) {
			for (int j = z; j < z + 5; j++) {
				this->insertCube(TexCube(i, k, j, 1.0f, Diamond));
			}
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			this->insertCube(TexCube(x + i + 1, y + 9, z + j + 1, 1.0f, Diamond));
		}
	}
	this->insertCube(TexCube(x, y + 9, z + 2, 1.0f, Diamond));
	this->insertCube(TexCube(x + 2, y + 9, z, 1.0f, Diamond));
	this->insertCube(TexCube(x + 2, y + 9, z + 4, 1.0f, Diamond));
	this->insertCube(TexCube(x + 4, y + 9, z + 2, 1.0f, Diamond));
	this->insertCube(TexCube(x + 2, y + 1, z, 1.0f, RedSand));
	this->insertCube(TexCube(x + 2, y + 2, z, 1.0f, RedSand));
	this->insertCube(TexCube(x + 1, y + 3, z, 1.0f, RedSand));
	this->insertCube(TexCube(x + 3, y + 3, z, 1.0f, RedSand));
	this->insertCube(TexCube(x + 2, y + 4, z, 1.0f, RedSand));
	this->insertCube(TexCube(x + 1, y + 5, z, 1.0f, RedSand));
	this->insertCube(TexCube(x + 3, y + 5, z, 1.0f, RedSand));
	this->insertCube(TexCube(x + 1, y + 6, z, 1.0f, RedSand));
	this->insertCube(TexCube(x + 2, y + 6, z, 1.0f, RedSand));
	this->insertCube(TexCube(x + 3, y + 6, z, 1.0f, RedSand));
}
