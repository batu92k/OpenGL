#include "opGlFuncs.h"
#include <GL/glut.h>
#include <stdlib.h>

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    initScreen(800,600);
    glutMainLoop();

    return EXIT_SUCCESS;
}
