#ifndef _STICK_H
#define _STICK_H
#include "glut.h"
#include "math.h"
#include "sphere.h"
#include <vector>

extern GLfloat ctrlpointsA[3][4];
extern int g_window_width;
extern int g_window_height;

class Stick
{
private:
	int id;
	bool doublebond;
	// generate the stick according to the corresponding spheres
	Sphere sp1;
	Sphere sp2;	

	GLfloat color[3];
	GLfloat radius;
	MATERIAL stMaterial;
	// binding light,etc to be added

public:
	static int count;
	static int stickcreate(Sphere sp1, Sphere sp2);
	Stick() {};
	Stick(int id, Sphere sp1, Sphere sp2)
	{
		this->id = id;
		this->sp1 = sp1;
		this->sp2 = sp2;
		this->doublebond = false;
		for (int i = 0; i < 3; i++)color[i] = 0.0f;
		radius = 0.0f;
		stMaterial.ambient[0] = 0.1;
		stMaterial.ambient[1] = 0.1;
		stMaterial.ambient[2] = 0.1;
		stMaterial.ambient[3] = 1.0;
		stMaterial.diffuse[0] = 1.0;
		stMaterial.diffuse[1] = 1.0;
		stMaterial.diffuse[2] = 1.0;
		stMaterial.diffuse[3] = 1.0;
		stMaterial.specular[0] = 0.0;
		stMaterial.specular[1] = 0.0;
		stMaterial.specular[2] = 0.0;
		stMaterial.specular[3] = 1.0;
		stMaterial.shininess = 100.0;
	}

	void setRadius(GLfloat r) { radius = r; }

	void setColor(GLfloat r, GLfloat g, GLfloat b)
	{
		color[0] = r;
		color[1] = g;
		color[2] = b;
	}

	void setDoublebone(bool state)
	{
		doublebond = state;
	}

	// draw by parametric equation
	void Draw(GLint iSlices, GLint iStacks);

	MATERIAL mat(){ return stMaterial; }
};
extern std::vector<Stick> StickVector;

#endif