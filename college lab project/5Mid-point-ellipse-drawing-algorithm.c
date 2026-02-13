#include <stdio.h>
#include <GL/Glut.h>

int xc, yc, a, b;

void plotPoints(int x, int y)
{
    // Polot all 4 symmetric ponts in 4 quadrants for each region, so total 8
    glVertex2i(xc + x, yc + y);
    glVertex2i(xc - x, yc + y);
    glVertex2i(xc + x, yc - y);
    glVertex2i(xc - x, yc - y);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POINTS);

    int x = 0;
    int y = b;
    int p1 = b * b - a * a + a * a / 4; // initial decision parameter for region 1

    // for region 1, slope < 1
    while (b * b * x <= a * a * y)
    {
        plotPoints(x, y);

        if (p1 < 0)
        {
            x += 1;
            p1 = p1 + 2 * b * b * x + b * b;
        }
        else
        {
            x = x + 1;
            y = y - 1;
            p1 = p1 + 2 * b * b * x - 2 * a * a * y + b * b;
        }
    }

    int p2 = b * b * (x + 0.5) * (x + 0.5) + a * a * (y - 1) * (y - 1) - a * a * b * b; // initial decision parameter for region 2

    // for region 2, slope >1
    while (y >= 0)
    {
        plotPoints(x, y);

        if (p2 > 0)
        {
            y = y - 1;
            p2 = p2 - 2 * a * a * y + a * a;
        }
        else
        {
            x = x + 1;
            y = y - 1;
            p2 = p2 + 2 * b * b * x - 2 * a * a * y + a * a;
        }
    }

    glEnd();
    glFlush();
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-50, 50, -50, 50); 
    glPointSize(4.0f);
}

int main(int argc, char **argv)
{
    printf("Enter center of ellipse (xc yc): ");
    scanf("%d %d", &xc, &yc);

    printf("Enter semi-major axis a and semi-minor axis b: ");
    scanf("%d %d", &a, &b);

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);     // 300 height 300 widhth of window
    glutInitWindowPosition(100, 100); // window appears 100 left of my laptop monitor/screen and 100 down of laptop monitor
    glutCreateWindow(" Ellipse 081BCT0072 (Samrachana Sharma)");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}