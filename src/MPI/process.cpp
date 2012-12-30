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

#include "process.hpp"
#include "MPIhelper.hpp"
#include "../Game/game.hpp"
#include "MPIplayer.hpp"
#include "MPIMessage.hpp"
#include <iostream>
#include <mpi.h>

void initProcess(int argc, char *argv[])
{
	int myrank;

	/* Initialize MPI */

	MPI_Init(&argc, &argv);

	/* Find out my identity in the default communicator */

	MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
	
	if(myrank == 0)
	{	// the root process
		int size;
		MPI_Comm_size(MPI_COMM_WORLD, &size);

		rootProcess(size-1);
	}	
	else
		childProcess(myrank); // the child process

	MPI_Finalize();
}

void rootProcess(int f_iNbrPlayer)
{
	CGame cGame;

	// adding players
	cGame.addPlayer(getPlayer(0, true));
	for(int i = 0; i < f_iNbrPlayer; ++i)
		cGame.addPlayer(new MPIPlayer( i+1 ));

	// init the game
	cGame.initGame();

	// waiting the initialization of players
	syncProcess();

	// playing
	cGame.play();	
}

void getSuggOrAcc( int f_iFrom, g_eMsg eMsg, CPlayer *currPlayer )
{
	char *strName = receiveName( f_iFrom );
	uCardSet uSet = receiveCardSet( f_iFrom );

	bool bSuggestion = eMsg == SUGGESTION;

	currPlayer->notifyPlayerPlays(bSuggestion, strName, uSet);
	delete[] strName;
}

void showWinner( int f_iFrom, CPlayer *currPlayer )
{
	char *strName = receiveName( f_iFrom );
	uCardSet uSet = receiveCardSet( f_iFrom );

	currPlayer->end(strName, uSet);
	delete[] strName;
}

void childProcess(int f_iMyRank)
{
	// This function maps the MPI message to the concrete players.
	CPlayer *currPlayer = getPlayer(f_iMyRank, false);
	int iRoot = 0;

	g_eMsg eMsg;
	do { 
		eMsg = receiveMsg( iRoot );
		switch(eMsg)
		{
			case GETNAME:	sendName( iRoot, currPlayer->getName() );
					break;
			case ADD:	currPlayer->add( receiveCard(iRoot) );
					break;
			case START:	syncProcess();
					break;
			case PLAY:	sendBool(iRoot, currPlayer->isSuggestion());
					sendCardSet( iRoot, currPlayer->getHand() );
					break;
			case CHECK:	if( currPlayer->checkHand( receiveCardSet(iRoot).m_vecCard ) )
					{
						sendBool(iRoot, true);
						sendCard(iRoot, currPlayer->chooseCardToDisprove() ) ;
					}
					else
						sendBool(iRoot, false);
				
					break;
			case DISPROVE:	currPlayer->announceDisprovedCard( receiveCard(iRoot) );
				 	break;

			case SUGGESTION: 
			case ACCUSATION: 	getSuggOrAcc(iRoot, eMsg, currPlayer);
						break; 
			case VERIFYACCUSATION:	currPlayer->correctHand( receiveCardSet(iRoot) );
						break;
			case END: showWinner( iRoot, currPlayer );	
			default: ;
		}
		
	}while(eMsg != END);

	delete currPlayer;
}
