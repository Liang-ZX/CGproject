#include "glut.h"

class Stick
{
private:
	int id;
	// generate the stick according to the corresponding spheres
	int SphereID1;
	int SphereID2;	

	GLfloat color[3];
	GLfloat radius;

	// binding light,texture,etc to be added

public:
	Stick(int id, int SphereID1, int SphereID2)
	{
		this->id = id;
		this->SphereID1;
		this->SphereID2;
		for (int i = 0; i < 3; i++)color[i] = 0.0f;
		radius = 0.0f;
	}

	void setColor(GLfloat r, GLfloat g, GLfloat b)
	{
		color[0] = r;
		color[1] = g;
		color[2] = b;
	}

	void setRadius(GLfloat r) { radius = r; }
};