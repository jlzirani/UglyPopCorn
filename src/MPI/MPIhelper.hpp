/*
 This file is part of UglyPopCorn.
 
 UglyPopCorn is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 UglyPopCorn is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
 Copyright 2012 Cédric L && Jean-Luc Z
 */

#ifndef __MPIHELPER_HPP__
#define __MPIHELPER_HPP__
#include "../Game/player.hpp"
#include "../Game/card.hpp"
#include "MPIMessage.hpp"

CPlayer *getPlayer(int f_iID = 0, bool isHuman = true);

void syncProcess();

bool	receiveBool(int f_iFrom );
g_eCard receiveCard( int f_iFrom );
g_eMsg	receiveMsg( int f_iFrom );
uCardSet receiveCardSet( int f_iFrom );

void sendCard( int f_iDest, g_eCard f_eCard );
void sendMsg( int f_iDest, g_eMsg f_eMsg );
void sendCardSet( int f_iDest, uCardSet f_uCardSet );
void sendBool( int f_iDest, bool f_bBool );

char 	*receiveName( int f_iFrom );
void 	sendName( int f_iDest, char fc_strName[] );



#endif
