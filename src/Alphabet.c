/*
 *  Copyright 2015 David Ridpath <r6inhardt@hotmail.com>
 *
 *  Licensed under GNU General Public License 3.0
 *  See COPYING.
 * 
 *  This file is part of Pong.
 *
 *  Pong is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Pong is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with Pong.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "Alphabet.h"
#include <stdio.h>
#include <string.h>
#include <BB.h>

/* number of tile widths per character */
#define ACROSS 7.0
#define HIGH 9.0

/* private state vars */
double alphabet_x = 0.0;
double alphabet_y = 0.0;
double alphabet_x_size = 10.0;
double alphabet_y_size = 10.0;

/* private funcs */
void Alphabet_CursorForward()
{
    /* forward on cursor */
    alphabet_x += alphabet_x_size * ACROSS;
}
void Alphabet_CursorNewline(double from_x)
{
    /* newline cursor */
    alphabet_x = from_x;
    alphabet_y -= alphabet_y_size * HIGH;
}
void Alphabet_BBsUnderscore(double x, double y, double x_size, double y_size, BB *pBBs, int pBBs_size)
{
    /* bbs size isn't correct return */
    if(pBBs_size != 1) return;

    BB_Init( &(pBBs[0]) , x, y, 0, x_size*7, y_size, 0);
}
void Alphabet_BBsSquare_filled(double x, double y, double x_size, double y_size, BB *pBBs, int pBBs_size)
{
    /* bbs size isn't correct return */
    if(pBBs_size != 1) return;
    BB_Init( &(pBBs[0]) , x, y, 0, x_size*7, y_size*9, 0);
}
void Alphabet_BBsSquare_border(double x, double y, double x_size, double y_size, BB *pBBs, int pBBs_size)
{
    /* bbs size isn't correct return */
    if(pBBs_size != 4) return;
    BB_Init( &(pBBs[0]) , x, y, 0, x_size*7, y_size, 0);
    BB_Init( &(pBBs[1]) , x, y+y_size*8, 0, x_size*7, y_size, 0);
    BB_Init( &(pBBs[2]) , x, y+y_size, 0, x_size, y_size*7, 0);
    BB_Init( &(pBBs[3]) , x+x_size*6, y+y_size, 0, x_size, y_size*7, 0);
}
void Alphabet_BBs0(double x, double y, double x_size, double y_size, BB *pBBs, int pBBs_size)
{
    /* bbs size isn't correct return */
    if(pBBs_size != 7) return;

    BB_Init( &(pBBs[0]) , x+x_size, y+y_size, 0, x_size, y_size*7, 0);
    BB_Init( &(pBBs[1]) , x+x_size*5, y+y_size, 0, x_size, y_size*7, 0);
    BB_Init( &(pBBs[2]) , x+x_size*2, y+y_size, 0, x_size*3, y_size, 0);
    BB_Init( &(pBBs[3]) , x+x_size*2, y+y_size*7, 0, x_size*3, y_size, 0);
    BB_Init( &(pBBs[4]) , x+x_size*2, y+y_size*3, 0, x_size, y_size, 0);
    BB_Init( &(pBBs[5]) , x+x_size*3, y+y_size*4, 0, x_size, y_size, 0);
    BB_Init( &(pBBs[6]) , x+x_size*4, y+y_size*5, 0, x_size, y_size, 0);
}
void Alphabet_BBs1(double x, double y, double x_size, double y_size, BB *pBBs, int pBBs_size)
{
    /* bbs size isn't correct return */
    if(pBBs_size != 4) return;

    BB_Init( &(pBBs[0]) , x+x_size, y+y_size, 0, x_size*5, y_size, 0);
    BB_Init( &(pBBs[1]) , x+x_size*3, y+y_size*2, 0, x_size, y_size*6, 0);
    BB_Init( &(pBBs[2]) , x+x_size, y+y_size*5, 0, x_size, y_size, 0);
    BB_Init( &(pBBs[3]) , x+x_size*2, y+y_size*6, 0, x_size, y_size, 0);
}
void Alphabet_BBs2(double x, double y, double x_size, double y_size, BB *pBBs, int pBBs_size)
{
    /* bbs size isn't correct return */
    if(pBBs_size != 8) return;

    BB_Init( &(pBBs[0]) , x+x_size, y+y_size, 0, x_size*5, y_size, 0);
    BB_Init( &(pBBs[1]) , x+x_size, y+y_size*2, 0, x_size, y_size, 0);
    BB_Init( &(pBBs[2]) , x+x_size*2, y+y_size*3, 0, x_size, y_size, 0);
    BB_Init( &(pBBs[3]) , x+x_size*3, y+y_size*4, 0, x_size, y_size, 0);
    BB_Init( &(pBBs[4]) , x+x_size*4, y+y_size*5, 0, x_size, y_size, 0);
    BB_Init( &(pBBs[5]) , x+x_size*5, y+y_size*5, 0, x_size, y_size*2, 0);
    BB_Init( &(pBBs[6]) , x+x_size*2, y+y_size*7, 0, x_size*4, y_size, 0);
    BB_Init( &(pBBs[7]) , x+x_size, y+y_size*5, 0, x_size, y_size*2, 0);
}
void Alphabet_BBs3(double x, double y, double x_size, double y_size, BB *pBBs, int pBBs_size)
{
    /* bbs size isn't correct return */
    if(pBBs_size != 6) return;

    BB_Init( &(pBBs[0]) , x+x_size, y+y_size*2, 0, x_size, y_size, 0);
    BB_Init( &(pBBs[1]) , x+x_size, y+y_size*6, 0, x_size, y_size, 0);
    BB_Init( &(pBBs[2]) , x+x_size*2, y+y_size, 0, x_size*3, y_size, 0);
    BB_Init( &(pBBs[3]) , x+x_size*2, y+y_size*7, 0, x_size*3, y_size, 0);
    BB_Init( &(pBBs[4]) , x+x_size*3, y+y_size*4, 0, x_size*2, y_size, 0);
    BB_Init( &(pBBs[5]) , x+x_size*5, y+y_size*2, 0, x_size, y_size*5, 0);
}
void Alphabet_BBs4(double x, double y, double x_size, double y_size, BB *pBBs, int pBBs_size)
{
    /* bbs size isn't correct return */
    if(pBBs_size != 3) return;

    BB_Init( &(pBBs[0]) , x+x_size, y+y_size*4, 0, x_size, y_size*4, 0);
    BB_Init( &(pBBs[1]) , x+x_size*2, y+y_size*4, 0, x_size*4, y_size, 0);
    BB_Init( &(pBBs[2]) , x+x_size*3, y+y_size, 0, x_size, y_size*5, 0);
}
void Alphabet_BBs5(double x, double y, double x_size, double y_size, BB *pBBs, int pBBs_size)
{
    /* bbs size isn't correct return */
    if(pBBs_size != 6) return;

    BB_Init( &(pBBs[0]) , x+x_size, y+y_size, 0, x_size*4, y_size, 0);
    BB_Init( &(pBBs[1]) , x+x_size, y+y_size*2, 0, x_size, y_size, 0);
    BB_Init( &(pBBs[2]) , x+x_size*5, y+y_size*2, 0, x_size, y_size*2, 0);
    BB_Init( &(pBBs[3]) , x+x_size, y+y_size*4, 0, x_size*5, y_size, 0);
    BB_Init( &(pBBs[4]) , x+x_size, y+y_size*5, 0, x_size, y_size*2, 0);
    BB_Init( &(pBBs[5]) , x+x_size, y+y_size*7, 0, x_size*5, y_size, 0);
}
void Alphabet_BBs6(double x, double y, double x_size, double y_size, BB *pBBs, int pBBs_size)
{
    /* bbs size isn't correct return */
    if(pBBs_size != 5) return;

    BB_Init( &(pBBs[0]) , x+x_size, y+y_size, 0, x_size*5, y_size, 0);
    BB_Init( &(pBBs[1]) , x+x_size, y+y_size*2, 0, x_size, y_size*5, 0);
    BB_Init( &(pBBs[2]) , x+x_size*5, y+y_size*2, 0, x_size, y_size*2, 0);
    BB_Init( &(pBBs[3]) , x+x_size*2, y+y_size*4, 0, x_size*4, y_size, 0);
    BB_Init( &(pBBs[4]) , x+x_size*2, y+y_size*7, 0, x_size*4, y_size, 0);
}
void Alphabet_BBs7(double x, double y, double x_size, double y_size, BB *pBBs, int pBBs_size)
{
    /* bbs size isn't correct return */
    if(pBBs_size != 6) return;

    BB_Init( &(pBBs[0]) , x+x_size, y+y_size, 0, x_size, y_size, 0);
    BB_Init( &(pBBs[1]) , x+x_size*2, y+y_size*2, 0, x_size, y_size, 0);
    BB_Init( &(pBBs[2]) , x+x_size*3, y+y_size*3, 0, x_size, y_size, 0);
    BB_Init( &(pBBs[3]) , x+x_size*4, y+y_size*4, 0, x_size, y_size, 0);
    BB_Init( &(pBBs[4]) , x+x_size*5, y+y_size*5, 0, x_size, y_size*2, 0);
    BB_Init( &(pBBs[5]) , x+x_size, y+y_size*7, 0, x_size*5, y_size, 0);
}
void Alphabet_BBs8(double x, double y, double x_size, double y_size, BB *pBBs, int pBBs_size)
{
    /* bbs size isn't correct return */
    if(pBBs_size != 5) return;

    BB_Init( &(pBBs[0]) , x+x_size, y+y_size, 0, x_size*5, y_size, 0);
    BB_Init( &(pBBs[1]) , x+x_size*2, y+y_size*4, 0, x_size*3, y_size, 0);
    BB_Init( &(pBBs[2]) , x+x_size, y+y_size*7, 0, x_size*5, y_size, 0);
    BB_Init( &(pBBs[3]) , x+x_size, y+y_size*2, 0, x_size, y_size*5, 0);
    BB_Init( &(pBBs[4]) , x+x_size*5, y+y_size*2, 0, x_size, y_size*5, 0);
}
void Alphabet_BBs9(double x, double y, double x_size, double y_size, BB *pBBs, int pBBs_size)
{
    /* bbs size isn't correct return */
    if(pBBs_size != 4) return;

    BB_Init( &(pBBs[0]) , x+x_size, y+y_size*4, 0, x_size*4, y_size, 0);
    BB_Init( &(pBBs[1]) , x+x_size, y+y_size*7, 0, x_size*4, y_size, 0);
    BB_Init( &(pBBs[2]) , x+x_size, y+y_size*5, 0, x_size, y_size*2, 0);
    BB_Init( &(pBBs[3]) , x+x_size*5, y+y_size, 0, x_size, y_size*7, 0);
}

