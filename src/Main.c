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

    
    Pong
*/
#include "Util.h"
#include "Resource.h"
#include "Window.h"
#include "Messages.h"
#include "Loop.h"
#include "Keyboard.h"
#include "Counter.h"
#include "Strategy.h"


Resource ps[1];


int __stdcall WinMain(  HINSTANCE hInstance,
                        HINSTANCE hPrevInstance,
                        LPSTR lpCmdLine,
                        int nCmdShow)
{
    int nRet = 0;
    
    
    Resource_Init(ps);
    
    Messages_Init(ps->psMessages);
    Window_Init(ps->psWindow, hInstance, "Class1", "Pong", 800, 600);
    Keyboard_Init(ps->psKeys, ps->psMessages);
    
    nRet = Loop_Init(ps->psLoop, ps->psMessages, ps->psKeys);
    if( nRet ) 
    {
        printf("Error.\n");
        return 1;
    }
    
    nRet = Window_ShowWindow(ps->psWindow);
    if( nRet ) 
    {
        printf("Error.\n");
        return 1;
    }
    
    if( Window_ResizeScene2D(ps->psWindow) )
    {
        printf("Error resizing opengl scene 2D\n");
        return 1;
    }
    
    
    while(Loop_Start(ps->psLoop) )
    {
        /* Update Loop */
        while( Loop_Updates(ps->psLoop) )
        {
            /* Input */
            Messages_Process(ps->psMessages);
            Keyboard_Process(ps->psKeys);
            
            /* Reason to Quit? */
            if( ps->psMessages->bWMQuit == true)
            {
                ps->psLoop->bRunning = false;
            }
            
            /* Updates */
            nRet = Strategy_ExecuteInput(ps);
            if( nRet == -1 )
            {
                ps->psLoop->bRunning = false;
                break;
            }
            else if( nRet > 0 )
            {
                printf("Error: Strategy Execute Input.\n");
                return 1;
            }
            
            nRet = Strategy_ExecuteUpdate(ps);
            if( nRet == -1 )
            {
                ps->psLoop->bRunning = false;
                break;
            }
            else if( nRet > 0 )
            {
                printf("Error: Strategy Execute Update.\n");
                return 1;
            }
        }
        
        Window_Clear(ps->psWindow);
        
        /* Render */
        nRet = Strategy_ExecuteRender(ps);
        if( nRet == -1 ) ps->psLoop->bRunning = false;
        else if( nRet > 0 )
        {
            printf("Error: Strategy Execute Render.\n");
            return 1;
        }
        
        Window_SwapBuffers(ps->psWindow);
        
        Loop_End(ps->psLoop);
    }
    
    
    return 0;
}