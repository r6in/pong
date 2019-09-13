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
#ifndef DIRECTION_H_INCLUDED
#define DIRECTION_H_INCLUDED

#include <stdbool.h>

typedef struct Direction Direction;

struct Direction
{
    double dRadians;
};

void Direction_Init(Direction *psDirection, double dRadians);

double Direction_SetRadians(Direction *psDirection, double dRadians);

double Direction_Clockwise(Direction *psDirection, double dRadians);

double Direction_AntiClockwise(Direction *psDirection, double dRadians);

double Direction_Radians45();

double Direction_Radians90();

double Direction_Radians135();

double Direction_Radians180();

double Direction_Radians225();

double Direction_Radians270();

double Direction_Radians315();

double Direction_Radians360();

double Direction_Radians(double dDegrees);

double Direction_Degrees(double dRadians);

bool Direction_IsNorthEast(Direction *psDirection);

bool Direction_IsNorthWest(Direction *psDirection);

bool Direction_IsSouthWest(Direction *psDirection);

bool Direction_IsSouthEast(Direction *psDirection);

#endif