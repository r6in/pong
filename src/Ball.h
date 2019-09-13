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
#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED

#include <stdbool.h>
#include <Vector.h>
#include <Direction.h>
#include <Cooldown.h>

typedef struct Resource Resource;
typedef struct Ball Ball;

struct Ball
{
    Vector psPos[1];
    Vector psSize[1];
    Vector psVel[1];
    double dSpeed;
    Direction psDir[1];
    Cooldown psCooldown[1];
    bool bMovement;
};

void Ball_Init(  Ball *psBall, Resource *psResource);

void Ball_Reset(Ball *psBall, Resource *psResource);

void Ball_RandomPlaceBall(Ball *psBall, Resource *psResource);

void Ball_PlaceBall(Ball *psBall, bool bRightSide, Resource *psResource);

void Ball_Input( Ball *psBall, Resource *psResource);

void Ball_Update(Ball *psBall, Resource *psResource);

void Ball_PaddleSound( void );

void Ball_Render(Ball *psBall, Resource *psResource);

#endif