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

double backColor[12] = {0.53/2, 1.09/2,1.51/2, 0.051, 0.156, 0.256, 0.051, 0.156, 0.256, 0.53/2, 1.09/2, 1.51/2};
unsigned int tex;

unsigned int loadTexture(const char* filename)
{
    SDL_Surface* img = SDL_LoadBMP(filename);
    unsigned int id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,img->w, img->h,0,GL_RGB,
    GL_UNSIGNED_SHORT_5_6_5, img->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    SDL_FreeSurface(img);
    return id;
}

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
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    // default texture import sequence
    std::string fileName = "\\wood565.bmp";
    fileName = getExePath()+ fileName;
    const char* fileChar = fileName.c_str();
    tex = loadTexture( fileChar );

    glutMainLoop();
}

void dynamicScreen(int widthDyn, int heightDyn)
{
    glClearColor(0,0,0,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glViewport(0, 0, widthDyn, heightDyn);
    glOrtho(0, widthDyn , 0, heightDyn , -4000, 4000);
    //-------------------- Smoothing Process --------------------
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    //-----------------------------------------------------------
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
    glDisable(GL_TEXTURE_2D); // disable TEXTURE_2D before drawing the background
    backgroundColor(backColor);
    glEnable(GL_TEXTURE_2D); // enable TEXTURE_2D before drawing the textured polygon
    glColor3f(1.0f, 1.0f, 1.0f); // reset colors

    glPushMatrix();
    glTranslated(50,-50,100);
    glBegin(GL_POLYGON);
    glTexCoord2d(0,0);
    glVertex3d(100,100,0);
    glTexCoord2d(1,0);
    glVertex3d(600,100,0);
    glTexCoord2d(1,1);
    glVertex3d(600,600,0);
    glTexCoord2d(0,1);
    glVertex3d(100,600,0);
    glEnd();
    glPopMatrix();

    Sleep(1);

    glutSwapBuffers();
}

void backgroundColor(double* backColor)
{

    glBegin(GL_POLYGON);
    glColor3d(*(backColor),*(backColor+1),*(backColor+2));
    glVertex3d(0,0,-300);
    glColor3d(*(backColor+3), *(backColor+4), *(backColor+5));
    glVertex3d(0,glutGet(GLUT_WINDOW_HEIGHT),-300);
    glColor3d(*(backColor+6), *(backColor+7), *(backColor+8));
    glVertex3d(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), -300);
    glColor3d(*(backColor+9), *(backColor+10), *(backColor+11));
    glVertex3d(glutGet(GLUT_WINDOW_WIDTH), 0, -300);
    glEnd();
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

std::string getExePath()
{
    char buffer[MAX_PATH];
    GetModuleFileName( NULL, buffer, MAX_PATH );
    std::string::size_type pos = std::string( buffer ).find_last_of( "\\/" );
    return std::string( buffer ).substr( 0, pos);
}
