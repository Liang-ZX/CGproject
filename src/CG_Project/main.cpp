#include "project.h"

float fTranslate = 0.0f;
float fRotate = 0.0f;
float fScale = 1.0f;	// set inital scale value to 1.0f

bool bPersp = true;
bool bAnim = false;

int wHeight = 0;
int wWidth = 0;

//fullscreen
bool g_fullscreen = false;// 全屏标志缺省，缺省设定成全屏模式
int g_window_width = 700;
int g_window_height = 600;

//gamestate
int gameState = GAMESTART;

//background
SkyBox sky;

//Sphere
Sphere sp1 = Sphere(1);
Sphere sp2 = Sphere(2);
float radius1 = 1;
float radius2 = 0.5;

//texture
string texture[20] = { "texturebmp\\stick.bmp", "texturebmp\\sun.bmp" , "texturebmp\\earth.bmp" ,
						"texturebmp\\start_image.bmp" };
string backgroundtex = texture[0];
string sticktex = texture[0];
string spheretex1 = texture[1];
string spheretex2 = texture[2];

void initialize(void)
{
	initLight();
	quit_btn = Button::create(0, 9.5);
	screenshot_button = Button::create(0, 9);
	obj_button = Button::create(0, 8.5);
}

void main_menu(int value) {

	if (value == 1) {//clear screen
		glClear(GL_COLOR_BUFFER_BIT);
		glutSwapBuffers();
		if (gameState != GAMESTART)
		{
			gameState = INITIAL;
		}
	}

	if (value == 2) {//start draw
		glClear(GL_COLOR_BUFFER_BIT);
		glutSwapBuffers();
		gameState = MAINWINDOW;
	}

	if (value == 20) {//exit
		exit(0);
	}

}

void texture_menu(int value)
{
	switch (value)
	{
	case 4:
		spheretex1 = texture[2];
		spheretex2 = texture[1];
		break;
	case 5:
		spheretex1 = texture[1];
		spheretex2 = texture[2];
		break;
	}
}

void size_menu(int value)
{
	switch (value)
	{
	case 10:
		radius1 += 0.1;
		break;
	case 11:
		if (radius1 > 0.4)
		{
			radius1 -= 0.1;
		}
		break;
	}
}

void SpecialKeys(int key, int x, int y)//fullscreen
{
	switch (key)
	{
	case GLUT_KEY_F1:
		g_fullscreen = !g_fullscreen;
		if (g_fullscreen)
		{
			g_window_width = glutGet(GLUT_WINDOW_WIDTH);
			g_window_height = glutGet(GLUT_WINDOW_HEIGHT);
			glutFullScreen();
		}
		else
		{
			g_window_width = 700;
			g_window_height = 600;
			glutReshapeWindow(g_window_width, g_window_height);
		}
		break;
	}
}

void Start()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(-7.5, 7.5, -5, 5, 0, 100);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glViewport(0, 0, g_window_width, g_window_height);
	Texture tex = Texture(texture[3]);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, tex.getID());
	glScalef(15, 10, 1);

	glBegin(GL_QUADS);
	{
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-0.5f, -0.5f, 0.5f);
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(0.5f, -0.5f, 0.5f);
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(0.5f, 0.5f, 0.5f);
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(-0.5f, 0.5f, 0.5f);
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void SetSphereTexture(string path, Sphere sp)
{
	Texture tex = Texture(path);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, tex.getID());
	glMaterialfv(GL_FRONT, GL_DIFFUSE, sp.mat().diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, sp.mat().specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, sp.mat().ambient);
	glMateriali(GL_FRONT, GL_SHININESS, sp.mat().shininess);
}

void SetStickTexture(string path, Stick st)
{
	Texture tex = Texture(path);
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, tex.getID());
	glMaterialfv(GL_FRONT, GL_DIFFUSE, st.mat().diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, st.mat().specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, st.mat().ambient);
	glMateriali(GL_FRONT, GL_SHININESS, st.mat().shininess);
}

void Draw_Leg()
{
	glScalef(1, 1, 3);
	glutSolidCube(1.0);
}

void Draw_Scene()
{
	glShadeModel(GL_SMOOTH);
	//baclground
	Background(backgroundtex);

	sp1.setColor(1.0, 1.0, 1.0);
	sp1.setPosition(1.1, 0.0, 0.0);
	sp1.setRadius(radius1);

	sp2.setColor(1.0, 1.0, 1.0);
	sp2.setPosition(-1.0, 0.0, 0.0);
	sp2.setRadius(0.5);

	SetSphereTexture(spheretex1, sp1);
	sp1.Draw(150, 200);
	glDisable(GL_TEXTURE_2D);

	SetSphereTexture(spheretex2, sp2);
	sp2.Draw(150, 200);
	glDisable(GL_TEXTURE_2D);

	Stick st = Stick(1, sp1, sp2);
	st.setColor(1.0, 1.0, 1.0);
	st.setRadius(0.13);

	SetStickTexture(sticktex, st);
	st.Draw(300, 300);
	glDisable(GL_TEXTURE_2D);
}

void updateView(int width, int height)
{
	g_window_width = width;
	g_window_height = height;
	int draw_width = commandbox.box_percent * width;

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

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
	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	if (draw_width <= height)
	{
		glViewport(0, 0, draw_width, height);
	}
	else {
		glViewport(0, 0, draw_width, height);
	}
}

void reshape(int width, int height)
{
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}

	wHeight = height;
	wWidth = width;

	updateView(wWidth, wHeight);
}

void idle()
{
	glutPostRedisplay();
}

float eye[] = { 0, 0, 8 };
float center[] = { 0, 0, 0 };

void redraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);
	glLoadIdentity();									// Reset The Current Modelview Matrix

	gluLookAt(eye[0], eye[1], eye[2],
		center[0], center[1], center[2],
		0, 1, 0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);

	if (gameState == GAMESTART)
	{
		//gameState = INITIAL;
		Start();
		//glutSolidCube(1.0);
		// used to test the MAINWINDOW
		//gameState = MAINWINDOW;
	}
	else if (gameState == MAINWINDOW)
	{
		Draw_Scene();						// Draw Scene	
		commandbox.create();
		button_control();
	}
	else if (gameState == GAMEEND)
	{
		exit(0);
	}

	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowPosition(300, 100);
	glutInitWindowSize(g_window_width, g_window_height);
	int windowHandle = glutCreateWindow("3D Material Structure");

	initialize();
	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutMouseFunc(MousFunc);
	glutMotionFunc(PassiveMotion);
	glutIdleFunc(idle);
	glutSpecialFunc(SpecialKeys);

	//rightbutton menu
	int sub_menu1 = glutCreateMenu(size_menu);
	glutAddMenuEntry("Increase", 10);
	glutAddMenuEntry("Decrease", 11);

	int sub_menu2 = glutCreateMenu(texture_menu);
	glutAddMenuEntry("sun texture", 4);
	glutAddMenuEntry("earth texture", 5);

	glutCreateMenu(main_menu);//注册菜单回调函数

	glutAddMenuEntry("Clear Screen", 1);//添加菜单项
	glutAddMenuEntry("Start Game", 2);
	glutAddSubMenu("Size", sub_menu1);
	glutAddSubMenu("Texture", sub_menu2);
	glutAddMenuEntry("Exit", 20);

	glutAttachMenu(GLUT_RIGHT_BUTTON);//把当前菜单注册到指定的鼠标键

	glutMainLoop();
	return 0;
}