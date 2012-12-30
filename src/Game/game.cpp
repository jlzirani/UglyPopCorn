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

#include "game.hpp"
#include "helper.hpp"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

void initPlaybleCard( std::vector<g_eCard> &f_vecCardDest, const g_eCard *fc_veceSrc, unsigned int f_iSizeMax, g_eCard eCardToAvoid )
{
	for(unsigned i = 0; i < f_iSizeMax; ++i)
	{
		if(fc_veceSrc[i] != eCardToAvoid)
			f_vecCardDest.push_back(fc_veceSrc[i]);
	}
} 

CGame::~CGame()
{
	for(IterPlayer it = m_vecPlayer.begin(); it != m_vecPlayer.end(); ++it)
		delete (*it);
	m_vecPlayer.clear();
}


void CGame::prepareNextPlayer(IterPlayer &f_cPlayer)
{
	if(f_cPlayer+1 == m_vecPlayer.end())
		f_cPlayer= m_vecPlayer.begin();
	else
		++f_cPlayer;
}

void CGame::initGame()
{
	m_currPlayer= m_vecPlayer.begin();
	srand ( time(0) );
	std::vector<g_eCard> vecCardToDist;

	// init hidden cards;
	m_sHiddenCards.m_eMurderer = gc_eSuspects[rand() % gc_iNbrSuspects];
	m_sHiddenCards.m_eWeapon = gc_eWeapons[rand() % gc_iNbrWeapons];
	m_sHiddenCards.m_eRoom = gc_eRooms[rand() % gc_iNbrRooms];

	// init playable cards
	initPlaybleCard(vecCardToDist, gc_eSuspects, gc_iNbrSuspects, m_sHiddenCards.m_eMurderer);
	initPlaybleCard(vecCardToDist, gc_eWeapons, gc_iNbrWeapons, m_sHiddenCards.m_eWeapon);
	initPlaybleCard(vecCardToDist, gc_eRooms, gc_iNbrRooms, m_sHiddenCards.m_eRoom);

	// we distribute the cards
	while (!vecCardToDist.empty()){
		prepareNextPlayer();
		int iIdCard= rand()%vecCardToDist.size();
		(*m_currPlayer)->add(vecCardToDist[iIdCard]);
		vecCardToDist.erase(vecCardToDist.begin() + iIdCard);		
	}

	// for each player, we notify that we can start the party
	for(IterPlayer it = m_vecPlayer.begin(); it != m_vecPlayer.end(); ++it)
	{
		(*it)->setPlayable(true);
		(*it)->start();	
	}
}

void CGame::turn()
{
	CPlayer &currPlayer = *(*m_currPlayer); 
	if(currPlayer.getPlayable())
	{
		bool bSuggestion = currPlayer.isSuggestion(); // ask the cyrrent player if he want a suggestion or an accusation

		uCardSet hand = currPlayer.getHand();

		// we notify all the player that the current player has just make a sugg or acc
		for(IterPlayer it = m_vecPlayer.begin(); it != m_vecPlayer.end(); ++it)
			if(it != m_currPlayer)	
				(*it)->notifyPlayerPlays(bSuggestion, currPlayer.getName(), hand);
		
		if(bSuggestion)
			suggestionProcess(hand);
		else // if it is an accusation
			accusationProcess(hand);
	}
}

void CGame::suggestionProcess(uCardSet &f_uHand)
{
	CPlayer &currPlayer = *(*m_currPlayer); 
	bool isDisproved = false;
	IterPlayer opponent = m_currPlayer;
	
	do // we ask the others players if they disprove
	{
		prepareNextPlayer(opponent);
		isDisproved = ((*opponent)->checkHand(f_uHand.m_vecCard));
	} while (opponent != m_currPlayer && !isDisproved );

	if (isDisproved) // if it is disprove, we notify the player.
	{
		g_eCard disprovedCard = (*opponent)->chooseCardToDisprove();		
		currPlayer.announceDisprovedCard(disprovedCard);
	}

	// check if the player has made a good guess.
	if( m_sHiddenCards.m_eMurderer == f_uHand.m_sCardset.m_eMurderer && m_sHiddenCards.m_eWeapon == f_uHand.m_sCardset.m_eWeapon && m_sHiddenCards.m_eRoom == f_uHand.m_sCardset.m_eRoom )
		m_cWinner = (*m_currPlayer);

}

void CGame::accusationProcess(uCardSet &f_uHand)
{
	// In all case, the player can't continue to play.
	(*m_currPlayer)->setPlayable(false);

	// verify if the player has the correct combination. 
	if( m_sHiddenCards.m_eMurderer == f_uHand.m_sCardset.m_eMurderer && m_sHiddenCards.m_eWeapon == f_uHand.m_sCardset.m_eWeapon && m_sHiddenCards.m_eRoom == f_uHand.m_sCardset.m_eRoom )
		m_cWinner = (*m_currPlayer);

	// send the correct hand to the player
	uCardSet uSet = { m_sHiddenCards };
	(*m_currPlayer)->correctHand(uSet);
}

void CGame::play()
{
	m_currPlayer = m_vecPlayer.begin();
	m_cWinner = 0;

	while (m_cWinner == 0)
	{
		turn();

		if (m_cWinner == 0) // we don't have any winner, so we continue the game with the following player.
			prepareNextPlayer();
	}

	// We notify each player that is the end of the game.
	for(IterPlayer it = m_vecPlayer.begin(); it != m_vecPlayer.end(); ++it)
		(*it)->end( m_cWinner->getName(), (uCardSet){m_sHiddenCards} );
}

