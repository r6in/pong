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
#include "BB.h"
#include <string.h>
#include <stdio.h>
#include <gl/gl.h>

void BB_Init(   BB *psBB,
                double x,
                double y,
                double z,
                double width,
                double height,
                double depth)
{
    
    if( psBB == NULL ) return;
    memset(psBB, 0, sizeof(BB));
    
    Vector_Init(psBB->psPos, x, y, z);
    
    Vector_Init(psBB->psSize, width, height, depth);
}


void BB_InitByVectors(BB *psBB, const Vector *psPos, const Vector *psSize)
{
    if( psPos == NULL ) return;
    if( psSize == NULL ) return;
    
    BB_Init(psBB, psPos->dX, psPos->dY, psPos->dZ,
            psSize->dX, psSize->dY, psSize->dZ);
}


int BB_GetBB(   const Vector *psPos,
                const Vector *psSize,
                const Vector *psVel,
                BB *psDst)
{
    
    if( psPos == NULL )
    {
        printf("Error: Null Pos in GetBB.\n");
        return 1;
    }
    if( psSize == NULL )
    {
        printf("Error: Null Size in GetBB.\n");
        return 1;
    }
    if( psDst == NULL )
    {
        printf("Error: Null Dst in GetBB.\n");
        return 1;
    }
    
    if( psVel == NULL )
    {
        printf("Error: Null Vel in GetBB.\n");
        return 1;
    }
    
    BB_Init(psDst,
            psPos->dX + psVel->dX,
            psPos->dY + psVel->dY,
            psPos->dZ + psVel->dZ,
            psSize->dX,
            psSize->dY,
            psSize->dZ);
    
    return 0;
}


int BB_Clone(const BB *psSrc, BB *psDst)
{
    if( psSrc == NULL ) return 1;
    if( psDst == NULL ) return 1;
    
    Vector_InitByVector(psDst->psPos, psSrc->psPos);

    Vector_InitByVector(psDst->psSize, psSrc->psSize);
    
    return 0;
}


double BB_LeftPlane(BB *psBB)
{
    
    if(psBB == NULL) return 0;
    return psBB->psPos->dX;
}


double BB_RightPlane(BB *psBB)
{
    
    if(psBB == NULL) return 0;
    return psBB->psPos->dX + psBB->psSize->dX;
}


double BB_BottomPlane(BB *psBB)
{
    
    if(psBB == NULL) return 0;
    return psBB->psPos->dY;
}


double BB_TopPlane(BB *psBB)
{
    
    if(psBB == NULL) return 0;
    return psBB->psPos->dY + psBB->psSize->dY;
}


double BB_FromTop(BB *psBB, double y)
{
    if(psBB == NULL) return 0;
    return BB_TopPlane(psBB) - y;
}


double BB_FromRight(BB *psBB, double x)
{
    if(psBB == NULL) return 0;
    return BB_RightPlane(psBB) - x;
}


double BB_FromBottom(BB *psBB, double y)
{
    if(psBB == NULL) return 0;
    return BB_BottomPlane(psBB) + y;
}


double BB_FromLeft(BB *psBB, double x)
{
    if(psBB == NULL) return 0;
    return BB_LeftPlane(psBB) + x;
}


double BB_FitCenterX(BB *psBB, BB *psFit)
{
    if(psBB == NULL) return 0;
    if(psFit == NULL) return 0;
    if(psBB->psSize->dX < psFit->psSize->dX) return 0;
    return (psBB->psSize->dX - psFit->psSize->dX) / 2.0;
}


double BB_FitCenterY(BB *psBB, BB *psFit)
{
    if(psBB == NULL) return 0;
    if(psFit == NULL) return 0;
    if(psBB->psSize->dY < psFit->psSize->dY) return 0;
    return (psBB->psSize->dY - psFit->psSize->dY) / 2.0;
}


void BB_Print(BB *psBB)
{

    if(psBB == NULL) return;
    printf( "Bounding Box x = %f, y = %f, width = %f, height = %f\n",
            psBB->psPos->dX,
            psBB->psPos->dY,
            psBB->psSize->dX,
            psBB->psSize->dY);
}


void BB_Draw(BB *psBB)
{
    
    if(psBB == NULL) return;
    
    glBegin(GL_QUADS);
    
    glTexCoord2f(0.0f,1.0f);
    glVertex2f(BB_LeftPlane(psBB), BB_TopPlane(psBB));
    
    glTexCoord2f(0.0f,0.0f);
    glVertex2f(BB_LeftPlane(psBB), BB_BottomPlane(psBB));
    
    glTexCoord2f(1.0f,0.0f);
    glVertex2f(BB_RightPlane(psBB), BB_BottomPlane(psBB));
    
    glTexCoord2f(1.0f,1.0f);
    glVertex2f(BB_RightPlane(psBB), BB_TopPlane(psBB));
    glEnd();
}


void BB_DrawBBs(BB *psBBs, int nSize)
{
    int i;
    
    for( i = 0; i < nSize; i++ )
    {
        BB_Draw(psBBs+i);
    }
}


bool BB_IsColliding(BB *psA, BB *psB)
{
    /* A left past B right */
    if( BB_LeftPlane(psA) > BB_RightPlane(psB) ) return false;
    
    /* A right before B left */
    if( BB_RightPlane(psA) < BB_LeftPlane(psB) ) return false;
    
    /* A bottom past B top */
    if( BB_BottomPlane(psA) > BB_TopPlane(psB) ) return false;
    
    /* A top before B bottom */
    if( BB_TopPlane(psA) < BB_BottomPlane(psB) ) return false;
    
    return true;
}


double BB_MidX(BB *psBB)
{
    return psBB->psPos->dX + (psBB->psSize->dX / 2.0);
}


double BB_MidY(BB *psBB)
{
    return psBB->psPos->dY + (psBB->psSize->dY / 2.0);
}


double BB_HalfWidth(BB *psBB)
{
    return psBB->psSize->dX / 2.0;
}


double BB_HalfHeight(BB *psBB)
{
    return psBB->psSize->dY / 2.0;
}

