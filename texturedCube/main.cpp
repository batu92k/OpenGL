/**
******************************************************************************
* @file    main.cpp
* @author  Ali Batuhan KINDAN
* @version V1.0.0
* @date    21.09.2016
* @brief   This is an example program about drawing a textured cube with OpenGL
******************************************************************************
Copyright (c) 2016 Ali Batuhan KINDAN
Distributed under the MIT License.
See License.txt or http://www.opensource.org/licenses/mit-license.php.
******************************************************************************/

#include "opGlFuncs.h"
#include <GL/glut.h>
#include <stdlib.h>

/**
* @brief  Program entry point
* @param  int argc, char *argv[]
* @retval EXIT_SUCCESS
*/
int main(int argc, char *argv[])
{
	glutInit(&argc, argv);																	// initialize GLUT
	Init_Screen(1024, 768);																	// initialize window
	glutMainLoop();																			// begin loop

	return EXIT_SUCCESS;
}
