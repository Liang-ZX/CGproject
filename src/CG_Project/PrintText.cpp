#include "PrintText.h"
void PrintText(const char * str)
{
	static bool FirstCall = true;
	static GLuint list;
	if (FirstCall)
	{
		FirstCall = false;
		list = glGenLists(256);
		wglUseFontBitmaps(wglGetCurrentDC(),0, 256, list);
	}
	while (*str != '\0')
	{
		glCallList(list + *str);
		str++;
	}
}
void PrintTextAtPosition(const char * str, float x, float y)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glRasterPos2f(x, y);
	PrintText(str);
	glutSwapBuffers();

}
