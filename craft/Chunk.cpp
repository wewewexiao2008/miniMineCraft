#include "Chunk.h"
#pragma once


Chunk::Chunk()
{
	//初始化vector多维数组
	chunk_data.resize(chunk_x);
	for (size_t i = 0; i < chunk_x; i++)
	{
		chunk_data[i].resize(chunk_y);
		for (size_t j = 0; j < chunk_y; j++)
		{
			chunk_data[i][j].resize(chunk_z);
		}
	}
	//cube_manager 
	
}

Chunk::~Chunk()
{
}


void Chunk::print_test()
{
	for (size_t i = 0; i < chunk_x; i++)
	{
		for (size_t j = 0; j < chunk_y; j++)
		{
			for (size_t k = 0; k < chunk_z; k++)
			{
				std::cout << chunk_data[i][j][k];
			}
		}
	}
}

bool Chunk::create_chunk(CubeManager &cube_mgr)
{
	//cube_manager = cube_mgr;
	for (size_t i = 0; i < chunk_x; i++)
	{
		for (size_t j = 0; j < chunk_y; j++)
		{
			for (size_t k = 0; k < chunk_z; k++)
			{
				if (j<1)
				{
					//std::cout << "in create_chunk" << std::endl;
					chunk_data[i][j][k] = CubeTex::Soil;
					cube_mgr.insertCube(TexCube(i, j, k, 1.0f, Soil));
					//cube_manager.insertCube(TexCube(i,j, k,1.0f,Soil));
				}
				else
				{
					if ((i==4&&j<6)|| (k == 4 && j<6))
					{
						//std::cout << "in create_chunk" << std::endl;
						chunk_data[i][j][k] = CubeTex::Soil;
						//cube_mgr.insertCube(TexCube(i, j, k, 1.0f, Soil));
						//cube_manager.insertCube(TexCube(i, j, k, 1.0f, Soil));
					}
				}
			}
		}
	}
	return false;
}

bool Chunk::add_new(size_t x, size_t y, size_t z, CubeTex new_block)
{
	if (x > chunk_x || y > chunk_y || z > chunk_z) {
		std::cout << "out of map" << std::endl;
		return false;
	}
	else
	{
		chunk_data[x][y][z] = new_block;
		return true;
	}
}

bool Chunk::delete_cube(size_t x, size_t y, size_t z)
{
	return true;
}


CubeTex Chunk::get_data(size_t x, size_t y, size_t z) const
{
	if (x>=chunk_x || y>=chunk_y || z>=chunk_z)
	{
		return CubeTex::Empty;
	}
	else
	{
		return chunk_data[x][y][z];
	}
}
