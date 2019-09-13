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
#include "StrategyPong.h"
#include <stdio.h>
#include <stdbool.h>
#include <gl/gl.h>
#include <Strategy.h>
#include <Resource.h>
#include <Paddle.h>
#include <Ball.h>
#include <BB.h>
#include <Dash.h>
#include <Alphabet.h>
#include <Scores.h>

/* Customised Functions */
/* Set up the game */
StrategyCode Strategy_MainInput(Resource *psResource)
{
    BB *psWindowCanvas;
    BB *psBorders;
    BB *psPlayArea;
    Dash *psDash;
    Scores *psScores;
    
    psWindowCanvas = psResource->psWindowCanvas;
    psBorders = psResource->psBorders;
    psPlayArea = psResource->psPlayArea;
    psDash = psResource->psDash;
    psScores = psResource->psScores;
    
    
    /* (Compatibility) Init WindowCanvas BB */
    BB_Init(psWindowCanvas, 0.0, 0.0, 0.0,
        psResource->psWindow->dCanvasWidth,
        psResource->psWindow->dCanvasHeight,
        0.0);
    
    /* GAME */
    /* Static Background */
    psResource->nBordersSize =
        sizeof(psResource->psBorders) / sizeof(psResource->psBorders[0]);
    
    /* Border Bottom & Top */
    BB_Init(&psBorders[0],
            BB_LeftPlane(psWindowCanvas) + 10.0,
            BB_BottomPlane(psWindowCanvas),
            0.0,
            psWindowCanvas->psSize->dX - 20.0,
            10.0,
            0.0);
    
    BB_Init(&psBorders[1],
            BB_LeftPlane(&psBorders[0]),
            BB_FromTop(psWindowCanvas, 10.0),
            0.0,
            psBorders[0].psSize->dX,
            10.0,
            0.0);
    
    /* Dash Middle */
    Dash_InitY(psDash, &psBorders[0], &psBorders[1], 10.0);
    
    /* Play Area */
    BB_Init(psPlayArea,
            BB_LeftPlane(&psBorders[0]),
            BB_TopPlane(&psBorders[0]),
            0.0,
            BB_RightPlane(&psBorders[0]) - BB_LeftPlane(&psBorders[0]),
            BB_BottomPlane(&psBorders[1]) - BB_TopPlane(&psBorders[0]),
            0.0);
    
    /* Scores */
    Scores_Init(psScores, psResource); 
    
    /* Paddle */
    Paddle_Init(&psResource->psPaddle[0], false, psResource);
    Paddle_Init(&psResource->psPaddle[1],
                true,
                psResource);
    
    /* Ball */
    Ball_Init(psResource->psBall, psResource);
    
    return STRATEGY_OK;
}


StrategyCode Strategy_TitleInput(Resource *psResource)
{
    
    /* Space */
    if( psResource->psKeys->bKeySpace  == true )
    {
        /* Continue */
        return STRATEGY_OK;
    }
    
    return STRATEGY_REPEAT;
}


StrategyCode Strategy_TitleUpdate(Resource *psResource)
{return STRATEGY_REPEAT;}


StrategyCode Strategy_TitleRender(Resource *psResource)
{
    if(psResource->psWindow->nWidth == 800 &&
        psResource->psWindow->nHeight == 600)
    {
        Alphabet_SetSize(15.0);
        Alphabet_SetCursor(190.0, 358.5);
        Alphabet_String("PONG");
        
        Alphabet_SetSize(3.5);
        Alphabet_SetCursor(216.25, 295.5);
        Alphabet_String("PLAYER CONTROLS");
        
        Alphabet_SetCursor(265.25, 232.5);
        Alphabet_String("UP      W  ");
        
        Alphabet_SetCursor(265.25, 201.0);
        Alphabet_String("DOWN    S  ");
        
        Alphabet_SetCursor(265.25, 169.5);
        Alphabet_String("MENU    ESC");
        
        Alphabet_SetCursor(155.0, 106.5);
        Alphabet_String("PRESS SPACE TO START");
        
    }
    
    return STRATEGY_REPEAT;
}


StrategyCode Strategy_ResetRender(Resource *psResource)
{
    /* Reset scores */
    Scores_Reset(psResource->psScores);
    
    /* Reset Ball position */
    Ball_Reset(psResource->psBall, psResource);
    
    /* Reset Paddles position */
    Paddle_Reset(psResource->psPaddle, psResource);
    
    return STRATEGY_OK;
}


