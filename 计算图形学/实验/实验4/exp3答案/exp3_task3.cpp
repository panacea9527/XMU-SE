#include <GL/glut.h>
#include<math.h>

#define PI 3.1415926535

/* 绘制正方体 */
GLfloat Vertices[8][3] = { {1,-1,1},{1,-1,-1},{-1,-1,-1},{-1,-1,1},{1,1,1},{1,1,-1},{-1,1,-1},{-1,1,1} }; //8个顶点坐标
GLint Faces[6][4] = { {0,3,7,4},{0,1,5,4},{1,2,6,5},{2,3,7,6},{4,5,6,7},{0,1,2,3} }; // 面顶点组索引，定义正方体的六个面
GLfloat normals[][3] = { {0.0,0.0,1.0},{1.0,0.0,0.0},{0.0,0.0,-1.0},{-1.0,0.0,0.0},{0.0,1.0,0.0},{0.0,-1.0,0.0} }; //正方体的面法线数组，定义每个面的法线方向
/* 物体旋转 */
GLfloat beta = 0; //旋转角度
GLfloat delta = 1.0; //旋转速度

/* 键盘交互 */
bool enableMove = true; //是否启用相机移动
GLfloat moveSpeed = 0.3; //相机移动的速度
GLfloat cameraPosX = 0.0f, cameraPosY = 0.0f, cameraPosZ = 10.0f;
GLfloat lookAtX = 0.0f, lookAtY = 0.0f, lookAtZ = -15.0f;

/* 鼠标交互 */
GLfloat latestX = 0, latestY = 0; //上一次鼠标位置的坐标
GLint w = 1000, h = 1000;

/* 描述光照的属性 */
typedef struct lightingStruct {
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
}lightingStruct;

lightingStruct whiteLighting = {
	{0.0,0.0,0.0,1.0},
	{1.0,1.0,1.0,1.0},
	{1.0,1.0,1.0,1.0}
};
lightingStruct coloredLighting = {
	{0.2,0.0,0.0,1.0},
	{1.0,0.0,0.0,1.0},
	{0.0,0.0,1.0,1.0}
};

void lighting(lightingStruct* lighting) {
	GLfloat position[] = { 0.0,0.0,0.0,1.0 }; //光源位于世界坐标原点
	glLightfv(GL_LIGHT0, GL_POSITION, position);  //光源的位置
	glLightfv(GL_LIGHT0, GL_AMBIENT, lighting->ambient);  //环境光
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lighting->diffuse);  //漫反射光
	glLightfv(GL_LIGHT0, GL_SPECULAR, lighting->specular);  //镜面反射光
}

typedef struct materialStruct {
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat shininess[1];
}materialStruct;

materialStruct brassMaterials = {
	{0.33,0.22,0.03,1.0},
	{0.78,0.57,0.11,1.0},
	{0.99,0.91,0.81,1.0},
	{27.8}
};
materialStruct redPlasticMaterials = {
	{0.3,0.0,0.0,1.0},
	{0.6,0.0,0.0,1.0},
	{0.8,0.6,0.6,1.0},
	{32.0}
};
materialStruct whiteShinyMaterials = {
	{1.0,1.0,1.0,1.0},
	{1.0,1.0,1.0,1.0},
	{1.0,1.0,1.0,1.0},
	{100.0}
};

void materials(materialStruct* materials) {
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, materials->ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, materials->diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, materials->specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, materials->shininess);
}


void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0, 0.0, 0.0);

	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST); //开启深度测试
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	materials(&whiteShinyMaterials);
	lighting(&whiteLighting);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80, 1, 0.1, 60); // 选择透视视景体
	glMatrixMode(GL_MODELVIEW);

	latestX = w / 2;
	latestY = h / 2;
	glutWarpPointer(w / 2, h / 2);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();
	gluLookAt(cameraPosX, cameraPosY, cameraPosZ,
		lookAtX, lookAtY, lookAtZ,
		0, 1, 0);

	glRotatef(beta, 1.0, -1.0, -1.0); //旋转

	for (int i = 0; i < 6; i++)
	{
		glNormal3fv(normals[i]);
		glBegin(GL_POLYGON);
		for (int j = 0; j < 4; j++)
			glVertex3fv(Vertices[Faces[i][j]]);
		glEnd();
	}

	glutSwapBuffers();
}


void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void idlefunc()
{
	//改变动画参数
	beta += delta;
	if (beta > 360) beta -= 360;
	glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
	GLfloat move = enableMove ? moveSpeed : 0;
	switch (key) {
	case 27: exit(0); break;
	case 's': cameraPosZ += move; lookAtZ += move; break;
	case 'w': cameraPosZ -= move; lookAtZ -= move; break;
	case 'd': cameraPosX += move; lookAtX += move; break;
	case 'a': cameraPosX -= move; lookAtX -= move; break;
	case 'q': cameraPosY += move; lookAtY += move; break;
	case 'e': cameraPosY -= move; lookAtY -= move; break;
	case 'l': enableMove = !enableMove; break; //禁用相机移动
	case 'b': materials(&brassMaterials); break;
	case 'n': materials(&redPlasticMaterials); break;
	case 'm': materials(&whiteShinyMaterials); break;
	case 'o': lighting(&whiteLighting); break;
	case 'p': lighting(&coloredLighting); break;
	}
}

void mouse(int x, int y)
{
	if (enableMove)
	{
		lookAtX += (x - latestX) / 25;
		lookAtY += (latestY - y) / 25;
	}
	latestX = x;
	latestY = y;
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutPassiveMotionFunc(mouse);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idlefunc);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
