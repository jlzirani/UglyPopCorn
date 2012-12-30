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

#ifndef __GAME_HPP__
#define __GAME_HPP__
#include <vector>
#include <string>
#include "card.hpp"
#include "player.hpp"

class CGame {
	typedef std::vector<CPlayer *> VecPlayer;
	typedef VecPlayer::iterator IterPlayer;
	VecPlayer m_vecPlayer;
	IterPlayer m_currPlayer;
	
	sCardSet m_sHiddenCards;

	CPlayer *m_cWinner;

	void turn(); // play a step
	void suggestionProcess(uCardSet &f_uHand);
	void accusationProcess(uCardSet &f_uHand);

public:
	CGame(): m_vecPlayer(0), m_cWinner(0) {}
	~CGame();

	VecPlayer &getPlayers() { return m_vecPlayer; }

	inline void prepareNextPlayer() { prepareNextPlayer(m_currPlayer); }
	void prepareNextPlayer(IterPlayer &f_cPlayer );

	void addPlayer(CPlayer *f_pcNewPlayer) { m_vecPlayer.push_back(f_pcNewPlayer); }

	void initGame();
	void play();
};
#endif 
