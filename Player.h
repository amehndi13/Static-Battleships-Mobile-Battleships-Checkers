//checkerPlayer.h
//Anuj Mehndiratta (amehndi1)
//Brennan Schneider (bschne20)
//Garren Angacian (gangaci1)
//April 20, 2016
//CS120 Intermediate Programming

#ifndef CHECKERPLAYER_H
#define CHECKERPLAYER_H
#include "game.h"
#include <vector>
#include <iostream>
#include <array>
#include <map>

class Player {
	friend class CheckersGame;
	public:
		Player() {};
	private:
		std::map<Coord, char> chips;
};
#endif
