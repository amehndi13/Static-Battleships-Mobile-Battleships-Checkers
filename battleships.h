//battleship.h
//Anuj Mehndiratta (amehndi1)
//Brennan Schneider (bschne20)
//Garren Angacian (gangaci1)
//April 20, 2016
//CS120 Intermediate Programming

#ifndef BATTLESHIPS_H
#define BATTLESHIPS_H
#include <vector>
#include <iostream>
#include <array>
#include "Ship.h"
#include "BattleshipPlayer.h"
#include "Piece.h"
#include "game.h"

class BattleshipGame : public Game {
	public:
		BPlayer player1;
		BPlayer player2;
		//Initialize int to keep track of how many player1 ships havent been sunk
		int numships1 = 17;
		//Initialize int to keep track of how many player2 ships havent been sunk
		int numships2 = 17;
		//Constructor of battlship game
		BattleshipGame(BPlayer playerx, BPlayer playery);
		virtual GameResult attack_square(Coord position, std::string ss);
	private:
		void checkSunkShip(char s);

};

#endif
