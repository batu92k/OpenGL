/**
******************************************************************************
* @file    opGLFuncs.h
* @author  Ali Batuhan KINDAN
* @version V1.0.0
* @date    21.09.2016
* @brief   This file contains the function prototypes that are used for OpelGL features in the program.
******************************************************************************
Copyright (c) 2016 Ali Batuhan KINDAN
Distributed under the MIT License.
See License.txt or http://www.opensource.org/licenses/mit-license.php.
******************************************************************************/

#ifndef OPGLFUNCS_H
#define OPGLFUNCS_H

#include <string>

void initScreen(int, int);
void dynamicScreen(int , int );
void resize(int, int );
void display(void);
void key(unsigned char, int, int);
void glMouse(int, int , int , int );
void idle(void);

#endif 
