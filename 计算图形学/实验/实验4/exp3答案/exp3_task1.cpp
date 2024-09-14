#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<GL/glut.h>
#include<math.h>
#define WIDTH 500
#define HEIGHT 500

using namespace std;

typedef struct Coordinate
{
	float x;
	float y;
	float z;
	float nx;
	float ny;
	float nz;
}Coordinate;

typedef struct Face
{
	int vertex1;
	int vertex2;
	int vertex3;
}Face;

Coordinate* coordinates;
Face* face;
int vertexNum, faceNum;
float center_x = 0, center_y = 0, center_z = 0;

void init()
{
	glClearColor(0, 0, 0, 0);
	glEnable(GL_DEPTH_TEST);
}

void LoadFile()
{
	//读取ply文件，并将其显示出来
	FILE* fp = fopen("lizhenxiout.ply", "r");

	char s[100];
	for (int i = 1; i <= 3; i++)
	{
		fgets(s, 100, fp);
	}

	//读取有多少个顶点
	fscanf(fp, "element vertex %d\n", &vertexNum);
	for (int i = 1; i <= 6; i++)
	{
		fgets(s, 100, fp);
	}
	//读取有多少个面
	fscanf(fp, "element face %d\n", &faceNum);
	for (int i = 1; i <= 2; ++i)
	{
		fgets(s, 100, fp);
	}

	//读取每个顶点的信息
	coordinates = new Coordinate[vertexNum];
	for (int i = 0; i < vertexNum; i++)
	{
		fscanf(fp, "%f %f %f %f %f %f\n", &coordinates[i].x, &coordinates[i].y, &coordinates[i].z,
			&coordinates[i].nx, &coordinates[i].ny, &coordinates[i].nz);
		center_x += coordinates[i].x;
		center_y += coordinates[i].y;
		center_z += coordinates[i].z;
	}

	center_x /= vertexNum;
	center_y /= vertexNum;
	center_z /= vertexNum;

	//读取每个面的信息
	face = new Face[faceNum];
	for (int i = 0; i < faceNum; ++i)
	{
		fscanf(fp, "3 %d %d %d\n", &face[i].vertex1, &face[i].vertex2, &face[i].vertex3);
	}

	fclose(fp);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//绘制小人
	glColor3f(1, 0, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(center_x, center_y, center_z + 1500, center_x, center_y, center_z, 0, 1, 0);

	for (int i = 0; i < faceNum; i++)
	{
		glBegin(GL_TRIANGLES);
		glVertex3f(coordinates[face[i].vertex1].x, coordinates[face[i].vertex1].y, coordinates[face[i].vertex1].z);
		glVertex3f(coordinates[face[i].vertex2].x, coordinates[face[i].vertex2].y, coordinates[face[i].vertex2].z);
		glVertex3f(coordinates[face[i].vertex3].x, coordinates[face[i].vertex3].y, coordinates[face[i].vertex3].z);
		glEnd();
	}

	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, 1, 0.1, 2000);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(WIDTH, HEIGHT);
	LoadFile();
	glutCreateWindow("Exp3 Task1");
	glutDisplayFunc(display);
	init();
	glutReshapeFunc(reshape);
	glutMainLoop();
}