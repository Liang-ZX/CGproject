#ifndef _COMMANDBOX_H
#define _COMMANDBOX_H

#include "glut.h"
#include "button.h"
#include "PrintText.h"

extern int quit_btn;
extern int g_window_width;
extern int g_window_height;
void updateView(int width, int height);

class CommandBox
{
private:
	GLint x;
	GLint y;
	GLint width;
	GLint height;
	void updateBox();
public:
	GLfloat box_percent;
	CommandBox();
	void create();
};


#endif