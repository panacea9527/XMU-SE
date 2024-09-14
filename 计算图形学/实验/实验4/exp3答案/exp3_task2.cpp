#include <iostream>
#include <fstream>
#include <GL/glut.h>
#include <math.h>

#define ENABLE_LIGHT 
using namespace std;


struct Vertex {
	GLfloat x, y, z, nx, ny, nz;
}ver;

struct Face {
	int a, b, c;
}f;

Vertex* v_arr;
Face* f_arr;
int f_num;
int v_num;
GLfloat avg_x, avg_y, avg_z;
int init_w = 800;
int init_h = 800;
GLfloat aspectRatio = init_w / init_h;// 保存窗口的宽高比
float pi = 3.1415926535;
GLfloat R = 100.0;
float theta = 20;
//材质反光性设置
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };  //镜面反射参数
GLfloat mat_shininess[] = { 50.0 };               //高光指数
GLfloat light_position[] = { R * sin(theta / (360) * 2 * pi), 0.0, R * cos(theta / (360) * 2 * pi), 0.0 }; //灯位置(1,1,1), 最后1-开关
GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };    //白色光
GLfloat Light_Model_Ambient[] = { 0.2, 0.2, 0.2, 1.0 }; //环境光参数

bool read_ply() {
	char ch[50];
	ifstream filein("lizhenxiout.ply");
	if (!filein) {
		cout << "文件打开失败!" << endl;
		return false;
	}

	//跳过前三行，这些行通常是文件的头部信息，不包含模型的几何数据
	for (int i = 0; i < 3; i++) {
		filein.getline(ch, 50);
	}

	//第四行展示点的个数,前两个单词信息没用
	for (int i = 0; i < 3; i++) {
		filein >> ch;
	}

	//点的个数以字符串的形式存储,将点的个数由字符串形式转化成int
	v_num = atoi(ch);

	filein.getline(ch, 50);//处理换行

	//下面6行还是没用
	for (int i = 0; i < 6; i++) {
		filein.getline(ch, 50);
	}

	//第11行展示面片的个数
	for (int i = 0; i < 3; i++) {
		filein >> ch;
	}

	f_num = atoi(ch);


	for (int i = 0; i < 3; i++)
		filein.getline(ch, 50);
	//文件头处理完毕,获取了模型的点的个数和面片的个数。

	v_arr = new Vertex[v_num];
	f_arr = new Face[f_num];
	GLfloat t_x = 0, t_y = 0, t_z = 0;  //用来累加所有顶点的x、y、z坐标
	GLfloat max_x, max_y, max_z;
	GLfloat min_x, min_y, min_z;
	//输入点的信息
	for (int i = 0; i < v_num; i++) {
		filein >> v_arr[i].x >> v_arr[i].y >> v_arr[i].z >>
			v_arr[i].nx >> v_arr[i].ny >> v_arr[i].nz;
		GLfloat x = v_arr[i].x, y = v_arr[i].y, z = v_arr[i].z;
		if (i == 0) {
			min_x = max_x = x;
			min_y = max_y = y;
			min_z = max_z = z;
		}
		if (x > max_x) max_x = x;
		if (x < min_x) min_x = x;
		if (y > max_y) max_y = y;
		if (y < min_y) min_y = y;
		if (z > max_z) max_z = z;
		if (z < min_z) min_z = z;
		t_x += x;
		t_y += y;
		t_z += z;
		/*cout<< v_arr[i].x << v_arr[i].y << v_arr[i].z <<
			v_arr[i].nx << v_arr[i].ny << v_arr[i].nz<<endl;*/
	}
	avg_x = t_x / v_num;
	avg_y = t_y / v_num;
	avg_z = t_z / v_num;
	//输入面的信息
	for (int i = 0; i < f_num; i++) {
		filein >> f_arr[i].a;
		filein >> f_arr[i].a >> f_arr[i].b >> f_arr[i].c;
	}

	return true;
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);

#ifdef ENABLE_LIGHT

	glShadeModel(GL_SMOOTH);

	//材质属性
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);  //设置镜面反射参数，即光照打在物体表面上产生的镜面反射的颜色
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);  //设置高光指数，决定了物体表面的光滑程度。值越大，高光部分越小，反之越大

	//灯光设置
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);  //设置光源的位置
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);   //散射光属性，光源产生的散射光的颜色
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);  //镜面反射光，光源产生的镜面反射光的颜色
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Light_Model_Ambient);  //环境光参数，整个场景的环境光的颜色

	glEnable(GL_LIGHTING);   //启用光照计算
	glEnable(GL_LIGHT0);     //启用0号光源

	glEnable(GL_DEPTH_TEST); //打开深度测试
#endif
	if (read_ply()) {
		printf("read in\n");
	}
	printf("avg_x:%lf, avg_y:%lf, avg_z:%lf\n", avg_x, avg_y, avg_z);

	glViewport(0, 0, init_w, init_h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glFrustum(-500, 500, -500, 500, 600.0, 1000.0);

	gluPerspective(80.0, aspectRatio, 60.0, 2000.0);  //视野角度、宽高比、近裁剪面距离、远裁剪面距离

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//第一行：相机所在位置 第二行：相机看的方向的坐标 第三行:z轴对的方向的点
	gluLookAt(0, 0, 500,
		0, 0, avg_z,
		0.0, 1.0, 0.0);

}

void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //清除颜色缓冲区和深度缓冲区
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_TRIANGLES);

	//f_arr[i].a 第一个面的第一个点
	glColor3f(1.0, 0.0, 0.0);
	//对每个面片进行绘制
	for (int i = 0; i < f_num; i++) {
		glNormal3f(v_arr[f_arr[i].a].nx, v_arr[f_arr[i].a].ny, v_arr[f_arr[i].a].nz);
		glVertex3f(v_arr[f_arr[i].a].x, v_arr[f_arr[i].a].y, v_arr[f_arr[i].a].z);
		glNormal3f(v_arr[f_arr[i].b].nx, v_arr[f_arr[i].b].ny, v_arr[f_arr[i].b].nz);
		glVertex3f(v_arr[f_arr[i].b].x, v_arr[f_arr[i].b].y, v_arr[f_arr[i].b].z);
		glNormal3f(v_arr[f_arr[i].c].nx, v_arr[f_arr[i].c].ny, v_arr[f_arr[i].c].nz);
		glVertex3f(v_arr[f_arr[i].c].x, v_arr[f_arr[i].c].y, v_arr[f_arr[i].c].z);
	}
	glEnd();

	glutSwapBuffers();  //交换前后缓冲区，将绘制的图形显示在屏幕上

}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

}

void idlefunc(void) {
	theta += 0.5;
	light_position[0] = R * sin(theta / (360) * 2 * pi);
	light_position[2] = R * cos(theta / (360) * 2 * pi);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position); //指定光源（0号光源）,光源属性（光源位置）
	glutPostRedisplay();

}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(init_w, init_h);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idlefunc);
	//glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}