StrategyCode Strategy_GameInput(Resource *psResource)
{
    Paddle *psPaddle;
    Ball *psBall;
    
    psPaddle = psResource->psPaddle;
    psBall = psResource->psBall;
    
    /*ESC*/
    if( psResource->psKeys->bKeyEsc == true )
    {
        /* To Pause */
        return STRATEGY_OK;
    }
    
    if( psResource->psKeys->bKeyW == true )    psPaddle[0].bUp    = true;
    if( psResource->psKeys->bKeyS == true )    psPaddle[0].bDown  = true;
    if( psResource->psKeys->bKeyUp == true )   psPaddle[1].bUp    = true;
    if( psResource->psKeys->bKeyDown == true ) psPaddle[1].bDown  = true;
    
    Paddle_Input(&psPaddle[0], psResource);
    Paddle_Input(&psPaddle[1], psResource);
    Ball_Input(psBall, psResource);
    
    return STRATEGY_REPEAT;
}
StrategyCode Strategy_GameUpdate(Resource *psResource)
{
    Scores  *psScores;
    Paddle  *psPaddle;
    Ball    *psBall;
    
    psScores = psResource ->psScores;
    psPaddle = psResource->psPaddle;
    psBall = psResource->psBall;
    
    /* Check for 11 points */
    /* Player Wins */
    if( (psScores->pnDigits[0] == 1 && psScores->pnDigits[1] == 1) ){
        /* Change Strategy */
        psResource->psStrategy->eCurrentStrategy = STRATEGY_PLAYERW;
        
        return STRATEGY_REPEAT;
    }
    /* Computer Wins */
    if( (psScores->pnDigits[2] == 1 && psScores->pnDigits[3] == 1) ){
        /* Change Strategy */
        psResource->psStrategy->eCurrentStrategy = STRATEGY_COMPUTERW;
        
        return STRATEGY_REPEAT;
    }
    
    Paddle_Update(&psPaddle[0], psResource);
    Paddle_Update(&psPaddle[1], psResource);
    Scores_Update(psScores, psResource);
    Ball_Update(psBall, psResource);
    
    return STRATEGY_REPEAT;
}
StrategyCode Strategy_GameRender(Resource *psResource)
{
    Scores  *psScores;
    Paddle  *psPaddle;
    BB *psDashArea;
    
    psScores = psResource ->psScores;
    psPaddle = psResource->psPaddle;
    
    psDashArea = psResource->psDash->psArea;
    
    Dash_Render(psResource->psDash);
    BB_DrawBBs(psResource->psBorders, psResource->nBordersSize);
    Scores_Render(psScores, psResource);
    Paddle_Render(&psPaddle[0], psResource);
    Paddle_Render(&psPaddle[1], psResource);
    Ball_Render(psResource->psBall, psResource);
    
    /* Render PLAYER (In top left of screen) */
    if(psResource->psWindow->nWidth == 800 &&
        psResource->psWindow->nHeight == 600)
    {
        Alphabet_SetSize(3.5);
        Alphabet_SetCursor( 0.0,
                            BB_TopPlane(psDashArea) - 31.5 );
        Alphabet_String("PLAYER");
        
        Alphabet_SetCursor( 604.0,
                            BB_TopPlane(psDashArea) - 31.5 );
        Alphabet_String("COMPUTER");
    }
    
    return STRATEGY_REPEAT;
}


StrategyCode Strategy_PauseInput(Resource *psResource)
{
    if( psResource->psKeys->bKeyQ == true )
    {
        /* Quit */
        return STRATEGY_FAIL;
    }
    if( psResource->psKeys->bKeySpace == true )
    {
        /* Continue */
        return STRATEGY_OK;
    }
    if( psResource->psKeys->bKeyR == true )
    {
        /* Change Strategy */
        psResource->psStrategy->eCurrentStrategy = STRATEGY_TITLE;
        
        /* Continue */
        return STRATEGY_REPEAT;
    }
    
    return STRATEGY_REPEAT;
}


StrategyCode Strategy_PauseUpdate(Resource *psResource)
{
    return STRATEGY_REPEAT;
}


