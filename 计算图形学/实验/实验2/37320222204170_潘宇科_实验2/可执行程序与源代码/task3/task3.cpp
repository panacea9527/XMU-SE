#include <GL/glut.h>
#include <cmath>

#define PI 3.14159265358979323846
#define DEG_TO_RAD (PI/180.0)

GLfloat beta = 0.0;  // Rotation angle for the cube in degrees

GLfloat camX = 0.0, camY = 0.0, camZ = 5.0; // Camera position
GLfloat camPitch = 0.0, camYaw = 0.0; // Camera looking angles
bool camLocked = false; // Camera movement lock

int mouseX = 0, mouseY = 0; // Last mouse position
float mouseSensitivity = 0.1f; // Mouse sensitivity

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    gluPerspective(60.0, 1.0, 1.0, 100.0);
}
void update(int value) {
    beta += 2.0f;  // Increment the rotation angle
    if (beta > 360.0) {
        beta -= 360.0;  // Wrap around if the angle exceeds 360 degrees
    }
    glutPostRedisplay();  // Redraw the scene with the new rotation angle
    glutTimerFunc(16, update, 0);  // Re-register the timer callback to keep updating
}

void display() {
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

    glColor3f(1.0, 0.0, 0.0); // Red color
    glutWireSphere(2.0, 20, 20);

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 27) {  // ESC key
        exit(0);
    }
    if (camLocked) return;
    switch (key) {
    case 'w': camZ -= 0.1; break;
    case 's': camZ += 0.1; break;
    case 'a': camX -= 0.1; break;
    case 'd': camX += 0.1; break;
    case 'q': camY += 0.1; break;
    case 'e': camY -= 0.1; break;
    }
    glutPostRedisplay();
}

void mouseMove(int x, int y) {
    int deltaX = x - mouseX;
    int deltaY = y - mouseY;
    camYaw += deltaX * mouseSensitivity;
    camPitch -= deltaY * mouseSensitivity;

    mouseX = x;
    mouseY = y;
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Interactive 3D Wireframe Sphere");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutPassiveMotionFunc(mouseMove); // Register mouse movement callback
    glutTimerFunc(0, update, 0); // Register the timer callback
    glutMainLoop();
    return 0;
}
