#include "glut.h"
#include "math.h"
#include "sphere.h"
#include <vector>

class Stick
{
private:
	int id;
	// generate the stick according to the corresponding spheres
	Sphere sp1;
	Sphere sp2;	

	GLfloat color[3];
	GLfloat radius;
	MATERIAL stMaterial;
	// binding light,etc to be added

public:
	static int count;
	static int stickcreate(Sphere sp1, Sphere sp2);
	Stick() {};
	Stick(int id, Sphere sp1, Sphere sp2)
	{
		this->id = id;
		this->sp1 = sp1;
		this->sp2 = sp2;
		for (int i = 0; i < 3; i++)color[i] = 0.0f;
		radius = 0.0f;
		stMaterial.ambient[0] = 0.1;
		stMaterial.ambient[1] = 0.1;
		stMaterial.ambient[2] = 0.1;
		stMaterial.ambient[3] = 1.0;
		stMaterial.diffuse[0] = 1.0;
		stMaterial.diffuse[1] = 1.0;
		stMaterial.diffuse[2] = 1.0;
		stMaterial.diffuse[3] = 1.0;
		stMaterial.specular[0] = 0.0;
		stMaterial.specular[1] = 0.0;
		stMaterial.specular[2] = 0.0;
		stMaterial.specular[3] = 1.0;
		stMaterial.shininess = 100.0;
	}

	void setRadius(GLfloat r) { radius = r; }

	void setColor(GLfloat r, GLfloat g, GLfloat b)
	{
		color[0] = r;
		color[1] = g;
		color[2] = b;
	}

	// draw by parametric equation
	void Draw(GLint iSlices, GLint iStacks)
	{
		GLfloat vecX = sp2.getX() - sp1.getX();
		GLfloat vecY = sp2.getY() - sp1.getY();
		GLfloat vecZ = sp2.getZ() - sp1.getZ();
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
		glTranslatef(sp1.getX(), sp1.getY(), sp1.getZ());
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
		glPopMatrix();
		glPopName();
	}

	MATERIAL mat(){ return stMaterial; }
};
extern std::vector<Stick> StickVector;
