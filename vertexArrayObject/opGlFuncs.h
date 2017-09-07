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

void Init_Screen(int, int);
void Dynamic_Screen(int , int );
void Resize(int, int );
void Display(void);
void Key(unsigned char, int, int);
void GL_Mouse(int, int , int , int );
void Idle(void);
void Draw_VAO(double* , int, float, float, float, float);

#endif 
