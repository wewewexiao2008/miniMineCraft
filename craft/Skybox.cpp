#include "SkyBox.h"
#include<gl\glut.h>
#include<iostream>



CSkyBox::CSkyBox(){ }

/** 天空盒初始化 */
bool CSkyBox::Init()
{
	return true;
}

/** 构造天空盒 */
void  CSkyBox::CreateSkyBox(float x, float y, float z,
	float box_width, float box_height,
	float box_length)
{
	/** 获得场景中光照状态 */
	GLboolean lp;
	glGetBooleanv(GL_LIGHTING, &lp);

	/** 计算天空盒长 宽 高 */
	float width = MAP * box_width /8;
	float height = MAP * box_height /8;
	float length = MAP * box_length /8;

	/** 计算天空盒中心位置 */
	float _x = - width / 2;
	float _y =  - height / 3;
	float _z =  - length / 2;

	glDisable(GL_LIGHTING);            /**< 关闭光照 */
	glDepthFunc(GL_LEQUAL);//输入深度值小于等于参考值时通过
	//glDepthMask(GL_FALSE);
									   /** 开始绘制 */
	glPushMatrix();
	glTranslatef(_x, _y, _z);

	/** 绘制背面 */
	glBindTexture(GL_TEXTURE_2D, m_texture.texSkybox_back);
	glBegin(GL_QUADS);
	/** 指定纹理坐标和顶点坐标 */
	//glNormal3f(0, 0, 1);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
	glEnd();

	/** 绘制前面 */
	glBindTexture(GL_TEXTURE_2D, m_texture.texSkybox_front);
	glBegin(GL_QUADS);
	/** 指定纹理坐标和顶点坐标 */
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z + length);
	glEnd();

	/** 绘制底面 */
	glBindTexture(GL_TEXTURE_2D, m_texture.texSkybox_down);
	glBegin(GL_QUADS);
	/** 指定纹理坐标和顶点坐标 */
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
	glEnd();

	/** 绘制顶面 */
	glBindTexture(GL_TEXTURE_2D, m_texture.texSkybox_up);
	glBegin(GL_QUADS);
	/** 指定纹理坐标和顶点坐标 */
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z);
	glEnd();

	/** 绘制左面 */
	glBindTexture(GL_TEXTURE_2D, m_texture.texSkybox_left);
	glBegin(GL_QUADS);
	/** 指定纹理坐标和顶点坐标 */
	//glNormal3f(1,0,0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
	glEnd();

	/** 绘制右面 */
	glBindTexture(GL_TEXTURE_2D, m_texture.texSkybox_right);
	glBegin(GL_QUADS);
	/** 指定纹理坐标和顶点坐标 */
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glEnd();
	glPopMatrix();                 /** 绘制结束 */

	if (lp)                         /** 恢复光照状态 */
		glEnable(GL_LIGHTING);

	glDepthFunc(GL_LESS);//输入深度值小于参考值时通过
	//glDepthMask(GL_TRUE);
}