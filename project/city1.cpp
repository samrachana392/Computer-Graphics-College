#include <GL/glut.h>

/* ---------------- GLOBALS ---------------- */

float carX = -1.2f;   // Car position
float speed = 0.002f; // Movement speed

/* ---------------- BUILDINGS ---------------- */

void drawBuildings()
{
    glColor3f(0.7f, 0.7f, 0.8f);

    float x = -1.0f;

    for (int i = 0; i < 10; i++) {
        float w = 0.15f;
        float h = 0.3f + (i % 3) * 0.15f;

        glBegin(GL_QUADS);
        glVertex2f(x, 0.2f);
        glVertex2f(x + w, 0.2f);
        glVertex2f(x + w, 0.2f + h);
        glVertex2f(x, 0.2f + h);
        glEnd();

        x += 0.2f;
    }
}

/* ---------------- ROAD ---------------- */

void drawRoad()
{
    // Road
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
    glVertex2f(-1, -0.2f);
    glVertex2f( 1, -0.2f);
    glVertex2f( 1, -1);
    glVertex2f(-1, -1);
    glEnd();

    // Lane markings (dashed)
    glColor3f(1, 1, 1);

    for (float x = -1; x < 1; x += 0.2f) {
        glBegin(GL_QUADS);
        glVertex2f(x, -0.55f);
        glVertex2f(x + 0.1f, -0.55f);
        glVertex2f(x + 0.1f, -0.58f);
        glVertex2f(x, -0.58f);
        glEnd();
    }
}

/* ---------------- CAR ---------------- */

void drawCar()
{
    glPushMatrix();
    glTranslatef(carX, -0.55f, 0);

    // Car body (RED)
    glColor3f(1, 0, 0);
    glBegin(GL_QUADS);
    glVertex2f(-0.15f, 0.05f);
    glVertex2f( 0.15f, 0.05f);
    glVertex2f( 0.15f, 0.15f);
    glVertex2f(-0.15f, 0.15f);
    glEnd();

    // Car top
    glBegin(GL_QUADS);
    glVertex2f(-0.08f, 0.15f);
    glVertex2f( 0.08f, 0.15f);
    glVertex2f( 0.05f, 0.23f);
    glVertex2f(-0.05f, 0.23f);
    glEnd();

    // Wheels
    glColor3f(0, 0, 0);
    glutSolidTorus(0.01, 0.03, 10, 20); // Left wheel
    glTranslatef(0.18f, 0, 0);
    glutSolidTorus(0.01, 0.03, 10, 20); // Right wheel

    glPopMatrix();
}

/* ---------------- DISPLAY ---------------- */

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Sky background
    glColor3f(0.5f, 0.8f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-1, 1);
    glVertex2f( 1, 1);
    glVertex2f( 1, -0.2f);
    glVertex2f(-1, -0.2f);
    glEnd();

    drawBuildings();
    drawRoad();
    drawCar();

    glutSwapBuffers();
}

/* ---------------- ANIMATION ---------------- */

void update()
{
    carX += speed;

    if (carX > 1.2f)  // Reset when leaving screen
        carX = -1.2f;

    glutPostRedisplay();
}

/* ---------------- INIT ---------------- */

void init()
{
    glClearColor(1, 1, 1, 1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1);
}

/* ---------------- MAIN ---------------- */

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("2D Moving Car");

    init();

    glutDisplayFunc(display);
    glutIdleFunc(update);

    glutMainLoop();
    return 0;
}
