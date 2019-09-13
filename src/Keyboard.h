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
#ifndef KEYBOARD_H_INCLUDED
#define KEYBOARD_H_INCLUDED

#include "Util.h"

typedef struct Keyboard Keyboard;
typedef struct Messages Messages;

struct Keyboard
{
    Messages *psMessages;
    bool bKeyEsc;
    bool bKeySpace;
    bool bKeyLeft;
    bool bKeyRight;
    bool bKeyDown;
    bool bKeyUp;
    bool bKeyQ;
    bool bKeyW;
    bool bKeyR;
    bool bKeyA;
    bool bKeyS;
    bool bKeyD;
};

void Keyboard_Init(Keyboard *ps, Messages *psMessages);
void Keyboard_Process(Keyboard *ps);

#endif