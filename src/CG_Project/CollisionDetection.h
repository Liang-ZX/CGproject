#pragma once

bool check_collision(int sa, int sb);
bool check_view(int sa);
bool isLegalToMove(int cur,GLdouble posX, GLdouble posY, GLdouble posZ);
void changePosition(int cur);
void changeView();
bool isLegalToMoveView();
/******************常规的碰撞检测*********************/
/*
#include <float.h>
#include <limits.h>
class AABBBox {
	private:
	float minX;//x轴最小位置
	float maxX;//x轴最大位置
	float minY;//y轴最小位置
	float maxY;//y轴最大位置
	float minZ;//z轴最小位置
	float maxZ;//z轴最大位置

public:
	AABBBox(float vertices[])
	{
		init();
		findMinAndMax(vertices);
	}

	AABBBox(float minX, float maxX, float minY, float maxY, float minZ, float maxZ)
	{
		this->minX = minX;
		this->maxX = maxX;
		this->minY = minY;
		this->maxY = maxY;
		this->minZ = minZ;
		this->maxZ = maxZ;
	}
	//初始化包围盒的最小以及最大顶点坐标
    void init()
	{
		minX = FLT_MIN;
		maxX = FLT_MAX;
		minY = FLT_MIN;
		maxY = FLT_MAX;
		minZ = FLT_MIN;
		maxZ = FLT_MAX;
	}
	//获取包围盒的实际最小以及最大顶点坐标
	 void findMinAndMax(float vertices[])
	{
		for (int i = 0; i < 2; i++)
		{
			//判断X轴的最小和最大位置
			if (vertices[i * 3] < minX)
			{
				minX = vertices[i * 3];
			}
			if (vertices[i * 3] > maxX)
			{
				maxX = vertices[i * 3];
			}
			//判断Y轴的最小和最大位置
			if (vertices[i * 3 + 1] < minY)
			{
				minY = vertices[i * 3 + 1];
			}
			if (vertices[i * 3 + 1] > maxY)
			{
				maxY = vertices[i * 3 + 1];
			}
			//判断Z轴的最小和最大位置
			if (vertices[i * 3 + 2] < minZ)
			{
				minZ = vertices[i * 3 + 2];
			}
			if (vertices[i * 3 + 2] > maxZ)
			{
				maxZ = vertices[i * 3 + 2];
			}
		}
	}
	//获得物体平移后的AABB包围盒
	 void getCurrAABBBox(float currPosition[])
	{
		 this->minX + currPosition[0];
		 this->maxX + currPosition[0];
		 this->minY + currPosition[1];
		 this->maxY + currPosition[1];
		 this->minZ + currPosition[2];
		this->maxZ + currPosition[2];
	}
};
*/


