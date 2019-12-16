#include "glut.h"
#include "math.h"
class Sphere
{
private:
	int id;
	GLfloat position[3];
	GLfloat color[3];
	GLfloat radius;
	
	// binding light,texture,etc to be added

public:
	Sphere(int id)
	{
		this->id = id;
		for (int i = 0; i < 3; i++) {
			position[i] = 0.0f;
			color[i] = 0.0f;
		}
		radius = 0.0f;
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
		glPushMatrix();

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
	}
};

