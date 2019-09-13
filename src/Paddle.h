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
#ifndef PADDLE_H_INCLUDED
#define PADDLE_H_INCLUDED

#include <stdbool.h>
#include <Vector.h>

typedef struct Resource Resource;
typedef struct Paddle Paddle;

struct Paddle
{
    Vector psPos[1];
    Vector psSize[1];
    Vector psVel[1];
    double dSpeed;
    bool bUp;
    bool bDown;
    double dDir;
    bool bAI;
};

void Paddle_Init(Paddle *psPaddle, bool bAI, Resource *psResource);

void Paddle_Reset(Paddle *psPaddles, Resource *psResource);

void Paddle_Input(Paddle *psPaddle, Resource *psResource);

void Paddle_Update(Paddle *psPaddle, Resource *psResource);

void Paddle_Render(Paddle *psPaddle, Resource *psResource);

#endif