/**
******************************************************************************
* @file    opGLFuncs.cpp
* @author  Ali Batuhan KINDAN
* @version V1.0.0
* @date    21.09.2016
* @brief   This file contains the functions that are used for OpelGL features in the program.
******************************************************************************
Copyright (c) 2016 Ali Batuhan KINDAN
Distributed under the MIT License.
See License.txt or http://www.opensource.org/licenses/mit-license.php.
******************************************************************************/

#include "opGlFuncs.h"
#include <Gl/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <windows.h>
#include <iostream>
#include <SDL/SDL.h>

double backColor[12] = { 0.53 / 2, 1.09 / 2,
1.51 / 2, 0.051, 0.156,
0.256, 0.051, 0.156, 0.256,
0.53 / 2, 1.09 / 2, 1.51 / 2 };																		// default background color

unsigned int tex;

/**
* @brief  This function loads a texture from 5_6_5 bmp file
* @param  const char* filename
* @retval id;
*/
unsigned int Load_Texture(const char* filename)
{
	SDL_Surface* img = SDL_LoadBMP(filename);
	unsigned int id;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->w, img->h, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, img->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	SDL_FreeSurface(img);
	return id;
}

/**
* @brief  This function creates an OpenGL screen according to given integer paramers widthInit and heightInit
* @param  int widthInit, int heightInit
* @retval none
*/
void Init_Screen(int widthInit, int heightInit)
{
	std::cout << "initialize window..." << std::endl;																		// Inform user
	glutInitWindowSize(widthInit, heightInit);																				// Initialize the OpenGL window with given parameters
	glutInitWindowPosition(100, 100);																						// Set the default position of window
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);																// Set display mode
	glutCreateWindow("Monitor");																							// Set window name as "Monitor"
	std::cout << "window initialization complete..." << std::endl;															// Inform user

	/* OpenGL user call functions for reshape, display, keyboard, mouse and idle */
	glutReshapeFunc(Resize);
	glutDisplayFunc(Display);
	glutKeyboardFunc(Key);
	glutMouseFunc(GL_Mouse);
	glutIdleFunc(Idle);
	glutMotionFunc(On_Mouse_Move);
	glutMouseWheelFunc(Mouse_Wheel);

	glClearColor(0, 0, 0, 0);																								// clear OpenGL window color
	glMatrixMode(GL_MODELVIEW);																								// set matrix mode 
	glLoadIdentity();																										// reset the matrix back to it's default state
	glViewport(0, 0, widthInit, heightInit);																				// set viewport
	glOrtho(0, widthInit, 0, heightInit, -4000, 4000);																		// set origin point to bottom left
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);																		// clear color and dept buffer

	glClearDepth(1.0f);																										// clear depth buffer
	glEnable(GL_DEPTH_TEST);																								// do depth comparisons and update the depth buffer
	glEnable(GL_TEXTURE_2D);																								// do texture process and update the texture buffer
	glDepthFunc(GL_LEQUAL);																									// set depth function less or equal
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);																		// set perspective correction to nicest quality

	/* default texture import sequence */
	std::string fileName = "\\wood565.bmp";
	fileName = Get_Exe_Path() + fileName;
	const char* fileChar = fileName.c_str();
	tex = Load_Texture(fileChar);

    glutMainLoop();
}

/**
* @brief  This function adjusts the viewport of the OpenGL window whenever the window size changed
* @param  int widthDyn, int heightDyn
* @retval none
*/
void Dynamic_Screen(int widthDyn, int heightDyn)
{
	glClearColor(0.24, 0.45, 0.4, 0);																						// set background color
	glEnable(GL_DEPTH_TEST);																								// do depth comparisons and update the depth buffer
	glDepthFunc(GL_LEQUAL);																									// set depth function less or equal
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);																		// set perspective correction to nicest quality
	glMatrixMode(GL_MODELVIEW);																								// set matrix mode 
	glLoadIdentity();																										// reset the matrix back to it's default state
	glViewport(0, 0, widthDyn, heightDyn);																					// set viewport
	glOrtho(0, widthDyn, 0, heightDyn, -4000, 4000);																		// set origin point to bottom left
	//-------------------- Smoothing Process --------------------
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
}

/**
* @brief  This function automatically called by resize event when the window size changed. Almost same as Dynamic_Screen
* @param  int widthRes, int heightRes
* @retval none
*/
void Resize(int widthRes, int heightRes)
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

/**
* @brief  This function automatically called in glutMainLoop to display whatever user wants
* @param  void
* @retval none
*/
void Display(void)
{
	Dynamic_Screen(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));												// adjust screen
	glDisable(GL_TEXTURE_2D);																								// disable Texture_2D before drawing the background color
	Set_Background_Color(backColor);																						// set background color
	glEnable(GL_TEXTURE_2D);																								// enable Texture_2D before drawing the textured cube
	glColor3f(1.0f, 1.0f, 1.0f);																							// reset colors before drawing the textured cube

	/* draw textrured square */
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

    Sleep(1);																												// sleep ~1ms

    glutSwapBuffers();																										// swap buffers
}

/**
* @brief  This function sets the OpenGL window background color
* @param  double* backColor -> contents r,g,b for 4 points bottom left, top left, top right, bottom right
* @retval none
*/
void Set_Background_Color(double* backColor)
{
	/* draw background polygon according to given color parameters */
	glBegin(GL_POLYGON);
	glColor3d(*(backColor), *(backColor + 1), *(backColor + 2));
	glVertex3d(0, 0, -100);
	glColor3d(*(backColor + 3), *(backColor + 4), *(backColor + 5));
	glVertex3d(0, glutGet(GLUT_WINDOW_HEIGHT), -100);
	glColor3d(*(backColor + 6), *(backColor + 7), *(backColor + 8));
	glVertex3d(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT), -100);
	glColor3d(*(backColor + 9), *(backColor + 10), *(backColor + 11));
	glVertex3d(glutGet(GLUT_WINDOW_WIDTH), 0, -100);
	glEnd();
}

/**
* @brief  This function automatically called by any keyboard event in the program
* @param  unsigned char key, int x, int y
* @retval none
*/
void Key(unsigned char key, int x, int y)
{
    glutPostRedisplay();
}

/**
* @brief  This function automatically called by any mouse button event in the program
* @param  int mouseButton, int buttonState, int x, int y
* @retval none
*/
void GL_Mouse(int mouseButton, int buttonState, int x, int y)
{
    glutPostRedisplay();
}

/**
* @brief  Global glut idle function
* @param  void
* @retval none
*/
void Idle(void)
{
	glutPostRedisplay();
}

/**
* @brief  This function gets the execute path of application
* @param  void
* @retval string( buffer ).substr( 0, pos);
*/
std::string Get_Exe_Path()
{
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");
	return std::string(buffer).substr(0, pos);
}
