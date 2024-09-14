#include <GL/glut.h>
#include <math.h>

#define DEG_TO_RAD 0.017453
const GLfloat RR = 2.0; // Camera radius
GLfloat beta = 0;

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
    GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);

    glShadeModel(GL_SMOOTH);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(RR * sin(beta * DEG_TO_RAD), RR * cos(beta * DEG_TO_RAD) * cos(45.0), RR * cos(beta * DEG_TO_RAD) * sin(45.0),
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0);

    // 开始绘制立方体
    glBegin(GL_TRIANGLES);

    // Front face
    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, 1.0);

    // Back face
    glColor3f(0.0, 1.0, 0.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(1.0, -1.0, -1.0);

    // Top face
    glColor3f(0.0, 0.0, 1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(1.0, 1.0, -1.0);

    // Bottom face
    glColor3f(1.0, 1.0, 0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(-1.0, -1.0, 1.0);

    // Right face
    glColor3f(1.0, 0.0, 1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);

    // Left face
    glColor3f(0.0, 1.0, 1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, -1.0);

    glEnd();
    glutSwapBuffers();
}


void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-4.0, 4.0, -4.0, 4.0, -4.0, 4.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}

void idlefunc() {
    beta += 0.05;
    if (beta > 360) beta -= 360;
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'b': {
        GLfloat brass_ambient[] = { 0.33f, 0.22f, 0.03f, 1.0f };
        GLfloat brass_diffuse[] = { 0.78f, 0.57f, 0.11f, 1.0f };
        GLfloat brass_specular[] = { 0.99f, 0.94f, 0.81f, 1.0f };
        GLfloat brass_shininess = 27.8f;
        glMaterialfv(GL_FRONT, GL_AMBIENT, brass_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, brass_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, brass_specular);
        glMaterialf(GL_FRONT, GL_SHININESS, brass_shininess);
        break;
    }
    case 'n': {
        GLfloat plastic_ambient[] = { 0.3, 0.0, 0.0, 1.0 };
        GLfloat plastic_diffuse[] = { 0.6, 0.0, 0.0, 1.0 };
        GLfloat plastic_specular[] = { 0.8, 0.6, 0.6, 1.0 };
        GLfloat plastic_shininess = 32.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT, plastic_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, plastic_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, plastic_specular);
        glMaterialf(GL_FRONT, GL_SHININESS, plastic_shininess);
        break;
    }
    case 'm': {
        GLfloat white_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
        GLfloat white_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat white_specular[] = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat white_shininess = 100.0;
        glMaterialfv(GL_FRONT, GL_AMBIENT, white_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, white_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, white_specular);
        glMaterialf(GL_FRONT, GL_SHININESS, white_shininess);
        break;
    }
    case 'o': {
        GLfloat white_light[] = { 1.0, 1.0, 1.0, 1.0 };
        glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
        glLightfv(GL_LIGHT0, GL_SPECULAR, white_light);
        break;
    }
    case 'p': {
        GLfloat colorLight[] = { 1.0, 0.0, 0.0, 1.0 };  // 红色漫反射光
        GLfloat colorSpecular[] = { 0.0, 0.0, 1.0, 1.0 };  // 蓝色镜面反射光
        glLightfv(GL_LIGHT0, GL_DIFFUSE, colorLight);
        glLightfv(GL_LIGHT0, GL_SPECULAR, colorSpecular);
        break;
    }
    case 27:
        exit(0);
        break;
    }
    glutPostRedisplay();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idlefunc);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
