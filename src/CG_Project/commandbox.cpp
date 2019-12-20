#include "project.h"

CommandBox commandbox;

CommandBox::CommandBox()
{
	this->x = 0.85*g_window_width;
	this->y = 0;
	this->width = g_window_width - this->x;
	this->height = g_window_height;
}

void CommandBox::create()
{
	glPushMatrix();
	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glPushMatrix();
	glLoadIdentity();									// Reset The Projection Matrix
	glOrtho(0, 10, 0, 10, -100, 100);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glViewport(x, y, width, height);						// Reset The Current Viewport
	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 0.0f, 0.0f);
	//glRectf(this->x, this->y, this->x+this->width, this->y+this->height);
	glRectf(0, 0, 10, 10);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glViewport(0, 0, this->x, g_window_height);
}