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
#include "Counter.h"


/*
    Returns 0 on success
*/
int Counter_Init(Counter *ps)
{

    memset(ps, 0, sizeof(Counter));
    
    int nResult = QueryPerformanceFrequency( ps->psFrequency );
    
    if( ! nResult ) return 1;
    
    /* Return success */
    return 0;
}


void Counter_StartRecord(Counter *ps)
{
    QueryPerformanceCounter( ps->psCountStart );
}


void  Counter_EndRecord(Counter *ps)
{
    QueryPerformanceCounter( ps->psCountEnd );
}


double Counter_ElapsedMs(Counter *ps)
{
    LARGE_INTEGER psElapsedCounter[1];
    
    psElapsedCounter->QuadPart =
        ps->psCountEnd->QuadPart -
        ps->psCountStart->QuadPart;
    
    psElapsedCounter->QuadPart *= 1000000;
    psElapsedCounter->QuadPart /= ps->psFrequency->QuadPart;
    
    *ps->psCountStart = *ps->psCountEnd;
    
    return psElapsedCounter->QuadPart / 1000.0;
}


void Counter_GetOffsetTime( Counter *ps,
                            double dOffsetMs,
                            LARGE_INTEGER *psTime)
{
    LARGE_INTEGER psIncrease[1];
    
    if( ps == NULL )
    {
        printf("Error: NULL Counter.\n");
        return;
    }
    if( psTime == NULL )
    {
        printf("Error: NULL Time in Counter.\n");
        return;
    }
    
    psIncrease->QuadPart =
        ps->psFrequency->QuadPart * (dOffsetMs / 1000.0);
    
    psTime->QuadPart = ps->psCountStart->QuadPart + psIncrease->QuadPart;
    
}

