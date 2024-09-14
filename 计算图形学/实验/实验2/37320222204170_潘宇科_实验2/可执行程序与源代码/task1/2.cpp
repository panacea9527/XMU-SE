#include <GL/freeglut.h>
#include <cmath>

const int levels = 5;  // 递归层数

void drawTriangle(float ax, float ay, float bx, float by, float cx, float cy, float r, float g, float b) {
    glBegin(GL_TRIANGLES);
    glColor3f(r, g, b);
    glVertex2f(ax, ay);
    glVertex2f(bx, by);
    glVertex2f(cx, cy);
    glEnd();
}

void drawSierpinski(float ax, float ay, float bx, float by, float cx, float cy, int level) {
    if (level == 0) {
        // 基础级颜色为蓝色
        drawTriangle(ax, ay, bx, by, cx, cy, 0.1f * level, 0.1f * level, 1.0f - 0.2f * level);
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
    drawSierpinski(0.1, 0.1, 0.9, 0.1, 0.5, 0.9, levels);
    glFlush();  // 使用 glFlush() 替换 glutSwapBuffers() 用于单缓冲模式
}

void initOpenGL() {
    glClearColor(0.0, 0.0, 0.0, 1.0); // 设置背景颜色为黑色
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 1.0, 0.0, 1.0); // 设置二维视图区域
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // 使用单缓冲和 RGB 颜色模式
    glutInitWindowSize(600, 600); // 设置窗口大小
    glutCreateWindow("Static Sierpinski Gasket with Colors"); // 创建窗口
    initOpenGL();
    glutDisplayFunc(display); // 设置显示回调函数
    glutMainLoop();
    return 0;
}
