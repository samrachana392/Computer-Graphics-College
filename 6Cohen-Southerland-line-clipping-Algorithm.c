#include <stdio.h>
#include <GL/glut.h>

#define INSIDE 0   // 0000
#define LEFT   1   // 0001
#define RIGHT  2   // 0010
#define BOTTOM 4   // 0100
#define TOP    8   // 1000

int xmin=50 , ymin=50 , xmax=200 , ymax=200;

int x1, y1, x2, y2;

// calculating region code for a point 
int computeCode(int x, int y)
{
    int code = INSIDE;
    if (x < xmin)
        code |= LEFT;
    else if (x > xmax)
        code |= RIGHT;

    if (y < ymin)
        code |= BOTTOM;
    else if (y > ymax)
        code |= TOP;

    return code;
}
// Cohen–Sutherland line clipping algorithm 
void cohenSutherlandClip()
{
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);

    int accept = 0;

    while (1)
    {
        // Case 1: Both endpoints inside window 
        if ((code1 == 0) && (code2 == 0))
        {
            accept = 1;
            break;
        }
        // Case 2: Both endpoints share outside region 
        else if (code1 & code2)
        {
            break;
        }
        // Case 3: Line partially inside 
        else
        {
            int codeOut;
            float x, y;

            // Select outside point
            if (code1 != 0)
                codeOut = code1;
            else
                codeOut = code2;

            // Find intersection point 
            if (codeOut & TOP)
            {
                x = x1 + (x2 - x1) * (ymax - y1) / (float)(y2 - y1);
                y = ymax;
            }
            else if (codeOut & BOTTOM)
            {
                x = x1 + (x2 - x1) * (ymin - y1) / (float)(y2 - y1);
                y = ymin;
            }
            else if (codeOut & RIGHT)
            {
                y = y1 + (y2 - y1) * (xmax - x1) / (float)(x2 - x1);
                x = xmax;
            }
            else if (codeOut & LEFT)
            {
                y = y1 + (y2 - y1) * (xmin - x1) / (float)(x2 - x1);
                x = xmin;
            }

            // Replace outside point with intersection 
            if (codeOut == code1)
            {
                x1 = (int)x;
                y1 = (int)y;
                code1 = computeCode(x1, y1);
            }
            else
            {
                x2 = (int)x;
                y2 = (int)y;
                code2 = computeCode(x2, y2);
            }
        }
    }

    // Draw clipped line if accepted 
    if (accept)
    {
        glColor3f(0.0, 1.0, 0.0); // green clipped line
        glBegin(GL_LINES);
        glVertex2i(x1, y1);
        glVertex2i(x2, y2);
        glEnd();
    }
}

// Display function 
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw clipping window 
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
    glVertex2i(xmin, ymin);
    glVertex2i(xmax, ymin);
    glVertex2i(xmax, ymax);
    glVertex2i(xmin, ymax);
    glEnd();

    // Draw original line (red) 
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2i(x1, y1);
    glVertex2i(x2, y2);
    glEnd();

    // Perform clipping and draw clipped line
    cohenSutherlandClip();

    glFlush();
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-100, 100, -100, 100);
}

// Main function 
int main(int argc, char **argv)
{
    printf("Enter line endpoints (x1 y1 x2 y2): ");
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Cohen-Sutherland Line Clipping (Samrachana Sharma)");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
