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
#include "Ball.h"
#include <stdio.h>
#include <string.h>
#include <BB.h>
#include <Resource.h>
#include <math.h>
#include "Util.h"

#define BALL_PADDLE_SOUND "pb.wav"

void Ball_Init(  Ball *psBall, Resource *psResource)
{
    if( psBall == NULL )
    {
        printf("Error: NULL Ball.\n");
    }
    
    memset(psBall, 0, sizeof(Ball));
    
    Vector_Init(psBall->psSize, 10.0, 10.0, 0.0);
    
    /*psBall->dSpeed = 0.35;*/ /* Test */
    psBall->dSpeed = 0.45;
    
    /* srand call */
    srand(psResource->psLoop->psFull->psCountStart->QuadPart);
    
    Cooldown_Init(psBall->psCooldown, 1000.0, psResource);
}


void Ball_Reset(Ball *psBall, Resource *psResource)
{
    Vector_Init(psBall->psPos, 275.0, 275.0, 0.0);
    Vector_Init(psBall->psVel, 0.0, 0.0, 0.0);
    
    Ball_RandomPlaceBall(psBall, psResource);
}


void Ball_RandomPlaceBall(Ball *psBall, Resource *psResource)
{
    double dRand;
    double dRight;
    
    dRand = ((double) rand() / (RAND_MAX+1));
    
    dRight = dRand * 2.0;
    
    Ball_PlaceBall(psBall, (int)dRight, psResource);
    
}


void Ball_PlaceBall(Ball *psBall, bool bRightSide, Resource *psResource)
{
    double dRand;
    double dArc;
    BB *psPlayArea;
    
    psPlayArea = psResource->psPlayArea;
    
    dRand = ((double) rand() / (RAND_MAX+1));
    
    dArc = (dRand * Direction_Radians90()) - Direction_Radians45();
    
    Direction_Init(psBall->psDir, 0.0);
    
    if( bRightSide < 1 )
    {
        /* Left */
        psBall->psPos->dX = BB_FromLeft(psPlayArea, 200.0);
        psBall->psPos->dY = 275.0;
        /* Face Right */
        Direction_AntiClockwise(psBall->psDir, dArc);
    }
    else
    {
        /* Right */
        psBall->psPos->dX = BB_FromRight(psPlayArea, 200.0);
        psBall->psPos->dY = 275.0;
        /* Face Left */
        Direction_SetRadians(psBall->psDir, Direction_Radians180());
        Direction_AntiClockwise(psBall->psDir, dArc);
    }
    
    /* Wait a time */
    Cooldown_Start(psBall->psCooldown);
    
    psBall->bMovement = false;
}


void Ball_Input( Ball *psBall, Resource *psResource)
{
    /* Cooldown has finished? */
    if( Cooldown_Completed(psBall->psCooldown) == 0 )
    {
        /* Turn Movement On */
        psBall->bMovement = true;
    }
}


