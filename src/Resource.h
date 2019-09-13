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
#ifndef RESOURCE_H_INCLUDED
#define RESOURCE_H_INCLUDED

#include "Util.h"
#include "Messages.h"
#include "Window.h"
#include "Keyboard.h"
#include "Loop.h"
#include <BB.h>
#include <Strategy.h>
#include <Paddle.h>
#include <Ball.h>
#include <Dash.h>
#include <Scores.h>


typedef struct Resource Resource;

struct Resource
{
    Messages        psMessages[1];
    Window          psWindow[1];
    Keyboard        psKeys[1];
    Loop            psLoop[1];
    Strategy        psStrategy[1];
    BB              psWindowCanvas[1];
    BB              psPlayArea[1];
    Paddle          psPaddle[2];
    Ball            psBall[1];
    BB              psBorders[2];
    int             nBordersSize;
    Dash            psDash[1];
    Scores          psScores[1];
    
};

void Resource_Init(Resource *psResource);

#endif