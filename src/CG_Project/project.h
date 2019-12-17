#ifndef _PROJECT_H
#define _PROJECT_H

#include "texture.h"
#include "stdlib.h"
#include "mouse.h"
#include "glut.h"
#include "keyboard.h"
#include "light.h"
#include "initialize.h"
#include "define.h"

#include "sphere.h"
#include "stick.h"
//#include "view.h"

//���ڴ�С
#define WIDTH 600
#define HEIGHT 600

extern float eye[3];
extern float center[3];
extern int wHeight;
extern int wWidth;
extern bool bPersp;
extern bool bAnim;
extern int gameState;

void initialize(void);
void reshape(int width, int height);
void idle();
void redraw();

#endif