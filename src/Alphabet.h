/*
    Copyright 2015 David Ridpath <r6inhardt@hotmail.com>
 
    Licensed under GNU General Public License 3.0
    See COPYING.
   
    This file is part of Pong.
   
    Pong is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
   
    Pong is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with Pong.  If not, see <http://www.gnu.org/licenses/>.

    Alphabet
    
    TODO
    ====
    Function SetSize to take a size amount and set internal size to fit.
    Function to take center x,y and given the string and size info, work out..
        where to render from to center justify the text.
    
    Version History
    ===============
    25/07/14
    All vars now doubles.
    BB's now init as 3D with Z specified as 0.
    21/06/14
    Altered 'G' bb's to look nicer.
*/
#ifndef ALPHABET_H_INCLUDED
#define ALPHABET_H_INCLUDED

#include <stdbool.h>

typedef struct BB BB;

/* example: alphabet_string("po\npo"); */

void Alphabet_SetCursor(double x, double y);
void Alphabet_SetSize(double size);
void Alphabet_Char(char c);
void Alphabet_String(char *aString);

                    
#endif
