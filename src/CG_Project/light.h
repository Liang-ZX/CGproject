#include "glut.h"

class Light
{
private:
	int id;
	GLfloat position[4];
	GLfloat ambient[4];		//������
	GLfloat diffuse[4];		//������
	GLfloat specular[4];	//���淴��

public:
	Light(){}
	Light(int id)
	{
		this->id = id;
		for (int i = 0; i < 4; i++)
		{
			position[i] = 0.0f;
			ambient[i] = 0.0f;
			diffuse[i] = 0.0f;
			specular[i] = 0.0f;
		}
	}
	// typeΪ0ʱ����ʾ(x,y,z)����ķ����Դ��typeΪ1ʱ����ʾ(x,y,z)����ĵ��Դ
	void setPosition(GLfloat x, GLfloat y, GLfloat z, GLfloat type)
	{
		position[0] = x;
		position[1] = y;
		position[2] = z;
		position[3] = type;
	}
	void changePosition(GLfloat x, GLfloat y, GLfloat z) {
		position[0] +=x;
		position[1] += y;
		position[2] += z;
		printf("%f %f %f\n", position[0], position[1], position[2]);
	}
	void changeType(GLfloat type) {
		if (type == 0 || type == 1)
			position[3] = type;
	}
	//a��͸����
	void setAmbient(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
	{
		ambient[0] = r;
		ambient[1] = g;
		ambient[2] = b;
		ambient[3] = a;
	}
	void setDiffuse(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
	{
		diffuse[0] = r;
		diffuse[1] = g;
		diffuse[2] = b;
		diffuse[3] = a;
	}
	void setSpecular(GLfloat r, GLfloat g, GLfloat b, GLfloat a)
	{
		specular[0] = r;
		specular[1] = g;
		specular[2] = b;
		specular[3] = a;
	}
	void LightOn()
	{
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0 + id);
		// GL_LIGHTx = 0x4000 + x = GL_LIGHT0 + x
		glLightfv(GL_LIGHT0 + id, GL_POSITION, position);
		glLightfv(GL_LIGHT0 + id, GL_AMBIENT, ambient);
		glLightfv(GL_LIGHT0 + id, GL_DIFFUSE, diffuse);
		glLightfv(GL_LIGHT0 + id, GL_SPECULAR, specular);
	}
};