void Alphabet_BBsA(double x, double y, double x_size, double y_size, BB *pBBs, int pBBs_size)
{
    /* bbs size isn't correct return */
    if(pBBs_size != 4) return;

    BB_Init( &(pBBs[0]) , x+x_size, y+y_size, 0, x_size, y_size*6, 0);
    BB_Init( &(pBBs[1]) , x+x_size*5, y+y_size, 0, x_size, y_size*6, 0);
    BB_Init( &(pBBs[2]) , x+x_size*2, y+y_size*4, 0, x_size*3, y_size, 0);
    BB_Init( &(pBBs[3]) , x+x_size*2, y+y_size*7, 0, x_size*3, y_size, 0);
}
void Alphabet_BBsB(double x, double y, double x_size, double y_size, BB *pBBs, int pBBs_size)
{
    /* bbs size isn't correct return */
    if(pBBs_size != 5) return;

    BB_Init( &(pBBs[0]) , x+x_size, y+y_size, 0, x_size, y_size*7, 0);
    BB_Init( &(pBBs[1]) , x+x_size*2, y+y_size, 0, x_size*3, y_size, 0);
    BB_Init( &(pBBs[2]) , x+x_size*2, y+y_size*4, 0, x_size*3, y_size, 0);
    BB_Init( &(pBBs[3]) , x+x_size*2, y+y_size*7, 0, x_size*3, y_size, 0);
    BB_Init( &(pBBs[4]) , x+x_size*5, y+y_size*2, 0, x_size, y_size*5, 0);
}
void Alphabet_BBsC(double x, double y, double x_size, double y_size, BB *pBBs, int pBBs_size)
{
    /* bbs size isn't correct return */
    if(pBBs_size != 5) return;

    BB_Init( &(pBBs[0]) , x+x_size, y+y_size*2, 0, x_size, y_size*5, 0);
    BB_Init( &(pBBs[1]) , x+x_size*5, y+y_size*2, 0, x_size, y_size, 0);
    BB_Init( &(pBBs[2]) , x+x_size*5, y+y_size*6, 0, x_size, y_size, 0);
    BB_Init( &(pBBs[3]) , x+x_size*2, y+y_size, 0, x_size*3, y_size, 0);
    BB_Init( &(pBBs[4]) , x+x_size*2, y+y_size*7, 0, x_size*3, y_size, 0);
}
void Alphabet_BBsD(double x, double y, double x_size, double y_size, BB *pBBs, int pBBs_size)
{
    /* bbs size isn't correct return */
    if(pBBs_size != 4) return;

    BB_Init( &(pBBs[0]) , x+x_size, y+y_size, 0, x_size, y_size*7, 0);
    BB_Init( &(pBBs[1]) , x+x_size*2, y+y_size, 0, x_size*3, y_size, 0);
    BB_Init( &(pBBs[2]) , x+x_size*2, y+y_size*7, 0, x_size*3, y_size, 0);
    BB_Init( &(pBBs[3]) , x+x_size*5, y+y_size*2, 0, x_size, y_size*5, 0);
}
void Alphabet_BBsE(double x, double y, double x_size, double y_size, BB *pBBs, int pBBs_size)
{
    /* bbs size isn't correct return */
    if(pBBs_size != 4) return;

    BB_Init( &(pBBs[0]) , x+x_size, y+y_size, 0, x_size*5, y_size, 0);
    BB_Init( &(pBBs[1]) , x+x_size, y+y_size*7, 0, x_size*5, y_size, 0);
    BB_Init( &(pBBs[2]) , x+x_size*2, y+y_size*4, 0, x_size*2, y_size, 0);
    BB_Init( &(pBBs[3]) , x+x_size, y+y_size*2, 0, x_size, y_size*5, 0);
}
void Alphabet_BBsF(double x, double y, double x_size, double y_size, BB *pBBs, int pBBs_size)
{
    /* bbs size isn't correct return */
    if(pBBs_size != 3) return;

    BB_Init( &(pBBs[0]) , x+x_size, y+y_size, 0, x_size, y_size*7, 0);
    BB_Init( &(pBBs[1]) , x+x_size*2, y+y_size*4, 0, x_size*2, y_size, 0);
    BB_Init( &(pBBs[2]) , x+x_size*2, y+y_size*7, 0, x_size*4, y_size, 0);
}
void Alphabet_BBsG(double x, double y, double x_size, double y_size, BB *pBBs, int pBBs_size)
{
    /* bbs size isn't correct return */
    if(pBBs_size != 6) return;

    BB_Init( &(pBBs[0]) , x+x_size*2, y+y_size, 0, x_size*3, y_size, 0);
    BB_Init( &(pBBs[1]) , x+x_size*2, y+y_size*7, 0, x_size*3, y_size, 0);
    BB_Init( &(pBBs[2]) , x+x_size*3, y+y_size*4, 0, x_size*3, y_size, 0);
    BB_Init( &(pBBs[3]) , x+x_size*5, y+y_size*6, 0, x_size, y_size, 0);
    BB_Init( &(pBBs[4]) , x+x_size, y+y_size*2, 0, x_size, y_size*5, 0);
    BB_Init( &(pBBs[5]) , x+x_size*5, y+y_size*2, 0, x_size, y_size*2, 0);
}
void Alphabet_BBsH(double x, double y, double x_size, double y_size, BB *pBBs, int pBBs_size)
{
    /* bbs size isn't correct return */
    if(pBBs_size != 3) return;

    BB_Init( &(pBBs[0]) , x+x_size, y+y_size, 0, x_size, y_size*7, 0);
    BB_Init( &(pBBs[1]) , x+x_size*5, y+y_size, 0, x_size, y_size*7, 0);
    BB_Init( &(pBBs[2]) , x+x_size*2, y+y_size*4, 0, x_size*3, y_size, 0);
}
void Alphabet_BBsI(double x, double y, double x_size, double y_size, BB *pBBs, int pBBs_size)
{
    /* bbs size isn't correct return */
    if(pBBs_size != 3) return;

    BB_Init( &(pBBs[0]) , x+x_size, y+y_size, 0, x_size*5, y_size, 0);
    BB_Init( &(pBBs[1]) , x+x_size, y+y_size*7, 0, x_size*5, y_size, 0);
    BB_Init( &(pBBs[2]) , x+x_size*3, y+y_size*2, 0, x_size, y_size*5, 0);
}
void Alphabet_BBsJ(double x, double y, double x_size, double y_size, BB *pBBs, int pBBs_size)
{
    /* bbs size isn't correct return */
    if(pBBs_size != 4) return;

    BB_Init( &(pBBs[0]) , x+x_size, y+y_size, 0, x_size*3, y_size, 0);
    BB_Init( &(pBBs[1]) , x+x_size, y+y_size*7, 0, x_size*5, y_size, 0);
    BB_Init( &(pBBs[2]) , x+x_size, y+y_size*2, 0, x_size, y_size, 0);
    BB_Init( &(pBBs[3]) , x+x_size*3, y+y_size*2, 0, x_size, y_size*5, 0);
}
void Alphabet_BBsK(double x, double y, double x_size, double y_size, BB *pBBs, int pBBs_size)
{
    /* bbs size isn't correct return */
    if(pBBs_size != 8) return;

    BB_Init( &(pBBs[0]) , x+x_size, y+y_size, 0, x_size, y_size*7, 0);
    BB_Init( &(pBBs[1]) , x+x_size*2, y+y_size*4, 0, x_size, y_size, 0);
    BB_Init( &(pBBs[2]) , x+x_size*3, y+y_size*3, 0, x_size, y_size, 0);
    BB_Init( &(pBBs[3]) , x+x_size*3, y+y_size*5, 0, x_size, y_size, 0);
    BB_Init( &(pBBs[4]) , x+x_size*4, y+y_size*2, 0, x_size, y_size, 0);
    BB_Init( &(pBBs[5]) , x+x_size*4, y+y_size*6, 0, x_size, y_size, 0);
    BB_Init( &(pBBs[6]) , x+x_size*5, y+y_size, 0, x_size, y_size, 0);
    BB_Init( &(pBBs[7]) , x+x_size*5, y+y_size*7, 0, x_size, y_size, 0);
}
void Alphabet_BBsL(double x, double y, double x_size, double y_size, BB *pBBs, int pBBs_size)
{
    /* bbs size isn't correct return */
    if(pBBs_size != 2) return;

    BB_Init( &(pBBs[0]) , x+x_size, y+y_size, 0, x_size*5, y_size, 0);
    BB_Init( &(pBBs[1]) , x+x_size, y+y_size*2, 0, x_size, y_size*6, 0);
}
void Alphabet_BBsM(double x, double y, double x_size, double y_size, BB *pBBs, int pBBs_size)
{
    /* bbs size isn't correct return */
    if(pBBs_size != 4) return;

    BB_Init( &(pBBs[0]) , x+x_size, y+y_size*7, 0, x_size*5, y_size, 0);
    BB_Init( &(pBBs[1]) , x+x_size, y+y_size, 0, x_size, y_size*6, 0);
    BB_Init( &(pBBs[2]) , x+x_size*3, y+y_size, 0, x_size, y_size*6, 0);
    BB_Init( &(pBBs[3]) , x+x_size*5, y+y_size, 0, x_size, y_size*6, 0);
}
void Alphabet_BBsN(double x, double y, double x_size, double y_size, BB *pBBs, int pBBs_size)
{
    /* bbs size isn't correct return */
    if(pBBs_size != 5) return;

    BB_Init( &(pBBs[0]) , x+x_size, y+y_size, 0, x_size, y_size*7, 0);
    BB_Init( &(pBBs[1]) , x+x_size*2, y+y_size*5, 0, x_size, y_size*3, 0);
    BB_Init( &(pBBs[2]) , x+x_size*3, y+y_size*3, 0, x_size, y_size*3, 0);
    BB_Init( &(pBBs[3]) , x+x_size*4, y+y_size, 0, x_size, y_size*3, 0);
    BB_Init( &(pBBs[4]) , x+x_size*5, y+y_size, 0, x_size, y_size*7, 0);
}
void Alphabet_BBsO(double x, double y, double x_size, double y_size, BB *pBBs, int pBBs_size)
{
    /* bbs size isn't correct return */
    if(pBBs_size != 4) return;

    BB_Init( &(pBBs[0]) , x+x_size, y+y_size*2, 0, x_size, y_size*5, 0);
    BB_Init( &(pBBs[1]) , x+x_size*5, y+y_size*2, 0, x_size, y_size*5, 0);
    BB_Init( &(pBBs[2]) , x+x_size*2, y+y_size*7, 0, x_size*3, y_size, 0);
    BB_Init( &(pBBs[3]) , x+x_size*2, y+y_size, 0, x_size*3, y_size, 0);

}
void Alphabet_BBsP(double x, double y, double x_size, double y_size, BB *pBBs, int pBBs_size)
{
    /* bbs size isn't correct return */
    if(pBBs_size != 4) return;

    BB_Init( &(pBBs[0]) , x+x_size, y+y_size, 0, x_size, y_size*7, 0);
    BB_Init( &(pBBs[1]) , x+x_size*2, y+y_size*7, 0, x_size*3, y_size, 0);
    BB_Init( &(pBBs[2]) , x+x_size*2, y+y_size*4, 0, x_size*3, y_size, 0);
    BB_Init( &(pBBs[3]) , x+x_size*5, y+y_size*5, 0, x_size, y_size*2, 0);

}
void Alphabet_BBsQ(double x, double y, double x_size, double y_size, BB *pBBs, int pBBs_size)
{
    /* bbs size isn't correct return */
    if(pBBs_size != 7) return;

    BB_Init( &(pBBs[0]) , x+x_size*2, y+y_size, 0, x_size*2, y_size, 0);
    BB_Init( &(pBBs[1]) , x+x_size*2, y+y_size*7, 0, x_size*3, y_size, 0);
    BB_Init( &(pBBs[2]) , x+x_size*5, y+y_size, 0, x_size, y_size, 0);
    BB_Init( &(pBBs[3]) , x+x_size*4, y+y_size*2, 0, x_size, y_size, 0);
    BB_Init( &(pBBs[4]) , x+x_size*3, y+y_size*3, 0, x_size, y_size, 0);
    BB_Init( &(pBBs[5]) , x+x_size, y+y_size*2, 0, x_size, y_size*5, 0);
    BB_Init( &(pBBs[6]) , x+x_size*5, y+y_size*3, 0, x_size, y_size*4, 0);
}
void Alphabet_BBsR(double x, double y, double x_size, double y_size, BB *pBBs, int pBBs_size)
{
    /* bbs size isn't correct return */
    if(pBBs_size != 7) return;

    BB_Init( &(pBBs[0]) , x+x_size, y+y_size, 0, x_size, y_size*7, 0);
    BB_Init( &(pBBs[1]) , x+x_size*5, y+y_size*5, 0, x_size, y_size*2, 0);
    BB_Init( &(pBBs[2]) , x+x_size*2, y+y_size*7, 0, x_size*3, y_size, 0);
    BB_Init( &(pBBs[3]) , x+x_size*2, y+y_size*4, 0, x_size*3, y_size, 0);
    BB_Init( &(pBBs[4]) , x+x_size*3, y+y_size*3, 0, x_size, y_size, 0);
    BB_Init( &(pBBs[5]) , x+x_size*4, y+y_size*2, 0, x_size, y_size, 0);
    BB_Init( &(pBBs[6]) , x+x_size*5, y+y_size, 0, x_size, y_size, 0);
}
void Alphabet_BBsS(double x, double y, double x_size, double y_size, BB *pBBs, int pBBs_size)
{
    /* bbs size isn't correct return */
    if(pBBs_size != 7) return;

    BB_Init( &(pBBs[0]) , x+x_size*2, y+y_size, 0, x_size*3, y_size, 0);
    BB_Init( &(pBBs[1]) , x+x_size*2, y+y_size*4, 0, x_size*3, y_size, 0);
    BB_Init( &(pBBs[2]) , x+x_size*2, y+y_size*7, 0, x_size*3, y_size, 0);
    BB_Init( &(pBBs[3]) , x+x_size, y+y_size*2, 0, x_size, y_size, 0);
    BB_Init( &(pBBs[4]) , x+x_size, y+y_size*5, 0, x_size, y_size*2, 0);
    BB_Init( &(pBBs[5]) , x+x_size*5, y+y_size*2, 0, x_size, y_size*2, 0);
    BB_Init( &(pBBs[6]) , x+x_size*5, y+y_size*6, 0, x_size, y_size, 0);
}
void Alphabet_BBsT(double x, double y, double x_size, double y_size, BB *pBBs, int pBBs_size)
{
    /* bbs size isn't correct return */
    if(pBBs_size != 2) return;

    BB_Init( &(pBBs[0]) , x+x_size, y+y_size*7, 0, x_size*5, y_size, 0);
    BB_Init( &(pBBs[1]) , x+x_size*3, y+y_size, 0, x_size, y_size*6, 0);
}
void Alphabet_BBsU(double x, double y, double x_size, double y_size, BB *pBBs, int pBBs_size)
{
    /* bbs size isn't correct return */
    if(pBBs_size != 3) return;

    BB_Init( &(pBBs[0]) , x+x_size*2, y+y_size, 0, x_size*3, y_size, 0);
    BB_Init( &(pBBs[1]) , x+x_size, y+y_size*2, 0, x_size, y_size*6, 0);
    BB_Init( &(pBBs[2]) , x+x_size*5, y+y_size*2, 0, x_size, y_size*6, 0);
}
void Alphabet_BBsV(double x, double y, double x_size, double y_size, BB *pBBs, int pBBs_size)
{
    /* bbs size isn't correct return */
    if(pBBs_size != 5) return;

    BB_Init( &(pBBs[0]) , x+x_size, y+y_size*4, 0, x_size, y_size*4, 0);
    BB_Init( &(pBBs[1]) , x+x_size*5, y+y_size*4, 0, x_size, y_size*4, 0);
    BB_Init( &(pBBs[2]) , x+x_size*2, y+y_size*2, 0, x_size, y_size*2, 0);
    BB_Init( &(pBBs[3]) , x+x_size*4, y+y_size*2, 0, x_size, y_size*2, 0);
    BB_Init( &(pBBs[4]) , x+x_size*3, y+y_size, 0, x_size, y_size, 0);
}
void Alphabet_BBsW(double x, double y, double x_size, double y_size, BB *pBBs, int pBBs_size)
{
    /* bbs size isn't correct return */
    if(pBBs_size != 4) return;

    BB_Init( &(pBBs[0]) , x+x_size, y+y_size*2, 0, x_size, y_size*6, 0);
    BB_Init( &(pBBs[1]) , x+x_size*5, y+y_size*2, 0, x_size, y_size*6, 0);
    BB_Init( &(pBBs[2]) , x+x_size*3, y+y_size*2, 0, x_size, y_size*3, 0);
    BB_Init( &(pBBs[3]) , x+x_size*2, y+y_size, 0, x_size*3, y_size, 0);
}
void Alphabet_BBsX(double x, double y, double x_size, double y_size, BB *pBBs, int pBBs_size)
{
    /* bbs size isn't correct return */
    if(pBBs_size != 9) return;

    BB_Init( &(pBBs[0]) , x+x_size, y+y_size, 0, x_size, y_size*2, 0);
    BB_Init( &(pBBs[1]) , x+x_size*5, y+y_size, 0, x_size, y_size*2, 0);
    BB_Init( &(pBBs[2]) , x+x_size, y+y_size*6, 0, x_size, y_size*2, 0);
    BB_Init( &(pBBs[3]) , x+x_size*5, y+y_size*6, 0, x_size, y_size*2, 0);
    BB_Init( &(pBBs[4]) , x+x_size*2, y+y_size*3, 0, x_size, y_size, 0);
    BB_Init( &(pBBs[5]) , x+x_size*4, y+y_size*3, 0, x_size, y_size, 0);
    BB_Init( &(pBBs[6]) , x+x_size*2, y+y_size*5, 0, x_size, y_size, 0);
    BB_Init( &(pBBs[7]) , x+x_size*4, y+y_size*5, 0, x_size, y_size, 0);
    BB_Init( &(pBBs[8]) , x+x_size*3, y+y_size*4, 0, x_size, y_size, 0);
}
void Alphabet_BBsY(double x, double y, double x_size, double y_size, BB *pBBs, int pBBs_size)
{
    /* bbs size isn't correct return */
    if(pBBs_size != 5) return;

    BB_Init( &(pBBs[0]) , x+x_size, y+y_size*6, 0, x_size, y_size*2, 0);
    BB_Init( &(pBBs[1]) , x+x_size*5, y+y_size*6, 0, x_size, y_size*2, 0);
    BB_Init( &(pBBs[2]) , x+x_size*2, y+y_size*5, 0, x_size, y_size, 0);
    BB_Init( &(pBBs[3]) , x+x_size*4, y+y_size*5, 0, x_size, y_size, 0);
    BB_Init( &(pBBs[4]) , x+x_size*3, y+y_size, 0, x_size, y_size*4, 0);
}
void Alphabet_BBsZ(double x, double y, double x_size, double y_size, BB *pBBs, int pBBs_size)
{
    /* bbs size isn't correct return */
    if(pBBs_size != 7) return;

    BB_Init( &(pBBs[0]) , x+x_size, y+y_size*7, 0, x_size*5, y_size, 0);
    BB_Init( &(pBBs[1]) , x+x_size, y+y_size, 0, x_size*5, y_size, 0);
    BB_Init( &(pBBs[2]) , x+x_size, y+y_size*2, 0, x_size, y_size, 0);
    BB_Init( &(pBBs[3]) , x+x_size*5, y+y_size*6, 0, x_size, y_size, 0);
    BB_Init( &(pBBs[4]) , x+x_size*2, y+y_size*3, 0, x_size, y_size, 0);
    BB_Init( &(pBBs[5]) , x+x_size*3, y+y_size*4, 0, x_size, y_size, 0);
    BB_Init( &(pBBs[6]) , x+x_size*4, y+y_size*5, 0, x_size, y_size, 0);
}
void Alphabet_BBsVerticalBar(double x, double y, double x_size, double y_size, BB *pBBs, int pBBs_size)
{
    /* bbs size isn't correct return */
    if(pBBs_size != 1) return;

    BB_Init( &(pBBs[0]) , x+x_size*3, y+y_size*1, 0, x_size, y_size*8, 0);
}

