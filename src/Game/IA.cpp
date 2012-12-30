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

#include "IA.hpp"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

CIA::CIA(int f_uId): CPlayer(f_uId)
{
	char strName[25];
	sprintf( strName, "AI %d", f_uId);
	setName(strName);
	srand( time(0) + f_uId ); // we use the user id as the initializer of the random function

	for(unsigned int i = 0; i < gc_iNbrSuspects; ++i)
		m_vecPlayableSuspectsCards.push_back(gc_eSuspects[i]);

	for(unsigned int i = 0; i < gc_iNbrWeapons; ++i)
		m_vecPlayableWeaponsCards.push_back(gc_eWeapons[i]);

	for(unsigned int i = 0; i < gc_iNbrRooms; ++i)
		m_vecPlayableRoomsCards.push_back(gc_eRooms[i]);
}

void CIA::removePlayableCard(g_eCard f_eCard)
{
	// Updating Suspects cards
	VecCard::iterator it= m_vecPlayableSuspectsCards.begin();
	while(it != m_vecPlayableSuspectsCards.end())
	{
		if((*it) == f_eCard)
			it = m_vecPlayableSuspectsCards.erase(it);
		else
			++it;
	}

	// Updating Weapons cards
	it= m_vecPlayableWeaponsCards.begin();
	while(it != m_vecPlayableWeaponsCards.end())
	{
		if((*it) == f_eCard)
			it = m_vecPlayableWeaponsCards.erase(it);
		else
			++it;
	}
	
	// Updating Rooms cards
	it= m_vecPlayableRoomsCards.begin();
	while(it != m_vecPlayableRoomsCards.end())
	{
		if((*it) == f_eCard)
			it = m_vecPlayableRoomsCards.erase(it);
		else
			++it;
	}
}

void CIA::add(g_eCard f_eCard)
{
	removePlayableCard(f_eCard);
	m_vecHand.push_back(f_eCard);	
}

bool CIA::isSuggestion()
{
	return !(m_vecPlayableSuspectsCards.size() == 1 && m_vecPlayableWeaponsCards.size() == 1 &&  m_vecPlayableRoomsCards.size() == 1 );
}

void CIA::announceDisprovedCard(g_eCard f_eCard)
{
	removePlayableCard(f_eCard);
}

uCardSet CIA::getHand()
{
	uCardSet result;

	// the IA chooses randomly on his playable cards.
	result.m_sCardset.m_eMurderer = m_vecPlayableSuspectsCards[ rand() % m_vecPlayableSuspectsCards.size() ];
	result.m_sCardset.m_eWeapon = m_vecPlayableWeaponsCards[ rand() % m_vecPlayableWeaponsCards.size() ] ;
	result.m_sCardset.m_eRoom = m_vecPlayableRoomsCards[ rand() % m_vecPlayableRoomsCards.size() ] ;

	return result;
}

bool CIA::checkHand(g_eCard f_eCard[3])
{
	// The IA disprove the first card he can disprove
	std::vector<g_eCard> vecDisproveCard(0);
	for (unsigned int i= 0; i< 3; ++i){
		for (IterCard it= m_vecHand.begin(); it != m_vecHand.end(); ++it){
			if (f_eCard[i] == *it)
				vecDisproveCard.push_back(*it);
		}
	}

	if(!vecDisproveCard.empty())
		m_eDisproveCard = vecDisproveCard.front();

	return !vecDisproveCard.empty();
}

/* for example return card that came the most often during the game (IA) */
g_eCard CIA::chooseCardToDisprove(){
	return m_eDisproveCard;
}

