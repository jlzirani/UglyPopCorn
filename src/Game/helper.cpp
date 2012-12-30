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

#include "helper.hpp"

std::ostream &operator<<(std::ostream &f_strOut, const g_eCard &fc_eCard)
{
	switch(fc_eCard){
		case SCARLETT: f_strOut << "SCARLETT";
			break;
		case MUSTARD: f_strOut << "MUSTARD";
			break;
		case WHITE: f_strOut << "WHITE";
			break;
		case GREEN: f_strOut << "GREEN";
			break;
		case PEACOCK: f_strOut << "PEACOCK";
			break;
		case PLUM: f_strOut << "PLUM";
			break;
		case CANDLESTICK: f_strOut << "CANDLESTICK";
			break;
		case KNIFE: f_strOut << "KNIFE";
			break;
		case LEADPIPE: f_strOut << "LEADPIPE";
			break;
		case REVOLVER: f_strOut << "REVOLVER";
			break;
		case KNOT: f_strOut << "KNOT";
			break;
		case SPANNER: f_strOut << "SPANNER";
			break;
		case KITCHEN: f_strOut << "KITCHEN";
			break;
		case BALLROOM: f_strOut << "BALLROOM";
			break;
		case DININGROOM: f_strOut << "DININGROOM";
			break;
		case CONSERVATORY: f_strOut << "CONSERVATORY";
			break;
		case BILLIARDROOM: f_strOut << "BILLIARDROOM";
			break;
		case LIBRARY: f_strOut << "LIBRARY";
			break;
		case STUDY: f_strOut << "STUDY";
			break;
		case HALL: f_strOut << "HALL";
			break;
		case LOUNGE: f_strOut << "LOUNGE";
			break;
		default: f_strOut << "not recognized";
	}

	return f_strOut;
}
