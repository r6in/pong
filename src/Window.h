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
#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

#include "Util.h"

typedef struct Window Window;

struct Window
{
    char            *aClass;
    char            *aTitle;
    HINSTANCE       hInstance;
    HWND            hWND;
    HDC             hDC;
    HGLRC           hGLRC;
    int             nWidth;
    int             nHeight;
    double          dCanvasWidth;
    double          dCanvasHeight;

};

void Window_Init(Window    *ps,
                 HINSTANCE hInstance,
                 char      *aClass,
                 char      *aTitle,
                 int       nWidth,
                 int       nHeight);
int Window_ShowWindow(Window *ps);
int Window_ResizeScene2D(Window *ps);
void Window_Clear(Window *ps);
void Window_SwapBuffers(Window *ps);

#endif