#include "project.h"
#include "objFile.h"
#include "PrintText.h"

float fTranslate = 0.0f;
float fRotate = 0.0f;
float fScale = 1.0f;	// set inital scale value to 1.0f

bool bPersp = true;
bool bAnim = false;
bool bLoad = false;
GLdouble rotate_theta = 0.0f;

int wHeight = 0;
int wWidth = 0;
extern int move_sphere, move_stick;
//fullscreen
bool g_fullscreen = false;// 全屏标志缺省，缺省设定成全屏模式
int g_window_width = 700;
int g_window_height = 600;

//gamestate
int gameState = GAMESTART;

//background
SkyBox sky;
int backgroundid = 1;
int nobackground = 0;

// used to indicate click to draw a new sphere or stick
int drawNewSphere = 0;
int drawNewStick = 0;

//Sphere
int sp1;
int sp2;
int sphereid_now;

//Stick
int st1;
int stickid_now;

//texture
string othertexture[10] = { "othertexture\\start_image.bmp" , "othertexture\\background.bmp","othertexture\\background2.bmp",
"othertexture\\background3.bmp","othertexture\\background4.bmp","othertexture\\background5.bmp" };
string sticktexture[10] = { "sticktexture\\stick.bmp" };
//string spheretexture[20] = { "spheretexture\\sun.bmp" , "spheretexture\\earth.bmp" , "spheretexture\\jupiter.bmp"
//, "spheretexture\\mars.bmp","spheretexture\\mercurial.bmp","spheretexture\\moon.bmp" ,"spheretexture\\neptune.bmp"
//,"spheretexture\\pluto.bmp", "spheretexture\\saturn.bmp","spheretexture\\vranus.bmp" ,"spheretexture\\venus.bmp" };

string spheretexture[20] = { "spheretexture\\red.bmp", "spheretexture\\pink.bmp", "spheretexture\\blue.bmp",
"spheretexture\\orange.bmp","spheretexture\\yellow.bmp","spheretexture\\brown.bmp" ,"spheretexture\\purple.bmp",
};



string sticktex = sticktexture[0];
//string spheretex1 = texture[1];
//string spheretex2 = texture[2];

string spheretex[20];//初始状态没有纹理

void initialize(void)
{
	initLight();
	quit_btn = Button::create(0, 9.5);
	screenshot_button = Button::create(0, 9);
	obj_button = Button::create(0, 8.5);
}

static void draw_testscene(void)
{
	initialize();

	sp1 = Sphere::spherecreate(1.1, 0.0, 0.0);
	sp2 = Sphere::spherecreate(-1.0, 0.0, 0.0);
	SphereVector[sp1].setRadius(1);
	SphereVector[sp2].setRadius(0.5);
	st1 = Stick::stickcreate(sp1, sp2);
	StickVector[st1].setColor(1.0, 1.0, 1.0);
	StickVector[st1].setRadius(0.13);
}

void main_menu(int value) {

	//printf("size : %d\n", SphereVector.size());

	if (value == 1) {//clear screen
		initialize();
		SphereVector.erase(SphereVector.begin(), SphereVector.end());
		Sphere::count = 0;
		StickVector.erase(StickVector.begin(), StickVector.end());
		Stick::count = 0;
	}

	if (value == 2) {//start draw
		glClear(GL_COLOR_BUFFER_BIT);
		glutSwapBuffers();
		gameState = MAINWINDOW;
	}
	if (value == 3) {//change background
		backgroundid++;
		if (backgroundid == 6) backgroundid = 1;
	}
	if (value == 4) {//clear background
		nobackground = (nobackground == 0) ? 1 : 0;
	}
	if (value == 20) {//exit
		exit(0);
	}
}

static int texture_id[200] = { 0 };

void texture_menu(int value)
{
	srand((unsigned)time(NULL));
	switch (value)
	{
	case 4:
		spheretex[sphereid_now] = spheretexture[texture_id[sphereid_now]];
		texture_id[sphereid_now] = (texture_id[sphereid_now] + 1) % 8;
		//spheretex1 = texture[rand()%5];
		//spheretex2 = texture[rand() % 5];
		break;
		//case 5:
			//spheretex1 = texture[1];
			//spheretex2 = texture[rand() % 5];
			//break;
	}
}

