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
#include "Dash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>


void Dash_InitY(Dash *psDash,
                BB *psBottom,
                BB *psTop,
                double dSize)
{
    BB *psArea;
    BB *psBBs;
    double dY;
    bool bSolid = false;
    int i = 0;
    
    psArea = psDash->psArea;
    psBBs = psDash->psBBs;
    
    memset(psDash, 0, sizeof(Dash));
    
    /* Make Area */
    BB_Init(psArea,
            0.0,
            0.0,
            0.0,
            dSize,
            BB_BottomPlane(psTop) - BB_TopPlane(psBottom),
            0.0);
    
    psArea->psPos->dX = BB_FitCenterX(psBottom, psArea);
    psArea->psPos->dY = BB_TopPlane(psBottom);
    
    /* Set Dashes */
    psDash->nSize = sizeof(psDash->psBBs) / sizeof(psDash->psBBs[0]);
    
    dY = BB_BottomPlane(psArea);
    
    while(dY < BB_TopPlane(psArea) && i < psDash->nSize)
    {
        if( bSolid == true )
        {
            BB_Init(&psBBs[i],
                    BB_LeftPlane(psArea),
                    dY,
                    0.0,
                    dSize,
                    dSize,
                    0.0);
            
            bSolid = false;
            ++i;
        }
        else
        {
            bSolid = true;
        }
        
        dY += dSize;
    }
}


void Dash_Render(Dash *psDash)
{
    if(psDash == NULL) return;
    
    /* Test */
    BB_DrawBBs(psDash->psBBs, psDash->nSize);
}

