#include <GL/glut.h>
#include <math.h>
#define PI 3.1415926535

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);//�׵�
	glShadeModel(GL_FLAT); //ʹ�õ�һ��ɫ
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST); //������Ȳ���
	glDepthFunc(GL_LEQUAL);
	glLoadIdentity();       //��ǰ�����ʼ��Ϊ��λ����
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

//glTranslatef(0, 0, -0.2f);//ͨ���ƶ���� �ɹ� ��zΪ�� �����ӽ�ǰ���ƶ� zΪ�����ӽ�Խ��ԽԶ
void display(void)
{
	int n = 180;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//��ɫ��   
	glTranslatef(0, 0.2f, 0);	//��һ�������ƶ�x	 �ڶ�������y			
	glColor3f(0, 0, 0);
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < n + 1; i++)
	{
		glVertex3f(0.25 * cos(2 * PI * i / n), 0.25 * sin(2 * PI * i / n), 0.95f);
		glVertex3f(0.21 * cos(2 * PI * i / n), 0.21 * sin(2 * PI * i / n), 0.95f);
	}
	glEnd();
	//��ɫ�� 
	glTranslatef(-0.55f, 0, 0);
	glColor3f(0, 0.5, 0.8);
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < n + 1; i++)
	{
		glVertex3f(0.25 * cos(2 * PI * i / n), 0.25 * sin(2 * PI * i / n), 0.95f);
		glVertex3f(0.21 * cos(2 * PI * i / n), 0.21 * sin(2 * PI * i / n), 0.95f);
	}
	glEnd();
	//��ɫ��  
	glTranslatef(1.1f, 0, 0);
	glColor3f(0.9, 0.15, 0);
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < n + 1; i++)
	{
		glVertex3f(0.25 * cos(2 * PI * i / n), 0.25 * sin(2 * PI * i / n), 0.95f);
		glVertex3f(0.21 * cos(2 * PI * i / n), 0.21 * sin(2 * PI * i / n), 0.95f);
	}
	glEnd();
	//��ɫ�� 
	glTranslatef(-0.275f, -0.25f, 0);
	glColor3f(0, 0.8, 0);
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < n / 8 + 1; i++)
	{
		glVertex3f(0.25 * cos(2 * PI * i / n), 0.25 * sin(2 * PI * i / n), 1.0f);
		glVertex3f(0.21 * cos(2 * PI * i / n), 0.21 * sin(2 * PI * i / n), 1.0f);
	}
	for (int i = n / 8; i < n / 4 + 1; i++)
	{
		glVertex3f(0.25 * cos(2 * PI * i / n), 0.25 * sin(2 * PI * i / n), 0.9f);
		glVertex3f(0.21 * cos(2 * PI * i / n), 0.21 * sin(2 * PI * i / n), 0.9f);
	}
	for (int i = n / 4; i < n * 3 / 8 + 1; i++)
	{
		glVertex3f(0.25 * cos(2 * PI * i / n), 0.25 * sin(2 * PI * i / n), 1.0f);
		glVertex3f(0.21 * cos(2 * PI * i / n), 0.21 * sin(2 * PI * i / n), 1.0f);
	}
	for (int i = n * 3 / 8; i < n + 1; i++)
	{
		glVertex3f(0.25 * cos(2 * PI * i / n), 0.25 * sin(2 * PI * i / n), 0.9f);
		glVertex3f(0.21 * cos(2 * PI * i / n), 0.21 * sin(2 * PI * i / n), 0.9f);
	}
	glEnd();
	//��ɫ�� 
	glTranslatef(-0.55f, 0, 0);
	glColor3f(1.0f, 0.7f, 0);
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < n / 8 + 1; i++)
	{
		glVertex3f(0.25 * cos(2 * PI * i / n), 0.25 * sin(2 * PI * i / n), 1.0f);
		glVertex3f(0.21 * cos(2 * PI * i / n), 0.21 * sin(2 * PI * i / n), 1.0f);
	}
	for (int i = n / 8; i < n / 4 + 1; i++)
	{
		glVertex3f(0.25 * cos(2 * PI * i / n), 0.25 * sin(2 * PI * i / n), 0.9f);
		glVertex3f(0.21 * cos(2 * PI * i / n), 0.21 * sin(2 * PI * i / n), 0.9f);
	}
	for (int i = n / 4; i < n * 3 / 8 + 1; i++)
	{
		glVertex3f(0.25 * cos(2 * PI * i / n), 0.25 * sin(2 * PI * i / n), 1.0f);
		glVertex3f(0.21 * cos(2 * PI * i / n), 0.21 * sin(2 * PI * i / n), 1.0f);
	}
	for (int i = n * 3 / 8; i < n + 1; i++)
	{
		glVertex3f(0.25 * cos(2 * PI * i / n), 0.25 * sin(2 * PI * i / n), 0.9f);
		glVertex3f(0.21 * cos(2 * PI * i / n), 0.21 * sin(2 * PI * i / n), 0.9f);
	}
	glEnd();
	glFlush();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);   //�Ѿ�������ΪͶӰ����
	glLoadIdentity();
	//glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
	//glOrtho(-1.0, 1.0, -1.0 , 1.0 , -10.0, 10.0);
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:
		exit(0);
		break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(100, 100); //���ڴ�����Ļ���Ͻǵ�λ��
	glutCreateWindow("�����廷");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
