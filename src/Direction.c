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
#include "Direction.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define RADIANS_45 0.7853981633974483
#define RADIANS_90 1.570796326794897 /*North*/
#define RADIANS_135 2.356194490192345
#define RADIANS_180 3.141592653589793 /*West*/
#define RADIANS_225 3.926990816987241
#define RADIANS_270 4.71238898038469 /*South*/
#define RADIANS_315 5.497787143782138
#define RADIANS_360 6.283185307179586 /*East*/
#define PI 3.14159265358979323846

void Direction_Init(Direction *psDirection, double dRadians)
{
    
    if( psDirection == NULL )
    {
        printf("Error: NULL Direction.\n");
        return;
    }
    
    Direction_SetRadians(psDirection, dRadians);
}

double Direction_SetRadians(Direction *psDirection, double dRadians)
{
    
    while( dRadians >= RADIANS_360 )
    {
        dRadians -= RADIANS_360;
    }
    while( dRadians < 0.0 )
    {
        dRadians += RADIANS_360;
    }
    
    psDirection->dRadians = dRadians;
    
    return dRadians;
}


double Direction_Clockwise(Direction *psDirection, double dRadians)
{
    return Direction_SetRadians(psDirection, psDirection->dRadians - dRadians);
}


double Direction_AntiClockwise(Direction *psDirection, double dRadians)
{
    return Direction_SetRadians(psDirection, psDirection->dRadians + dRadians);
}


double Direction_Radians45()
{
    return RADIANS_45;
}


double Direction_Radians90()
{
    return RADIANS_90;
}


double Direction_Radians135()
{
    return RADIANS_135;
}


double Direction_Radians180()
{
    return RADIANS_180;
}


double Direction_Radians225()
{
    return RADIANS_225;
}


double Direction_Radians270()
{
    return RADIANS_270;
}


double Direction_Radians315()
{
    return RADIANS_315;
}


double Direction_Radians360()
{
    return RADIANS_360;
}


double Direction_Radians(double dDegrees)
{
    return dDegrees * PI / 180.0;
}


double Direction_Degrees(double dRadians)
{
    return (dRadians * 180.0) / PI;
}


bool Direction_IsNorthEast(Direction *psDirection)
{
    
    if( psDirection->dRadians >= 0.0 && psDirection->dRadians < RADIANS_90 )
    {
        return true;
    }
    
    return false;
}


bool Direction_IsNorthWest(Direction *psDirection)
{
    
    if( psDirection->dRadians >= RADIANS_90 && psDirection->dRadians < RADIANS_180 )
    {
        return true;
    }
    
    return false;
}


bool Direction_IsSouthWest(Direction *psDirection)
{
    
    if( psDirection->dRadians >= RADIANS_180 && psDirection->dRadians < RADIANS_270 )
    {
        return true;
    }
    
    return false;
}


bool Direction_IsSouthEast(Direction *psDirection)
{
    
    if( psDirection->dRadians >= RADIANS_270 && psDirection->dRadians < RADIANS_360 )
    {
        return true;
    }
    
    return false;
}

