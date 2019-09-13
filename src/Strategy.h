/*
    Copyright 2015 David Ridpath <r6inhardt@hotmail.com>
 
    Licensed under GNU General Public License 3.0
    See COPYING.
   
    This file is part of Pong.
   
    Pong is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
   
    Pong is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with Pong.  If not, see <http://www.gnu.org/licenses/>.

    
    Strategy
    
    How to Use  10/07/14
    ==========
    
    Use functions like:-
        Strategy_ExecuteInput(psResource);
    Return type is -1 for stop running, 0 for success and 1> for error.
    
    Resource.h:
    Include Strategy.h header like so:
        #include <Strategy.h>
    Add a pointer and struct to Singleton like so:
        Strategy        psStrategy[1];
    
    Resource.c:
    Add the line:
        Strategy_Init(psResource->psStrategy);
    
    Strategy.h:
    Edit StrategyState to the State's needed.
    
    Strategy.c:
    Change #include <PongStrategy.h> to header declaring functions used.
    Change the defines below to match start and end StrategyState:-
        #define STRATEGY_ENTRY STRATEGY_MAIN
        #define STRATEGY_EXIT STRATEGY_END
    Strategy_Init:
    Edit psStrategyTransitions to transition rules.
    Edit psStrategyFunctions to strategy functions.
    
    PongStrategy.h:
    include lines:-
        typedef enum StrategyCode StrategyCode;
        typedef struct Resource Resource;
    Ensure strategy functions return StrategyCode and the parameter is
    Resource *psResource (for singleton access).
    
    PongStrategy.c:
    include headers:-
        #include <Strategy.h>
        #include <Resource.h>
*/
#ifndef STRATEGY_H_INCLUDED
#define STRATEGY_H_INCLUDED


typedef enum StrategyState          StrategyState;
typedef enum StrategyCode           StrategyCode;

typedef struct StrategyFunctions    StrategyFunctions;
typedef struct StrategyTransition   StrategyTransition;
typedef struct Strategy             Strategy;
typedef struct Resource             Resource;

enum StrategyState
{
    STRATEGY_MAIN,
    STRATEGY_TITLE,
    STRATEGY_RESET,
    STRATEGY_GAME,
    STRATEGY_PAUSE,
    STRATEGY_PLAYERW,
    STRATEGY_COMPUTERW,
    STRATEGY_END
};
enum StrategyCode
{
    STRATEGY_OK      = 0,
    STRATEGY_FAIL    = 1,
    STRATEGY_REPEAT  = 2
};

struct StrategyFunctions
{
    StrategyCode(*pfnInput)(Resource *psResource);
    StrategyCode(*pfnUpdate)(Resource *psResource);
    StrategyCode(*pfnRender)(Resource *psResource);
};
struct StrategyTransition
{
    int eSrc;
    int eCode;
    int eDst;
};
struct Strategy
{
    StrategyState eCurrentStrategy;
    StrategyCode eCode;
    StrategyFunctions *psFunctions;
    int nStrategyFunctionsSize;
    StrategyTransition *psStrategyTransitions;
    int nStrategyTransitionSize;
};


void Strategy_Init(Strategy *psStrategy);


StrategyState LookupStrategy(Strategy *psStrategy);

/*
    Returns:
    -1  Exit state
    0   Success in transition
    0 > Error
*/
int Strategy_ExecuteInput(Resource *psResource);

int Strategy_ExecuteUpdate(Resource *psResource);

int Strategy_ExecuteRender(Resource *psResource);

#endif