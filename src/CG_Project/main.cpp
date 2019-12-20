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
int g_window_width = 600;
int g_window_height = 600;

//gamestate
int gameState = GAMESTART;

//background
SkyBox sky;

//texture
string backgroundtex = "texturebmp\\stick.bmp";
string sticktex="texturebmp\\stick.bmp";
string spheretex1 = "texturebmp\\sun.bmp";
string spheretex2 = "texturebmp\\earth.bmp";

void initialize(void)
{
	initLight();
}

void SpecialKeys(int key, int x, int y)
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
		else glutReshapeWindow(g_window_width, g_window_height);
		break;
	}
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
	//baclground
	Background(backgroundtex);
	commandbox.create();

	Sphere sp1 = Sphere(1);
	Sphere sp2 = Sphere(2);

	sp1.setColor(1.0, 1.0, 1.0);
	sp1.setPosition(1.1, 0.0, 0.0);
	sp1.setRadius(1);

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
	st.Draw(300,300);
	glDisable(GL_TEXTURE_2D);
}

static void updateView(int width, int height)
{
	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	float whRatio = (GLfloat)width/(GLfloat)height;
	
	if (bPersp){
		gluPerspective(75.0f, whRatio, 1.0f, 50.0f);
	}
	else
	    glOrtho(-3 ,3, -3, 3,-100,100);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
}

void reshape(int width, int height)
{
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	wHeight = height;
	wWidth = width;

	updateView(wHeight, wWidth);
}

void idle()
{
	glutPostRedisplay();
}

float eye[] = {0, 0, 8};
float center[] = {0, 0, 0};

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
		gameState = INITIAL;
		// used to test the MAINWINDOW
		gameState = MAINWINDOW;
	}
	else if (gameState == MAINWINDOW)
	{
		Draw_Scene();						// Draw Scene	
	}
	else if (gameState == GAMEEND)
	{

	}

	glutSwapBuffers();
}



int main (int argc,  char *argv[])
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

	glutMainLoop();
	return 0;
}