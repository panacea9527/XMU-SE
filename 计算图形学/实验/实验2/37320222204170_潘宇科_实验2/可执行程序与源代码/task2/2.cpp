#include <GL/glut.h>
#include <cmath>

#define DEG_TO_RAD 0.017453292519943295

GLfloat beta = 0.0;  // Rotation angle for the cube in degrees

void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);  // Black background
    glEnable(GL_DEPTH_TEST);            // Enable depth testing for 3D
    glShadeModel(GL_SMOOTH);            // Enable smooth shading
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0,  // Camera is at (0,0,5)
        0.0, 0.0, 0.0,  // Looking at the origin
        0.0, 1.0, 0.0); // Up vector is positive Y

    // Apply rotation to simulate original camera rotation
    glRotatef(beta, 0.0, 1.0, 0.0); // Rotate around the y-axis

    // Draw the cube
    glBegin(GL_QUADS); // Using quads to define faces of the cube
    // Top face (y = 1.0)
    glColor3f(1.0, 0.0, 0.0);  // Red
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);

    // Bottom face (y = -1.0)
    glColor3f(0.5, 0.5, 0.0);  // Yellow
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(1.0, -1.0, -1.0);

    // Front face  (z = 1.0)
    glColor3f(0.0, 1.0, 0.0);  // Green
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);

    // Back face (z = -1.0)
    glColor3f(0.0, 0.0, 1.0);  // Blue
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(1.0, 1.0, -1.0);

    // Left face (x = -1.0)
    glColor3f(1.0, 0.0, 1.0);  // Magenta
    glVertex3f(-1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, 1.0);

    // Right face (x = 1.0)
    glColor3f(0.0, 1.0, 1.0);  // Cyan
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, -1.0);

    glEnd();  // End of drawing color-cube

    glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
}

void update(int value)
{
    beta += 2.0f;  // Increase the rotation angle
    if (beta > 360.0) {
        beta -= 360.0;
    }

    glutPostRedisplay();  // Call display function to redraw the cube
    glutTimerFunc(16, update, 0);  // Set up next timer
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 27) {  // ESC key
        exit(0);
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("3D Cube Rotation");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, update, 0);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

