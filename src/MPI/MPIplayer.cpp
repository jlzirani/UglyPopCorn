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

#include "MPIplayer.hpp"
#include "MPIMessage.hpp"
#include "MPIhelper.hpp"

MPIPlayer::MPIPlayer(int f_iId, const char *fc_strName) : CPlayer(f_iId, fc_strName) 
{
	sendMsg(getId(), GETNAME);
	char *newName = receiveName(getId());
	setName(newName);
	delete[] newName;
}

void MPIPlayer::notifyPlayerPlays( bool f_bSuggestion, char *fc_strPlayer, uCardSet f_uCardSet )
{
	if(f_bSuggestion)
		sendMsg(getId(), SUGGESTION);
	else
		sendMsg(getId(), ACCUSATION);	
	sendName(getId(), fc_strPlayer );
	sendCardSet(getId(), f_uCardSet );
}

void MPIPlayer::add(g_eCard f_eCard)
{
	sendMsg(getId(), ADD);
	sendCard(getId(), f_eCard);
}	

uCardSet MPIPlayer::getHand()
{
	uCardSet uResult = receiveCardSet(getId());
	return uResult;
}

bool MPIPlayer::isSuggestion()
{
	sendMsg(getId(), PLAY);
	return receiveBool(getId());
}

bool MPIPlayer::checkHand(g_eCard f_eCard[3])
{
	uCardSet cardSet = { {f_eCard[0], f_eCard[1], f_eCard[2]}};
	sendMsg(getId(), CHECK);
	sendCardSet(getId(), cardSet);
	return receiveBool(getId());
}

void MPIPlayer::announceDisprovedCard(g_eCard f_eCard)
{
	sendMsg(getId(), DISPROVE);
	sendCard(getId(), f_eCard);
}

g_eCard MPIPlayer::chooseCardToDisprove()
{
	return receiveCard(getId());
}

void MPIPlayer::end(char *f_strWinner, uCardSet f_uCardSet)
{
	sendMsg(getId(), END);
	sendName(getId(), f_strWinner);
	sendCardSet(getId(), f_uCardSet);
}

void MPIPlayer::start()
{
	sendMsg(getId(), START);
}

void MPIPlayer::correctHand(uCardSet f_uCardSet)
{
	sendMsg(getId(), VERIFYACCUSATION);
	sendCardSet(getId(), f_uCardSet);
}



