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
GLfloat aspectRatio = init_w / init_h;// ���洰�ڵĿ�߱�
float pi = 3.1415926535;
GLfloat R = 100.0;
float theta = 20;
//���ʷ���������
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };  //���淴�����
GLfloat mat_shininess[] = { 50.0 };               //�߹�ָ��
GLfloat light_position[] = { R * sin(theta / (360) * 2 * pi), 0.0, R * cos(theta / (360) * 2 * pi), 0.0 }; //��λ��(1,1,1), ���1-����
GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };    //��ɫ��
GLfloat Light_Model_Ambient[] = { 0.2, 0.2, 0.2, 1.0 }; //���������

bool read_ply() {
	char ch[50];
	ifstream filein("lizhenxiout.ply");
	if (!filein) {
		cout << "�ļ���ʧ��!" << endl;
		return false;
	}

	//����ǰ���У���Щ��ͨ�����ļ���ͷ����Ϣ��������ģ�͵ļ�������
	for (int i = 0; i < 3; i++) {
		filein.getline(ch, 50);
	}

	//������չʾ��ĸ���,ǰ����������Ϣû��
	for (int i = 0; i < 3; i++) {
		filein >> ch;
	}

	//��ĸ������ַ�������ʽ�洢,����ĸ������ַ�����ʽת����int
	v_num = atoi(ch);

	filein.getline(ch, 50);//������

	//����6�л���û��
	for (int i = 0; i < 6; i++) {
		filein.getline(ch, 50);
	}

	//��11��չʾ��Ƭ�ĸ���
	for (int i = 0; i < 3; i++) {
		filein >> ch;
	}

	f_num = atoi(ch);


	for (int i = 0; i < 3; i++)
		filein.getline(ch, 50);
	//�ļ�ͷ�������,��ȡ��ģ�͵ĵ�ĸ�������Ƭ�ĸ�����

	v_arr = new Vertex[v_num];
	f_arr = new Face[f_num];
	GLfloat t_x = 0, t_y = 0, t_z = 0;  //�����ۼ����ж����x��y��z����
	GLfloat max_x, max_y, max_z;
	GLfloat min_x, min_y, min_z;
	//��������Ϣ
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
	//���������Ϣ
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

	//��������
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);  //���þ��淴������������մ�����������ϲ����ľ��淴�����ɫ
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);  //���ø߹�ָ�����������������Ĺ⻬�̶ȡ�ֵԽ�󣬸߹ⲿ��ԽС����֮Խ��

	//�ƹ�����
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);  //���ù�Դ��λ��
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);   //ɢ������ԣ���Դ������ɢ������ɫ
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);  //���淴��⣬��Դ�����ľ��淴������ɫ
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, Light_Model_Ambient);  //��������������������Ļ��������ɫ

	glEnable(GL_LIGHTING);   //���ù��ռ���
	glEnable(GL_LIGHT0);     //����0�Ź�Դ

	glEnable(GL_DEPTH_TEST); //����Ȳ���
#endif
	if (read_ply()) {
		printf("read in\n");
	}
	printf("avg_x:%lf, avg_y:%lf, avg_z:%lf\n", avg_x, avg_y, avg_z);

	glViewport(0, 0, init_w, init_h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glFrustum(-500, 500, -500, 500, 600.0, 1000.0);

	gluPerspective(80.0, aspectRatio, 60.0, 2000.0);  //��Ұ�Ƕȡ���߱ȡ����ü�����롢Զ�ü������

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//��һ�У��������λ�� �ڶ��У�������ķ�������� ������:z��Եķ���ĵ�
	gluLookAt(0, 0, 500,
		0, 0, avg_z,
		0.0, 1.0, 0.0);

}

void display(void) {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //�����ɫ����������Ȼ�����
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_TRIANGLES);

	//f_arr[i].a ��һ����ĵ�һ����
	glColor3f(1.0, 0.0, 0.0);
	//��ÿ����Ƭ���л���
	for (int i = 0; i < f_num; i++) {
		glNormal3f(v_arr[f_arr[i].a].nx, v_arr[f_arr[i].a].ny, v_arr[f_arr[i].a].nz);
		glVertex3f(v_arr[f_arr[i].a].x, v_arr[f_arr[i].a].y, v_arr[f_arr[i].a].z);
		glNormal3f(v_arr[f_arr[i].b].nx, v_arr[f_arr[i].b].ny, v_arr[f_arr[i].b].nz);
		glVertex3f(v_arr[f_arr[i].b].x, v_arr[f_arr[i].b].y, v_arr[f_arr[i].b].z);
		glNormal3f(v_arr[f_arr[i].c].nx, v_arr[f_arr[i].c].ny, v_arr[f_arr[i].c].nz);
		glVertex3f(v_arr[f_arr[i].c].x, v_arr[f_arr[i].c].y, v_arr[f_arr[i].c].z);
	}
	glEnd();

	glutSwapBuffers();  //����ǰ�󻺳����������Ƶ�ͼ����ʾ����Ļ��

}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

}

void idlefunc(void) {
	theta += 0.5;
	light_position[0] = R * sin(theta / (360) * 2 * pi);
	light_position[2] = R * cos(theta / (360) * 2 * pi);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position); //ָ����Դ��0�Ź�Դ��,��Դ���ԣ���Դλ�ã�
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