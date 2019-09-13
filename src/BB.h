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
#ifndef BB_H_INCLUDED
#define BB_H_INCLUDED

#include <stdbool.h>
#include <Vector.h>

typedef struct BB BB;

struct BB
{
    Vector psPos[1];
    Vector psSize[1];
};

void BB_Init(   BB *psBB,
                double x,
                double y,
                double z,
                double width,
                double height,
                double depth);
void BB_InitByVectors(BB *psBB, const Vector *psPos, const Vector *psSize);
int BB_GetBB(   const Vector *psPos,
                const Vector *psSize,
                const Vector *psVel,
                BB *psDst);
int BB_Clone(const BB *psSrc, BB *psDst);
double BB_LeftPlane(BB *psBB);
double BB_RightPlane(BB *psBB);
double BB_BottomPlane(BB *psBB);
double BB_TopPlane(BB *psBB);
/*  Returns x pos from top shrunk down. */
double BB_FromTop(BB *psBB, double y);
double BB_FromRight(BB *psBB, double x);
double BB_FromBottom(BB *psBB, double y);
double BB_FromLeft(BB *psBB, double x);
double BB_FitCenterX(BB *psBB, BB *psFit);
double BB_FitCenterY(BB *psBB, BB *psFit);
void BB_Print(BB *psBB);
void BB_Draw(BB *psBB);
void BB_DrawBBs(BB *psBBs, int nSize);
bool BB_IsColliding(BB *psA, BB *psB);
double BB_MidX(BB *psBB);
double BB_MidY(BB *psBB);
double BB_HalfWidth(BB *psBB);
double BB_HalfHeight(BB *psBB);


#endif