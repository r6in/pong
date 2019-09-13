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
#ifndef DASH_H_INCLUDED
#define DASH_H_INCLUDED

#include <BB.h>

typedef struct Dash Dash;

struct Dash
{
    BB psArea[1];
    BB psBBs[100];
    int nSize;
    
};


void Dash_InitY(Dash *psDash,
                BB *psBottom,
                BB *psTop,
                double dSize);

void Dash_Render(Dash *psDash);

#endif