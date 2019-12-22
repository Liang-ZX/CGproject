#include "project.h"

extern int g_window_width;
extern int g_window_height;
CommandBox commandbox;

CommandBox::CommandBox()
{
	this->box_percent = 0.85;
	this->x = (GLint)(box_percent*g_window_width);
	this->y = 0;
	this->width = g_window_width - this->x;
	this->height = g_window_height;
}

void CommandBox::create()
{
	updateBox();
	glPushMatrix();
	glLoadIdentity();
	glViewport(x, y, width, height);

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix
	gluOrtho2D(0, 10, 0, 10);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 0.0f, 0.0f);
	//glRectf(this->x, this->y, this->x+this->width, this->y+this->height);
	glRectf(0, 0, 10, 10);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	glPopMatrix();

	updateView(g_window_width, g_window_height);
}

void CommandBox::updateBox()
{
	this->x = (GLint)(box_percent*g_window_width);
	this->y = 0;
	this->width = g_window_width - this->x;
	this->height = g_window_height;
}