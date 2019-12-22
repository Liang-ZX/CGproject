#ifndef _COMMANDBOX_H
#define _COMMANDBOX_H

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