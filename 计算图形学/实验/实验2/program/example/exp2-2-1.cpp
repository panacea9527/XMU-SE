#include <GL/glut.h>
#include <cmath>

#define DEG_TO_RAD 0.017453292519943295

GLfloat beta = 0.0; // Rotation angle for the cube in degrees
GLfloat camX = 0.0, camY = 0.0, camZ = 5.0; // Camera position
GLfloat camPitch = 0.0, camYaw = 0.0; // Camera looking angles
bool camLocked = false; // Camera movement lock

const GLfloat camSpeed = 0.1;
const GLfloat camAngularSpeed = 0.5;

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

    GLfloat dirX = cos(camPitch * DEG_TO_RAD) * sin(camYaw * DEG_TO_RAD);
    GLfloat dirY = sin(camPitch * DEG_TO_RAD);
    GLfloat dirZ = -cos(camPitch * DEG_TO_RAD) * cos(camYaw * DEG_TO_RAD);

    gluLookAt(camX, camY, camZ,
        camX + dirX, camY + dirY, camZ + dirZ,
        0.0, 1.0, 0.0);

    glRotatef(beta, 0.0, 1.0, 0.0); // Rotate around the y-axis

    glBegin(GL_QUADS); // Using quads to define faces of the cube
    glColor3f(1.0, 0.0, 0.0); glVertex3f(1.0, 1.0, -1.0); glVertex3f(-1.0, 1.0, -1.0); glVertex3f(-1.0, 1.0, 1.0); glVertex3f(1.0, 1.0, 1.0);
    glColor3f(0.5, 0.5, 0.0); glVertex3f(1.0, -1.0, 1.0); glVertex3f(-1.0, -1.0, 1.0); glVertex3f(-1.0, -1.0, -1.0); glVertex3f(1.0, -1.0, -1.0);
    glColor3f(0.0, 1.0, 0.0); glVertex3f(1.0, 1.0, 1.0); glVertex3f(-1.0, 1.0, 1.0); glVertex3f(-1.0, -1.0, 1.0); glVertex3f(1.0, -1.0, 1.0);
    glColor3f(0.0, 0.0, 1.0); glVertex3f(1.0, -1.0, -1.0); glVertex3f(-1.0, -1.0, -1.0); glVertex3f(-1.0, 1.0, -1.0); glVertex3f(1.0, 1.0, -1.0);
    glColor3f(1.0, 0.0, 1.0); glVertex3f(-1.0, 1.0, 1.0); glVertex3f(-1.0, 1.0, -1.0); glVertex3f(-1.0, -1.0, -1.0); glVertex3f(-1.0, -1.0, 1.0);
    glColor3f(0.0, 1.0, 1.0); glVertex3f(1.0, 1.0, -1.0); glVertex3f(1.0, 1.0, 1.0); glVertex3f(1.0, -1.0, 1.0); glVertex3f(1.0, -1.0, -1.0);
    glEnd();

    glutSwapBuffers();
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
    if (camLocked) return;

    switch (key) {
    case 'w':
        camX += camSpeed * sin(camYaw * DEG_TO_RAD);
        camZ -= camSpeed * cos(camYaw * DEG_TO_RAD);
        break;
    case 's':
        camX -= camSpeed * sin(camYaw * DEG_TO_RAD);
        camZ += camSpeed * cos(camYaw * DEG_TO_RAD);
        break;
    case 'a':
        camX -= camSpeed * cos(camYaw * DEG_TO_RAD);
        camZ -= camSpeed * sin(camYaw * DEG_TO_RAD);
        break;
    case 'd':
        camX += camSpeed * cos(camYaw * DEG_TO_RAD);
        camZ += camSpeed * sin(camYaw * DEG_TO_RAD);
        break;
    case 'q':
        camY += camSpeed;
        break;
    case 'e':
        camY -= camSpeed;
        break;
    case 'l':
        camLocked = !camLocked; // Toggle camera movement lock
        break;
    }
    glutPostRedisplay();
}

void mouseMove(int x, int y)
{
    static int lastX = x, lastY = y;
    int deltaX = x - lastX;
    int deltaY = y - lastY;
    if (!camLocked) {
        camYaw += deltaX * camAngularSpeed;
        camPitch += deltaY * camAngularSpeed;
    }
    lastX = x;
    lastY = y;
    glutPostRedisplay();
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
    glutPassiveMotionFunc(mouseMove);  // Register mouse movement callback
    glutMainLoop();
    return 0;
}
