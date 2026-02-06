#include <stdio.h>        // For printf() and scanf()
#include <GL/glut.h>     // For OpenGL and GLUT functions

/* ------------------ REGION CODE DEFINITIONS ------------------ */
/*
Each region code is a 4-bit binary number.
Bit position (from LSB to MSB):

0001 -> LEFT
0010 -> RIGHT
0100 -> BOTTOM
1000 -> TOP
*/

#define INSIDE 0   // 0000 -> Point lies inside the clipping window
#define LEFT   1   // 0001 -> Point lies to the left of window
#define RIGHT  2   // 0010 -> Point lies to the right of window
#define BOTTOM 4   // 0100 -> Point lies below the window
#define TOP    8   // 1000 -> Point lies above the window

/* ------------------ GLOBAL VARIABLES ------------------ */

/* Clipping window boundaries */
int xmin, ymin;   // Bottom-left corner of window
int xmax, ymax;   // Top-right corner of window

/* Line endpoints */
int x1, y1;       // First endpoint of line
int x2, y2;       // Second endpoint of line

/* ------------------ FUNCTION TO COMPUTE REGION CODE ------------------ */
int computeCode(int x, int y)
{
    /*
    This function determines where a point (x, y) lies
    relative to the clipping window and returns its region code.
    */

    int code = INSIDE;   // Start assuming point is inside

    /* Check left side */
    if (x < xmin)
        code |= LEFT;    // Set LEFT bit

    /* Check right side */
    else if (x > xmax)
        code |= RIGHT;   // Set RIGHT bit

    /* Check bottom side */
    if (y < ymin)
        code |= BOTTOM;  // Set BOTTOM bit

    /* Check top side */
    else if (y > ymax)
        code |= TOP;     // Set TOP bit

    return code;         // Return final 4-bit region code
}

/* ------------------ COHEN–SUTHERLAND CLIPPING FUNCTION ------------------ */
void cohenSutherlandClip()
{
    /* Compute region codes for both endpoints */
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);

    int accept = 0;  // Flag to decide whether line is accepted

    while (1)
    {
        /* Case 1: Both endpoints are inside */
        if ((code1 == 0) && (code2 == 0))
        {
            accept = 1;   // Line is completely inside
            break;
        }

        /* Case 2: Logical AND is non-zero -> completely outside */
        else if (code1 & code2)
        {
            break;        // Reject the line
        }

        /* Case 3: Line is partially inside */
        else
        {
            int codeOut;  // Region code of point outside window
            float x, y;  // Intersection point

            /* Choose the endpoint which is outside */
            if (code1 != 0)
                codeOut = code1;
            else
                codeOut = code2;

            /* Find intersection with clipping boundary */

            /* Point is above the window */
            if (codeOut & TOP)
            {
                x = x1 + (x2 - x1) * (ymax - y1) / (float)(y2 - y1);
                y = ymax;
            }

            /* Point is below the window */
            else if (codeOut & BOTTOM)
            {
                x = x1 + (x2 - x1) * (ymin - y1) / (float)(y2 - y1);
                y = ymin;
            }

            /* Point is to the right of window */
            else if (codeOut & RIGHT)
            {
                y = y1 + (y2 - y1) * (xmax - x1) / (float)(x2 - x1);
                x = xmax;
            }

            /* Point is to the left of window */
            else if (codeOut & LEFT)
            {
                y = y1 + (y2 - y1) * (xmin - x1) / (float)(x2 - x1);
                x = xmin;
            }

            /* Replace outside point with intersection point */
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

    /* Draw clipped line if accepted */
    if (accept)
    {
        glColor3f(0.0, 1.0, 0.0);  // Green color for clipped line
        glBegin(GL_LINES);
        glVertex2i(x1, y1);
        glVertex2i(x2, y2);
        glEnd();
    }
}

/* ------------------ DISPLAY FUNCTION ------------------ */
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the screen

    /* Draw clipping window */
    glColor3f(1.0, 1.0, 1.0);      // White color
    glBegin(GL_LINE_LOOP);
    glVertex2i(xmin, ymin);
    glVertex2i(xmax, ymin);
    glVertex2i(xmax, ymax);
    glVertex2i(xmin, ymax);
    glEnd();

    /* Draw original line (before clipping) */
    glColor3f(1.0, 0.0, 0.0);      // Red color
    glBegin(GL_LINES);
    glVertex2i(x1, y1);
    glVertex2i(x2, y2);
    glEnd();

    /* Perform clipping and draw clipped line */
    cohenSutherlandClip();

    glFlush();                     // Render all OpenGL commands
}

/* ------------------ INITIALIZATION ------------------ */
void init()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);   // Black background
    glMatrixMode(GL_PROJECTION);        // Projection matrix
    glLoadIdentity();                   // Reset matrix
    gluOrtho2D(0,500, 0, 500);   // 2D coordinate system
}

/* ------------------ MAIN FUNCTION ------------------ */
int main(int argc, char **argv)
{
    printf("Enter clipping window (xmin ymin xmax ymax): ");
    scanf("%d %d %d %d", &xmin, &ymin, &xmax, &ymax);

    printf("Enter line endpoints (x1 y1 x2 y2): ");
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Cohen-Sutherland Line Clipping");

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
