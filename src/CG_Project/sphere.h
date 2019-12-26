#ifndef _SPHERE_H
#define _SPHERE_H
#include "glut.h"
#include <cmath>
#include "material.h"
#include "define.h"
#include <vector>
using namespace std;

class Sphere
{
private:
	int id;
	GLfloat position[3];
	GLfloat color[3];
	GLfloat radius;
	MATERIAL spMaterial;
	
	// binding light,etc to be added

public:
	static int count;
	Sphere(){};
	Sphere(int id)
	{
		this->id = id;
		for (int i = 0; i < 3; i++) {
			position[i] = 0.0f;
			color[i] = 0.0f;
		}
		radius = 0.0f;
		spMaterial.ambient[0] = 0.1;
		spMaterial.ambient[1] = 0.1;
		spMaterial.ambient[2] = 0.1;
		spMaterial.ambient[3] = 1.0;
		spMaterial.diffuse[0] = 1.0;
		spMaterial.diffuse[1] = 1.0;
		spMaterial.diffuse[2] = 1.0;
		spMaterial.diffuse[3] = 1.0;
		spMaterial.specular[0] = 0.0;
		spMaterial.specular[1] = 0.0;
		spMaterial.specular[2] = 0.0;
		spMaterial.specular[3] = 1.0;
		spMaterial.shininess = 100.0;
	}

	void setPosition(GLfloat x, GLfloat y, GLfloat z)
	{
		position[0] = x;
		position[1] = y;
		position[2] = z;
	}

	void setRadius(GLfloat r){ radius = r; }

	void setColor(GLfloat r, GLfloat g, GLfloat b)
	{
		color[0] = r;
		color[1] = g;
		color[2] = b;
	}

	// draw by parametric equation
	void Draw(GLint iSlices, GLint iStacks)
	{
		//glPushName(id);
		glPushMatrix();
		glEnable(GL_COLOR_MATERIAL);
		glTranslatef(position[0], position[1], position[2]);
		glColor3f(color[0], color[1], color[2]);

		GLfloat drho = (GLfloat)(PI) / (GLfloat)iStacks;
		GLfloat dtheta = 2.0f * (GLfloat)(PI) / (GLfloat)iSlices;
		GLfloat ds = 1.0f / (GLfloat)iSlices;
		GLfloat dt = 1.0f / (GLfloat)iStacks;
		GLfloat t = 1.0f;
		GLfloat s = 0.0f;
		GLint i, j;

		for (i = 0; i < iStacks; i++)
		{
			GLfloat rho = (GLfloat)i * drho;
			GLfloat srho = (GLfloat)(sin(rho));
			GLfloat crho = (GLfloat)(cos(rho));
			GLfloat srhodrho = (GLfloat)(sin(rho + drho));
			GLfloat crhodrho = (GLfloat)(cos(rho + drho));

			glBegin(GL_TRIANGLE_STRIP);
			s = 0.0f;
			for (j = 0; j <= iSlices; j++)
			{
				GLfloat theta = (j == iSlices) ? 0.0f : j * dtheta;
				GLfloat stheta = (GLfloat)(-sin(theta));
				GLfloat ctheta = (GLfloat)(cos(theta));

				GLfloat x = stheta * srho;
				GLfloat y = ctheta * srho;
				GLfloat z = crho;

				glTexCoord2f(s, t);
				glNormal3f(x, y, z);
				glVertex3f(x * radius, y * radius, z * radius);

				x = stheta * srhodrho;
				y = ctheta * srhodrho;
				z = crhodrho;
				glTexCoord2f(s, t - dt);
				s += ds;
				glNormal3f(x, y, z);
				glVertex3f(x * radius, y * radius, z * radius);
			}
			glEnd();

			t -= dt;
		}

		glPopMatrix();
		//glPopName();
	}
	static Sphere spherecreate(float x, float y, float z);

	GLfloat getX() { return position[0]; }
	GLfloat getY() { return position[1]; }
	GLfloat getZ() { return position[2]; }
	GLfloat getRadius(){ return radius; }
	MATERIAL mat(){ return spMaterial;}
};

extern vector<Sphere> SphereVector;

#endif
