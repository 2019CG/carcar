#ifndef OBJLOAD_H
#define OBJLOAD_H

#include <string>
#define NDEBUG
#include "GL\freeglut.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

//Load a obj file
class ObjLoader {
public:
	ObjLoader(string filename);
	void Draw(); 
private:
	vector<vector<GLfloat>>vSets;		//��Ŷ���(x,y,z)����
	vector<vector<GLint>>fSets;			//������������������
};

//Create a car
void CreateCar(ObjLoader objModel);

#endif