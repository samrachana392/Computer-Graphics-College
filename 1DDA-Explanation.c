#include <GL/glut.h> // Includes GLUT, OpenGL Utility Toolkit
#include <stdio.h>
#include <math.h>

/*
    Global variables to store the start and end points of the line. These are declared globally so that both main() and display() functions can access them.
*/
float x_start, y_start, x_end, y_end;

/*
    display() function: This function is called automatically by GLUT whenever the window needs to be redrawn.
*/
void display()
{
    // Clear the color buffer (screen)
    glClear(GL_COLOR_BUFFER_BIT);

    /*  Set drawing color. glColor3f(r, g, b) r, g, b values range from 0.0 to 1.0 Here we are setting the color to white.
     */
    glColor3f(1.0, 1.0, 1.0);

    /*Begin drawing points. GL_POINTS means we will plot individual pixels.
     */
    glBegin(GL_POINTS);

    /*
        DDA ALGORITHM STARTS
    */

    // Calculate differences in x and y directions
    float dx = x_end - x_start;
    float dy = y_end - y_start;

    /*  Determine the number of steps. We take the maximum of |dx| and |dy| so that the line is drawn smoothly regardless of slope.
     */
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    /*Calculate increment values for x and y. These tell us how much x and y should change for each step.
     */
    float xIncrement = dx / steps;
    float yIncrement = dy / steps;

    /* Initialize x and y with starting point. These values will be updated step-by-step.
     */

    float x = x_start;
    float y = y_start;
    /* Loop through each step and plot pixels. For every iteration: - Plot the current pixel -Increment x and y
     */
    for (int i = 0; i <= steps; i++)
    {
        /* glVertex2i(x, y): Plots a pixel at integer coordinates. Since x and y are floating-point values, we round them to the nearest integer for accurate pixel placement.
         */
        glVertex2i(round(x), round(y));

        // Increment x and y for next point
        x = x + xIncrement;
        y = y + yIncrement;
    }

    /*
        End drawing points.
    */
    glEnd();

    /*
        Force execution of OpenGL commands. Ensures everything is rendered immediately.
    */
    glFlush();
}

/*
    init() function: Used to initialize OpenGL settings.
*/
void init()
{
    /*
        Set background color.
        glClearColor(r, g, b, alpha)
        alpha is opacity (1.0 means fully opaque).
        Here background color is black.
    */
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    /*
        Set the current matrix mode to projection. This tells OpenGL that we are defining the camera/coordinate system.
    */
    glMatrixMode(GL_PROJECTION);

    /*
       Reset the projection matrix to identity. This prevents unwanted transformations.
   */
    glLoadIdentity();

    /*
        Set the coordinate system. gluOrtho2D(left, right, bottom, top)
        This creates a 2D coordinate system
        where: x ranges from 0 to 100 y ranges from 0 to 100
    */
    gluOrtho2D(0, 100, 0, 100);

    /*
       Set the size of points to make plotted pixels clearly visible.
   */
    glPointSize(4.0f);
}

/*
    main() function: Program execution starts here.
*/
int main(int argc, char **argv)
{
    /*
        Take input from the user for line endpoints.
    */

    printf("Enter x_start y_start: ");
    scanf("%f %f", &x_start, &y_start);

    printf("Enter x_end y_end: ");
    scanf("%f %f", &x_end, &y_end);

    /*
        Initialize GLUT. &argc and argv allow GLUT to process command-line arguments.
    */
    glutInit(&argc, argv);

    /*
        Set display mode.
        GLUT_SINGLE  -> Single buffer
        GLUT_RGB     -> RGB color mode
    */
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    /*
        Set window size (width, height) in pixels.
    */
    glutInitWindowSize(500, 500);

    /*
        Set window position on screen.
    */
    glutInitWindowPosition(100, 100);

    /*
        Create the window with a title.
    */
    glutCreateWindow("DDA Line Drawing Algorithm");

    /*
        Call initialization function.
    */
    init();

    /*
        Register display callback function. Whenever GLUT wants to redraw the window, it will call display().
    */
    glutDisplayFunc(display);

    /*
        Enter the GLUT event processing loop. This keeps the program running.
    */
    glutMainLoop();

    return 0;
}
