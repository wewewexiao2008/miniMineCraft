#pragma once
#include<map>
#include<iostream>
#include<string>
#include"TexCube.h"
#include"AABB.h"

/**
* @brief 方块管理类
* 6.22 comment: Chunk形同虚设，直接用CubeManager进行世界操作
*/
class CubeManager 
{
public:

	CubeManager() {};

	~CubeManager() {};

	// 增加方块
	bool insertCube(const TexCube &texcube);

	bool deleteCube(const TexCube &texcube);

	bool isExist(std::string);

	bool isAround(std::string);

	// 绘制所有
	void createAllCube();

	/**
	* @brief 构建沙漠神庙
	*/
	void buildPyramid(int x, int y, int z);

	void buildannexBuilding(int x, int y, int z);

	/**
	* @brief 构建水池
	*/
	void buildPool(int x, int y, int z);
	/**
	* @brief 构建树木
	*/
	void buildTree(int x, int y, int z);

	void buildDiamondBuilding(int x, int y, int z);

	std::map<std::string, TexCube> cubeMap;
	std::map<std::string, AABB> aabbMap;
};

