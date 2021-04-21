#pragma once
#include"Point.h"
#include"Chunk.h"


/**
* @brief �����࣬���Դ�����chunk���ɵĵ�ͼ
*/
class Word
{
public:
	Word();
	/**
	* @param center:�������ĵ�Ĭ��Ϊopenglԭ��  
	* num_chunk�����ص����������1��chunkΪ1�㣬9��Ϊ2�㣬25Ϊ3��....��
	*/
	Word(Point center,size_t num_chunk);

	/**
	* @brief ��������
	*/
	void display_word();
	/**
	* @param a:��������ϵ�µ�ĳһ��
	* @brief ȡ����������ϵ��ĳһ��ķ������
	* @return ��ȡ�ɹ����ض�Ӧ��ţ����򷵻�-1
	*/
	int get_block(Point a);
	/**
	* @param x,y,z:��������ϵ�µ�ĳһ���x,y,z����
	* @brief ȡ����������ϵ��ĳһ��ķ������
	* @return ��ȡ�ɹ����ض�Ӧ��ţ����򷵻�-1
	*/
	int get_block(int x,int y,int z);

	/**
	* @param a:��������ϵ�µ�ĳһ��  new_block:�·���Ĵ���
	* @brief �޸���������ϵ��ĳһ��ķ������
	* @return �޸ĳɹ�����true
	*/
	bool set_block(Point a, size_t new_block);
	/**
	* @param x,y,z:��������ϵ�µ�ĳһ���x,y,z����  new_block:�·���Ĵ���
	* @brief �޸���������ϵ��ĳһ��ķ������
	* @return �޸ĳɹ����ض�true
	*/
	bool set_block(int x, int y, int z, size_t new_block);


	~Word();

private:
	//�ݶ������СΪword_max*word_max��С�ľ���
	const size_t word_max = 6;
	std::vector<std::vector<Chunk>> word_data;

};
