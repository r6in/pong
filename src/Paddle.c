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
#include "Paddle.h"
#include <stdio.h>
#include <string.h>
#include <BB.h>
#include <Resource.h>


void Paddle_Init(Paddle *psPaddle, bool bAI, Resource *psResource)
{
    if( psPaddle == NULL )
    {
        printf("Error: NULL Paddle.\n");
    }
    
    memset(psPaddle, 0, sizeof(Paddle));
    
    Vector_Init(psPaddle->psSize, 10.0, 50.0, 0.0);
    
    psPaddle->dSpeed = 0.3;/*1.6*/
    
    psPaddle->dDir = 0.0;
    
    psPaddle->bAI = bAI;
}

/* Must be array of 2 */
void Paddle_Reset(Paddle *psPaddles, Resource *psResource)
{
    Paddle *psPaddleA;
    Paddle *psPaddleB;
    BB *psWindowCanvas;
    BB psSizeBB[1];
    
    psPaddleA = &psPaddles[0];
    psPaddleB = &psPaddles[1];
    
    psWindowCanvas = psResource->psWindowCanvas;
    
    /* (Doesn't matter which paddle) */
    BB_Init(psSizeBB,
            0.0, 0.0, 0.0,
            psPaddles->psSize->dX, psPaddles->psSize->dY, 0.0);
    
    /* Paddle A */
    Vector_Init(psPaddleA->psPos,
                0.0,
                BB_FitCenterY(psWindowCanvas, psSizeBB),
                0.0);
    
    Vector_Init(psPaddleA->psVel, 0.0, 0.0, 0.0);
    
    /* Paddle B */
    Vector_Init(psPaddleB->psPos,
                BB_FromRight(psWindowCanvas, 10.0),
                BB_FitCenterY(psWindowCanvas, psSizeBB),
                0.0);
    
    Vector_Init(psPaddleB->psVel, 0.0, 0.0, 0.0);
}

void Paddle_Input(Paddle *psPaddle, Resource *psResource)
{
    BB psBallBB[1];
    BB psPaddleBB[1];
    
    BB_InitByVectors(   psBallBB,
                        psResource->psBall->psPos,
                        psResource->psBall->psSize);
    
    BB_InitByVectors(   psPaddleBB,
                        psPaddle->psPos,
                        psPaddle->psSize);
    
    psPaddle->dDir = 0.0;
    
    /* Human Control? */
    if( psPaddle->bAI == false )
    {
        /* Movement switches On? */
        if( psPaddle->bUp  == true )
        {
            psPaddle->dDir += 1.0;
        }
        if( psPaddle->bDown == true )
        {
            psPaddle->dDir -= 1.0;
        }
        
    }
    /* AI control */
    else
    {
        /* Above? */
        if( BB_TopPlane(psBallBB) > BB_TopPlane(psPaddleBB) )
        {
            psPaddle->dDir += 1.0;
        }
        /* Below? */
        else if( BB_BottomPlane(psBallBB) < BB_BottomPlane(psPaddleBB) )
        {
            psPaddle->dDir -= 1.0;
        }
    }
    
    psPaddle->bUp = false;
    psPaddle->bDown = false;
}


void Paddle_Update(Paddle *psPaddle, Resource *psResource)
{
    double dSpeed = 0.0;
    BB psCurrent[1];
    BB psProjected[1];
    BB *psPlayArea;
    
    
    psPlayArea = psResource->psPlayArea;
    
    
    /* Set Velocity */
    dSpeed = psPaddle->dSpeed * psResource->psLoop->dUpdateMs;
    
    psPaddle->psVel->dY = dSpeed * psPaddle->dDir;
    
    /* Bounding Box */
    BB_InitByVectors(psCurrent, psPaddle->psPos, psPaddle->psSize);
    BB_GetBB(psPaddle->psPos, psPaddle->psSize, psPaddle->psVel, psProjected);
    
    /* Out of Bounds? */
    if( BB_TopPlane(psProjected) > BB_TopPlane(psPlayArea) )
    {
        /* adjust velocity */
        psPaddle->psVel->dY = BB_TopPlane(psPlayArea) - BB_TopPlane(psCurrent);
    }
    else if( BB_BottomPlane(psProjected) < BB_BottomPlane(psPlayArea) )
    {
        /* adjust velocity */
        psPaddle->psVel->dY = BB_BottomPlane(psPlayArea) - BB_BottomPlane(psCurrent);
    }
    
    /* Update Pos from Vel */
    psPaddle->psPos->dX +=  psPaddle->psVel->dX;
    psPaddle->psPos->dY +=  psPaddle->psVel->dY;
    psPaddle->psPos->dZ +=  psPaddle->psVel->dZ;
    
    /* Zero Velocity */
    Vector_Zero(psPaddle->psVel);
}   
    

void Paddle_Render(Paddle *psPaddle, Resource *psResource)
{
    BB psBB[1];
    double pct;
    
    pct = psResource->psLoop->dAcuMs / psResource->psLoop->dUpdateMs;
    
    BB_Init(psBB,
            psPaddle->psPos->dX + (psPaddle->psVel->dX * pct),
            psPaddle->psPos->dY + (psPaddle->psVel->dY * pct),
            psPaddle->psPos->dZ + (psPaddle->psVel->dZ * pct),
            psPaddle->psSize->dX,
            psPaddle->psSize->dY,
            psPaddle->psSize->dZ);
    
    BB_Draw(psBB);
}
