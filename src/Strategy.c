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
#include "Strategy.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <Resource.h>
#include <StrategyPong.h>

#define STRATEGY_ENTRY STRATEGY_MAIN
#define STRATEGY_EXIT STRATEGY_END

/* Declared */
/*
    nFunction   0 for pfnInput
                1 for pfnUpdate
                2 for pfnRender
*/
int Execute(Resource *psResource, int nFunction);

/* Defined */
void Strategy_Init(Strategy *psStrategy)
{
    int i;
    StrategyTransition psStrategyTransitions[] =
    {
        {STRATEGY_MAIN, STRATEGY_OK, STRATEGY_TITLE},
        {STRATEGY_MAIN, STRATEGY_FAIL, STRATEGY_EXIT},
        {STRATEGY_MAIN, STRATEGY_REPEAT, STRATEGY_MAIN},
        
        {STRATEGY_TITLE, STRATEGY_OK, STRATEGY_RESET},
        {STRATEGY_TITLE, STRATEGY_FAIL, STRATEGY_EXIT},
        {STRATEGY_TITLE, STRATEGY_REPEAT, STRATEGY_TITLE},
        
        {STRATEGY_RESET, STRATEGY_OK, STRATEGY_GAME},
        {STRATEGY_RESET, STRATEGY_FAIL, STRATEGY_EXIT},
        {STRATEGY_RESET, STRATEGY_REPEAT, STRATEGY_RESET},
        
        {STRATEGY_GAME, STRATEGY_OK, STRATEGY_PAUSE},
        {STRATEGY_GAME, STRATEGY_FAIL, STRATEGY_EXIT},
        {STRATEGY_GAME, STRATEGY_REPEAT, STRATEGY_GAME},
        
        {STRATEGY_PAUSE, STRATEGY_OK, STRATEGY_GAME},
        {STRATEGY_PAUSE, STRATEGY_FAIL, STRATEGY_EXIT},
        {STRATEGY_PAUSE, STRATEGY_REPEAT, STRATEGY_PAUSE},
        
        {STRATEGY_PLAYERW, STRATEGY_OK, STRATEGY_GAME},
        {STRATEGY_PLAYERW, STRATEGY_FAIL, STRATEGY_EXIT},
        {STRATEGY_PLAYERW, STRATEGY_REPEAT, STRATEGY_PLAYERW},
        
        {STRATEGY_COMPUTERW, STRATEGY_OK, STRATEGY_GAME},
        {STRATEGY_COMPUTERW, STRATEGY_FAIL, STRATEGY_EXIT},
        {STRATEGY_COMPUTERW, STRATEGY_REPEAT, STRATEGY_COMPUTERW},
        
    };
    StrategyFunctions psStrategyFunctions[] =
    {
        {Strategy_MainInput, 0, 0},
        {Strategy_TitleInput, Strategy_TitleUpdate, Strategy_TitleRender},
        {0, 0, Strategy_ResetRender},
        {Strategy_GameInput,    Strategy_GameUpdate,    Strategy_GameRender},
        {Strategy_PauseInput, Strategy_PauseUpdate, Strategy_PauseRender},
        {Strategy_PlayerWInput, Strategy_PlayerWUpdate, Strategy_PlayerWRender},
        {Strategy_ComputerWInput, Strategy_ComputerWUpdate, Strategy_ComputerWRender},
        {Strategy_End, 0, 0}
    };
    
    if( psStrategy == NULL ) return;
    
    memset(psStrategy, 0, sizeof(Strategy));
    
    psStrategy->eCurrentStrategy = STRATEGY_ENTRY;
    
    /* Store array sizes */
    psStrategy->nStrategyTransitionSize =
        sizeof(psStrategyTransitions) / sizeof(StrategyTransition);
    
    psStrategy->nStrategyFunctionsSize =
        sizeof(psStrategyFunctions) / sizeof(StrategyFunctions);
    
    /* memory allocate */
    psStrategy->psStrategyTransitions =
        calloc( psStrategy->nStrategyTransitionSize, sizeof(StrategyTransition) );
    
    psStrategy->psFunctions =
        calloc( psStrategy->nStrategyFunctionsSize, sizeof(StrategyFunctions) );
    
    /* Clone Contents */
    for(i = 0; i < psStrategy->nStrategyTransitionSize; ++i)
    {
    
        psStrategy->psStrategyTransitions[i].eSrc =
            psStrategyTransitions[i].eSrc;
        psStrategy->psStrategyTransitions[i].eCode =
            psStrategyTransitions[i].eCode;
        psStrategy->psStrategyTransitions[i].eDst =
            psStrategyTransitions[i].eDst;
    }
    for(i = 0; i < psStrategy->nStrategyFunctionsSize; ++i)
    {
        psStrategy->psFunctions[i].pfnInput = psStrategyFunctions[i].pfnInput;
        psStrategy->psFunctions[i].pfnUpdate = psStrategyFunctions[i].pfnUpdate;
        psStrategy->psFunctions[i].pfnRender = psStrategyFunctions[i].pfnRender;        
    }
    
}


int Strategy_ExecuteInput(Resource *psResource)
{
    return Execute(psResource, 0);
}
int Strategy_ExecuteUpdate(Resource *psResource)
{
    return Execute(psResource, 1);
}
int Strategy_ExecuteRender(Resource *psResource)
{
    return Execute(psResource, 2);
}


int Execute(Resource *psResource, int nFunction)
{
    Strategy *psStrategy;
    StrategyCode(*pfnFunction)(Resource *psResource);
    
    if( psResource == NULL ) return 1;
    
    psStrategy = psResource->psStrategy;
    
    if( psStrategy == NULL ) return 1;
    
    switch(nFunction)
    {
    case 0:
        pfnFunction =
            psStrategy->psFunctions[psStrategy->eCurrentStrategy].pfnInput;
        break;
    case 1:
        pfnFunction =
            psStrategy->psFunctions[psStrategy->eCurrentStrategy].pfnUpdate;
        break;
    case 2:
        pfnFunction =
            psStrategy->psFunctions[psStrategy->eCurrentStrategy].pfnRender;
        break;
    default:
        /* Error */
        printf("Unexpected nFunction.\n");
        return 1;
        break;
    }
    
    /* Is function NULL? */
    if( pfnFunction == NULL ) return 0;
    
    psStrategy->eCode = pfnFunction(psResource);
    
    if( psStrategy->eCurrentStrategy == STRATEGY_EXIT ) return -1;
    
    psStrategy->eCurrentStrategy = LookupStrategy(psStrategy);
    
    return 0;
}


StrategyState LookupStrategy(Strategy *psStrategy)
{
    StrategyState eCurrentStrategy;
    StrategyCode eCode;
    StrategyTransition *psStrategyTransitions;
    int nSize;
    int i;
    StrategyTransition *psTransition;
    
    eCurrentStrategy        = psStrategy->eCurrentStrategy;
    eCode                   = psStrategy->eCode;
    psStrategyTransitions   = psStrategy->psStrategyTransitions;
    nSize                   = psStrategy->nStrategyTransitionSize;
    
    for(i = 0; i < nSize; ++i)
    {
        /* Cast to each object */
        psTransition = psStrategyTransitions + i;
        
        if( eCurrentStrategy == psTransition->eSrc &&
            eCode == psTransition->eCode)
        {
            return psTransition->eDst;
        }
    }
    
    return STRATEGY_EXIT;
}

