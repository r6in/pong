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
#include "Keyboard.h"
#include "Messages.h"


void Keyboard_Init(Keyboard *ps, Messages *psMessages)
{
    memset(ps, 0, sizeof(Keyboard));
    
    ps->psMessages = psMessages;
}


void Keyboard_Process(Keyboard *ps)
{
    ps->bKeyEsc = ps->psMessages->pbKeyDown[27 /* Esc */];
    
    ps->bKeySpace = ps->psMessages->pbKeyDown[32 /* Space */];
    
    ps->bKeyLeft = ps->psMessages->pbKeyDown[37 /* Left */];
    ps->bKeyRight = ps->psMessages->pbKeyDown[39 /* Right */];
    ps->bKeyUp = ps->psMessages->pbKeyDown[38 /* Up */];
    ps->bKeyDown = ps->psMessages->pbKeyDown[40 /* Down */];
    
    ps->bKeyQ = ps->psMessages->pbKeyDown[(int)'Q'];
    ps->bKeyW = ps->psMessages->pbKeyDown[(int)'W'];
    ps->bKeyR = ps->psMessages->pbKeyDown[(int)'R'];
    ps->bKeyA = ps->psMessages->pbKeyDown[(int)'A'];
    ps->bKeyS = ps->psMessages->pbKeyDown[(int)'S'];
    ps->bKeyD = ps->psMessages->pbKeyDown[(int)'D'];
    
}