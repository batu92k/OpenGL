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
    glOrtho(0 , widthInit, 0, heightInit , -4000, 4000);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glutMainLoop();
}

void resize(int widthRes, int heightRes)
{
    glutPostRedisplay();
}

void display(void)
{
    glClearColor(0.24,0.45,0.4,0); // default background color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
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


