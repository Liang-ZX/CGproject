#pragma once 
#include "project.h"
#include <vector>
#include <string>
using namespace std;

class Vertex3f {
public:
	float x, y, z;
};

class Vertex2f {
public:
	float x, y;
};

class Face {
public:
	int v[4];
	int vt[4];
	int vn[4];
};

class myObjLoader {
public:
	myObjLoader(string objfilename, int t);
	void Draw();
private:
	vector<Vertex3f> Vertices;
	vector<Vertex2f> tVertices;
	vector<Vertex3f> Normals;
	vector<Face> Faces;
	GLuint texture;
	int facetype = 4;
};

