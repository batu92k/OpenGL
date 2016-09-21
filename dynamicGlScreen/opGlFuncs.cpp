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
    glClearColor(0.24,0.45,0.4,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0, 0, widthDyn, heightDyn); // set origin point to bottom left according to new screen sizes
    glOrtho(0, widthDyn , 0, heightDyn , -4000, 4000);
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

void display(void)
{
    dynamicScreen(glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));
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


