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
void showInformation(int x, int y)
{
	char buffer[1024];
	strcpy_s(buffer, "\n");
	strcat_s(buffer, "MOUSE:\n LEFT BUTTON: click and pick\n RIGHT BUTTON: call out the menu\n DRAG MOUSE:  roam\n\n");
	strcat_s(buffer, "KEYBOARD:\n WSAD: viewpoint translate\n ZC: zoom in/out\n ");
	strcat_s(buffer, "IKJLM: light conversion;\n P: perspective transformation.\n Space: control rotation.\n X: load.\n F: screenshot.\n Q: quit.");
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION); 
	glPushMatrix();
	glLoadIdentity(); 
	glOrtho(0, 800, 0, 800, -1, 1);
	glMatrixMode(GL_MODELVIEW);		//Modelview
	glPushMatrix();
	glLoadIdentity();
	char button[20];
	char *c;
	glColor3f(0.0, 0.0, 0.0);
	glRasterPos2f(200, 765);
	strcpy_s(button, "quit");
	for (c = button; *c != '\0'; c++) {

		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
	//glColor3f(0.0, 0.0, 0.0);
	glRasterPos2f(50, 725);
	strcpy_s(button, "screenshot");
	for (c = button; *c != '\0'; c++) {

		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
	//glColor3f(0.0, 0.0, 0.0);
	/*glRasterPos2f(100, 690);
	strcpy_s(button, "export");
	for (c = button; *c != '\0'; c++) {

		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}*/

	int xx = x;
	int yy = y;
	int i = 0;
	glRasterPos2f(xx, yy);
	glColor3f(1.0, 1.0, 1.0);
	for (c = buffer; *c != '\0'; c++) {
		if ((i >= 14 && *c == ' ') || *c == '\n') {
			yy -= 30;
			if (*c == '\n') {
				yy -= 5;
			}
			glRasterPos2f(xx, yy);
			/*if (*c != '\n' && *c != ' ') {
				glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, '-');
			}*/
			
			i = 0;
		}
		//glColor3f(1.0, 1.0, 1.0);
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *c);
		i++;
	}
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
}