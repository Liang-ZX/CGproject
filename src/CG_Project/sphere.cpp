#include "sphere.h"

std::vector<Sphere> SphereVector;

int Sphere::count = 0;

int Sphere::spherecreate(float x, float y, float z)	//called only once for each ball, so not in ���ƹ���
{													//sphere.draw should be called additionally
	Sphere tmpsp = Sphere(count++);
	tmpsp.setColor(1.0, 1.0, 1.0);
	tmpsp.setPosition(x, y, z);
	tmpsp.setRadius(0.5);
	SphereVector.push_back(tmpsp);
	return count-1;
}