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
#ifndef COOLDOWN_H_INCLUDED
#define COOLDOWN_H_INCLUDED

#include <windows.h>

typedef struct Resource Resource;
typedef struct Cooldown Cooldown;

struct Cooldown
{
    double dDuration;
    LARGE_INTEGER psCompletedCounter[1];
    Resource *psResource;
};

void Cooldown_Init( Cooldown *psCooldown,
                    double dDuration,
                    Resource *psResource);

void Cooldown_Duration(Cooldown *psCooldown, double dDuration);

void Cooldown_Start(Cooldown *psCooldown);

int Cooldown_Completed(Cooldown *psCooldown);


#endif