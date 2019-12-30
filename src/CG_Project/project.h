#ifndef _PROJECT_H
#define _PROJECT_H

#include "texture.h"
#include "background.h"
#include "stdlib.h"
#include "mouse.h"
#include "glut.h"
#include "keyboard.h"
#include "light.h"
#include "initialize.h"
#include "define.h"
#include <vector>
#include <string.h>
#include <cstdio>
#include <ctime>
#include "SOIL.h"
#include "screenshot.h"

#include "sphere.h"
#include "stick.h"
#include "commandbox.h"
#include "glew.h"
#include "windows.h"
#include "button.h"
#include "button_control.h"
using namespace std;
//#include "view.h"

//screen height and width
extern int g_window_width;
extern int g_window_height;

extern float r_eye;
extern float eye[3];
extern float center[3];
extern int wHeight;
extern int wWidth;
extern bool bPersp;
extern bool bAnim;
extern int gameState;

// used to indicate click to draw a new sphere or stick
extern int drawNewSphere;
extern int drawNewStick;

extern CommandBox commandbox;

void initialize(void);
void reshape(int width, int height);
void idle();
void redraw();
void updateView(int width, int height);
void Start();

#endif