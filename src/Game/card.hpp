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

#ifndef __CARD_HPP__
#define __CARD_HPP__

enum g_eCard { SCARLETT, MUSTARD, WHITE, GREEN, PEACOCK, PLUM,
CANDLESTICK, KNIFE, LEADPIPE, REVOLVER, KNOT, SPANNER,
KITCHEN, DININGROOM, BALLROOM, CONSERVATORY, BILLIARDROOM, LIBRARY, STUDY, HALL, LOUNGE};

const g_eCard gc_eSuspects[] = {SCARLETT, MUSTARD, WHITE, GREEN, PEACOCK, PLUM};
const g_eCard gc_eWeapons[] = {CANDLESTICK, KNIFE, LEADPIPE, REVOLVER, KNOT, SPANNER};
const g_eCard gc_eRooms[] = {KITCHEN, DININGROOM, BALLROOM, CONSERVATORY, BILLIARDROOM, LIBRARY, STUDY, HALL, LOUNGE};

const unsigned int gc_iNbrSuspects = sizeof(gc_eSuspects)/sizeof(g_eCard);
const unsigned int gc_iNbrWeapons = sizeof(gc_eWeapons)/sizeof(g_eCard);
const unsigned int gc_iNbrRooms = sizeof(gc_eRooms)/sizeof(g_eCard);

struct sCardSet
{
	g_eCard m_eMurderer;
	g_eCard m_eWeapon;
	g_eCard m_eRoom;
};

union uCardSet
{
	sCardSet m_sCardset;
	g_eCard m_vecCard[3];
};





#endif

