#pragma once
#include"Point.h"
#include"Chunk.h"


/**
* @brief 世界类，用以储存多个chunk构成的地图
*/
class Word
{
public:
	Word();
	/**
	* @param center:世界中心点默认为opengl原点  
	* num_chunk：加载的区块层数（1个chunk为1层，9个为2层，25为3层....）
	*/
	Word(Point center,size_t num_chunk);

	/**
	* @brief 绘制世界
	*/
	void display_word();
	/**
	* @param a:世界坐标系下的某一点
	* @brief 取得世界坐标系下某一点的方块代码
	* @return 获取成功返回对应编号，否则返回-1
	*/
	int get_block(Point a);
	/**
	* @param x,y,z:世界坐标系下的某一点的x,y,z坐标
	* @brief 取得世界坐标系下某一点的方块代码
	* @return 获取成功返回对应编号，否则返回-1
	*/
	int get_block(int x,int y,int z);

	/**
	* @param a:世界坐标系下的某一点  new_block:新方块的代码
	* @brief 修改世界坐标系下某一点的方块代码
	* @return 修改成功返回true
	*/
	bool set_block(Point a, size_t new_block);
	/**
	* @param x,y,z:世界坐标系下的某一点的x,y,z坐标  new_block:新方块的代码
	* @brief 修改世界坐标系下某一点的方块代码
	* @return 修改成功返回对true
	*/
	bool set_block(int x, int y, int z, size_t new_block);


	~Word();

private:
	//暂定世界大小为word_max*word_max大小的矩形
	const size_t word_max = 6;
	std::vector<std::vector<Chunk>> word_data;

};
