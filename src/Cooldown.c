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
#include "Cooldown.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <Resource.h>
#include <Counter.h>

void Cooldown_Init( Cooldown *psCooldown,
                    double dDuration,
                    Resource *psResource)
{
    if( psCooldown == NULL )
    {
        printf("Error: NULL Cooldown.\n");
        return;
    }
    if( psResource == NULL )
    {
        printf("Error: NULL Resource in Cooldown.\n");
        return;
    }
    
    
    memset(psCooldown, 0, sizeof(Cooldown));
    
    psCooldown->psResource = psResource;
    
    Cooldown_Duration(psCooldown, dDuration);
}


void Cooldown_Duration(Cooldown *psCooldown, double dDuration)
{
    if( psCooldown == NULL )
    {
        printf("Error: NULL Cooldown.\n");
        return;
    }
    
    psCooldown->dDuration = dDuration;
}


void Cooldown_Start(Cooldown *psCooldown)
{
    Resource *psResource;
    Counter *psCounter;
    
    if( psCooldown == NULL )
    {
        printf("Error: NULL Cooldown.\n");
        return;
    }
    
    psResource = psCooldown->psResource;
    
    if( psResource == NULL )
    {
        printf("Error: NULL Resource in Cooldown.\n");
        return;
    }
    
    psCounter = psResource->psLoop->psFull;
    
    if( psCounter == NULL )
    {
        printf("Error: NULL Counter in Cooldown.\n");
        return;
    }
    
    /* Set Completed time */
    Counter_GetOffsetTime(  psCounter,
                            psCooldown->dDuration,
                            psCooldown->psCompletedCounter);
    
}


int Cooldown_Completed(Cooldown *psCooldown)
{
    Resource *psResource;
    Counter *psCounter;
    
    if( psCooldown == NULL )
    {
        printf("Error: NULL Cooldown.\n");
        return 1;
    }
    
    psResource = psCooldown->psResource;
    
    if( psResource == NULL )
    {
        printf("Error: NULL Resource in Cooldown.\n");
        return 1;
    }
    
    psCounter = psResource->psLoop->psFull;
    
    if( psCounter == NULL )
    {
        printf("Error: NULL Counter in Cooldown.\n");
        return 1;
    }
    
    /* Enough time has passed? */
    if( psCounter->psCountStart->QuadPart >=
        psCooldown->psCompletedCounter->QuadPart )
    {
        
        return 0;
    }
    
    return -1;
}
