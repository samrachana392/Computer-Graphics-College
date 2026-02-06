#include <stdio.h>
#include <GL/Glut.h>

int xc, yc, r;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POINTS);

    int x = 0;
    int y = r;
    int p = 1 - r; // initial decision parameter P0

    while (x <= y)
    {
        // Plot 8 symmetric points for 8 octants
        // initial points
        glVertex2i(xc + x, yc + y);
        glVertex2i(xc - x, yc + y);
        glVertex2i(xc + x, yc - y);
        glVertex2i(xc - x, yc - y);

        glVertex2i(xc + y, yc + x);
        glVertex2i(xc - y, yc + x);
        glVertex2i(xc + y, yc - x);
        glVertex2i(xc - y, yc - x);

        if (p < 0)
        {
            x += 1;
            p = p + 2 * x + 1;
        }
        else
        {
            x = x + 1;
            y = y - 1;
            p = p + 2 * x - 2 * y + 1;
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
    gluOrtho2D(-50, 50, -50, 50);  //  gluOrtho2D(0, 100, 0, 100) would map form 0 to 100 in x axis and 0 to 100 in y axis 
    // but here since we need all axes, we do -50 to 50 for x axis and -50 to 50 in y axis so that all negative numbers are also shown  
 
 
    glPointSize(2.0f);
}

int main(int argc, char **argv)
{
    printf("Enter center of circle (xc yc): ");
    scanf("%d %d", &xc, &yc);

    printf("Enter radius: ");
    scanf("%d", &r);

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);     // 300 height 300 widhth of window
    glutInitWindowPosition(100, 100); // window appears 100 left of my laptop monitor/screen and 100 down of laptop monitor
    glutCreateWindow("Circle 081BCT0072 (Samrachana Sharma)");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}