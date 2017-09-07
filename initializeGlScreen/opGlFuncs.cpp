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

	glClearColor(0, 0, 0, 0);																								// clear OpenGL window color
	glMatrixMode(GL_MODELVIEW);																								// set matrix mode 
	glLoadIdentity();																										// reset the matrix back to it's default state
	glViewport(0, 0, widthInit, heightInit);																				// set viewport
	glOrtho(0, widthInit, 0, heightInit, -4000, 4000);																		// set origin point to bottom left
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);																		// clear color and dept buffer

	glutMainLoop();																											// enter the GLUT event processing loop
}

/**
* @brief  This function adjusts the viewport of the OpenGL window whenever the window size changed
* @param  int widthDyn, int heightDyn
* @retval none
*/
void Dynamic_Screen(int widthDyn, int heightDyn)
{
	glClearColor(0.24, 0.45, 0.4, 0);																						// set background color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);																		// clear color and dept buffer
	glMatrixMode(GL_MODELVIEW);																								// set matrix mode 
	glLoadIdentity();																										// reset the matrix back to it's default state
	glViewport(0, 0, widthDyn, heightDyn);																					// set viewport
	glOrtho(0, widthDyn, 0, heightDyn, -4000, 4000);																		// set origin point to bottom left
}

/**
* @brief  This function automatically called by resize event when the window size changed.
* @param  int widthRes, int heightRes
* @retval none
*/
void Resize(int widthRes, int heightRes)
{
	glutPostRedisplay();																									// re-display window
}

/**
* @brief  This function automatically called in glutMainLoop to display whatever user wants
* @param  void
* @retval none
*/
void Display(void)
{
	Dynamic_Screen(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));												// adjust OpenGL window height and width according to resize
	Sleep(1);																												// sleep ~1ms
	glutSwapBuffers();																										// swap buffers
}

/**
* @brief  This function automatically called by any keyboard event in the program
* @param  unsigned char key, int x, int y
* @retval none
*/
void Key(unsigned char key, int x, int y)
{
	glutPostRedisplay();																									// re-display window
}

/**
* @brief  This function automatically called by any mouse event in the program
* @param  int mouseButton, int buttonState, int x, int y
* @retval none
*/
void GL_Mouse(int mouseButton, int buttonState, int x, int y)
{
	glutPostRedisplay();																									// re-display window
}

/**
* @brief  Global glut idle function
* @param  void
* @retval none
*/
void Idle(void)
{
	glutPostRedisplay();																									// re-display window
}


