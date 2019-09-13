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
#include "Scores.h"
#include <Resource.h>
#include <BB.h>
#include <Dash.h>
#include <Alphabet.h>

void Scores_Init(Scores *psScores, Resource *psResource)
{
    BB *psDashArea;
    
    psDashArea = psResource->psDash->psArea;
    
    if(psResource->psWindow->nWidth == 800 &&
        psResource->psWindow->nHeight == 600)
    {
        /* A Tens */
        Vector_Init(&psScores->psPos[0],
                    BB_LeftPlane(psDashArea) - 49.0,
                    BB_TopPlane(psDashArea) - 31.5,
                    0.0);
        /* A Ones */
        Vector_Init(&psScores->psPos[1],
                    BB_LeftPlane(psDashArea) - 24.5,
                    BB_TopPlane(psDashArea) - 31.5,
                    0.0);
        /* B Tens */
        Vector_Init(&psScores->psPos[2],
                    BB_RightPlane(psDashArea),
                    BB_TopPlane(psDashArea) - 31.5,
                    0.0);
        /* B Ones */
        Vector_Init(&psScores->psPos[3],
                    BB_RightPlane(psDashArea) + 24.5,
                    BB_TopPlane(psDashArea) - 31.5,
                    0.0);
        
        psScores->dSize = 3.5;
        
    }
}


void Scores_Update(Scores *psScores, Resource *psResource)
{}


void Scores_Render(Scores *psScores, Resource *psResource)
{
    Vector *psPos;
    int i;
    
    psPos = psScores->psPos;
    
    for( i = 0; i < 4; ++i)
    {
        Alphabet_SetSize(psScores->dSize);
        Alphabet_SetCursor(psPos[i].dX, psPos[i].dY);
        switch( psScores->pnDigits[i] )
        {
        case 0:
            Alphabet_Char('0');
            break;
        case 1:
            Alphabet_Char('1');
            break;
        case 2:
            Alphabet_Char('2');
            break;
        case 3:
            Alphabet_Char('3');
            break;
        case 4:
            Alphabet_Char('4');
            break;
        case 5:
            Alphabet_Char('5');
            break;
        case 6:
            Alphabet_Char('6');
            break;
        case 7:
            Alphabet_Char('7');
            break;
        case 8:
            Alphabet_Char('8');
            break;
        case 9:
            Alphabet_Char('9');
            break;
        }
    }
}


void Scores_PlusOneA(Scores *psScores)
{
    int *pnDigits;
    
    pnDigits = psScores->pnDigits;
    
    if( pnDigits[1] == 9 )
    {
        pnDigits[1] = 0;
        ++pnDigits[0];
    }
    else
    {
        ++pnDigits[1];
    }
    
    if( pnDigits[0] > 9 )
    {
        pnDigits[0] = 0;
        pnDigits[1] = 0;
    }
}


void Scores_PlusOneB(Scores *psScores)
{
    int *pnDigits;
    
    pnDigits = psScores->pnDigits;
    
    if( pnDigits[3] == 9 )
    {
        pnDigits[3] = 0;
        ++pnDigits[2];
    }
    else
    {
        ++pnDigits[3];
    }
    
    if( pnDigits[2] > 9 )
    {
        pnDigits[2] = 0;
        pnDigits[3] = 0;
    }
}


void Scores_Reset(Scores *psScores)
{
    memset(psScores->pnDigits, 0, 4 * sizeof(int));
}

