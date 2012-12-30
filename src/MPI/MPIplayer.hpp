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

#ifndef __MPIPLAYER_HPP__
#define __MPIPLAYER_HPP__

#include "../Game/player.hpp"

class MPIPlayer: public CPlayer
{
public:
	MPIPlayer(int f_iId, const char *fc_strName = "Player") ;
	~MPIPlayer() {}

	// functions to determine the begin and the end of the game
	virtual void end(char *f_strWinner, uCardSet f_uCardSet);
	virtual void start();

	// functions to ask the player to plays
	virtual bool isSuggestion();
	virtual uCardSet getHand();
	virtual void announceDisprovedCard(g_eCard f_eCard);
	virtual void correctHand(uCardSet f_uCardSet);
	
	//functions to ask the player to disprove a set of cards
	virtual bool checkHand(g_eCard f_eCard[3]);
	virtual g_eCard chooseCardToDisprove();
	
	// MISC
	virtual void add(g_eCard f_eCard);
	virtual void notifyPlayerPlays( bool f_bSuggestion, char *fc_strPlayer, uCardSet f_uCardSet );
};

#endif
