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

#include "human.hpp"
#include <algorithm>
#include <iostream>
#include "helper.hpp"

Human::Human(int f_uId): CPlayer(f_uId, "Human") {}

void Human::showPlayedCards()
{
	std::cout << "Played suspects cards: ";
	for(VecCard::iterator it = m_vecPlayedSuspectsCards.begin(); it != m_vecPlayedSuspectsCards.end(); ++it)
		std::cout << (*it) << " ";
	std::cout << std::endl;

	std::cout << "Played weapons cards: ";
	for(VecCard::iterator it = m_vecPlayedWeaponsCards.begin(); it != m_vecPlayedWeaponsCards.end(); ++it)
		std::cout << (*it) << " ";
	std::cout << std::endl;

	std::cout << "Played room cards: ";
	for(VecCard::iterator it = m_vecPlayedRoomsCards.begin(); it != m_vecPlayedRoomsCards.end(); ++it)
		std::cout << (*it) << " ";
	std::cout << std::endl;

	std::cout << "Disproved cards: ";
	for(VecCard::iterator it = getDisprovedCards().begin(); it != getDisprovedCards().end(); ++it)
		std::cout << (*it) << " ";
	std::cout << std::endl;
}

void Human::showHands()
{
	std::cout << "Your Hand cards: ";
	for(VecCard::iterator it = getHands().begin(); it != getHands().end(); ++it)
		std::cout << (*it) << " ";
	std::cout << std::endl;
}

void Human::notifyPlayerPlays( bool f_bSuggestion, char *fc_strPlayer, uCardSet f_uCardSet )
{
	sCardSet &sSet = f_uCardSet.m_sCardset; 
	std::cout << fc_strPlayer << " makes ";
	
	if(f_bSuggestion)
		std::cout << "a suggestion ";
	else
		std::cout << "an accusation ";


	std::cout	<< "with " << sSet.m_eMurderer << " "
			<< sSet.m_eWeapon << " " << sSet.m_eRoom << std::endl;
}


void Human::announceDisprovedCard(g_eCard f_eCard)
{
	m_vecDisprovedCards.push_back(f_eCard);
	std::cout << "The card " << f_eCard << " has been disproved !" << std::endl;
}

uCardSet Human::makeSuggestion()
{
	uCardSet f_suggestion;
	
	std::cout << std::endl << "Please choose between the following suggestion of murderer, weapon and the rooms." << std::endl;
	std::cout << "To confirm, please enter the number between parentheses. Any other choice will lead you back to the main menu." << std::endl << std::endl;
	bool bMenuLoop = true;
	
	while(bMenuLoop)
	{
		unsigned int iChoice =0;

		std::cout << "The suspect list :";
		for(unsigned int i = 0; i < gc_iNbrSuspects; ++i)
			std::cout << gc_eSuspects[i] << "(" << i << ")" << " " ;
		std::cout << std::endl << "Your choice :";
		std::cin >> iChoice;

		if(iChoice <= gc_iNbrSuspects)
		{
			f_suggestion.m_sCardset.m_eMurderer = gc_eSuspects[iChoice];

			std::cout << "The Weapons list :";
			for(unsigned int i = 0; i < gc_iNbrSuspects; ++i)
				std::cout << gc_eWeapons[i] << "(" << i << ")" << " " ;
			std::cout << std::endl << "Your choice :";
			std::cin >> iChoice;

			if(iChoice <= gc_iNbrWeapons)
			{
				f_suggestion.m_sCardset.m_eWeapon = gc_eWeapons[iChoice];

				std::cout << "The suspect list :";
				for(unsigned int i = 0; i < gc_iNbrRooms; ++i)
					std::cout << gc_eRooms[i] << "(" << i << ")" << " " ;
				std::cout << std::endl << "Your choice :";
				std::cin >> iChoice;
				if( iChoice <= gc_iNbrRooms)
				{
					bMenuLoop = false;
					f_suggestion.m_sCardset.m_eRoom = gc_eRooms[iChoice];
				}			
			}
		}
	}
	return f_suggestion;
}


