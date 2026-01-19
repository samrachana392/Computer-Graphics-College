#include <stdio.h>
#include <GL/Glut.h>

// Assumptions we made:
// line drawn left to right
// slope 0 <= m <= 1
// x_end > x_start

int x_start, y_start, x_end, y_end;


void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POINTS);

    int dx = x_end - x_start;
    int dy = y_end - y_start;

    int p = 2 * dy - dx; // initial P0

    int x = x_start;
    int y = y_start;

    glVertex2i(x, y); // 2i means 2 coordinates (x and y) and data type = integer

    while (x < x_end) // or for (int i=0;i<dx;i++)
    {
        if (p < 0){
            x += 1;
            p = p + 2 * dy;
        }
        else{
            x += 1;
            y += 1;
            p = p + 2 * dy - 2 * dx;
        }
        glVertex2i(x, y);
    }

    glEnd();
    glFlush();
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);      
    glLoadIdentity();
    gluOrtho2D(0,100,0,100);
    glPointSize(4.0f); 
}

int main(int argc, char **argv)
{
    printf("Enter starting points (x_start, y_start): ");
    scanf("%d %d", &x_start, &y_start);

    printf("Enter ending points (x_end, y_end): ");
    scanf("%d %d", &x_end, &y_end);

    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500); // 500 height 500 widhth of window
    glutInitWindowPosition(100, 100); // window appears 100 left of my laptop monitor/screen and 100 down of laptop monitor
    glutCreateWindow("Bresenham Line Algorithm");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}