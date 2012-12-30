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

#include "MPIhelper.hpp"
#include <mpi.h>
#include "../Game/human.hpp"
#include "../Game/IA.hpp"

CPlayer *getPlayer(int f_iId, bool isHuman)
{
	if(isHuman)
		return new Human(f_iId);

	return new CIA(f_iId);
}

void syncProcess()
{
	MPI_Barrier(MPI_COMM_WORLD);
}

bool	receiveBool(int f_iFrom )
{
	MPI_Status status;
	bool bResult;
	MPI_Recv( &bResult , 1, MPI_BYTE, f_iFrom, 0, MPI_COMM_WORLD, &status);
	return bResult;
}

g_eCard receiveCard( int f_iFrom )
{
	MPI_Status status;
	g_eCard eCard;
	MPI_Recv( &eCard , 1, MPI_INT, f_iFrom, 0, MPI_COMM_WORLD, &status);
	return eCard;
}

g_eMsg receiveMsg( int f_iFrom )
{
	MPI_Status status;
	g_eMsg eMsg;
	MPI_Recv( &eMsg , 1, MPI_INT, f_iFrom, 0, MPI_COMM_WORLD, &status);
	return eMsg;
}

uCardSet receiveCardSet( int f_iFrom )
{
	MPI_Status status;
	uCardSet uSet;
	MPI_Recv( uSet.m_vecCard , 3, MPI_INT, f_iFrom, 0, MPI_COMM_WORLD, &status);
	return uSet;
}

void sendBool( int f_iDest, bool f_bBool )
{
	MPI_Send( &f_bBool, 1, MPI_BYTE, f_iDest, 0, MPI_COMM_WORLD );
}


void sendCard( int f_iDest, g_eCard f_eCard )
{
	MPI_Send( &f_eCard, 1, MPI_INT, f_iDest, 0, MPI_COMM_WORLD );
}

void sendMsg( int f_iDest, g_eMsg f_eMsg )
{
	MPI_Send( &f_eMsg, 1, MPI_INT, f_iDest, 0, MPI_COMM_WORLD );
}

void sendCardSet( int f_iDest, uCardSet f_uCardSet )
{
	MPI_Send( f_uCardSet.m_vecCard, 3, MPI_INT, f_iDest, 0, MPI_COMM_WORLD );
}

char *receiveName( int f_iFrom )
{
	char *strName = new char[25];
	MPI_Status status;
	MPI_Recv( strName, 25, MPI_CHAR, f_iFrom, 0, MPI_COMM_WORLD, &status );
	return strName;
}

void 	sendName( int f_iDest, char fc_strName[] )
{
	MPI_Send( fc_strName, 25, MPI_CHAR, f_iDest, 0, MPI_COMM_WORLD );
}


