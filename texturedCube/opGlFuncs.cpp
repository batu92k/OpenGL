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
#include <Gl/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <windows.h>
#include <iostream>
#include <SDL/SDL.h>
#include <math.h>
#include <string>
#include <winbase.h>

/* constant light parameters */
const GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 0.10f, 0.10f, 0.80f, 0.0f };

/* constant material parameters */
const GLfloat mat_ambient[] = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 500.0f };

unsigned int i = 0;																											// general purpose sentinel
int lenght = 200;
double backColor[12] = { 0.53 / 2, 1.09 / 2,	
						1.51 / 2, 0.051, 0.156, 
						0.256, 0.051, 0.156, 0.256, 
						0.53 / 2, 1.09 / 2, 1.51 / 2 };																		// default background color
unsigned int tex;
int oldX = 0;																												// mouse cursor old X variable
int oldY = 0;																												// mouse cursor old Y variable
bool rotate = false;																										// rotate permission variable
float theta = 0;																											// x axis mouse orbit
float  phi = 0;																												// y axis mouse orbit
double scale = 1.0;																											// defaulyt scale 

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
void initScreen(int widthInit, int heightInit)
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
	fileName = Get_Exe_Path()+ fileName;
    const char* fileChar = fileName.c_str();
	tex = Load_Texture( fileChar );
	
	/* Light and Material settings */
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

	glutMainLoop();																											// begin main loop
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
    glHint(GL_POLYGON_SMOOTH_HINT,GL_NICEST);
	//-----------------------------------------------------------

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
	glDisable(GL_POLYGON_SMOOTH);																							// disable Polygon Smooth before drawing the background color

	/* Draw Background */
	glPushMatrix();
	glTranslated(0, 0, -500);
	Set_Background_Color(backColor);
	glPopMatrix();

    glEnable(GL_POLYGON_SMOOTH);																							// enable Polygon Smooth before drawing the textured cube
	glEnable(GL_TEXTURE_2D);																								// enable Texture_2D before drawing the textured cube
	glColor3f(1.0f, 1.0f, 1.0f);																							// reset colors before drawing the textured cube

	glPushMatrix();
	glTranslated(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2, -100);
	glScaled(scale, scale, scale);																							// mouse wheel zoom
	glRotated(phi * 15, 1, 0, 0);																							// basic mouse orbit
	glRotated(theta * 15, 0, 1, 0);																							// basic mouse orbit
	glTranslated(-100, -100, -100);																							// offset for getting the center of the cube
	Draw_Wireframe_Cube(200);																								// draw cube (wireframe)
	Draw_Textured_Cube(lenght, tex);																						// draw cube (textured)
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
* @brief  This function draws a wireframe cube to screen
* @param  int wireLenght
* @retval none
*/
void Draw_Wireframe_Cube(int wireLenght)
{
	glLineWidth(0.5f);
	glColor3d(0, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex3d(0, 0, 0);
	glVertex3d(wireLenght, 0, 0);
	glVertex3d(wireLenght, wireLenght, 0);
	glVertex3d(0, wireLenght, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, wireLenght);
	glVertex3d(0, wireLenght, wireLenght);
	glVertex3d(0, wireLenght, 0);
	glVertex3d(wireLenght, wireLenght, 0);
	glVertex3d(wireLenght, wireLenght, wireLenght);
	glVertex3d(0, wireLenght, wireLenght);
	glVertex3d(0, 0, wireLenght);
	glVertex3d(wireLenght, 0, wireLenght);
	glVertex3d(wireLenght, wireLenght, wireLenght);
	glVertex3d(wireLenght, wireLenght, 0);
	glVertex3d(wireLenght, 0, 0);
	glVertex3d(wireLenght, 0, wireLenght);
	glEnd();
	glColor3d(1, 1, 1);
}

/**
* @brief  This function draws a wireframe cube to screen
* @param  int wireLenght
* @retval none
*/
void Draw_Textured_Cube(int cubeEdge, unsigned int texture)
{
	glBindTexture(GL_TEXTURE_2D, texture);

	/* 1st face of cube */
	glBegin(GL_QUADS);
	glNormal3d(0, 0, -1);//
	glTexCoord2d(0.0, 0.0);
	glVertex3d(0.0, 0.0, 0.0);
	glNormal3d(0, 0, -1);//
	glTexCoord2d(0.0, 1);
	glVertex3d(0.0, cubeEdge, 0.0);
	glNormal3d(0, 0, -1);//
	glTexCoord2d(1, 1);
	glVertex3d(cubeEdge, cubeEdge, 0.0);
	glNormal3d(0, 0, -1);//
	glTexCoord2d(1, 0.0);
	glVertex3d(cubeEdge, 0.0, 0.0);
	glEnd();

	/* 2nd face of cube */
	glBegin(GL_QUADS);
	glNormal3d(-1, 0, 0);//
	glTexCoord2d(0.0, 0.0);
	glVertex3d(0.0, 0.0, 0.0);
	glNormal3d(-1, 0, 0);//
	glTexCoord2d(0.0, 1);
	glVertex3d(0.0, cubeEdge, 0.0);
	glNormal3d(-1, 0, 0);//
	glTexCoord2d(1, 1);
	glVertex3d(0, cubeEdge, cubeEdge);
	glNormal3d(-1, 0, 0);//
	glTexCoord2d(1, 0.0);
	glVertex3d(0.0, 0.0, cubeEdge);
	glEnd();

	/* 3rd face of cube */
	glBegin(GL_QUADS);
	glNormal3d(0, 1, 0);//
	glTexCoord2d(0.0, 0.0);
	glVertex3d(0.0, cubeEdge, 0.0);
	glNormal3d(0, 1, 0);//
	glTexCoord2d(0.0, 1);
	glVertex3d(0.0, cubeEdge, cubeEdge);
	glNormal3d(0, 1, 0);//
	glTexCoord2d(1, 1);
	glVertex3d(cubeEdge, cubeEdge, cubeEdge);
	glNormal3d(0, 1, 0);//
	glTexCoord2d(1, 0.0);
	glVertex3d(cubeEdge, cubeEdge, 0.0);
	glEnd();

	/* 4th face of cube */
	glBegin(GL_QUADS);
	glNormal3d(0, -1, 0);//
	glTexCoord2d(0.0, 0.0);
	glVertex3d(0.0, 0.0, 0.0);
	glNormal3d(0, -1, 0);//
	glTexCoord2d(0.0, 1);
	glVertex3d(0.0, 0.0, cubeEdge);
	glNormal3d(0, -1, 0);//
	glTexCoord2d(1, 1);
	glVertex3d(cubeEdge, 0.0, cubeEdge);
	glNormal3d(0, -1, 0);//
	glTexCoord2d(1, 0.0);
	glVertex3d(cubeEdge, 0.0, 0.0);
	glEnd();

	/* 5th face of cube */
	glBegin(GL_QUADS);
	glNormal3d(1, 0, 0);//
	glTexCoord2d(0.0, 0.0);
	glVertex3d(cubeEdge, 0.0, 0.0);
	glNormal3d(1, 0, 0);//
	glTexCoord2d(0.0, 1);
	glVertex3d(cubeEdge, cubeEdge, 0.0);
	glNormal3d(1, 0, 0);//
	glTexCoord2d(1, 1);
	glVertex3d(cubeEdge, cubeEdge, cubeEdge);
	glNormal3d(1, 0, 0);//
	glTexCoord2d(1, 0.0);
	glVertex3d(cubeEdge, 0.0, cubeEdge);
	glEnd();

	/* 6th face of cube */
	glBegin(GL_QUADS);
	glNormal3d(0, 0, 1);//
	glTexCoord2d(0.0, 0.0);
	glVertex3d(0.0, 0.0, cubeEdge);
	glNormal3d(0, 0, 1);//
	glTexCoord2d(0.0, 1);
	glVertex3d(0.0, cubeEdge, cubeEdge);
	glNormal3d(0, 0, 1);//
	glTexCoord2d(1, 1);
	glVertex3d(cubeEdge, cubeEdge, cubeEdge);
	glNormal3d(0, 0, 1);//
	glTexCoord2d(1, 0.0);
	glVertex3d(cubeEdge, 0.0, cubeEdge);
	glEnd();

}

/**
* @brief  This function automatically called by any keyboard event in the program
* @param  unsigned char key, int x, int y
* @retval none
*/
void Key(unsigned char key, int x, int y)
{
	/* press 'w' and 'a' key to change cube texture */
    if(key == 'w')
    {
		std::string fileName = "\\wood565.bmp";
    	fileName = Get_Exe_Path() + fileName;
		const char* fileChar = fileName.c_str();
		tex = loadTexture( fileChar );
		delete fileChar;
    }
    else if(key == 'a')
    {
		std::string fileName = "\\brick565.bmp";
		fileName = Get_Exe_Path() + fileName;
		const char* fileChar = fileName.c_str();
		tex = loadTexture( fileChar );
		delete fileChar;
    }
	else
	{

	}
	
	glutPostRedisplay();
}


/**
* @brief  This function automatically called by any mouse button event in the program
* @param  int mouseButton, int buttonState, int x, int y
* @retval none
*/
void GL_Mouse(int mouseButton, int buttonState, int x, int y)
{
	rotate = false;
	if (mouseButton == GLUT_RIGHT_BUTTON)
    {
		oldX = x;
		oldY = y;
		rotate = true;
	}
	glutPostRedisplay();
}

/**
* @brief  This function automatically called by any mouse move event in the program
* @param  int mouseButton, int buttonState, int x, int y
* @retval none
*/
void On_Mouse_Move(int x, int y)
{
	/* when user press the "right button" of the mouse, GL_Mouse event triggered and sets "true" the quasi global bool rotate variable
	   when rotate variable set as "true" this function calculate the differential position of mouse cursor and get rotate amounts whenever mouse moves */	    
	if (rotate)
    {
		theta += (x - oldX)*0.01f;
		phi += (y - oldY)*0.01f;
	}
	else
	{
	}
	oldX = x;
	oldY = y;

	glutPostRedisplay();
}

/**
* @brief  This function automatically called by any mouse wheel event in the program
* @param  int mouseButton, int buttonState, int x, int y
* @retval none
*/
void Mouse_Wheel(int wheel, int direction, int x, int y)
{
	/* adjust scale variable according to mouse wheel  */
	if (direction > 0)
	{
		scale += 0.2;
	}
	else if (direction < 0)
	{
		scale -= 0.2;
	}
	else
	{

	}

	/* limit minimum scale amount to 0.4 */
	if (scale < 0.4)
	{
		scale = 0.4;
	}
	else
	{

	}

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
    GetModuleFileName( NULL, buffer, MAX_PATH );
    std::string::size_type pos = std::string( buffer ).find_last_of( "\\/" );
    return std::string( buffer ).substr( 0, pos);
}

