#pragma once

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include "stb_image.h"
#include<glm/glm.hpp>

#include<vector>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

GLfloat step = 0.0, s = 0.1, move[] = { 0,0,0 };

class obj3dmodel {
	struct vertex {
		double x, y, z;
	};
	struct face {
		unsigned int v1, v2, v3;
	};
	vector<vertex>vertexs;
	vector<face>faces;

public:
	void parse(const char* filename);
	void draw();
};
void obj3dmodel::parse(const char* filename) {
	string s;
	ifstream fin(filename);
	if (!fin)return;
	while (fin >> s) {
		switch (*s.c_str()) {
		case 'f':
		{
			face f;
			fin >> f.v1 >> f.v2 >> f.v3;
			cout << "f      " << f.v1 << "       " << f.v2 << "       " << f.v3 << endl;
			faces.push_back(f);
		}
		break;

		case 'v':
		{
			vertex v;
			fin >> v.x >> v.y >> v.z;
			cout << "v      " << v.x << "       " << v.y << "       " << v.z << "       " << endl;
			this->vertexs.push_back(v);
		}
		break;
		case 'w':break;
		case 'x':break;
		case 'y':break;
		case 'z':break;
		case '#':break;

		default:
		{}
		break;

		}
	}
}

void obj3dmodel::draw() {
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < faces.size(); i++) {
		//下标减一
		float move_y = 0.5; //控制模型的位置
		vertex v1 = vertexs[faces[i].v1 - 1];
		vertex v2 = vertexs[faces[i].v2 - 1];
		vertex v3 = vertexs[faces[i].v3 - 1];
		glColor3f(0.3, 0.5, 0);
		glVertex3f(v1.x, v1.y - move_y, v1.z);

		glColor3f(1, 1, 0);
		glVertex3f(v2.x, v2.y - move_y, v2.z);

		glColor3f(0.5, 0.5, 0);
		glVertex3f(v3.x, v3.y - move_y, v3.z);
	}
	glEnd();
}