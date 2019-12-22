#ifndef _MOUSE_H
#define _MOUSE_H

extern float yaw, pitch;
extern float mouseX, mouseY;

void MousFunc(int button, int state, int x, int y);
void PassiveMotion(int x, int y);

#endif