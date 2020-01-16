#include "ObjFile.h"
#include <fstream>
#include <iostream>
#include <sstream>

myObjLoader::myObjLoader(string objfilename, int t) {
	facetype = t;
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
			if (t == 4) {
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
				t2 = line.find_first_of(' ', t1);
				f.vn[2] = stoi(line.substr(t1, t2)) - 1;

				//forth vertex
				t1 = t2 + 1;
				t2 = line.find_first_of('/', t1);
				f.v[3] = stoi(line.substr(t1, t2)) - 1;

				t1 = t2 + 1;
				t2 = line.find_first_of('/', t1);
				f.vt[3] = stoi(line.substr(t1, t2)) - 1;

				t1 = t2 + 1;
				//t2 = line.find_first_of(' ', t1);
				f.vn[3] = stoi(line.substr(t1)) - 1;

				Faces.push_back(f);
			}
			else if (t == 3) {
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
	//glBegin(GL_TRIANGLES);
	Texture tex = Texture("spheretexture\\red.bmp");
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glBindTexture(GL_TEXTURE_2D, tex.getID());
	
	glEnable(GL_DEPTH_TEST);
	if (facetype == 4) {
		glBegin(GL_QUADS);
		for (unsigned int i = 0; i < Faces.size(); i++) {
			//first vertex
			glNormal3f(Normals[Faces[i].vn[0]].x, Normals[Faces[i].vn[0]].y, Normals[Faces[i].vn[0]].z);
			glTexCoord2f(tVertices[Faces[i].vt[0]].x, tVertices[Faces[i].vt[0]].y);
			glVertex3f(Vertices[Faces[i].v[0]].x, Vertices[Faces[i].v[0]].y, Vertices[Faces[i].v[0]].z);
			//second vertex
			glNormal3f(Normals[Faces[i].vn[1]].x, Normals[Faces[i].vn[1]].y, Normals[Faces[i].vn[1]].z);
			glTexCoord2f(tVertices[Faces[i].vt[1]].x, tVertices[Faces[i].vt[1]].y);
			glVertex3f(Vertices[Faces[i].v[1]].x, Vertices[Faces[i].v[1]].y, Vertices[Faces[i].v[1]].z);
			//third vertex
			glNormal3f(Normals[Faces[i].vn[2]].x, Normals[Faces[i].vn[2]].y, Normals[Faces[i].vn[2]].z);
			glTexCoord2f(tVertices[Faces[i].vt[2]].x, tVertices[Faces[i].vt[2]].y);
			glVertex3f(Vertices[Faces[i].v[2]].x, Vertices[Faces[i].v[2]].y, Vertices[Faces[i].v[2]].z);
			//forth vertex
			if (facetype == 4) {
				glNormal3f(Normals[Faces[i].vn[3]].x, Normals[Faces[i].vn[3]].y, Normals[Faces[i].vn[3]].z);
				glTexCoord2f(tVertices[Faces[i].vt[3]].x, tVertices[Faces[i].vt[3]].y);
				glVertex3f(Vertices[Faces[i].v[3]].x, Vertices[Faces[i].v[3]].y, Vertices[Faces[i].v[3]].z);
			}

		}
		glEnd();
	}
	else if (facetype == 3) {
		glPushMatrix();
		glRotatef(90, 1, 0, 0);
		glBegin(GL_TRIANGLES);
		for (unsigned int i = 0; i < Faces.size(); i++) {
			//first vertex
			glNormal3f(Normals[Faces[i].vn[0]].x, Normals[Faces[i].vn[0]].y, Normals[Faces[i].vn[0]].z);
			glTexCoord2f(tVertices[Faces[i].vt[0]].x, tVertices[Faces[i].vt[0]].y);
			glVertex3f(Vertices[Faces[i].v[0]].x / 10, Vertices[Faces[i].v[0]].y / 10, Vertices[Faces[i].v[0]].z / 10);
			//second vertex
			glNormal3f(Normals[Faces[i].vn[1]].x, Normals[Faces[i].vn[1]].y, Normals[Faces[i].vn[1]].z);
			glTexCoord2f(tVertices[Faces[i].vt[1]].x, tVertices[Faces[i].vt[1]].y);
			glVertex3f(Vertices[Faces[i].v[1]].x / 10, Vertices[Faces[i].v[1]].y / 10, Vertices[Faces[i].v[1]].z / 10);
			//third vertex
			glNormal3f(Normals[Faces[i].vn[2]].x, Normals[Faces[i].vn[2]].y, Normals[Faces[i].vn[2]].z);
			glTexCoord2f(tVertices[Faces[i].vt[2]].x, tVertices[Faces[i].vt[2]].y);
			glVertex3f(Vertices[Faces[i].v[2]].x / 10, Vertices[Faces[i].v[2]].y / 10, Vertices[Faces[i].v[2]].z / 10);

		}
		glEnd();
		glPopMatrix();
	}
	
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
}