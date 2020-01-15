#include "stick.h"

int Stick::count = 0;

static GLfloat ctrlpointsA[3][4];

static GLdouble cal_normal(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2)
{	//calculate angle between vectors
	GLdouble n = x1 * x2 + y1 * y2 + z1 * z2;
	GLdouble m = sqrt(x1*x1 + y1 * y1 + z1 * z1) + sqrt(x2*x2 + y2 * y2 + z2 * z2);
	return acos(n / m) / PI * 180;
}

std::vector<Stick> StickVector;

static void drawbond(int flag, Sphere sp1, Sphere sp2, GLUquadricObj* quad_obj, GLfloat radius); //direction�ǽ��ϰ��ķ���

int Stick::stickcreate(int sp1, int sp2)
{
	Stick tmp = Stick(count++, sp1, sp2);
	StickVector.push_back(tmp);
	
	return count - 1;
}

void Stick::Draw(GLint iSlices, GLint iStacks)
{
	GLfloat vecX = SphereVector[sp2].getX() - SphereVector[sp1].getX();
	GLfloat vecY = SphereVector[sp2].getY() - SphereVector[sp1].getY();
	GLfloat vecZ = SphereVector[sp2].getZ() - SphereVector[sp1].getZ();
	GLfloat stlength = sqrt(vecX * vecX + vecY * vecY + vecZ * vecZ);

	static GLUquadricObj* quad_obj = NULL;
	if (quad_obj == NULL)
		quad_obj = gluNewQuadric();
	gluQuadricDrawStyle(quad_obj, GLU_FILL);
	gluQuadricNormals(quad_obj, GLU_SMOOTH);

	glEnable(GL_COLOR_MATERIAL);
	glColor3f(color[0], color[1], color[2]);

	glPushName(100 + id);	//name id of stick is from 100
	glPushMatrix();

	if (doublebond == true)
	{

		//used to debug
		glTranslatef(SphereVector[sp1].getX(), SphereVector[sp1].getY(), SphereVector[sp1].getZ());
		vecX /= stlength;
		vecY /= stlength;
		vecZ /= stlength;

		GLfloat up_x, up_y, up_z;
		up_x = 0.0;
		up_y = 1.0;
		up_z = 0.0;
		GLfloat side_x, side_y, side_z;
		side_x = up_y * vecZ - up_z * vecY;
		side_y = up_z * vecX - up_x * vecZ;
		side_z = up_x * vecY - up_y * vecX;
		GLfloat length = sqrt(side_x * side_x + side_y * side_y + side_z * side_z);
		side_x /= length; side_y /= length; side_z /= length;
		up_x = vecY * side_z - vecZ * side_y;
		up_y = vecZ * side_x - vecX * side_z;
		up_z = vecX * side_y - vecY * side_x;
		GLdouble m[16] = { side_x, side_y, side_z, 0.0,
			up_x, up_y, up_z, 0.0,
			vecX, vecY, vecZ, 0.0,
			0.0,  0.0,  0.0,  1.0 };
		glMultMatrixd(m);
		GLdouble slices = 8.0;
		GLdouble stack = 3.0;
		gluCylinder(quad_obj, 2*radius, 2*radius, stlength, iSlices, iStacks);

		//drawbond(1, sp1, sp2, quad_obj, radius);	//draw double bonds
		//drawbond(-1, sp1, sp2, quad_obj, radius);
	}
	else {
		glTranslatef(SphereVector[sp1].getX(), SphereVector[sp1].getY(), SphereVector[sp1].getZ());
		vecX /= stlength;
		vecY /= stlength;
		vecZ /= stlength;

		GLfloat up_x, up_y, up_z;
		up_x = 0.0;
		up_y = 1.0;
		up_z = 0.0;
		GLfloat side_x, side_y, side_z;
		side_x = up_y * vecZ - up_z * vecY;
		side_y = up_z * vecX - up_x * vecZ;
		side_z = up_x * vecY - up_y * vecX;
		GLfloat length = sqrt(side_x * side_x + side_y * side_y + side_z * side_z);
		side_x /= length; side_y /= length; side_z /= length;
		up_x = vecY * side_z - vecZ * side_y;
		up_y = vecZ * side_x - vecX * side_z;
		up_z = vecX * side_y - vecY * side_x;
		GLdouble m[16] = { side_x, side_y, side_z, 0.0,
			up_x, up_y, up_z, 0.0,
			vecX, vecY, vecZ, 0.0,
			0.0,  0.0,  0.0,  1.0 };
		glMultMatrixd(m);
		GLdouble slices = 8.0;
		GLdouble stack = 3.0;
		gluCylinder(quad_obj, radius, radius, stlength, iSlices, iStacks);
	}
	glPopMatrix();
	glPopName();
}

