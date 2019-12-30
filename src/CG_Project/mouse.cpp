#include "mouse.h"

extern int g_window_width, g_window_height, gameState, sphereid_now, stickid_now;
float yaw = 0, pitch = 0;
float mouseX, mouseY;
int tmp_index;
//used to designate the 2 spheres corresponding to the stick 
int tmpSp1 = -1;
int tmpSp2 = -1; 
void MousFunc(int button, int state, int x, int y)
{
	mouseX = x;
	mouseY = y;
	//
	GLint viewport[4];
	GLdouble mvmatrix[16], projmatrix[16];
	GLint realy;
	GLdouble wx, wy, wz;
	//
	if (button == GLUT_LEFT_BUTTON) {

		//
		glGetIntegerv(GL_VIEWPORT, viewport);
		glGetDoublev(GL_MODELVIEW_MATRIX, mvmatrix);
		glGetDoublev(GL_PROJECTION_MATRIX, projmatrix);
		realy = viewport[3] - y - 1;
		printf("Coordinate at curosr are (%4d, %4d, %4d)\n", x, y, viewport[3]);
		gluUnProject(x, realy, 0, mvmatrix, projmatrix, viewport, &wx, &wy, &wz);
		printf("World coords at z=0 are (%f, %f, %f)\n", wx, wy, wz);
		//gluUnProject(x, realy, 1, mvmatrix, projmatrix, viewport, &wx, &wy, &wz);
		//printf("World coords at z=1 are (%f, %f, %f)\n", wx, wy, wz);
		//

		if (gameState == GAMESTART && state == GLUT_DOWN) {
			//change the gameState
			if (1.0*x / g_window_width >= 1.0 * 83 / 256 && 1.0*x / g_window_width <= 1.0 * 164 / 256
				&& 1.0*y / g_window_height >= 1.0 * 157 / 256 && 1.0*y / g_window_height <= 1.0 * 178 / 256)
				gameState = MAINWINDOW;
			if (1.0*x / g_window_width >= 1.0 * 99 / 256 && 1.0*x / g_window_width <= 1.0 * 148 / 256
				&& 1.0*y / g_window_height >= 1.0 * 224 / 256 && 1.0*y / g_window_height <= 1.0 * 240 / 256)
				gameState = GAMEEND;
		}
		if (gameState == MAINWINDOW) {
			switch (state)
			{
			case GLUT_DOWN:
				//left mouse down
				if (x > 0.85 * g_window_width)
				{
					Btn[0].OnMouseDown((x - 0.85*g_window_width)*10.0 / (0.15*g_window_width), y*10.0 / g_window_height);
					Btn[screenshot_button].OnMouseDown((x - 0.85*g_window_width)*10.0 / (0.15*g_window_width), y*10.0 / g_window_height);
					Btn[obj_button].OnMouseDown((x - 0.85*g_window_width)*10.0 / (0.15*g_window_width), y*10.0 / g_window_height);
					break;
				}
				else {
					GLuint pickBuffer[256];
					GLint viewport[4];

					glSelectBuffer(256, pickBuffer);
					glRenderMode(GL_SELECT);
					glInitNames();
					glMatrixMode(GL_PROJECTION);
					glPushMatrix();
					glLoadIdentity();

					glGetIntegerv(GL_VIEWPORT, viewport);
					gluPickMatrix(GLdouble(x), GLdouble(viewport[3] - y), 5, 5, viewport);

					//update view
					int height = g_window_height;
					int draw_width = commandbox.box_percent * g_window_width;
					
					float whRatio = (GLfloat)draw_width / (GLfloat)height;

					if (bPersp) {
						gluPerspective(75.0f, whRatio, 1.0f, 50.0f);
					}
					else {
						if (draw_width <= height)
						{
							gluOrtho2D(-3, 3, -3, 3.0 / whRatio);
						}
						else {
							gluOrtho2D(-3, 3 * whRatio, -3, 3);
						}
					}
					glMatrixMode(GL_MODELVIEW);
					redraw();
					glMatrixMode(GL_PROJECTION);
					glPopMatrix();
					glMatrixMode(GL_MODELVIEW);
					GLint hits = glRenderMode(GL_RENDER);
					GLuint *ptr = pickBuffer;
					GLuint hitname;
					unsigned int min_dist = 0xffffffff;
					tmp_index = -1;
					while (hits != 0)
					{
						hitname = *ptr;
						ptr += 3;
						if (hitname != 0)
						{
							if (*(ptr - 2) < min_dist)
							{
								min_dist = *(ptr - 2);
								tmp_index = *ptr;
							}
						}
						ptr+=hitname;
						hits--;
					}
					if (tmp_index < 100)
					{
						printf("Sphere: %d\n", tmp_index);
						if (tmp_index != -1)
						{
							sphereid_now = tmp_index;
							//printf("sphereid: %d\n", sphereid_now);
							//SphereVector[tmp_index].setRadius(SphereVector[tmp_index].getRadius()+0.1);	
						}
					}
					else if (tmp_index < 200)
					{
						printf("Stick: %d\n", tmp_index - 100);
						stickid_now = tmp_index - 100;
					}
				}

				//draw new sphere
				if (drawNewSphere == 1) {
					int spnew;
					spnew = Sphere::spherecreate(wx, wy, wz);
					SphereVector[spnew].setRadius(1);
					drawNewSphere = 0;
				}

				if (drawNewStick == 2) {
					tmpSp1 = tmp_index < 100 ? tmp_index : -1;
					if (tmpSp1 != -1)drawNewStick--;
				}
				if (drawNewStick == 1) {
					tmpSp2 = tmp_index < 100 ? tmp_index : -1;
					if (tmpSp2 != -1 && tmpSp2 != tmpSp1) {
						int stnew;
						stnew = Stick::stickcreate(SphereVector[tmpSp1], SphereVector[tmpSp2]);
						StickVector[stnew].setColor(1.0, 1.0, 1.0);
						StickVector[stnew].setRadius(0.13);
						tmpSp1 = -1;
						tmpSp2 = -1;
						drawNewStick = 0;
					}
				}

			case GLUT_UP:
				if (x > 0.85 * g_window_width)
				{
					Btn[0].OnMouseUp();
					Btn[screenshot_button].OnMouseUp();
					Btn[obj_button].OnMouseUp();
					break;
				}
			}
		}

	}
	/*
if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
{
	if (gameState == MAINWINDOW)
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
}*/

	return;
}

void PassiveMotion(int x, int y)
{
	if (gameState == MAINWINDOW)
	{
		yaw = yaw - 2 * PI * (x - mouseX) / wWidth;
		pitch = pitch + PI * (y - mouseY) / wHeight;
		if (pitch >= PI / 2)
			pitch = PI / 2 - 0.02;
		else if (pitch <= -PI / 2)
			pitch = -PI / 2 + 0.02;
		mouseX = x;
		mouseY = y;
		/*eye[0] = 8 * sin(yaw);
		eye[1] = 8 * cos(yaw) * sin(pitch);
		eye[2] = 8 * cos(yaw) * cos(pitch);*/
		r_eye = sqrt(eye[0] * eye[0] + eye[1] * eye[1] + eye[2] * eye[2]);
		eye[0] = r_eye * sin(yaw);
		eye[1] = r_eye * cos(yaw) * sin(pitch);
		eye[2] = r_eye * cos(yaw) * cos(pitch);
		redraw();
	}
}