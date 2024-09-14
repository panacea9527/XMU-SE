#include <GL/freeglut.h>
#include <stdlib.h>
#include <vector>
using namespace std;

class Point2d {
public:
    GLfloat x = 0.0f;
    GLfloat y = 0.0f;
    Point2d(const GLfloat& a, const GLfloat& b) : x(a), y(b) {}
    Point2d() {}
};

Point2d triVer[3];  // 初始三角形顶点

// 计算两点连线的中点
Point2d halfScale(const Point2d& a, const Point2d& b) {
    Point2d res;
    res.x = (a.x + b.x) / 2.0;
    res.y = (a.y + b.y) / 2.0;
    return res;
}

void SierpinskiDisp() {

    // 设置初始三角形顶点
    triVer[0] = Point2d(-0.8f, -0.8f);
    triVer[1] = Point2d(0.0f, 0.8f);
    triVer[2] = Point2d(0.8f, -0.8f);

    vector<Point2d> points(5000);

    // 取三角形一条中位线的中点做为初始三角形内的点
    Point2d u, v, p;
    u = halfScale(triVer[0], triVer[1]);
    v = halfScale(triVer[0], triVer[2]);
    p = halfScale(u, v);
    points[0].x = p.x;
    points[0].y = p.y;

    for (int i = 1; i < 5000; i++) {
        int j = rand() % 3;
        p = halfScale(points[i - 1], triVer[j]);
        points[i] = p;
    }
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    // 画三角形顶点
    glColor3f(1.0f, 0.0f, 0.0f);
    glPointSize(6.0f);
    glBegin(GL_POINTS);
    for (int i = 0; i < 3; i++) {
        glVertex2f(triVer[i].x, triVer[i].y);
    }
    glEnd();

    // 画随机生成的5000个点
    glColor3f(1.0f, 1.0f, 0.0f);
    glPointSize(3.0f);
    glBegin(GL_POINTS);
    for (int i = 0; i < 5000; i++) {
        glVertex2f(points[i].x, points[i].y);
    }
    glEnd();
    glFlush();
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Sierpinski镂垫");
    glutDisplayFunc(&SierpinskiDisp);
    glutMainLoop();
}
