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
#include "Messages.h"


void Messages_Init(Messages *ps)
{
    memset(ps, 0, sizeof(Messages) );
    
}


void Messages_Process(struct Messages *ps)
{
    MSG msg;
    
    /* if PeekMesasge ,Hwnd is NULL will pick up Thread message WM_QUIT */
    while( PeekMessage(&msg, /*gmWindowHwnd*/NULL,  0, 0, PM_REMOVE) )
    {
        if( msg.message == WM_QUIT )
        {
            ps->bWMQuit = true;
        }
        else if( msg.message == WM_KEYDOWN )
        {
            /* Print Key Down */
            /*printf("Key Down Int = %d\n", (int)msg.wParam);
            */
            /*
                Key Codes:
                Esc = 27
                Left = 37
                Right = 39
            */
            /* Set Key Down */
            ps->pbKeyDown[msg.wParam] = true;
            
        }
        else if( msg.message == WM_KEYUP )
        {
            ps->pbKeyDown[msg.wParam] = false;
            
        }
        
        TranslateMessage( &msg );
        DispatchMessage( &msg );
    }
    
    /* return void */
}
