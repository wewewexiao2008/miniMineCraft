#pragma once
#include "Point.h"
#include "coll_dete.h"

#define PI 3.1415926535898
/**
* @brief ������
* @TODO �Ժ��ǲ�������һ��������Ļ��࣬Ȼ�����ǣ����񣬿�������ȥ�̳��أ���
*/
class Man
{
public:
	///������С
	float basic_size;
	///�ٶ�
	float speed;
	Point hair_scale, head_scale, thigh_scale, body_scale, arm_scale, eye_scale, mouth_scale;
	Point head, hair, body, thighL, thighR, armL, armR, eyeL, eyeR, mouth;
	//Point* bodyArray[] = { &head, &hair, &body, &thighL, &thighR, &armL, &armR, &eyeL, &eyeR, &mouth };

	float x, y, z;
	float vangle;  // �ٶ�ƫ��
	float ltangle; // ����ƫ��
	float rtangle;// ����ƫ��
	float laangle;// ���ƫ��
	float raangle; // �ұ�ƫ��
	bool move;


public:
	/// ���캯��
	Man();

	//@TODO �˶���غ���������ײ��⡣������Ӧ�����������������չ������������⣩
	/**
	* @brief ������ǰ�ƶ�
	* @return �������ƶ��򷵻�false
	*/
	bool forward(Chunk &world);
	/**
	* @brief ��������ƶ�
	* @return �������ƶ��򷵻�false
	*/
	bool back(Chunk &world);
	/**
	* @brief ���������ƶ�
	* @return �������ƶ��򷵻�false
	*/
	bool left(Chunk &world);
	/**
	* @brief ���������ƶ�
	* @return �������ƶ��򷵻�false
	*/
	bool right(Chunk &world);
	
	/**
	* @brief ������Ծ
	* @return �������ƶ��򷵻�false
	*/
	bool jump();
	
	/**
	* @brief ���������С
	*/
	void resetSize(float new_basic) 
	{
		this->basic_size = new_basic;
		reset();
	}

	/**
	* @brief �Ƿ������ƶ�
	* @return �����ƶ�����true
	*/
	bool is_moving();
	
	/**
	* @brief �ı�move��־
	*/
	void set_move(bool move);

	/**
	* @brief �趨�������꣬Ҳ�����趨�ĳ�ʼλ�ã�������^_^��
	*/
	void setLocation(float x, float y, float z) 
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	/**
	* @brief ����ˢ�º���
	*/
	void refresh();

	/**
	* @brief ����������ʾ����
	*/
	void reset()
	{
		// ��������
		head_scale = Point(0.5, 0.5, 0.75, basic_size);
		body_scale = Point(0.3, 1.25, 0.75, basic_size);
		eye_scale = Point(0.2, 0.2, 0.2, basic_size);
		mouth_scale = Point(0.2, 0.2, 0.5, basic_size);
		hair_scale = Point(head_scale.x, 0.3, head_scale.z, basic_size); // ͷ��xz��ͷ��ͬ
		thigh_scale = Point(body_scale.x, 1.4, body_scale.z / 2, basic_size); // ��x������ͬ��zΪ���һ��
		arm_scale = Point(body_scale.x, body_scale.y, 0.3, basic_size); //�ֱ�xy������ͬ

																		// ���λ�ÿ���
		head = Point(0, thigh_scale.y + body_scale.y + head_scale.y / 2, 0, basic_size);
		hair = Point(0, thigh_scale.y + body_scale.y + head_scale.y + hair_scale.y / 2, 0, basic_size);
		body = Point(0, thigh_scale.y + body_scale.y / 2, 0, basic_size);
		thighL = Point(0, thigh_scale.y / 2, -thigh_scale.z / 2, basic_size);
		thighR = Point(0, thigh_scale.y / 2, thigh_scale.z / 2, basic_size);
		armL = Point(0, thigh_scale.y + arm_scale.y / 2, -(arm_scale.z + body_scale.z) / 2, basic_size);
		armR = Point(0, thigh_scale.y + arm_scale.y / 2, (arm_scale.z + body_scale.z) / 2, basic_size);
		eyeL = Point(head_scale.x / 2, thigh_scale.y + body_scale.y + head_scale.y / 2, -(eye_scale.z / 2 + 0.1),
			basic_size);
		eyeR = Point(head_scale.x / 2, thigh_scale.y + body_scale.y + head_scale.y / 2, (eye_scale.z / 2 + 0.1),
			basic_size);
		mouth = Point(head_scale.x / 2, thigh_scale.y + body_scale.y + head_scale.y / 2 - 0.1, 0, basic_size);
	}

	/**
	* @brief ���ﶯ����־ˢ��
	* @TODO ���������
	*/
	void refresh_ini(int c);
private:
	///��ײ�����
	Collision coll_check;
	///
	/// ��Ծ����
	bool jumping;
	bool falling;
	float jump_speed;
	float fall_speed;
	const float max_height = 3.0;
	const float ground_height = 1.00;
	const int delay_time = 12;
	///����������
	bool left_forward;
	bool right_forward;
	bool look_from_left;

private:
	/**
	* @��ʼ����
	*/
	void _ini();
};