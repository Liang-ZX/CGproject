#include "ObjFile.h"
#include <fstream>
#include <iostream>
#include <sstream>

myObjLoader::myObjLoader(string objfilename) {
	ifstream fs(objfilename);
	string line;
	while (getline(fs, line)) {
		if (line.substr(0, 2) == "v ") {
			Vertex3f v;
			istringstream iss;
			iss.str(line.substr(2));
			iss >> v.x;
			iss >> v.y;
			iss >> v.z;
			Vertices.push_back(v);
		}
		else if (line.substr(0, 2) == "vt") {
			Vertex2f vt;
			istringstream iss;
			iss.str(line.substr(2));
			iss >> vt.x;
			iss >> vt.y;
			tVertices.push_back(vt);
		}
		else if (line.substr(0, 2) == "vn") {
			Vertex3f vn;
			istringstream iss;
			iss.str(line.substr(2));
			iss >> vn.x;
			iss >> vn.y;
			iss >> vn.z;
			Normals.push_back(vn);
		}
		else if (line.substr(0, 2) == "f ") {
			Face f;
			int t1, t2;
			//int index;
			//first vertex
			t1 = 2;
			t2 = line.find_first_of('/', t1);
			f.v[0] = stoi(line.substr(t1, t2)) - 1;

			t1 = t2 + 1;
			t2 = line.find_first_of('/', t1);
			f.vt[0] = stoi(line.substr(t1, t2)) - 1;

			t1 = t2 + 1;
			t2 = line.find_first_of(' ', t1);
			f.vn[0] = stoi(line.substr(t1, t2)) - 1;
			
			//second vertex
			t1 = t2 + 1;
			t2 = line.find_first_of('/', t1);
			f.v[1] = stoi(line.substr(t1, t2)) - 1;

			t1 = t2 + 1;
			t2 = line.find_first_of('/', t1);
			f.vt[1] = stoi(line.substr(t1, t2)) - 1;

			t1 = t2 + 1;
			t2 = line.find_first_of(' ', t1);
			f.vn[1] = stoi(line.substr(t1, t2)) - 1;

			//third vertex
			t1 = t2 + 1;
			t2 = line.find_first_of('/', t1);
			f.v[2] = stoi(line.substr(t1, t2)) - 1;

			t1 = t2 + 1;
			t2 = line.find_first_of('/', t1);
			f.vt[2] = stoi(line.substr(t1, t2)) - 1;

			t1 = t2 + 1;
			//t2 = line.find_first_of(' ', t1);
			f.vn[2] = stoi(line.substr(t1)) - 1;

			Faces.push_back(f);
		}
		else {

		}
	}
	
	fs.close();
	//texture = 
}

void myObjLoader::Draw() {
	//draw all faces
	//glBindTexture(GL_TEXTURE_2D, texture);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < Faces.size(); i++) {
		//first vertex
		glNormal3f(Normals[Faces[i].vn[0]].x, Normals[Faces[i].vn[0]].y, Normals[Faces[i].vn[0]].z);
		//glTexCoord2f(tVertices[Faces[i].vt[0]].x, tVertices[Faces[i].vt[0]].y);
		glVertex3f(Vertices[Faces[i].v[0]].x, Vertices[Faces[i].v[0]].y, Vertices[Faces[i].v[0]].z);
		//second vertex
		glNormal3f(Normals[Faces[i].vn[1]].x, Normals[Faces[i].vn[1]].y, Normals[Faces[i].vn[1]].z);
		//glTexCoord2f(tVertices[Faces[i].vt[1]].x, tVertices[Faces[i].vt[1]].y);
		glVertex3f(Vertices[Faces[i].v[1]].x, Vertices[Faces[i].v[1]].y, Vertices[Faces[i].v[1]].z);
		//third vertex
		glNormal3f(Normals[Faces[i].vn[2]].x, Normals[Faces[i].vn[2]].y, Normals[Faces[i].vn[2]].z);
		//glTexCoord2f(tVertices[Faces[i].vt[2]].x, tVertices[Faces[i].vt[2]].y);
		glVertex3f(Vertices[Faces[i].v[2]].x, Vertices[Faces[i].v[2]].y, Vertices[Faces[i].v[2]].z);
	}
	glEnd();
}