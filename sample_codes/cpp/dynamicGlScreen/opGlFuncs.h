#ifndef OPGLFUNCS_H_INCLUDED
#define OPGLFUNCS_H_INCLUDED

#include <string>

void initScreen(int, int);
void dynamicScreen(int , int );
void resize(int, int );
void display(void);
void key(unsigned char, int, int);
void glMouse(int, int , int , int );
void idle(void);

#endif // OPGLFUNCS_H_INCLUDED
