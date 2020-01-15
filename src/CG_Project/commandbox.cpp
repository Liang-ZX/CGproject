#include "commandbox.h"

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
	glEnable(GL_DEPTH);
	glDisable(GL_LIGHTING);
	glColor3f(0.0f,0.0f, 0.0f);
	glRectf(0, 0, 10, 10);
	Btn[quit_btn].Render();
	Btn[screenshot_button].Render();
	//Btn[obj_button].Render();
	glEnable(GL_LIGHTING);
	glPopMatrix();
	glPopMatrix();

	showInformation(5, 650);//show the information

	updateView(g_window_width, g_window_height);
}

void CommandBox::updateBox()
{
	this->x = (GLint)(box_percent*g_window_width);
	this->y = 0;
	this->width = g_window_width - this->x;
	this->height = g_window_height;
}