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
#ifndef STRATEGYPONG_H_INCLUDED
#define STRATEGYPONG_H_INCLUDED

typedef enum StrategyCode StrategyCode;

typedef struct Resource Resource;


StrategyCode Strategy_MainInput(Resource *psResource);
StrategyCode Strategy_TitleInput(Resource *psResource);
StrategyCode Strategy_TitleUpdate(Resource *psResource);
StrategyCode Strategy_TitleRender(Resource *psResource);
StrategyCode Strategy_ResetRender(Resource *psResource);
StrategyCode Strategy_GameInput(Resource *psResource);
StrategyCode Strategy_GameUpdate(Resource *psResource);
StrategyCode Strategy_GameRender(Resource *psResource);
StrategyCode Strategy_PauseInput(Resource *psResource);
StrategyCode Strategy_PauseUpdate(Resource *psResource);
StrategyCode Strategy_PauseRender(Resource *psResource);
StrategyCode Strategy_PlayerWInput(Resource *psResource);
StrategyCode Strategy_PlayerWUpdate(Resource *psResource);
StrategyCode Strategy_PlayerWRender(Resource *psResource);
StrategyCode Strategy_ComputerWInput(Resource *psResource);
StrategyCode Strategy_ComputerWUpdate(Resource *psResource);
StrategyCode Strategy_ComputerWRender(Resource *psResource);
StrategyCode Strategy_End(Resource *psResource);


#endif