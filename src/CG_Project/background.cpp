#include "background.h"

SkyBox skybox;

void Background(string path)
{
	GLfloat size = 15.0;
	
	//sphere mode
	if (skybox.mode==sphere)
	{
		glScalef(size, size, size);
		skybox.Draw(path);
		glScalef(1 / size, 1 / size, 1 / size);
	}

	//cube mode
	if (skybox.mode==cube)
	{
		glScalef(size, size, size);
		skybox.Draw(path);//front
		glRotatef(90, 1, 0, 0);
		skybox.Draw(path);//down
		glRotatef(90, 1, 0, 0);
		skybox.Draw(path);//back
		glRotatef(90, 1, 0, 0);
		skybox.Draw(path);//up
		glRotatef(90, 0, 1, 0);
		skybox.Draw(path);//right
		glRotatef(180, 0, 1, 0);
		skybox.Draw(path);//left
		glScalef(1 / size, 1 / size, 1 / size);

		//recover view
		glRotatef(90, 0, 1, 0);
	}
}