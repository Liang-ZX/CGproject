#ifndef	_VIEW_H_
#define	_VIEW_H_
#include "glut.h"
#include <math.h>
#include <iostream>
#include "define.h"
//#include "CollisionDetection.h"
#include "vector.h"
//#include "music.h"
class Position
{
public:
	int x, y;
	Position() { x = 0; y = 0; }
	void reset(int x_p, int y_p) { x = x_p; y = y_p; }
	Position operator-(Position &p1)
	{
		Position p2;
		p2.x = x - p1.x;
		p2.y = y - p1.y;
		return p2;
	}
};


class View {
private:
	float velocity;
	bool isJump;
	int count;
	//isLegalToMove canMove;
public:
	Vector3 eye;  //视点
	Vector3 neweye;
	Vector3 center;//视角中心
	Vector3 newcenter;
	Vector3 polar;
	static int viewRate;

	View()
	{
		reset();
	}
	static void setRate(float Rate)
	{
		viewRate = Rate;
	}
	void viewMove(int direction)
	{
		Vector3 Dir, M1, M2;
		Dir = center - eye;
		M1 = Dir.unit();
		M2 = M1.unit_inv();
		switch (direction)
		{
		case FORWARD:
		{
			//FSOUND_Stream_Play(FSOUND_FREE, footstep);
			neweye = eye + M1;
			newcenter = center + M1;
			/*if (canMove.judgeIsOkToMove(&neweye, &newcenter, eye, center))
			{
				eye = neweye;
				center = newcenter;
			}*/
			eye = neweye;
			center = newcenter;
			break;
		}
		case BACKWARD:
		{
			//FSOUND_Stream_Play(FSOUND_FREE, footstep);
			neweye = eye - M1;
			newcenter = center - M1;
			eye = neweye;
			center = newcenter;
			break;
		}
		case RIGHT:
		{
			//FSOUND_Stream_Play(FSOUND_FREE, footstep);
			neweye = eye - M2;
			newcenter = center - M2;
			eye = neweye;
			center = newcenter;
			break;
		}
		case LEFT:
		{
			//FSOUND_Stream_Play(FSOUND_FREE, footstep);
			neweye = eye + M2;
			newcenter = center + M2;
			eye = neweye;
			center = newcenter;
			break;
		}
		/*case JUMP:
		{
			if (!isJump)
			{
				FSOUND_Stream_Play(FSOUND_FREE, jump);
				canMove.setJump();
				isJump = true;
				velocity = 0.8f;
			}
			break;
		}*/
		}
	}

	void update()
	{
		if (count == 0)
		{
			neweye.x = eye.x;
			neweye.y = eye.y + velocity;
			neweye.z = eye.z;
			newcenter.x = center.x;
			newcenter.y = center.y + velocity;
			newcenter.z = center.z;
			count = 15;
			/*if (canMove.judgeIsOkToMove(&neweye, &newcenter, eye, center))
			{
				eye = neweye;
				center = newcenter;
				velocity = velocity - 0.05;
			}
			else {
				velocity = -0.05;
				isJump = false;
			}*/
			eye = neweye;
			center = newcenter;
			velocity = velocity - 0.05;
		}
		else
			count--;
	}

	void reset()
	{
		isJump = false;
		velocity = -0.05;
		eye.reset(3, -3, 15);
		neweye.reset(3, -3, 15);
		center.reset(0, -3, 0);
		newcenter.reset(0, -3, 0);
		polar.reset(sqrt(234), -90, 90);
		neweye = eye;
		newcenter = center;
	}
	void setView(float x, float y)
	{
		x /= viewRate;
		y /= viewRate;
		Vector3 Dir;
		GLfloat alpha, fy;                  /*和它的名字一样，不过是单位是弧度*/
											//x = x / 15;
											//y = y / 15;
		if ((polar.z + y) > 5.0f && (polar.z + y) < 175.0f)
		{     /*定义竖直偏角只能在5°到175°之间*/
			polar.y += x;                  /*根据鼠标移动的方向设置新的球坐标*/
			polar.z += y;

			if (polar.y > 360.0f) polar.y -= 360.0f;
			if (polar.y < 0.0f) polar.y += 360.0f;      /*将水平偏角锁定在0°到360°之间*/

			alpha = polar.y*PI / 180;
			fy = polar.z*PI / 180;               /*角度转弧度*/
			Dir.x = -1 * polar.x * sin(fy) * cos(alpha);       /*极坐标转直角坐标*/
			Dir.z = polar.x * sin(fy) * sin(alpha);
			Dir.y = -1 * polar.x * cos(fy);                 /*注意：竖直方向的是y轴*/
			center.x = eye.x + Dir.x;
			center.y = eye.y + Dir.y;
			center.z = eye.z + Dir.z;
		}
	}
};

int Vector3::moveRate = 0.5;
int View::viewRate = 20;


class Line {
public:
	Vector3 near_point, far_point;
	Line()
	{
		near_point.reset(0, 0, 0);
		far_point.reset(1, 0, 0);
	}

	void getLine(int mouse_x, int mouse_y)
	{
		GLdouble modelview[16];
		GLdouble projection[16];
		GLint viewport[4];
		glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
		glGetDoublev(GL_PROJECTION_MATRIX, projection);
		glGetIntegerv(GL_VIEWPORT, viewport); GLdouble world_x, world_y, world_z; // 获取近裁剪面上的交点
		gluUnProject((GLdouble)mouse_x, (GLdouble)mouse_y, 0.0,
			modelview, projection, viewport,
			&world_x, &world_y, &world_z);
		near_point.reset(world_x, world_y, world_z); // 获取远裁剪面上的交点
		gluUnProject((GLdouble)mouse_x, (GLdouble)mouse_y, 1.0,
			modelview, projection, viewport,
			&world_x, &world_y, &world_z);
		far_point.reset(world_x, world_y, world_z);
	}

	/*
	BOOLEAN isEvent(Vector3 eye, Vector3 point, double r) {
		Vector3 vec;
		vec = point - eye;
		if (getDistance(point) < r && vec.getLength() < 8)
			return true;
		else
			return false;
	}*/

	double getDistance(Vector3 point)
	{
		Vector3 v1, v2;
		double value;
		v1 = far_point - near_point;
		v2 = point - near_point;
		if (v1*v2 < 0) return 10.0;
		value = (1 - (v1*v2)*(v1*v2) / (v1.getSquareLength()*v2.getSquareLength()))*v2.getSquareLength();
		return sqrt(value);
	}
};

#endif