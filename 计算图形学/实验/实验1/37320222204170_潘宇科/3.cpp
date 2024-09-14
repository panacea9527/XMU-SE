#include <GL/glut.h>
#include <math.h>

const GLfloat R = 0.25f;
const GLfloat r = 0.2f;
const GLfloat Pi = 3.1415926536f;
const int n = 3600;

// Function prototype for drawLines
void drawLines(GLfloat red, GLfloat green, GLfloat blue, int start, int end);

void init() {
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glShadeModel(GL_FLAT);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Draw the lines with specified colors and translations
    glTranslatef(0.0f, 0.25f, 0.0f);
    drawLines(0.0f, 0.0f, 0.0f, 0, n);

    glTranslatef(0.55f, 0.0f, 0.0f);
    drawLines(1.0f, 0.0f, 0.0f, 0, n);

    glTranslatef(-1.1f, 0.0f, 0.0f);
    drawLines(0.0f, 0.5f, 0.8f, 0, n);

    glTranslatef(0.275f, -0.25f, 0.0f);
    drawLines(1.0f, 0.8f, 0.0f, 0, n);

    glTranslatef(0.55f, 0.0f, 0.0f);
    drawLines(0.1f, 0.6f, 0.0f, 0, n);

    glTranslatef(-0.275f, 0.25f, 0.0f);
    drawLines(0.0f, 0.0f, 0.0f, 900, 1300);

    drawLines(0.0f, 0.0f, 0.0f, 1800, 2200);

    glTranslatef(0.55f, 0.0f, 0.0f);
    drawLines(1.0f, 0.0f, 0.0f, 1800, 2200);

    glTranslatef(-1.1f, 0.0f, 0.0f);
    drawLines(0.0f, 0.5f, 0.8f, 900, 1300);

    glFlush();
}

// Draw lines with specified color and range
void drawLines(GLfloat red, GLfloat green, GLfloat blue, int start, int end) {
    glBegin(GL_LINES);
    glColor3f(red, green, blue);
    for (int i = start; i <= end; i++) {
        glVertex2f(r * sin(2 * Pi / n * i), r * cos(2 * Pi / n * i));
        glVertex2f(R * sin(2 * Pi / n * i), R * cos(2 * Pi / n * i));
    }
    glEnd();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Task3");

    glutDisplayFunc(display);
    init();

    glutMainLoop();

    return 0;
}
