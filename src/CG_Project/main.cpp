#include "project.h"

float fTranslate = 0.0f;
float fRotate = 0.0f;
float fScale = 1.0f;	// set inital scale value to 1.0f

bool bPersp = false;
bool bAnim = false;

int wHeight = 0;
int wWidth = 0;

int gameState = GAMESTART;

void initialize(void)
{
	initLight();
}

void Draw_Leg()
{
	glScalef(1, 1, 3);
	glutSolidCube(1.0);
}

void Draw_Scene()
{
	Sphere sp1 = Sphere(1);
	Sphere sp2 = Sphere(2);

	sp1.setColor(0.0, 0.0, 1.0);
	sp1.setPosition(1.1, 0.0, 0.0);
	sp1.setRadius(1);

	sp2.setColor(0.0, 1.0, 1.0);
	sp2.setPosition(-1.0, 0.0, 0.0);
	sp2.setRadius(0.5);

	sp1.Draw(150, 200);
	sp2.Draw(150, 200);
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
		//��ʼ����

		// used to test the MAINWINDOW
		gameState = MAINWINDOW;
	}
	else if (gameState == MAINWINDOW)
	{
		//������
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
	glutInitWindowSize(WIDTH,HEIGHT);
	int windowHandle = glutCreateWindow("3D Material Structure");

	initialize();
	glutDisplayFunc(redraw);
	glutReshapeFunc(reshape);	
	glutKeyboardFunc(key);
	glutMouseFunc(MousFunc);
	glutMotionFunc(PassiveMotion);
	glutIdleFunc(idle);

	glutMainLoop();
	return 0;
}