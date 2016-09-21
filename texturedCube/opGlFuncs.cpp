/*
Copyright (c) 2016 Batuhan KINDAN
Distributed under the MIT License.
See License.txt or http://www.opensource.org/licenses/mit-license.php.
*/

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

const GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 0.10f, 0.10f, 0.80f, 0.0f };

const GLfloat mat_ambient[] = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 500.0f };

unsigned int i = 0;
int lenght = 200;
double backColor[12] = { 0.53 / 2, 1.09 / 2, 1.51 / 2, 0.051, 0.156, 0.256, 0.051, 0.156, 0.256, 0.53 / 2, 1.09 / 2, 1.51 / 2 };
unsigned int tex;
int oldX, oldY;
bool rotate = false;
float theta = 0, phi = 0;
double scale = 1;

unsigned int loadTexture(const char* filename)
{
	SDL_Surface* img = SDL_LoadBMP(filename);
	unsigned int id;
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img->w, img->h, 0, GL_RGB,
    	GL_UNSIGNED_SHORT_5_6_5, img->pixels);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	SDL_FreeSurface(img);
	return id;
}


void initScreen(int widthInit, int heightInit)
{
	std::cout << "pencere baslatiliyor..." << std::endl;
	glutInitWindowSize(widthInit, heightInit);
	glutInitWindowPosition(100, 100);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("Monitor");
	std::cout << "pencere baslatildi..." << std::endl;

	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(key);
	glutMouseFunc(glMouse);
	glutMotionFunc(OnMouseMove);
	glutMouseWheelFunc(mouseWheel);
	glutIdleFunc(idle);

	glClearColor(0, 0, 0, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(0, 0, widthInit, heightInit);
	glOrtho(0, widthInit, 0, heightInit, -4000, 4000);
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
	//----------------------------------------------------------------------------------------
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
	glutMainLoop();
}

void dynamicScreen(int widthDyn, int heightDyn)
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glViewport(0, 0, widthDyn, heightDyn);
	glOrtho(0, widthDyn, 0, heightDyn, -4000, 4000);
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
	dynamicScreen(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
	glDisable(GL_TEXTURE_2D); //disable Texture_2D before drawing the background color
	glDisable(GL_POLYGON_SMOOTH); //disable Polygon Smooth before drawing the background color
	glPushMatrix();
	glTranslated(0, 0, -500);
	backgroundColor(backColor);
	glPopMatrix();

    glEnable(GL_POLYGON_SMOOTH); // enable Polygon Smooth before drawing the textured cube
	glEnable(GL_TEXTURE_2D); //  // enable Texture_2D before drawing the textured cube
	glColor3f(1.0f, 1.0f, 1.0f); // reset colours before drawing the textured cube

	glPushMatrix();
	glTranslated(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2, -100);
	glScaled(scale, scale, scale); // mouse wheel zoom
	glRotated(phi * 15, 1, 0, 0); // mouse orbit
	glRotated(theta * 15, 0, 1, 0); // mouse orbit
	glTranslated(-100, -100, -100); // offset for getting the center of the cube
	drawWireframeCube(200);
	drawTexturedCube(lenght, tex);
	glPopMatrix();

	Sleep(1);
	glutSwapBuffers();
}

void backgroundColor(double* backColor)
{
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

void drawWireframeCube(int wireLenght)
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

void drawTexturedCube(int cubeEdge, unsigned int texture)
{
	glBindTexture(GL_TEXTURE_2D, texture);
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

void key(unsigned char key, int x, int y)
{
    if(key == 'w')
    {
		std::string fileName = "\\wood565.bmp";
    	fileName = getExePath()+ fileName;
		const char* fileChar = fileName.c_str();
		tex = loadTexture( fileChar );
		delete fileChar;
    }
    else if(key == 'a')
    {
		std::string fileName = "\\brick565.bmp";
		fileName = getExePath()+ fileName;
		const char* fileChar = fileName.c_str();
		tex = loadTexture( fileChar );
		delete fileChar;
    }
	glutPostRedisplay();
}



void glMouse(int mouseButton, int buttonState, int x, int y)
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

void OnMouseMove(int x, int y)
{
	if (rotate)
    {
		theta += (x - oldX)*0.01f;
		phi += (y - oldY)*0.01f;
	}
	oldX = x;
	oldY = y;
	glutPostRedisplay();
}


void mouseWheel(int wheel, int direction, int x, int y)
{
	if (direction > 0)
	{
		scale += 0.2;
	}
	else if (direction < 0)
	{
		scale -= 0.2;
	}
	if (scale < 0.4)
	{
		scale = 0.4;
	}
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

