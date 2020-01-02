#include "ObjLoad.h"
using namespace std;

//Create a car
void CreateCar(ObjLoader objModel) {

	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();

	//For testing - car position
	glScalef(10.0, 10.0, 10.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	glTranslatef(0.0, 0.0, -2.0);

	objModel.Draw();
	glPopMatrix();

}

ObjLoader::ObjLoader(string filename)
{
	cout << "Objloader initializing" << endl;
	string line;
	fstream f;
	f.open(filename, ios::in);
	if (!f.is_open()) {
		cout << "Fail to open obj file" << endl;
	}

	while (!f.eof()) {
		getline(f, line);
		vector<string>parameters;
		string tailMark = " ";
		string ans = "";

		line = line.append(tailMark);
		for (int i = 0; i < line.length(); i++) {
			char ch = line[i];
			if (ch != ' ') {
				ans += ch;
			}
			else {
				parameters.push_back(ans);
				ans = "";
			}
		}

		if (parameters[0] == "v") {   //If it's vertex
			vector<GLfloat>Point;
			for (int i = 1; i < 4; i++) {   //push in to vector
				GLfloat xyz = atof(parameters[i].c_str());
				Point.push_back(xyz);
			}
			vSets.push_back(Point);
		}

		else if (parameters[0] == "f") {   //If it's surface
			vector<GLint>vIndexSets;
			for (int i = 1; i < 4; i++) {
				string x = parameters[i];
				string ans = "";
				for (int j = 0; j < x.length(); j++) {
					char ch = x[j];
					if (ch != '/') {
						ans += ch;
					}
					else {
						break;
					}
				}
				GLint index = atof(ans.c_str());
				index = index--;				//obj index start from index
				vIndexSets.push_back(index);	//push the points of a surface
			}
			fSets.push_back(vIndexSets);		//push the surface 
		}
	}
	f.close();
}


void ObjLoader::Draw() {

	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_TRIANGLES);

	for (int i = 0; i < fSets.size(); i++) {
		GLfloat VN[3];
		//Èý¸ö¶¥µã
		GLfloat SV1[3];
		GLfloat SV2[3];
		GLfloat SV3[3];

		if ((fSets[i]).size() != 3) {
			cout << "the fSetsets_Size is not correct" << endl;
		}
		else {
			GLint firstVertexIndex = (fSets[i])[0];
			GLint secondVertexIndex = (fSets[i])[1];
			GLint thirdVertexIndex = (fSets[i])[2];

			SV1[0] = (vSets[firstVertexIndex])[0];
			SV1[1] = (vSets[firstVertexIndex])[1];
			SV1[2] = (vSets[firstVertexIndex])[2];

			SV2[0] = (vSets[secondVertexIndex])[0];
			SV2[1] = (vSets[secondVertexIndex])[1];
			SV2[2] = (vSets[secondVertexIndex])[2];

			SV3[0] = (vSets[thirdVertexIndex])[0];
			SV3[1] = (vSets[thirdVertexIndex])[1];
			SV3[2] = (vSets[thirdVertexIndex])[2];


			GLfloat vec1[3], vec2[3], vec3[3];
			//(x2-x1,y2-y1,z2-z1)
			vec1[0] = SV1[0] - SV2[0];
			vec1[1] = SV1[1] - SV2[1];
			vec1[2] = SV1[2] - SV2[2];

			//(x3-x2,y3-y2,z3-z2)
			vec2[0] = SV1[0] - SV3[0];
			vec2[1] = SV1[1] - SV3[1];
			vec2[2] = SV1[2] - SV3[2];

			//(x3-x1,y3-y1,z3-z1)
			vec3[0] = vec1[1] * vec2[2] - vec1[2] * vec2[1];
			vec3[1] = vec2[0] * vec1[2] - vec2[2] * vec1[0];
			vec3[2] = vec2[1] * vec1[0] - vec2[0] * vec1[1];

			GLfloat D = sqrt(pow(vec3[0], 2) + pow(vec3[1], 2) + pow(vec3[2], 2));

			VN[0] = vec3[0] / D;
			VN[1] = vec3[1] / D;
			VN[2] = vec3[2] / D;

			glNormal3f(VN[0], VN[1], VN[2]);

			glVertex3f(SV1[0], SV1[1], SV1[2]); 
				glVertex3f(SV2[0], SV2[1], SV2[2]);
			glVertex3f(SV3[0], SV3[1], SV3[2]);
			//if (SV3[0] != 0)
			//	cout << SV2[0]<< " " << SV2[1] << " " << SV2[2] << " " << endl;
		}
	}
	glEnd();
}