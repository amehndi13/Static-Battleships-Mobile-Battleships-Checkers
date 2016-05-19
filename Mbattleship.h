//Mbattleship.h
//Anuj Mehndiratta (amehndi1)
//Brennan Schneider (bschne20)
//Garren Angacian (gangaci1)
//April 20, 2016
//CS120 Intermediate Programming

#ifndef MBATTLESHIPGAME_H
#define MBATTLESHIPGAME_H
#include <vector>
#include <iostream>
#include <string>
#include <array>
#include <map>
#include "Ship.h"
#include "BattleshipPlayer.h"
#include "battleships.h"


class MBattleshipGame : public BattleshipGame {
	public:
		//Constructor of mobile battlship game 
		MBattleshipGame(BPlayer playerx, BPlayer playery) : BattleshipGame(playerx,playery) { 
		};
		//The function that gets called to move ships in mobile battleships
		GameResult moveShip(std::string input);
		
	private:
		//Check whether the move entered is valid for player 2
		bool checkValidMovePlayer2(int top, int bottom, int right, int left, int size, std::array<Coord, 5> location, char direction, int numSpots);
		//Check whether the move entered is valid for player 1
		bool checkValidMovePlayer1(int top, int bottom, int right, int left, int size, std::array<Coord, 5> location, char direction, int numSpots);
		//gets the type of ship based on the character
		int getShipType(char s);
		//gets the ship size from a char
		int getShipSize(char s);
		//gets ships size from an integer
		int getShipSizefromint(int s);		
};

#endif