void Ball_Update(Ball *psBall, Resource *psResource)
{
    double dSpeed;
    BB *psPlayArea;
    BB psCurrent[1];
    BB psProjected[1];
    double dSepDst; /* separating distance */
    double dSepPct; /* separating distance vs original velocity */
    Direction *psDir;
    Paddle *psPadA;
    Paddle *psPadB;
    BB psPaddleBBa[1];
    BB psPaddleBBb[1];
    double dCenterDst; /* distance from center of paddle */
    double dCenterPct; /* distance from center of paddle vs paddle half height*/
    
    
    psPlayArea = psResource->psPlayArea;
    psDir = psBall->psDir;
    psPadA = &psResource->psPaddle[0];
    psPadB = &psResource->psPaddle[1];
    
    
    /* No Movement? */
    if( psBall->bMovement == false ) return;
    
    /* Set Velocity */
    dSpeed = psBall->dSpeed * psResource->psLoop->dUpdateMs;
    
    psBall->psVel->dX = dSpeed * cos(psBall->psDir->dRadians);
    psBall->psVel->dY = dSpeed * sin(psBall->psDir->dRadians);
    
    /* Bounding Box */
    BB_InitByVectors(psCurrent, psBall->psPos, psBall->psSize);
    BB_GetBB(psBall->psPos, psBall->psSize, psBall->psVel, psProjected);
    
    /* Bounding Box */
    BB_GetBB(psPadA->psPos, psPadA->psSize, psPadA->psVel, psPaddleBBa);
    BB_GetBB(psPadB->psPos, psPadB->psSize, psPadB->psVel, psPaddleBBb);
    
    /* Colliding */
    /* Paddle Left */
    if( BB_IsColliding(psPaddleBBa, psProjected) == true)
    {
        dCenterDst = BB_MidY(psCurrent) - BB_MidY(psPaddleBBa);
        dCenterPct =
            dCenterDst /
            (BB_HalfHeight(psPaddleBBa) + BB_HalfHeight(psCurrent));
        
        Direction_SetRadians(psDir, 0.0);
        Direction_AntiClockwise(psDir, Direction_Radians45()*dCenterPct);
        
        /* Calculate Separating Distance */
        dSepDst = BB_LeftPlane(psPlayArea) - BB_LeftPlane(psCurrent);
        /* Calculate Separating Proportion */
        dSepPct = dSepDst / psBall->psVel->dX;
        /* Adjust velocity to separate */
        psBall->psVel->dX = dSepDst;
        psBall->psVel->dY = psBall->psVel->dX * dSepPct;
        
        /* Play sound */
        Ball_PaddleSound();
        
    }
    /* Paddle Right */
    else if( BB_IsColliding(psPaddleBBb, psProjected) == true)
    {
        dCenterDst = BB_MidY(psCurrent) - BB_MidY(psPaddleBBb);
        dCenterPct =
            dCenterDst /
            (BB_HalfHeight(psPaddleBBb) + BB_HalfHeight(psCurrent));
        
        Direction_SetRadians(psDir, Direction_Radians180());
        Direction_Clockwise(psDir, Direction_Radians45()*dCenterPct);
        
        /* Calculate Separating Distance */
        dSepDst = BB_RightPlane(psPlayArea) - BB_RightPlane(psCurrent);
        /* Calculate Separating Proportion */
        dSepPct = dSepDst / psBall->psVel->dX;
        /* Adjust velocity to separate */
        psBall->psVel->dX = dSepDst;
        psBall->psVel->dY = psBall->psVel->dX * dSepPct;
        
        /* Play sound */
        Ball_PaddleSound();
        
    }
    /* Out of Bounds? */
    else if( BB_RightPlane(psProjected) > BB_RightPlane(psPlayArea) )
    {
        /* Out Right Side */
        Vector_Zero(psBall->psVel);
        
        Scores_PlusOneA(psResource->psScores);
        
        Ball_PlaceBall(psBall, false, psResource);
    }
    else if( BB_LeftPlane(psProjected) < BB_LeftPlane(psPlayArea) )
    {
        /* Out Left Side */
        Vector_Zero(psBall->psVel);
        
        Scores_PlusOneB(psResource->psScores);
        
        Ball_PlaceBall(psBall, true, psResource);
    }
    /* Collided Borders? */
    else if( BB_TopPlane(psProjected) > BB_TopPlane(psPlayArea) )
    {
        /* Top Border */
        /* Calculate Separating Distance */
        dSepDst = BB_TopPlane(psPlayArea) - BB_TopPlane(psCurrent);
        /* Calculate Separating Proportion */
        dSepPct = dSepDst / psBall->psVel->dY;
        /* Adjust velocity to separate */ 
        psBall->psVel->dX = psBall->psVel->dX * dSepPct;
        psBall->psVel->dY = dSepDst;
        
        /* Calculate Bounce */
        if( Direction_IsNorthEast(psDir) == true )
        {
            psDir->dRadians = Direction_Radians45() - psDir->dRadians + Direction_Radians315();
        }
        else
        {
            psDir->dRadians = Direction_Radians135() - psDir->dRadians + Direction_Radians225();
        }
        
    }
    else if( BB_BottomPlane(psProjected) < BB_BottomPlane(psPlayArea) )
    {
        /* Bottom Border */
        /* Calculate Separating Distance */
        dSepDst = BB_BottomPlane(psPlayArea) - BB_BottomPlane(psCurrent);
        /* Calculate Separating Proportion */
        dSepPct = dSepDst / psBall->psVel->dY;
        /* adjust velocity to separate */
        psBall->psVel->dX = psBall->psVel->dX * dSepPct;
        psBall->psVel->dY = dSepDst;
        
        /* Calculate Bounce */
        if( Direction_IsSouthWest(psDir) == true )
        {
            psDir->dRadians = Direction_Radians225() - psDir->dRadians + Direction_Radians135();
        }
        else
        {
            psDir->dRadians = Direction_Radians315() - psDir->dRadians + Direction_Radians45();
        }
        
    }
    
    /* Update Pos from Vel */
    psBall->psPos->dX +=  psBall->psVel->dX;
    psBall->psPos->dY +=  psBall->psVel->dY;
    psBall->psPos->dZ +=  psBall->psVel->dZ;
    
    /* Zero Velocity */
    Vector_Zero(psBall->psVel);
}

void Ball_PaddleSound( void ){

    PlaySound( (const char *)BALL_PADDLE_SOUND, NULL, SND_FILENAME | SND_ASYNC );
    
}

void Ball_Render(Ball *psBall, Resource *psResource)
{
    BB psBB[1];
    double pct;
    
    pct = psResource->psLoop->dAcuMs / psResource->psLoop->dUpdateMs;
    
    BB_Init(psBB,
            psBall->psPos->dX + (psBall->psVel->dX * pct),
            psBall->psPos->dY + (psBall->psVel->dY * pct),
            psBall->psPos->dZ + (psBall->psVel->dZ * pct),
            psBall->psSize->dX,
            psBall->psSize->dY,
            psBall->psSize->dZ);
    
    /*BB_Init(psBB,
            psBall->psPos->dX,
            psBall->psPos->dY,
            psBall->psPos->dZ,
            psBall->psSize->dX,
            psBall->psSize->dY,
            psBall->psSize->dZ);
    */
    BB_Draw(psBB);
}
