#include <GL/freeglut.h>
#include <cmath>

const int levels = 5;  // µÝ¹é²ãÊý
float angle = 0.0;
float scale = 1.0;
bool scalingUp = true;
float colorShift = 0.0;

void drawTriangle(float ax, float ay, float bx, float by, float cx, float cy) {
    glBegin(GL_TRIANGLES);
    glColor3f((sin(colorShift) + 1) / 2, (sin(colorShift + 2) + 1) / 2, (sin(colorShift + 4) + 1) / 2);
    glVertex2f(ax, ay);
    glVertex2f(bx, by);
    glVertex2f(cx, cy);
    glEnd();
}

void drawSierpinski(float ax, float ay, float bx, float by, float cx, float cy, int level) {
    if (level == 0) {
        drawTriangle(ax, ay, bx, by, cx, cy);
    }
    else {
        float abx = (ax + bx) / 2;
        float aby = (ay + by) / 2;
        float acx = (ax + cx) / 2;
        float acy = (ay + cy) / 2;
        float bcx = (bx + cx) / 2;
        float bcy = (by + cy) / 2;
        drawSierpinski(ax, ay, abx, aby, acx, acy, level - 1);
        drawSierpinski(abx, aby, bx, by, bcx, bcy, level - 1);
        drawSierpinski(acx, acy, bcx, bcy, cx, cy, level - 1);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glTranslatef(0.5f, 0.5f, 0.0f);
    glScalef(scale, scale, 1.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glTranslatef(-0.5f, -0.5f, 0.0f);
    drawSierpinski(0.1, 0.1, 0.9, 0.1, 0.5, 0.9, levels);
    glutSwapBuffers();
}

void update(int value) {
    angle += 0.5;
    if (scalingUp) {
        scale += 0.01;
        if (scale >= 1.2) scalingUp = false;
    }
    else {
        scale -= 0.01;
        if (scale <= 0.8) scalingUp = true;
    }
    colorShift += 0.05;
    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void initOpenGL() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 1.0, 0.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Animated Sierpinski Gasket");
    initOpenGL();
    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}
