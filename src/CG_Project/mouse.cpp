#include "project.h"

float yaw = 0, pitch = 0;
float mouseX, mouseY;

void MousFunc(int button, int state, int x, int y)
{
	mouseX = x;
	mouseY = y;
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		GLuint pickBuffer[50];
		GLint viewport[4];

		glSelectBuffer(10, pickBuffer);
		glRenderMode(GL_SELECT);
		glInitNames();
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();

		glGetIntegerv(GL_VIEWPORT, viewport);
		gluPickMatrix(GLdouble(x), GLdouble(viewport[3] - y), 2.0, 2.0, viewport);

		if (bPersp)
			gluPerspective(45.0f, wWidth / wHeight, 0.1f, 100.0f);
		else
			glOrtho(-3, 3, -3, 3, -100, 100);
		glMatrixMode(GL_MODELVIEW);
		redraw();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		GLint hits = glRenderMode(GL_RENDER);
		GLuint *ptr = pickBuffer;
		while (hits != 0)
		{
			ptr += 4;
			hits--;
		}
	}

	return;
}

void PassiveMotion(int x, int y)
{
	yaw = yaw - 2 * PI * (x - mouseX) / wWidth;
	pitch = pitch + PI * (y - mouseY) / wHeight;
	if (pitch >= PI / 2)
		pitch = PI / 2 - 0.02;
	else if (pitch <= -PI / 2)
		pitch = -PI / 2 + 0.02;
	mouseX = x;
	mouseY = y;
	eye[0] = 8 * sin(yaw);
	eye[1] = 8 * cos(yaw) * sin(pitch);
	eye[2] = 8 * cos(yaw) * cos(pitch);
	redraw();
}