void size_menu(int value)
{
	switch (value)
	{
	case 10:
		SphereVector[sphereid_now].setRadius(SphereVector[sphereid_now].getRadius() + 0.1);
		break;
	case 11:
		if (SphereVector[sphereid_now].getRadius() > 0.4)
		{
			SphereVector[sphereid_now].setRadius(SphereVector[sphereid_now].getRadius() - 0.1);
		}
		break;
	}
}

void draw_menu(int value)
{
	switch (value)
	{
	case 16:
		drawNewSphere = 1;
		break;
	case 17:
		drawNewStick = 2; // indicates that 2 sphere should be clicked 
		break;
	}
}

void zoom_menu(int value)
{
	switch (value)
	{
	case 21:
		eye[2] += -0.5;
		r_eye = sqrt(eye[0] * eye[0] + eye[1] * eye[1] + eye[2] * eye[2]);
		//center[2] += -0.5;
		break;
	case 22:
		eye[2] += 0.5;
		r_eye = sqrt(eye[0] * eye[0] + eye[1] * eye[1] + eye[2] * eye[2]);
		//center[2] += 0.5;
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
	Texture tex = Texture(othertexture[0]);
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

void Draw_Scene()
{
	glShadeModel(GL_SMOOTH);
	//background
	//Background(backgroundtex);
	glRotatef(rotate_theta, 0, 0, 1.0f);
	unsigned int itr;
	
	if (bLoad) {
		myObjLoader obj0("sphere.obj", 3);
		obj0.Draw();
	}
	
	if (SphereVector.size() > 0)
	{
		for (itr = 0; itr < SphereVector.size(); itr++)
		{
			//if (mode == GL_SELECT)
				//glLoadName(itr);
			SetSphereTexture(spheretex[itr], SphereVector[itr]);
			SphereVector[itr].Draw(150, 200);
			glDisable(GL_TEXTURE_2D);
		}
	}
	
	if (StickVector.size() > 0)
	{
		for (itr = 0; itr < StickVector.size(); itr++)
		{
			SetStickTexture(sticktex, StickVector[itr]);
			StickVector[itr].Draw(300, 300);
			glDisable(GL_TEXTURE_2D);
		}
	}
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
	glViewport(0, 0, draw_width, height);

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
float r_eye = 8.0;

void redraw()
{
	//for debug
	//printf("spheresize : %d, sticksize : %d\n", SphereVector.size(), StickVector.size());

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0, 0, 0, 0);
	glLoadIdentity();									// Reset The Current Modelview Matrix

	changeLight();
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
		if(nobackground) glClearColor(1.0, 1.0, 1.0, 0.0);
		else {
			string backgroundtex = othertexture[backgroundid];
			Background(backgroundtex);
		}
		Draw_Scene();						// Draw Scene	

		commandbox.create();
		//showInformation(700,500);
		button_control();
		
		//printf("sphereid: %d\n", sphereid_now);
	}
	else if (gameState == GAMEEND)
	{
		exit(0);
	}
	if(bAnim) rotate_theta += 4;
	glutSwapBuffers();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowPosition(300, 100);
	glutInitWindowSize(g_window_width, g_window_height);
	int windowHandle = glutCreateWindow("3D Material Structure");

	draw_testscene();
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
	glutAddMenuEntry("Change texture", 4);
	//glutAddMenuEntry("earth texture", 5);

	int sub_menu3 = glutCreateMenu(draw_menu);
	glutAddMenuEntry("Draw a new sphere", 16);
	glutAddMenuEntry("Draw a new stick", 17);

	int sub_menu4 = glutCreateMenu(zoom_menu);
	glutAddMenuEntry("Zoom in", 21);
	glutAddMenuEntry("Zoom out", 22);

	glutCreateMenu(main_menu);//注册菜单回调函数

	glutAddMenuEntry("Clear Screen", 1);//添加菜单项
	//glutAddMenuEntry("Start Game", 2);

	glutAddMenuEntry("Change Background", 3);
	glutAddMenuEntry("Show/Clear Background", 4);

	glutAddSubMenu("Size", sub_menu1);
	glutAddSubMenu("Texture", sub_menu2);
	//glutAddMenuEntry("Exit", 20);
	glutAddSubMenu("Draw", sub_menu3);
	glutAddSubMenu("Zoom", sub_menu4);

	glutAttachMenu(GLUT_RIGHT_BUTTON);//把当前菜单注册到指定的鼠标键

	glutMainLoop();
	return 0;
}
