//player.h
//Anuj Mehndiratta (amehndi1)
//Brennan Schneider (bschne20)
//Garren Angacian (gangaci1)
//April 20, 2016
//CS120 Intermediate Programming

#ifndef BATTLESHIPPLAYER_H
#define BATTLESHIPPLAYER_H
#include <vector>
#include <iostream>
#include <string>
#include <array>
#include <map>
#include "game.h"
#include "Ship.h"
#include "Player.h"

class BPlayer : public Player {
	public:
	    BPlayer();
	    std::array<Ship, 5> ships;
	    Board playerBoard = Board(10);

        void setShips(std::array<Ship, 5> inputships);
        //creates an aircraft ship
		Ship makeAircraft(std::string input);

        //creates a battleship ship
        Ship makeBattle(std::string input);

        //creates a cruiser type ship
        Ship makeCruiser(std::string input);

        //creates submarine type ship
        Ship makeSub(std::string input);

        //creates destroyer ship
        Ship makeDestroyer(std::string input);

        //fills the board with the ship objects
		bool fillBoard(Ship filler);
		//Method to print the board of player1. I just used this for debugging purposes
		void printBoard();

	private:
		
};

#endif
