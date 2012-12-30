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

#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__
#include <vector>
#include <string>
#include "card.hpp"

class CPlayer {
	typedef std::vector<g_eCard> VecCard;

	int m_iId;
	char m_strName[25];
	bool m_bPlayable;
	
public:	
	//Cstr && destr
	CPlayer(int f_iId = 0 , const char fc_strName[] = "Player");	
	virtual ~CPlayer() {}
	
	//Getter and setter
	inline int getId() const { return m_iId; }
	inline bool getPlayable() const { return m_bPlayable; }
	inline void setPlayable(bool f_bValue) { m_bPlayable = f_bValue; }
	inline char *getName() {return m_strName;}
	void setName(const char fc_strName[]);
	
	// functions to determine the begin and the end of the game
	virtual void end(char *f_strWinner, uCardSet f_uCardSet) {}
	virtual void start() {}

	// functions to ask the player to plays
	virtual bool isSuggestion() = 0;
	virtual uCardSet getHand() = 0;
	virtual void announceDisprovedCard(g_eCard f_eCard) = 0;
	virtual void correctHand(uCardSet f_uCardSet) {}
	
	//functions to ask the player to disprove a set of cards
	virtual bool checkHand(g_eCard f_eCard[3]) = 0;
	virtual g_eCard chooseCardToDisprove() = 0;
	
	// MISC
	virtual void add(g_eCard f_eCard) = 0;
	virtual void notifyPlayerPlays( bool f_bSuggestion, char *fc_strPlayer, uCardSet f_uCardSet ) = 0;

};

#endif 
