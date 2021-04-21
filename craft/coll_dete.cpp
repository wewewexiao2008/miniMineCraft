#include "coll_dete.h"

Collision::Collision()
{
}

bool Collision::is_collision(Point a, Point b)
{
	
	return false;
}

bool Collision::is_collision(const float a_x, const float a_y, const float a_z,
	const float b_x, const float b_y, const float b_z, const Chunk &my_chunk)
{
	//所有浮点数都向上取整
	int x1 = (int)(a_x + 0.5);
	int y1 = (int)(a_y + 0.5);
	int z1 = (int)(a_z + 0.5);
	int x2 = (int)(b_x + 0.5);
	int y2 = (int)(b_y + 0.5);
	int z2 = (int)(b_z + 0.5);

	/*
	/////测试用////
	int t1 = my_chunk.get_data(x1, y1, z1);
	int t2 = my_chunk.get_data(x1, y1, z2);
	int t11 = my_chunk.get_data(x1, y2, z1);
	int t21 = my_chunk.get_data(x1, y2, z2);
	int tt1 = my_chunk.get_data(x2, y1, z1);
	int tt2 = my_chunk.get_data(x2, y1, z2);
	int tt11 = my_chunk.get_data(x2, y2, z1);
	int tt21 = my_chunk.get_data(x2, y2, z2);
	///////
	*/

	if (my_chunk.get_data(x1, y1, z1) == 0 && my_chunk.get_data(x1, y1, z2) == 0 &&
		my_chunk.get_data(x1, y2, z1) == 0 && my_chunk.get_data(x1, y2, z2) == 0 &&
		my_chunk.get_data(x2, y1, z1) == 0 && my_chunk.get_data(x2, y1, z2) == 0 &&
		my_chunk.get_data(x2, y2, z1) == 0 && my_chunk.get_data(x2, y2, z2) == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}
