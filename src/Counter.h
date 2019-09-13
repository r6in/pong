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
#ifndef COUNTER_H_INCLUDED
#define COUNTER_H_INCLUDED

#include "Util.h"

typedef struct Counter Counter;

struct Counter
{
    LARGE_INTEGER psFrequency[1];
    LARGE_INTEGER psCountStart[1];
    LARGE_INTEGER psCountEnd[1];
    
};


int Counter_Init(Counter *ps);
void Counter_StartRecord(Counter *ps);
void  Counter_EndRecord(Counter *ps);
double Counter_ElapsedMs(Counter *ps);
void Counter_GetOffsetTime( Counter *ps,
                            double dOffsetMs,
                            LARGE_INTEGER *psTime);


#endif