/* public funcs */
void Alphabet_SetCursor(double x, double y)
{
    alphabet_x = x;
    alphabet_y = y;
}
void Alphabet_SetSize(double size)
{
    alphabet_x_size = size;
    alphabet_y_size = size;
}
void Alphabet_Char(char c)
{
    if(c == ' ')
    {
        Alphabet_CursorForward();
    }
    /*else if(c == '|')
    {
        nBBs = 1;
        if( nRoomLeft < nBBs )
        {
            return nIndexStart;
        }
        BB *bbs = psBBs + nIndexStart;
        Alphabet_BBsVerticalBar(alphabet_x, alphabet_y, alphabet_x_size, alphabet_y_size, bbs, nBBs );
        Alphabet_CursorForward();
    }*/
    else if(c == '_')
    {
        BB bbs[1];
        Alphabet_BBsUnderscore(alphabet_x, alphabet_y, alphabet_x_size, alphabet_y_size, bbs, sizeof(bbs)/sizeof(bbs[0]) );
        BB_DrawBBs(bbs, sizeof(bbs)/sizeof(bbs[0]) );
        Alphabet_CursorForward();
    }
    else if(c == '0')
    {
        BB bbs[7];
        Alphabet_BBs0(alphabet_x, alphabet_y, alphabet_x_size, alphabet_y_size, bbs, sizeof(bbs)/sizeof(bbs[0]) );
        BB_DrawBBs(bbs, sizeof(bbs)/sizeof(bbs[0]) );
        Alphabet_CursorForward();
    }
    else if(c == '1')
    {
        BB bbs[4];
        Alphabet_BBs1(alphabet_x, alphabet_y, alphabet_x_size, alphabet_y_size, bbs, sizeof(bbs)/sizeof(bbs[0]) );
        BB_DrawBBs(bbs, sizeof(bbs)/sizeof(bbs[0]) );
        Alphabet_CursorForward();
    }
    else if(c == '2')
    {
        BB bbs[8];
        Alphabet_BBs2(alphabet_x, alphabet_y, alphabet_x_size, alphabet_y_size, bbs, sizeof(bbs)/sizeof(bbs[0]) );
        BB_DrawBBs(bbs, sizeof(bbs)/sizeof(bbs[0]) );
        Alphabet_CursorForward();
    }
    else if(c == '3')
    {
        BB bbs[6];
        Alphabet_BBs3(alphabet_x, alphabet_y, alphabet_x_size, alphabet_y_size, bbs, sizeof(bbs)/sizeof(bbs[0]) );
        BB_DrawBBs(bbs, sizeof(bbs)/sizeof(bbs[0]) );
        Alphabet_CursorForward();
    }
    else if(c == '4')
    {
        BB bbs[3];
        Alphabet_BBs4(alphabet_x, alphabet_y, alphabet_x_size, alphabet_y_size, bbs, sizeof(bbs)/sizeof(bbs[0]) );
        BB_DrawBBs(bbs, sizeof(bbs)/sizeof(bbs[0]) );
        Alphabet_CursorForward();
    }
    else if(c == '5')
    {
        BB bbs[6];
        Alphabet_BBs5(alphabet_x, alphabet_y, alphabet_x_size, alphabet_y_size, bbs, sizeof(bbs)/sizeof(bbs[0]) );
        BB_DrawBBs(bbs, sizeof(bbs)/sizeof(bbs[0]) );
        Alphabet_CursorForward();
    }
    else if(c == '6')
    {
        BB bbs[5];
        Alphabet_BBs6(alphabet_x, alphabet_y, alphabet_x_size, alphabet_y_size, bbs, sizeof(bbs)/sizeof(bbs[0]) );
        BB_DrawBBs(bbs, sizeof(bbs)/sizeof(bbs[0]) );
        Alphabet_CursorForward();
    }
    else if(c == '7')
    {
        BB bbs[6];
        Alphabet_BBs7(alphabet_x, alphabet_y, alphabet_x_size, alphabet_y_size, bbs, sizeof(bbs)/sizeof(bbs[0]) );
        BB_DrawBBs(bbs, sizeof(bbs)/sizeof(bbs[0]) );
        Alphabet_CursorForward();
    }
    else if(c == '8')
    {
        BB bbs[5];
        Alphabet_BBs8(alphabet_x, alphabet_y, alphabet_x_size, alphabet_y_size, bbs, sizeof(bbs)/sizeof(bbs[0]) );
        BB_DrawBBs(bbs, sizeof(bbs)/sizeof(bbs[0]) );
        Alphabet_CursorForward();
    }
    else if(c == '9')
    {
        BB bbs[4];
        Alphabet_BBs9(alphabet_x, alphabet_y, alphabet_x_size, alphabet_y_size, bbs, sizeof(bbs)/sizeof(bbs[0]) );
        BB_DrawBBs(bbs, sizeof(bbs)/sizeof(bbs[0]) );
        Alphabet_CursorForward();
    }

    else if(c == 'a' || c == 'A')
    {
        BB bbs[4];
        Alphabet_BBsA(alphabet_x, alphabet_y, alphabet_x_size, alphabet_y_size, bbs, sizeof(bbs)/sizeof(bbs[0]) );
        BB_DrawBBs(bbs, sizeof(bbs)/sizeof(bbs[0]) );
        Alphabet_CursorForward();
    }
    else if(c == 'b' || c == 'B')
    {
        BB bbs[5];
        Alphabet_BBsB(alphabet_x, alphabet_y, alphabet_x_size, alphabet_y_size, bbs, sizeof(bbs)/sizeof(bbs[0]) );
        BB_DrawBBs(bbs, sizeof(bbs)/sizeof(bbs[0]) );
        Alphabet_CursorForward();
    }
    else if(c == 'c' || c == 'C')
    {
        BB bbs[5];
        Alphabet_BBsC(alphabet_x, alphabet_y, alphabet_x_size, alphabet_y_size, bbs, sizeof(bbs)/sizeof(bbs[0]) );
        BB_DrawBBs(bbs, sizeof(bbs)/sizeof(bbs[0]) );
        Alphabet_CursorForward();
    }
    else if(c == 'd' || c == 'D')
    {
        BB bbs[4];
        Alphabet_BBsD(alphabet_x, alphabet_y, alphabet_x_size, alphabet_y_size, bbs, sizeof(bbs)/sizeof(bbs[0]) );
        BB_DrawBBs(bbs, sizeof(bbs)/sizeof(bbs[0]) );
        Alphabet_CursorForward();
    }
    else if(c == 'e' || c == 'E')
    {
        BB bbs[4];
        Alphabet_BBsE(alphabet_x, alphabet_y, alphabet_x_size, alphabet_y_size, bbs, sizeof(bbs)/sizeof(bbs[0]) );
        BB_DrawBBs(bbs, sizeof(bbs)/sizeof(bbs[0]) );
        Alphabet_CursorForward();
    }
    else if(c == 'f' || c == 'F')
    {
        BB bbs[3];
        Alphabet_BBsF(alphabet_x, alphabet_y, alphabet_x_size, alphabet_y_size, bbs, sizeof(bbs)/sizeof(bbs[0]) );
        BB_DrawBBs(bbs, sizeof(bbs)/sizeof(bbs[0]) );
        Alphabet_CursorForward();
    }
    else if(c == 'g' || c == 'G')
    {
        BB bbs[6];
        Alphabet_BBsG(alphabet_x, alphabet_y, alphabet_x_size, alphabet_y_size, bbs, sizeof(bbs)/sizeof(bbs[0]) );
        BB_DrawBBs(bbs, sizeof(bbs)/sizeof(bbs[0]) );
        Alphabet_CursorForward();
    }
    else if(c == 'h' || c == 'H')
    {
        BB bbs[3];
        Alphabet_BBsH(alphabet_x, alphabet_y, alphabet_x_size, alphabet_y_size, bbs, sizeof(bbs)/sizeof(bbs[0]) );
        BB_DrawBBs(bbs, sizeof(bbs)/sizeof(bbs[0]) );
        Alphabet_CursorForward();
    }
    else if(c == 'i' || c == 'I')
    {
        BB bbs[3];
        Alphabet_BBsI(alphabet_x, alphabet_y, alphabet_x_size, alphabet_y_size, bbs, sizeof(bbs)/sizeof(bbs[0]) );
        BB_DrawBBs(bbs, sizeof(bbs)/sizeof(bbs[0]) );
        Alphabet_CursorForward();
    }
    else if(c == 'j' || c == 'J')
    {
        BB bbs[4];
        Alphabet_BBsJ(alphabet_x, alphabet_y, alphabet_x_size, alphabet_y_size, bbs, sizeof(bbs)/sizeof(bbs[0]) );
        BB_DrawBBs(bbs, sizeof(bbs)/sizeof(bbs[0]) );
        Alphabet_CursorForward();
    }
    else if(c == 'k' || c == 'K')
    {
        BB bbs[8];
        Alphabet_BBsK(alphabet_x, alphabet_y, alphabet_x_size, alphabet_y_size, bbs, sizeof(bbs)/sizeof(bbs[0]) );
        BB_DrawBBs(bbs, sizeof(bbs)/sizeof(bbs[0]) );
        Alphabet_CursorForward();
    }
    else if(c == 'l' || c == 'L')
    {
        BB bbs[2];
        Alphabet_BBsL(alphabet_x, alphabet_y, alphabet_x_size, alphabet_y_size, bbs, sizeof(bbs)/sizeof(bbs[0]) );
        BB_DrawBBs(bbs, sizeof(bbs)/sizeof(bbs[0]) );
        Alphabet_CursorForward();
    }
    else if(c == 'm' || c == 'M')
    {
        BB bbs[4];
        Alphabet_BBsM(alphabet_x, alphabet_y, alphabet_x_size, alphabet_y_size, bbs, sizeof(bbs)/sizeof(bbs[0]) );
        BB_DrawBBs(bbs, sizeof(bbs)/sizeof(bbs[0]) );
        Alphabet_CursorForward();
    }
    else if(c == 'n' || c == 'N')
    {
        BB bbs[5];
        Alphabet_BBsN(alphabet_x, alphabet_y, alphabet_x_size, alphabet_y_size, bbs, sizeof(bbs)/sizeof(bbs[0]) );
        BB_DrawBBs(bbs, sizeof(bbs)/sizeof(bbs[0]) );
        Alphabet_CursorForward();
    }
    else if(c == 'o' || c == 'O')
    {
        BB bbs[4];
        Alphabet_BBsO(alphabet_x, alphabet_y, alphabet_x_size, alphabet_y_size, bbs, sizeof(bbs)/sizeof(bbs[0]) );
        BB_DrawBBs(bbs, sizeof(bbs)/sizeof(bbs[0]) );
        Alphabet_CursorForward();
    }
    else if(c == 'p' || c == 'P')
    {
        BB bbs[4];
        Alphabet_BBsP(alphabet_x, alphabet_y, alphabet_x_size, alphabet_y_size, bbs, sizeof(bbs)/sizeof(bbs[0]) );
        BB_DrawBBs(bbs, sizeof(bbs)/sizeof(bbs[0]) );
        Alphabet_CursorForward();
    }
    else if(c == 'q' || c == 'Q')
    {
        BB bbs[7];
        Alphabet_BBsQ(alphabet_x, alphabet_y, alphabet_x_size, alphabet_y_size, bbs, sizeof(bbs)/sizeof(bbs[0]) );
        BB_DrawBBs(bbs, sizeof(bbs)/sizeof(bbs[0]) );
        Alphabet_CursorForward();
    }
    else if(c == 'r' || c == 'R')
    {
        BB bbs[7];
        Alphabet_BBsR(alphabet_x, alphabet_y, alphabet_x_size, alphabet_y_size, bbs, sizeof(bbs)/sizeof(bbs[0]) );
        BB_DrawBBs(bbs, sizeof(bbs)/sizeof(bbs[0]) );
        Alphabet_CursorForward();
    }
    else if(c == 's' || c == 'S')
    {
        BB bbs[7];
        Alphabet_BBsS(alphabet_x, alphabet_y, alphabet_x_size, alphabet_y_size, bbs, sizeof(bbs)/sizeof(bbs[0]) );
        BB_DrawBBs(bbs, sizeof(bbs)/sizeof(bbs[0]) );
        Alphabet_CursorForward();
    }
    else if(c == 't' || c == 'T')
    {
        BB bbs[2];
        Alphabet_BBsT(alphabet_x, alphabet_y, alphabet_x_size, alphabet_y_size, bbs, sizeof(bbs)/sizeof(bbs[0]) );
        BB_DrawBBs(bbs, sizeof(bbs)/sizeof(bbs[0]) );
        Alphabet_CursorForward();
    }
    else if(c == 'u' || c == 'U')
    {
        BB bbs[3];
        Alphabet_BBsU(alphabet_x, alphabet_y, alphabet_x_size, alphabet_y_size, bbs, sizeof(bbs)/sizeof(bbs[0]) );
        BB_DrawBBs(bbs, sizeof(bbs)/sizeof(bbs[0]) );
        Alphabet_CursorForward();
    }
    else if(c == 'v' || c == 'V')
    {
        BB bbs[5];
        Alphabet_BBsV(alphabet_x, alphabet_y, alphabet_x_size, alphabet_y_size, bbs, sizeof(bbs)/sizeof(bbs[0]) );
        BB_DrawBBs(bbs, sizeof(bbs)/sizeof(bbs[0]) );
        Alphabet_CursorForward();
    }
    else if(c == 'w' || c == 'W')
    {
        BB bbs[4];
        Alphabet_BBsW(alphabet_x, alphabet_y, alphabet_x_size, alphabet_y_size, bbs, sizeof(bbs)/sizeof(bbs[0]) );
        BB_DrawBBs(bbs, sizeof(bbs)/sizeof(bbs[0]) );
        Alphabet_CursorForward();
    }
    else if(c == 'x' || c == 'X')
    {
        BB bbs[9];
        Alphabet_BBsX(alphabet_x, alphabet_y, alphabet_x_size, alphabet_y_size, bbs, sizeof(bbs)/sizeof(bbs[0]) );
        BB_DrawBBs(bbs, sizeof(bbs)/sizeof(bbs[0]) );
        Alphabet_CursorForward();
    }
    else if(c == 'y' || c == 'Y')
    {
        BB bbs[5];
        Alphabet_BBsY(alphabet_x, alphabet_y, alphabet_x_size, alphabet_y_size, bbs, sizeof(bbs)/sizeof(bbs[0]) );
        BB_DrawBBs(bbs, sizeof(bbs)/sizeof(bbs[0]) );
        Alphabet_CursorForward();
    }
    else if(c == 'z' || c == 'Z')
    {
        BB bbs[7];
        Alphabet_BBsZ(alphabet_x, alphabet_y, alphabet_x_size, alphabet_y_size, bbs, sizeof(bbs)/sizeof(bbs[0]) );
        BB_DrawBBs(bbs, sizeof(bbs)/sizeof(bbs[0]) );
        Alphabet_CursorForward();
    }
    
}
void Alphabet_String(char *aString)
{
    int nMaxChars = 500; /* Max characters to loop through */
    int i = 0;
    double dBeginX = alphabet_x; /* store where the cursor began on x axis */
    
    /* Do one Char at a time */
    /* While not max characters */
    while(i < nMaxChars)
    {
        if( aString[i] == '\0' )
        {
            return;
        }
        else if( aString[i] == '\n' )
        {
            Alphabet_CursorNewline(dBeginX);
        }
        else
        {
            Alphabet_Char(aString[i]);
        }
        ++i;
    }
    
}
