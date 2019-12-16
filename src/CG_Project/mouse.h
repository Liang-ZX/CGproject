#ifndef _MOUSE_H
#define _MOUSE_H

#define PI 3.14159

#include "project.h"
#include <math.h>

extern float yaw, pitch;
extern float mouseX, mouseY;

void MousFunc(int button, int state, int x, int y);
void PassiveMotion(int x, int y);

#endif