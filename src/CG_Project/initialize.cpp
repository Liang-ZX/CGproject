#include "project.h"

//Light
Light light[8];
GLint light_cur = 0;
void initLight(void)
{
	light[0] = Light(0);
	light[0].setPosition(5, 5, 5, 1);
	light[0].setDiffuse(1.0, 1.0, 1.0, 1.0);
	light[0].LightOn();
}

void changeLight(void) {
	light[light_cur].LightOn();
}