static void drawbond(int flag, Sphere sp1, Sphere sp2, GLUquadricObj* quad_obj, GLfloat radius) //draw one bond
{
	ctrlpointsA[0][0] = sp1.getX();
	ctrlpointsA[0][1] = sp1.getY();
	ctrlpointsA[0][2] = sp1.getZ();
	ctrlpointsA[0][3] = 1.0;

	ctrlpointsA[2][0] = sp2.getX();
	ctrlpointsA[2][1] = sp2.getY();
	ctrlpointsA[2][2] = sp2.getZ();
	ctrlpointsA[2][3] = 1.0;

	ctrlpointsA[1][0] = (sp1.getX() + sp2.getX()) / 2.0;
	ctrlpointsA[1][1] = (sp1.getY() + sp2.getY()) / 2.0;
	ctrlpointsA[1][2] = (sp1.getZ() + sp2.getZ()) / 2.0 + 0.5 * flag;
	ctrlpointsA[1][3] = 1.0;

	glPushMatrix();

	glMap1f(GL_MAP1_VERTEX_4, 0.0, 1.0, 4, 3, &ctrlpointsA[0][0]);
	glEnable(GL_MAP1_VERTEX_4);

	if (NowRenderMode == GL_RENDER)
	{
		GLfloat buffer[300];
		glFeedbackBuffer(300, GL_3D, buffer);

		glRenderMode(GL_FEEDBACK);
		//glPointSize(0.4);
		glBegin(GL_POINTS);
		int division = 30;
		for (int i = 0; i <= division; i++)
		{
			glEvalCoord1f((GLfloat)i / division);
		}
		glEnd();
		glDisable(GL_MAP2_VERTEX_4);

		int size = glRenderMode(GL_RENDER);

		glPushMatrix();

		GLfloat winx, winy, winz;
		GLdouble posx, posy, posz;
		GLdouble lastx = sp1.getX(), lasty = sp1.getY(), lastz = sp1.getZ();

		glPushMatrix();
		glGetIntegerv(GL_VIEWPORT, viewport);   // ��ȡ�������� 
		glGetDoublev(GL_MODELVIEW_MATRIX, mvmatrix);
		glGetDoublev(GL_PROJECTION_MATRIX, projmatrix);
		glPopMatrix();

		for (int j = 0; j < size / 4 - 1; j++)
		{
			winx = buffer[j * 4 + 1];
			winy = g_window_height - buffer[j * 4 + 2];
			winz = buffer[j * 4 + 3];

			gluUnProject(winx, winy, winz, mvmatrix, projmatrix, viewport, &posx, &posy, &posz); // ��ȡ��ά���� 
			posz = -posz;
			GLdouble angle = cal_normal(division * (posx - lastx), division * (posy - lasty), division * (posz - lastz), 0, 1, 0);
			glPushMatrix();
			glTranslatef(posx, posy, posz);
			glRotatef(angle, 0, 0, 1);
			glRotatef(-90, 1, 0, 0);
			gluCylinder(quad_obj, radius, radius, 0.1, 150, 200);
			glPopMatrix();

			lastx = posx;
			lasty = posy;
			lastz = posz;
		}
		glPopMatrix();
	}
	else {
		glBegin(GL_LINE_STRIP);
		glLineWidth(10);
		int division = 30;
		for (int i = 0; i <= division; i++)
		{
			glEvalCoord1f((GLfloat)i / division);
		}
		glEnd();
		glDisable(GL_MAP2_VERTEX_4);
	}
	glPopMatrix();
}