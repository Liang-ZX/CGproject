#include "mouse.h"

extern int g_window_width, g_window_height, gameState;
float yaw = 0, pitch = 0;
float mouseX, mouseY;

void MousFunc(int button, int state, int x, int y)
{
	mouseX = x;
	mouseY = y;
	if (button == GLUT_LEFT_BUTTON) {
		if (gameState == GAMESTART && state == GLUT_DOWN) {
			//change the gameState
			if (1.0*x / g_window_width >= 1.0 *83/256 && 1.0*x / g_window_width <= 1.0 * 164/256
				&& 1.0*y / g_window_height >= 1.0 * 157/256 && 1.0*y / g_window_height <= 1.0 * 178/256)
				gameState = MAINWINDOW;
			if (1.0*x / g_window_width >= 1.0 * 99/256 && 1.0*x / g_window_width <= 1.0 * 148/256
				&& 1.0*y / g_window_height >= 1.0 * 224/256 && 1.0*y / g_window_height <= 1.0 * 240/256)
				gameState = GAMEEND;		
		}
		if (gameState == MAINWINDOW) {
			switch (state)
			{
			case GLUT_DOWN:
				//左键按下：
				if (x > 0.85 * g_window_width)
				{	
					Btn[0].OnMouseDown((x-0.85*g_window_width)*10.0/(0.15*g_window_width), y*10.0/g_window_height);
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
					unsigned int min_dist = 0xffffffff, tmp_index = -1;
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
					printf("捕获: %d\n", tmp_index);
					if (tmp_index != -1)
					{
						SphereVector[tmp_index].setRadius(SphereVector[tmp_index].getRadius()+0.1);	//换其他功能吧
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
		eye[0] = 8 * sin(yaw);
		eye[1] = 8 * cos(yaw) * sin(pitch);
		eye[2] = 8 * cos(yaw) * cos(pitch);
		redraw();
	}
}