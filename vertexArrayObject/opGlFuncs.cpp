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

/* VAO array */
double vaoArray[15] =
{
	0, 0, 0,
	200, 0, 0,
	200, 200, 0,
	0, 200, 0,
	0, 0, 0
};

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

    glutMainLoop();
}

/**
* @brief  This function adjusts the viewport of the OpenGL window whenever the window size changed (in this program, this function fixes the size of window)
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
    glutReshapeWindow(800, 600);																							// fixed size glut window
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
    Dynamic_Screen(glutGet(GLUT_WINDOW_WIDTH),glutGet(GLUT_WINDOW_HEIGHT));

	/* draw VAO arrays with DRAW_VAO function */
    glTranslated(150, 350, 0);
	Draw_VAO(vaoArray, 5, 2.0f, 0.647, 0.165, 0.165);
    glTranslated(250, 0, 0);
	Draw_VAO(vaoArray, 5, 2.0f, 0.647, 0.165, 0.165);
    glTranslated(0, -250, 0);
	Draw_VAO(vaoArray, 5, 2.0f, 0.647, 0.165, 0.165);
    glTranslated(-250, 0, 0);
	Draw_VAO(vaoArray, 5, 2.0f, 0.647, 0.165, 0.165);

    glTranslated(205, 205, 0);
    glScaled(0.2, 0.2, 0.2);
	Draw_VAO(vaoArray, 5, 2.0f, 0.647, 0.165, 0.165);

    Sleep(1);

    glutSwapBuffers();
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
* @brief  VAO draw function
* @param  double* array, int vertexNumber, float lineWidthf, float R, float G, float B
* @retval none
*/
void Draw_VAO(double* array, int vertexNumber, float lineWidthf, float R, float G, float B)
{
    glLineWidth(lineWidthf);																								// line width
    glEnableClientState(GL_VERTEX_ARRAY);																					// set state as vertex array
    glVertexPointer(3, GL_DOUBLE, 0, array);																				// vertex pointer type double, every vertex contains 3 parameter
    glColor3f(R, G, B);																										// set color

	/* every 3 members of vaoArray (x, y, z) creates a vertex, 
	thats why vertexNumber = lenght of vaoArray / 3 */
    glDrawArrays(GL_LINE_STRIP, 0, vertexNumber);																			// draw vao arrays

    glDisableClientState(GL_VERTEX_ARRAY);																					// clear state

}


