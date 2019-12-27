#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include "texture.h"
#include "glut.h"
#include <iostream>

using namespace std;

class SkyBox {
public:
	//mode
	GLint mode=cube;

	void Draw(string path)
	{
		Texture tex0 = Texture(path);

		glDisable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, tex0.getID());

		//environment texture
		//glEnable(GL_TEXTURE_GEN_S);
		//glEnable(GL_TEXTURE_GEN_T);
		//glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
		//glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
		
		//a cube
		if (mode==cube)
		{
			glBegin(GL_QUADS);

			glColor4ub(255, 255, 255, 255);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-0.5f, -0.5f, 0.5f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(0.5f, -0.5f, 0.5f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(0.5f, 0.5f, 0.5f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-0.5f, 0.5f, 0.5f);

			glEnd();
		}
		
		//sphere
		if (mode==sphere)
		{
			//glutWireSphere(1.0f, 40000, 40000);
			
			GLUquadric* quad;
			quad = gluNewQuadric();
			gluQuadricDrawStyle(quad, GLU_FILL);//多边形模拟
			gluQuadricNormals(quad, GLU_SMOOTH);						// 使用平滑法线
			gluQuadricTexture(quad, GLU_TRUE);						// 使用纹理

			gluSphere(quad, 1.0f, 32, 32);

			gluDeleteQuadric(quad);
			
		}
		
		glDisable(GL_TEXTURE_2D);
	}
};