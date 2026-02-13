#include <GL/glut.h>

/* ---------------- GLOBALS ---------------- */

float carScale = 0.2f;      // Small (far)
float carY = 0.6f;          // Near horizon
float speed = 0.0008f;      // Animation speed
bool approaching = true;

/* ---------------- ROAD ---------------- */

void drawRoad()
{
    glColor3f(0.15f, 0.15f, 0.15f);

    glBegin(GL_QUADS);
    glVertex2f(-0.2f, -1.0f);   // Bottom left
    glVertex2f( 0.2f, -1.0f);   // Bottom right
    glVertex2f( 0.05f,  1.0f);  // Top right (narrow)
    glVertex2f(-0.05f,  1.0f);  // Top left
    glEnd();

    // Lane divider
    glColor3f(1, 1, 1);
    for (float y = -1; y < 1; y += 0.2f) {
        glBegin(GL_QUADS);
        glVertex2f(-0.01f, y);
        glVertex2f( 0.01f, y);
        glVertex2f( 0.01f, y + 0.1f);
        glVertex2f(-0.01f, y + 0.1f);
        glEnd();
    }
}

/* ---------------- GRASS ---------------- */

void drawGrass()
{
    glColor3f(0.2f, 0.7f, 0.2f);

    glBegin(GL_QUADS);
    glVertex2f(-1, -1);
    glVertex2f(-0.2f, -1);
    glVertex2f(-0.05f, 1);
    glVertex2f(-1, 1);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(0.2f, -1);
    glVertex2f(1, -1);
    glVertex2f(1, 1);
    glVertex2f(0.05f, 1);
    glEnd();
}

/* ---------------- BUILDINGS ---------------- */

void drawBuildings()
{
    glColor3f(0.6f, 0.6f, 0.8f);

    // Left buildings
    for (float x = -0.9f; x < -0.25f; x += 0.25f) {
        glBegin(GL_QUADS);
        glVertex2f(x, 0.2f);
        glVertex2f(x + 0.15f, 0.2f);
        glVertex2f(x + 0.15f, 0.7f);
        glVertex2f(x, 0.7f);
        glEnd();
    }

    // Right buildings
    for (float x = 0.3f; x < 0.9f; x += 0.25f) {
        glBegin(GL_QUADS);
        glVertex2f(x, 0.2f);
        glVertex2f(x + 0.15f, 0.2f);
        glVertex2f(x + 0.15f, 0.75f);
        glVertex2f(x, 0.75f);
        glEnd();
    }
}

/* ---------------- CAR (FRONT VIEW) ---------------- */

void drawCar()
{
    glPushMatrix();

    glTranslatef(0.0f, carY, 0);
    glScalef(carScale, carScale, 1);

    // Body (Red)
    glColor3f(1, 0, 0);
    glBegin(GL_QUADS);
    glVertex2f(-0.3f, -0.2f);
    glVertex2f( 0.3f, -0.2f);
    glVertex2f( 0.3f,  0.2f);
    glVertex2f(-0.3f,  0.2f);
    glEnd();

    // Windshield
    glColor3f(0.8f, 0.9f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.2f, 0.0f);
    glVertex2f( 0.2f, 0.0f);
    glVertex2f( 0.15f, 0.2f);
    glVertex2f(-0.15f, 0.2f);
    glEnd();

    // Headlights
    glColor3f(1, 1, 0.3f);
    glBegin(GL_QUADS);
    glVertex2f(-0.25f, -0.05f);
    glVertex2f(-0.15f, -0.05f);
    glVertex2f(-0.15f,  0.05f);
    glVertex2f(-0.25f,  0.05f);

    glVertex2f(0.15f, -0.05f);
    glVertex2f(0.25f, -0.05f);
    glVertex2f(0.25f,  0.05f);
    glVertex2f(0.15f,  0.05f);
    glEnd();

    glPopMatrix();
}

/* ---------------- DISPLAY ---------------- */

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Sky
    glColor3f(0.5f, 0.8f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-1, 1);
    glVertex2f( 1, 1);
    glVertex2f( 1, -1);
    glVertex2f(-1, -1);
    glEnd();

    drawGrass();
    drawRoad();
    drawBuildings();
    drawCar();

    glutSwapBuffers();
}

/* ---------------- ANIMATION ---------------- */

void update()
{
    if (approaching) {
        carScale += speed;
        carY -= speed;    // Move downward (towards viewer)

        if (carScale > 0.8f)
            approaching = false;
    }
    else {
        carScale -= speed;
        carY += speed;    // Move upward (away)

        if (carScale < 0.2f)
            approaching = true;
    }

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
    glutCreateWindow("Front View Road Perspective");

    init();

    glutDisplayFunc(display);
    glutIdleFunc(update);

    glutMainLoop();
    return 0;
}
