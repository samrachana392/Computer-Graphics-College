#include <GL/glut.h> 
#include <stdio.h>
#include <math.h>

float x_start, y_start, x_end, y_end;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_POINTS);

    float dx = x_end - x_start;
    float dy = y_end - y_start;

    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    float xIncrement = dx / steps;
    float yIncrement = dy / steps;

    float x = x_start;
    float y = y_start;

    for (int i = 0; i <= steps; i++)
    {
        glVertex2i(round(x), round(y));

        x = x + xIncrement;
        y = y + yIncrement;
    }

    glEnd();
    glFlush();
}

void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 100, 0, 100);
    glPointSize(4.0f);
}

int main(int argc, char **argv)
{
    printf("Enter x_start y_start: ");
    scanf("%f %f", &x_start, &y_start);

    printf("Enter x_end y_end: ");
    scanf("%f %f", &x_end, &y_end);

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("DDA Line Drawing Algorithm");
    
    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
