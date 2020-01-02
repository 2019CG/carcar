#include <iostream>
#include "Background.hpp"
#include "ObjLoad.h"

string ObjPath = "./obj/smallCar.obj";
ObjLoader objModel = ObjLoader(ObjPath);

void display()
{
	/* Observation */
	gluLookAt(0, -2000, 1000,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);
	
	/* The function is used to draw the background. */
	CreateBackground();

	/* The function draws a car */
	CreateCar(objModel);

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, w * 1.0 / h, 0.1, 20000);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(900, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("cube");
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);

	Binit();
	glutMainLoop();
}

