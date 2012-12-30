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

#ifndef __IA_HPP__
#define __IA_HPP__

#include "player.hpp"

// YOU ARE UNDER ARREST !
class CIA: public CPlayer
{
	typedef std::vector<g_eCard> VecCard;
	typedef VecCard::iterator IterCard;

	VecCard m_vecPlayableSuspectsCards;
	VecCard m_vecPlayableWeaponsCards;
	VecCard m_vecPlayableRoomsCards;
	VecCard m_vecHand;

	g_eCard m_eDisproveCard;

	void removePlayableCard(g_eCard f_eCard);
public:
	CIA(int f_uId = 0);
	
	// functions to ask the player to plays
	virtual bool isSuggestion();
	virtual uCardSet getHand();
	virtual void announceDisprovedCard(g_eCard f_eCard);	
	
	//functions to ask the player to disprove a set of cards
	virtual bool checkHand(g_eCard f_eCard[3]);
	virtual g_eCard chooseCardToDisprove();	

	// MISC
	virtual void add(g_eCard f_eCard);
	virtual void notifyPlayerPlays( bool f_bSuggestion, char *fc_strPlayer, uCardSet f_uCardSet ) {}
	
};

#endif


