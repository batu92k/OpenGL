/*
	Copyright (c) 2016 Batuhan KINDAN
	Distributed under the MIT License.
	See License.txt or http://www.opensource.org/licenses/mit-license.php.
*/


#include "opGlFuncs.h"
#include <Gl/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <windows.h>
#include <iostream>
#include <SDL/SDL.h>


void initScreen(int widthInit, int heightInit)
{
    std::cout << "initialize window..." << std::endl;
    glutInitWindowSize(widthInit, heightInit);
    glutInitWindowPosition(100,100);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
    glutCreateWindow("Monitor");
    std::cout << "window initialization complete..." << std::endl;

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutMouseFunc(glMouse);
    glutIdleFunc(idle);

    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0, 0, widthInit, heightInit);
    glOrtho(0 , widthInit, 0, heightInit , -4000, 4000); // set origin point to bottom left
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glutMainLoop();
}

void dynamicScreen(int widthDyn, int heightDyn)
{
    glClearColor(0.118, 0.565, 1.000, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0, 0, widthDyn, heightDyn); // set origin point to bottom left according to new screen sizes
    glOrtho(0, widthDyn , 0, heightDyn , -4000, 4000);
    glutReshapeWindow(800, 600); // fixed size glut window
}

void resize(int widthRes, int heightRes)
{
    // these codes works almost same as the dynamic screen function, you can pick one
    /*
    glViewport(0, 0, widthRes, heightRes);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(widthRes / 2, widthRes / 2, -heightRes / 2, heightRes / 2, 200, 200);
	glutReshapeWindow(1024, 768); // disable sizable window feature
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	*/

    glutPostRedisplay();
}

double vaoArray[15] =
                {
                0, 0, 0,
                200, 0, 0,
                200, 200, 0,
                0, 200, 0,
                0, 0, 0
                };

void display(void)
{
    dynamicScreen(glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));

    glTranslated(150, 350, 0);
    drawVAO(vaoArray, 5, 2.0f, 0.647, 0.165, 0.165);
    glTranslated(250, 0, 0);
    drawVAO(vaoArray, 5, 2.0f, 0.647, 0.165, 0.165);
    glTranslated(0, -250, 0);
    drawVAO(vaoArray, 5, 2.0f, 0.647, 0.165, 0.165);
    glTranslated(-250, 0, 0);
    drawVAO(vaoArray, 5, 2.0f, 0.647, 0.165, 0.165);

    glTranslated(205, 205, 0);
    glScaled(0.2, 0.2, 0.2);
    drawVAO(vaoArray, 5, 2.0f, 0.647, 0.165, 0.165);

    Sleep(1);
    glutSwapBuffers();
}


void key(unsigned char key, int x, int y)
{
    glutPostRedisplay();
}

void glMouse(int mouseButton, int buttonState, int x, int y)
{
    glutPostRedisplay();
}

void idle(void)
{
    glutPostRedisplay();
}

void drawVAO(double* array, int vertexNumber, float lineWidthf, float R, float G, float B)
{
    glLineWidth(lineWidthf); // line width
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, array);
    glColor3f(R, G, B);
    glDrawArrays(GL_LINE_STRIP, 0, vertexNumber); // every 3 members of vaoArray (x, y, z) creates a vertex, thats why vertexNumber = lenght of vaoArray / 3
    glDisableClientState(GL_VERTEX_ARRAY);

}