uCardSet Human::getHand()
{
	// ask what hand he wants to play.
	uCardSet hand = makeSuggestion();

	// adding the cards to the played cards
	if(std::find(m_vecPlayedSuspectsCards.begin(), m_vecPlayedSuspectsCards.end(), hand.m_sCardset.m_eMurderer)==m_vecPlayedSuspectsCards.end())
		m_vecPlayedSuspectsCards.push_back(hand.m_sCardset.m_eMurderer);

	if(std::find(m_vecPlayedWeaponsCards.begin(), m_vecPlayedWeaponsCards.end(), hand.m_sCardset.m_eWeapon)==m_vecPlayedWeaponsCards.end())
		m_vecPlayedWeaponsCards.push_back(hand.m_sCardset.m_eWeapon);

	if(std::find(m_vecPlayedRoomsCards.begin(), m_vecPlayedRoomsCards.end(), hand.m_sCardset.m_eRoom)==m_vecPlayedRoomsCards.end())
		m_vecPlayedRoomsCards.push_back(hand.m_sCardset.m_eRoom);

	std::cout << std::endl ;

	return hand;
}

bool Human::isSuggestion()
{
	bool bMenu = true;
	std::cout << std::endl << "----------------" << std::endl;
	std::cout << "It's your turn !" << std::endl;
	std::cout << "----------------" << std::endl << std::endl;
	
	showPlayedCards();
	showHands();

	int iMenuChoice;

	// ask the user to make a choice
	while(bMenu)
	{
		iMenuChoice = 0;
		std::cout << "1) Display hands" << std::endl
			<< "2) Display played and disproved cards" << std::endl
			<< "3) Make a suggestion" << std::endl
			<< "4) Make an accusation" << std::endl
			<< "Your choice :";
		std::cin >> iMenuChoice;

		switch(iMenuChoice)
		{
			case 1: showHands();
				break;
			case 2: showPlayedCards();
				break;
			case 3: 
			case 4: bMenu = false;
				break;
			default: std::cout << "Command not recognized!" << std::endl;
		}
	}
	return iMenuChoice == 3;
}

void Human::add(g_eCard f_eCard){
	m_vecHand.push_back(f_eCard);
}

g_eCard Human::chooseCardToDisprove(){
	return m_eDisproveCard;
}

bool Human::checkHand(g_eCard f_eCard[3])
{
	// determine the cards to disprove
	std::vector<g_eCard> vecDisproveCard;
	for (unsigned int i= 0; i< 3; ++i){
		for (IterCard it= m_vecHand.begin(); it != m_vecHand.end(); ++it){
			if (f_eCard[i] == *it)
				vecDisproveCard.push_back(*it);
		}
	}

	if(vecDisproveCard.empty())
	{
		std::cout << "You have nothing to disprove" << std::endl;
		return false;	
	}	
	else
	{
		// ask to the player what card he wants to disprove
		unsigned int i = 0;
		std::cout << std::endl;
		do
		{		
			std::cout << "Card to disprove :" ;
			for (IterCard it= vecDisproveCard.begin(); it != vecDisproveCard.end(); ++it)
				std::cout << (*it) << "(" << i++ << ") ";
			std::cout << std::endl << "Your choice :";
			std::cin >> i;
		} while ( i > vecDisproveCard.size() );
		m_eDisproveCard = vecDisproveCard[i];
		return true;
	}
}

void Human::correctHand(uCardSet f_uCardSet)
{
	std::cout << "The correct hand was " << f_uCardSet.m_sCardset.m_eMurderer << " " << f_uCardSet.m_sCardset.m_eWeapon << " " << f_uCardSet.m_sCardset.m_eRoom << std::endl;
}

void Human::end(char *f_strWinner, uCardSet f_uCardSet)
{
	std::cout << "The winner is " << f_strWinner << " with the hand : " << f_uCardSet.m_sCardset.m_eMurderer << " " << f_uCardSet.m_sCardset.m_eWeapon << " " << f_uCardSet.m_sCardset.m_eRoom << std::endl;
}