StrategyCode Strategy_PauseRender(Resource *psResource)
{
    /* Render game screen */
    Strategy_GameRender(psResource);
    
    /*
        Press Q to Quit
        
        Press R to Repeat
        
        Press Space to Continue
        6     6     3  8        = 23
    */
    if(psResource->psWindow->nWidth == 800 &&
        psResource->psWindow->nHeight == 600)
    {
        /* Black Square */
        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex2f(93.75f, 410.25f);
            glVertex2f(93.75f, 189.75f);
            glVertex2f(706.25f, 189.75f);
            glVertex2f(706.25f, 410.25f);
        glEnd();
        glColor3f(1.0f, 1.0f, 1.0f);
        
        /* Menu */
        Alphabet_SetSize(3.5);
        /*
            x_size = max chars 23 * 24.5 = 563.5
            y_size = 5 lines = 31.5 = 157.5
            x = 400 - (563.5 / 2) = 118.25
            y = 300 - (78.75 + 31.5 * 4) = 347.25
        */
        Alphabet_SetCursor(118.25, 347.25);
        Alphabet_String("Press R to Restart\n\n"
                        "Press Q to QUIT\n\n"
                        "Press Space to Continue");
    }
    
    return STRATEGY_REPEAT;
}

StrategyCode Strategy_PlayerWInput(Resource *psResource)
{
    if( psResource->psKeys->bKeyQ == true )
    {
        /* Quit */
        return STRATEGY_FAIL;
    }
    if( psResource->psKeys->bKeyR == true )
    {
        /* Change Strategy */
        psResource->psStrategy->eCurrentStrategy = STRATEGY_TITLE;
        
        /* Continue */
        return STRATEGY_REPEAT;
    }
    
    return STRATEGY_REPEAT;
}


StrategyCode Strategy_PlayerWUpdate(Resource *psResource)
{
    return STRATEGY_REPEAT;
}


StrategyCode Strategy_PlayerWRender(Resource *psResource)
{
    /* Render game screen */
    Strategy_GameRender(psResource);
    
    /*
        Press Q to Quit
        
        Press R to Repeat
        
    */
    if(psResource->psWindow->nWidth == 800 &&
        psResource->psWindow->nHeight == 600)
    {
        /* Black Square */
        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex2f(169.0f, 421.5f);
            glVertex2f(169.0f, 178.5f);
            glVertex2f(631.0f, 178.5f);
            glVertex2f(631.0f, 421.5f);
        glEnd();
        glColor3f(1.0f, 1.0f, 1.0f);
        
        /* Player Wins */
        Alphabet_SetSize(6.0);
        Alphabet_SetCursor(169.0, 336.0);
        Alphabet_String("PLAYER WINS");
        
        Alphabet_SetSize(3.5);
        Alphabet_SetCursor(179.5, 273.0);
        Alphabet_String("PRESS R TO RESTART\n\n"
                        "PRESS Q TO QUIT\n\n");
        
    }
    
    return STRATEGY_REPEAT;
}

StrategyCode Strategy_ComputerWInput(Resource *psResource)
{
    if( psResource->psKeys->bKeyQ == true )
    {
        /* Quit */
        return STRATEGY_FAIL;
    }
    if( psResource->psKeys->bKeyR == true )
    {
        /* Change Strategy */
        psResource->psStrategy->eCurrentStrategy = STRATEGY_TITLE;
        
        /* Continue */
        return STRATEGY_REPEAT;
    }
    
    return STRATEGY_REPEAT;
}


StrategyCode Strategy_ComputerWUpdate(Resource *psResource)
{
    return STRATEGY_REPEAT;
}


StrategyCode Strategy_ComputerWRender(Resource *psResource)
{
    /* Render game screen */
    Strategy_GameRender(psResource);
    
    /*
        Press Q to Quit
        
        Press R to Repeat
        
    */
    if(psResource->psWindow->nWidth == 800 &&
        psResource->psWindow->nHeight == 600)
    {
        /* Black Square */
        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin(GL_QUADS);
            glVertex2f(127.0f, 421.5f);
            glVertex2f(127.0f, 178.5f);
            glVertex2f(673.0f, 178.5f);
            glVertex2f(673.0f, 421.5f);
        glEnd();
        glColor3f(1.0f, 1.0f, 1.0f);
        
        /* Player Wins */
        Alphabet_SetSize(6.0);
        Alphabet_SetCursor(127.0, 336.0);
        Alphabet_String("COMPUTER WINS");
        
        Alphabet_SetSize(3.5);
        Alphabet_SetCursor(179.5, 273.0);
        Alphabet_String("PRESS R TO RESTART\n\n"
                        "PRESS Q TO QUIT\n\n");
        
    }
    
    return STRATEGY_REPEAT;
}

StrategyCode Strategy_End(Resource *psResource)
{
    psResource->psLoop->bRunning = false;
    
    return STRATEGY_END;
}
