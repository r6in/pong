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
#ifndef LOOP_H_INCLUDED
#define LOOP_H_INCLUDED

#include "Util.h"
#include "Counter.h"

typedef struct Loop Loop;
typedef struct Keyboard Keyboard;
typedef struct Messages Messages;

struct Loop
{
    Counter   psFull[1];
    Counter   psNoYield[1];
    double    dFullMs;
    double    dNoYieldMs;
    double    dTargetMs;
    double    dUpdateMs;
    double    dAcuMs;
    int       nMaxUpdates;
    int       i;
    Messages *psMessages;
    Keyboard *psKeys;
    bool      bRunning;
};


int  Loop_Init(Loop *ps, Messages *psMessages, Keyboard *psKeys);
bool Loop_Start(Loop *ps);
bool Loop_Updates(Loop *ps);
void Loop_End(Loop *ps);

#endif