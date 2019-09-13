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
#include "Window.h"
#include "BB.h"


#define FWG 1.0f, 1.0f, 1.0f, 1.0f /* White */
#define BKG 0.0f, 0.0f, 0.0f, 1.0f /* Black */


/* Declarations */
LRESULT CALLBACK WndProc(HWND hWND, UINT nMsg, WPARAM wParam, LPARAM lParam);


/* Function Definitions */
void Window_Init(Window    *ps,
                 HINSTANCE hInstance,
                 char      *aClass,
                 char      *aTitle,
                 int       nWidth,
                 int       nHeight)
{
    
    assert( hInstance );
    assert( aClass );
    assert( aTitle );
    assert( nWidth > 0 );
    assert( nHeight > 0 );
    
    memset(ps, 0, sizeof(Window) );
    
    ps->hInstance = hInstance;
    ps->aClass = aClass;
    ps->aTitle = aTitle;
    ps->nWidth = nWidth;
    ps->nHeight = nHeight;
}

int Window_ShowWindow(Window *ps)
{
    WNDCLASSEX  psWindowClassEx[1];
    PIXELFORMATDESCRIPTOR psPixelFormatDescriptor[1];
    RECT psWindowCanvas[1];
    int nPixelFormat;
    int nError;
    DWORD hFlags;
    DWORD hExFlags;
    
    /* Specify window class */
    memset(psWindowClassEx, 0, sizeof(WNDCLASSEX) );
    psWindowClassEx->cbSize = sizeof( WNDCLASSEX );
    psWindowClassEx->style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    psWindowClassEx->lpfnWndProc = WndProc;
    psWindowClassEx->cbClsExtra = 0;
    psWindowClassEx->cbWndExtra = 0;
    psWindowClassEx->hInstance = ps->hInstance;
    psWindowClassEx->hIcon = LoadIcon( NULL, IDI_APPLICATION );
    psWindowClassEx->hCursor = LoadCursor( NULL, IDC_ARROW );
    psWindowClassEx->hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    psWindowClassEx->lpszMenuName = NULL;
    psWindowClassEx->lpszClassName = ps->aClass;
    psWindowClassEx->hIconSm = 0;
    
    /* Register window class. Failed? */
    if( ! RegisterClassEx( psWindowClassEx ) )
    {
        /* Fail */
        return 1;
    }
    
    /* Select Flags */
    hFlags   = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
    hExFlags = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
    
    /* Create RECT from width and height */
    psWindowCanvas->left = 0;
    psWindowCanvas->right = ps->nWidth;
    psWindowCanvas->top = 0;
    psWindowCanvas->bottom = ps->nHeight;
    
    /* Adjust canvas to fit width & height */
    AdjustWindowRectEx( psWindowCanvas, hFlags, 0, hExFlags );
    
    /* CreateWindowEx */
    ps->hWND = CreateWindowEx(  hExFlags,
                                ps->aClass,
                                ps->aTitle,
                                hFlags | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
                                CW_USEDEFAULT,
                                CW_USEDEFAULT,
                                psWindowCanvas->right - psWindowCanvas->left,
                                psWindowCanvas->bottom - psWindowCanvas->top,
                                0,
                                0,
                                0,
                                NULL);
    
    if( ! ps->hWND )
    {
        /* Fail */
        /* Clean up and return*/
        UnregisterClass( ps->aClass, ps->hInstance );
        return 1;
    }
    
    ps->hDC = GetDC(ps->hWND);
    if( ps->hDC == NULL )
	{
		/* Fail */
        return 1;
	}
    
    memset(psPixelFormatDescriptor, 0, sizeof(PIXELFORMATDESCRIPTOR) );
    psPixelFormatDescriptor->nSize = sizeof(PIXELFORMATDESCRIPTOR);
	psPixelFormatDescriptor->nVersion = 1;
    psPixelFormatDescriptor->dwFlags = PFD_DRAW_TO_WINDOW |	
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER;
    psPixelFormatDescriptor->iPixelType = PFD_TYPE_RGBA;
    psPixelFormatDescriptor->cColorBits = 32;
    psPixelFormatDescriptor->cRedBits = 0;
    psPixelFormatDescriptor->cRedShift = 0;
    psPixelFormatDescriptor->cGreenBits = 0;
    psPixelFormatDescriptor->cGreenShift = 0;
    psPixelFormatDescriptor->cBlueBits = 0;
    psPixelFormatDescriptor->cBlueShift = 0;
	psPixelFormatDescriptor->cAlphaBits = 0;
    psPixelFormatDescriptor->cAlphaShift = 0;
    psPixelFormatDescriptor->cAccumBits = 0;
    psPixelFormatDescriptor->cAccumRedBits = 0;
    psPixelFormatDescriptor->cAccumGreenBits = 0;
    psPixelFormatDescriptor->cAccumBlueBits = 0;
    psPixelFormatDescriptor->cAccumAlphaBits = 0;
    psPixelFormatDescriptor->cDepthBits = 32;
    psPixelFormatDescriptor->cStencilBits = 0;
    psPixelFormatDescriptor->cAuxBuffers = 0;
    psPixelFormatDescriptor->iLayerType = PFD_MAIN_PLANE;
    psPixelFormatDescriptor->bReserved = 0;
    psPixelFormatDescriptor->dwLayerMask = 0;
    psPixelFormatDescriptor->dwVisibleMask = 0;
    psPixelFormatDescriptor->dwDamageMask = 0;
    
    nPixelFormat = ChoosePixelFormat(   ps->hDC,
                                        psPixelFormatDescriptor);
    if( nPixelFormat == 0 )
	{
		/* Fail */
        return 1;
	}
    
    nError = SetPixelFormat(ps->hDC,
                            nPixelFormat,
                            psPixelFormatDescriptor);
    if( nError == 0 )
	{
		/* Fail */
        return 1;
	}
    
    ps->hGLRC = wglCreateContext(ps->hDC);
    if( ps->hGLRC == 0 )
	{
		/* Fail */
        return 1;
	}
    
    nError = wglMakeCurrent(ps->hDC,
                            ps->hGLRC);
	if( nError == 0 )
	{
		/* Fail */
        return 1;
	}
    
    
    /* Get actual canvas drawing area */
    GetClientRect(ps->hWND, psWindowCanvas);
    
    /* Canvas area as width and height */
    ps->dCanvasWidth = psWindowCanvas->right;
    ps->dCanvasHeight = psWindowCanvas->bottom;
    
    
    /* Show the window */
    ShowWindow( ps->hWND, SW_SHOWNORMAL );
    
    return 0;
}


LRESULT CALLBACK WndProc(HWND hWND, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
    
    switch(nMsg)
    {
        case WM_CLOSE:
            PostQuitMessage(WM_QUIT);
        break;
        default:
            return DefWindowProc(hWND, nMsg, wParam, lParam);
        break;
    }
    return 0; /* processed */
}


int Window_ResizeScene2D(Window *ps)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0,
            ps->dCanvasWidth,
            0.0,
            ps->dCanvasHeight,
            -1.0,
            1.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    glClearColor(BKG); /* See define */
    
    glColor4f(FWG); /* See define */
    
    /* return success */
    return 0;
}


void Window_Clear(Window *ps)
{
    BB psCanvas[1];
    
    
    BB_Init(psCanvas, 0.0, 0.0, 0.0, ps->dCanvasWidth, ps->dCanvasHeight, 0.0);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glColor4f(BKG);
    BB_Draw(psCanvas);
    glColor4f(FWG);
}


void Window_SwapBuffers(Window *ps)
{
    SwapBuffers(ps->hDC);
}

