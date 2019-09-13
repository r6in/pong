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
#include "Loop.h"
#include "Keyboard.h"
#include "Messages.h"


/* Declarations */
bool Loop_Continue(Loop *ps);


/*
    Returns 0 on success
*/
int Loop_Init(Loop *ps, Messages *psMessages, Keyboard *psKeys)
{
    int nRet;
    
    memset(ps, 0, sizeof(Loop));
    
    ps->psMessages = psMessages;
    ps->psKeys = psKeys;
    
    nRet = Counter_Init(ps->psFull);
    if( nRet )
    {
        return 1;
    }
    
    nRet = Counter_Init(ps->psNoYield);
    if( nRet )
    {
        return 1;
    }
    
    ps->nMaxUpdates = 10; /* Frame Skip */
    ps->dTargetMs = 16.0;
    ps->dUpdateMs = 8.0;
    ps->bRunning = true;
    
    return 0;
}


/*
    Returns true to continue looping.
    
    Note: parameter for while loop.
*/
bool Loop_Start(Loop *ps)
{
    
    /* Quit? */
    if( ps->bRunning == false )
    {
        return false;
    }
    
    /* Start Full loop Timer` */
    Counter_StartRecord(ps->psFull);
    
    /* Start NoYield Timer */
    Counter_StartRecord(ps->psNoYield);
    
    /* Set Frame Skip to Zero */
    ps->i = 0;
    
    /* return continue */
    return true;
}


/*
    Returns true if more updates available
    Returns false when finished
    Parameter for while loop.
    
    Note:
    Accumulator is decreased on successful Loop_Update
    
    Accumulator is increased at Loop_End by Full timer
    
    Or Reset to zero if Max Updates reached.
*/
bool Loop_Updates(Loop *ps)
{
    
    /* Not enough Accumulated Ms? */
    if( ps->dAcuMs < ps->dUpdateMs )
    {
        /* Stop Updates */
        return false;
    }
    
    /* Too many frame skips? */
    if( ps->i >= ps->nMaxUpdates )
    {
        /* Stop Updates */
        return false;
    }
    
    /* Decrease Accumulated */
    ps->dAcuMs -= ps->dUpdateMs;
    
    /* Increment Frame Skip` */
    ++ps->i;
    
    return true;
}


void Loop_End(Loop *ps)
{
    double dDeltaMs;
    
    
    /* Stop NoYield Timer */
    Counter_EndRecord(ps->psNoYield);
    
    /* Elapsed NoYield Ms */
    ps->dNoYieldMs = Counter_ElapsedMs( ps->psNoYield );
    
    /* Yield left */
    dDeltaMs = ps->dTargetMs - ps->dNoYieldMs;
    
    /* Do Yield */
    if( dDeltaMs > 0.0 )
    Sleep(dDeltaMs);
    
    /* Stop Full Timer */
    Counter_EndRecord(ps->psFull);
    
    /* Elapsed Full Ms */
    ps->dFullMs = Counter_ElapsedMs( ps->psFull );
    
    /* Max Updates reached */
    if( ps->i == ps->nMaxUpdates )
    {
        /* Reset Accumulated */
        ps->dAcuMs = 0.0;
    }
    else
    {
        /* Accumulate Full Elapsed */
        ps->dAcuMs += ps->dFullMs;
    }
    
}


