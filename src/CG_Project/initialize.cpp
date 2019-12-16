#include "project.h"

void initLight(void)
{
	Light light0 = Light(0);
	light0.setPosition(5, 5, 5, 1);
	light0.setDiffuse(1.0, 1.0, 1.0, 1.0);
	light0.LightOn();
}