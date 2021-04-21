#include<iostream>
#include"Cube.h"

class CSkyBox
{
public:
	/** ���캯�� */
	CSkyBox();
	/** ��ʼ�� */
	bool Init();

	/** ��Ⱦ��� */
	void  CreateSkyBox(float x, float y, float z,
		float width, float height, float length);

private:

	Cube m_texture;   /**< ��պ����� */
	const unsigned int MAP_WIDTH = 1024;
	const unsigned int CELL_WIDTH = 16;
	const unsigned int MAP = MAP_WIDTH * CELL_WIDTH / 2;
};
