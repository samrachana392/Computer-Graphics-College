#include <GL/glut.h>

/* ---------------- GLOBALS ---------------- */

float carScale = 0.25f;
float carY = 0.5f;
bool approaching = true;

float laneOffset = 0.0f;   // Controls road animation

/* ---------------- ROAD ---------------- */

void drawRoad()
{
    // Road trapezoid (perspective)
    glColor3f(0.12f, 0.12f, 0.12f);
    glBegin(GL_QUADS);
    glVertex2f(-0.25f, -1.0f);
    glVertex2f( 0.25f, -1.0f);
    glVertex2f( 0.05f,  1.0f);
    glVertex2f(-0.05f,  1.0f);
    glEnd();

    /* -------- MOVING LANE DASHES -------- */

    glColor3f(1, 1, 1);

    for (float y = -1.0f + laneOffset; y < 1.0f; y += 0.2f)
    {
        float width = 0.02f * (1.0f - y); // perspective shrink

        glBegin(GL_QUADS);
        glVertex2f(-width, y);
        glVertex2f( width, y);
        glVertex2f( width, y + 0.08f);
        glVertex2f(-width, y + 0.08f);
        glEnd();
    }
}

/* ---------------- GRASS ---------------- */

void drawGrass()
{
    glColor3f(0.2f, 0.75f, 0.2f);

    glBegin(GL_QUADS);
    glVertex2f(-1, -1);
    glVertex2f(-0.25f, -1);
    glVertex2f(-0.05f,  1);
    glVertex2f(-1,  1);
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(0.25f, -1);
    glVertex2f(1, -1);
    glVertex2f(1,  1);
    glVertex2f(0.05f, 1);
    glEnd();
}

/* ---------------- BUILDINGS ---------------- */

void drawBuildings()
{
    glColor3f(0.65f, 0.65f, 0.85f);

    // Left
    for (float x = -0.9f; x < -0.3f; x += 0.25f) {
        glBegin(GL_QUADS);
        glVertex2f(x, 0.1f);
        glVertex2f(x + 0.15f, 0.1f);
        glVertex2f(x + 0.15f, 0.8f);
        glVertex2f(x, 0.8f);
        glEnd();
    }

    // Right
    for (float x = 0.35f; x < 0.9f; x += 0.25f) {
        glBegin(GL_QUADS);
        glVertex2f(x, 0.1f);
        glVertex2f(x + 0.15f, 0.1f);
        glVertex2f(x + 0.15f, 0.85f);
        glVertex2f(x, 0.85f);
        glEnd();
    }
}

/* ---------------- CAR (BETTER FRONT VIEW) ---------------- */

void drawCar()
{
    glPushMatrix();

    glTranslatef(0.0f, carY, 0);
    glScalef(carScale, carScale, 1);

    // Body
    glColor3f(1, 0, 0);
    glBegin(GL_QUADS);
    glVertex2f(-0.35f, -0.2f);
    glVertex2f( 0.35f, -0.2f);
    glVertex2f( 0.35f,  0.25f);
    glVertex2f(-0.35f,  0.25f);
    glEnd();

    // Windshield
    glColor3f(0.8f, 0.9f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-0.22f, 0.02f);
    glVertex2f( 0.22f, 0.02f);
    glVertex2f( 0.15f, 0.25f);
    glVertex2f(-0.15f, 0.25f);
    glEnd();

    // Headlights
    glColor3f(1, 1, 0.4f);
    glBegin(GL_QUADS);
    glVertex2f(-0.3f, -0.05f);
    glVertex2f(-0.18f, -0.05f);
    glVertex2f(-0.18f,  0.05f);
    glVertex2f(-0.3f,  0.05f);

    glVertex2f(0.18f, -0.05f);
    glVertex2f(0.3f, -0.05f);
    glVertex2f(0.3f,  0.05f);
    glVertex2f(0.18f,  0.05f);
    glEnd();

    glPopMatrix();
}

/* ---------------- DISPLAY ---------------- */

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Sky
    glColor3f(0.55f, 0.82f, 1.0f);
    glBegin(GL_QUADS);
    glVertex2f(-1, 1);
    glVertex2f( 1, 1);
    glVertex2f( 1,-1);
    glVertex2f(-1,-1);
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
    /* ---- Car Depth Simulation ---- */

    if (approaching) {
        carScale += 0.0005f;
        carY     -= 0.0005f;

        if (carScale > 0.9f)
            approaching = false;
    }
    else {
        carScale -= 0.0005f;
        carY     += 0.0005f;

        if (carScale < 0.25f)
            approaching = true;
    }

    /* ---- Road Motion (CRUCIAL FOR REALISM) ---- */

    laneOffset -= 0.01f;
    if (laneOffset < -0.2f)
        laneOffset = 0.0f;

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
    glutCreateWindow("Realistic Road Motion");

    init();

    glutDisplayFunc(display);
    glutIdleFunc(update);

    glutMainLoop();
    return 0;
}
