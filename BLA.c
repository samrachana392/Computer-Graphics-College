#include <stdio.h>
#include <GL/glut.h>

int x_start, y_start, x_end, y_end;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POINTS);

    int x = x_start;
    int y = y_start;

    int dx = abs(x_end - x_start);
    int dy = abs(y_end - y_start);

    int sx = (x_end > x_start) ? 1 : -1;   // step for x
    int sy = (y_end > y_start) ? 1 : -1;   // step for y

    glVertex2i(x, y);

    // if slope < 1
    if (dx >= dy)
    {
        int p = 2 * dy - dx;

        for (int i = 0; i < dx; i++)
        {
            x += sx;

            if (p < 0)
            {
                p = p + 2 * dy;
            }
            else
            {
                y += sy;
                p = p + 2 * dy - 2 * dx;
            }

            glVertex2i(x, y);
        }
    }
    // if slope > 1
    else
    {
        int p = 2 * dx - dy;

        for (int i = 0; i < dy; i++)
        {
            y += sy;

            if (p < 0)
            {
                p = p + 2 * dx;
            }
            else
            {
                x += sx;
                p = p + 2 * dx - 2 * dy;
            }

            glVertex2i(x, y);
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
    gluOrtho2D(0, 100, 0, 100);
    glPointSize(4.0);
}

int main(int argc, char **argv)
{
    printf("Enter starting point (x1 y1): ");
    scanf("%d %d", &x_start, &y_start);

    printf("Enter ending point (x2 y2): ");
    scanf("%d %d", &x_end, &y_end);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("BLA (081BCT072 Samrachana Sharma)");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
