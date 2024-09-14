#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

const GLfloat PI = 3.1415926536f;
const GLfloat RADIUS = 0.5f;
const int NUM_SEGMENTS = 70;

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glShadeModel(GL_FLAT);
}

void drawCircleSegment(GLfloat startAngle, GLfloat endAngle, GLfloat red, GLfloat green, GLfloat blue) {
    glBegin(GL_POLYGON);
    glColor3f(red, green, blue);
    glVertex2f(0, 0);
    for (int i = 0; i <= NUM_SEGMENTS; ++i) {
        GLfloat angle = startAngle + (endAngle - startAngle) * i / NUM_SEGMENTS;
        glVertex2f(RADIUS * sin(angle), RADIUS * cos(angle));
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    GLfloat angleDelta = 2 * PI / 7;
    GLfloat angle = 0.0;

    // 七种不同颜色
    GLfloat colors[7][3] = {
        {1.0, 0.0, 0.0}, // 红色
        {1.0, 0.5, 0.0}, // 橙色
        {1.0, 1.0, 0.0}, // 黄色
        {0.0, 1.0, 0.0}, // 绿色
        {0.0, 0.0, 1.0}, // 蓝色
        {0.5, 0.0, 1.0}, // 靛蓝色
        {1.0, 0.0, 1.0}  // 紫色
    };

    for (int i = 0; i < 7; ++i) {
        drawCircleSegment(angle, angle + angleDelta, colors[i][0], colors[i][1], colors[i][2]);
        angle += angleDelta;
    }

    glFlush();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Task2");

    if (!glutGet(GLUT_DISPLAY_MODE_POSSIBLE)) {
        fprintf(stderr, "Cannot set OpenGL display mode\n");
        return 1;
    }

    init();
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}

