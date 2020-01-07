#include "mouse.h"
#include "viewmatrix.h"
#define BUFSIZE 512

extern int g_window_width, g_window_height, gameState, sphereid_now, stickid_now;
int move_sphere = 0, move_stick = 0;
float yaw = 0, pitch = 0;
float mouseX, mouseY;
int tmp_index;
//used to designate the 2 spheres corresponding to the stick 
int tmpSp1 = -1;
int tmpSp2 = -1; 
int NowRenderMode = GL_RENDER;
void MousFunc(int button, int state, int x, int y)
{
	mouseX = x;
	mouseY = y;
	//
	GLfloat winx, winy, winz;
	GLdouble posx, posy, posz;
	//

	if (button == GLUT_LEFT_BUTTON) {

		glPushMatrix();
		glGetIntegerv(GL_VIEWPORT, viewport);
		glGetDoublev(GL_MODELVIEW_MATRIX, mvmatrix);
		glGetDoublev(GL_PROJECTION_MATRIX, projmatrix);
		glPopMatrix();
		
		winx = x; winy = g_window_height - y; winz = 0;
		gluUnProject(winx, winy, winz, mvmatrix, projmatrix, viewport, &posx, &posy, &posz);

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

					glSelectBuffer(256, pickBuffer);
					glRenderMode(GL_SELECT);
					NowRenderMode = GL_SELECT;
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
					NowRenderMode = GL_RENDER;
					GLuint *ptr = pickBuffer;
					GLuint hitname;
					unsigned int min_dist = 0xffffffff;
					tmp_index = -1;
					printf("hits:%d\n", hits);
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
						{	move_sphere = 1;
							sphereid_now = tmp_index;
							//printf("sphereid: %d\n", sphereid_now);
							//SphereVector[tmp_index].setRadius(SphereVector[tmp_index].getRadius()+0.1);	
						}
					}
					else if (tmp_index < 200)
					{
						move_stick = 1;
						printf("Stick: %d\n", tmp_index - 100);
						stickid_now = tmp_index - 100;
					}
				}
				//printf("%d %d\n", move_sphere, move_stick);
				//draw new sphere
				if (drawNewSphere == 1) {
					int spnew = Sphere::spherecreate(0, 0, 0);
					changePosition(spnew);
					drawNewSphere = 0;
				}

				if (drawNewStick == 2) {
					tmpSp1 = tmp_index < 100 ? tmp_index : -1;
					if (tmpSp1 != -1)
						drawNewStick--;
				}
				if (drawNewStick == 1) {
					if(tmp_index!=tmpSp1 && tmp_index<100)tmpSp2 = tmp_index;
					if (tmpSp2 != -1 && tmpSp2 != tmpSp1 && SphereVector.size()>1) {
						int stnew = Stick::stickcreate(SphereVector[tmpSp1], SphereVector[tmpSp2]);
						printf("Stick %d created.\n", stnew);
						StickVector[stnew].setColor(1.0, 1.0, 1.0);
						StickVector[stnew].setRadius(0.13);
						tmpSp1 = -1;
						tmpSp2 = -1;
						drawNewStick = 0;
					}
				}
				if (tmp_index >= 100 && tmp_index < 200) {
					if (StickVector[tmp_index - 100].getDoubleBond() == TRUE) StickVector[tmp_index - 100].setDoublebone(FALSE);
					else StickVector[tmp_index - 100].setDoublebone(TRUE);
				}
				break;
			case GLUT_UP:
				move_sphere = 0;
				move_stick = 0;
				if (x > 0.85 * g_window_width)
				{
					Btn[0].OnMouseUp();
					Btn[screenshot_button].OnMouseUp();
					Btn[obj_button].OnMouseUp();
					break;
				}
				
				break;
			}
		}

	}
	return;
}

void PassiveMotion(int x, int y)
{
	GLint viewport[4];
	GLdouble modelview[16];
	GLdouble projection[16];
	GLdouble winX, winY, winZ;
	GLdouble posX, posY, posZ;

	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);
	float cx = SphereVector[sphereid_now].getX();
	float cy = SphereVector[sphereid_now].getY();
	float cz = SphereVector[sphereid_now].getZ();
	gluProject(cx, cy, cz, modelview, projection, viewport, &winX, &winY, &winZ);
	winX = (float)x;
	winY = (float)viewport[3] - (float)y;
	//glReadPixels(x, int(winY), 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &winZ);

	gluUnProject(winX, winY, winZ, modelview, projection, viewport, &posX, &posY, &posZ);
	//gluUnProject(winX, winY, 1.0, modelview, projection, viewport, &posX2, &posY2, &posZ2);
	//cout << posX << posY << posZ << endl;
	//printf("%d %d\n", move_sphere, move_stick);
	if (gameState == MAINWINDOW)
	{
		if (!move_sphere && !move_stick) {
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
			changeView();
			redraw();
		}
		else if (move_sphere) {
			if (isLegalToMove(sphereid_now,posX,posY,posZ))
				SphereVector[sphereid_now].setPosition(posX, posY, posZ);
		}
		else {
			;
		}
	}
}