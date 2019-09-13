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
#include "Vector.h"
#include <string.h>
#include <stdio.h>

void Vector_Init(Vector *psVector, double x, double y, double z)
{
    if( psVector == NULL )
    {
        printf("Error: NULL Vector.\n");
        return;
    }
    
    memset(psVector, 0, sizeof(Vector));
    
    psVector->dX = x;
    psVector->dY = y;
    psVector->dZ = z;
}


void Vector_InitByVector(Vector *psVector, const Vector *psBy)
{
    if( psBy == NULL )
    {
        printf("Error: NULL By Vector.\n");
        return;
    }
    Vector_Init(psVector, psBy->dX, psBy->dY, psBy->dZ);
}


void Vector_Zero(Vector *psVector)
{
    Vector_Init(psVector, 0.0, 0.0, 0.0);
}


void Vector_Print(Vector *psVector)
{

    printf(
        "Vector x: %f, y: %f, z: %f.\n",
        psVector->dX,
        psVector->dY,
        psVector->dZ);
}