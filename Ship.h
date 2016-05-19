//Ship.h
//Anuj Mehndiratta (amehndi1)
//Brennan Schneider (bschne20)
//Garren Angacian (gangaci1)
//April 20, 2016
//CS120 Intermediate Programming

#ifndef SHIP_H
#define SHIP_H
#include <vector>
#include <iostream>
#include <string>
#include <array>
#include <map>
#include "game.h"
#include "Piece.h"

class Ship : public Piece {
	public:
		Ship(){};
		std::map <char, std::array<Coord, 5>> shipInfo;
		std::array<Coord, 5> shipCoords;
		int shipSize;
		char orientation;
		Ship(std::string type, std::array<Coord, 5> indeces, int size) : shipCoords(indeces), shipSize(size) {
			piecetype = type;
			shipInfo.insert(std::pair<char, std::array<Coord, 5>>(piecetype[0],shipCoords));
			if (shipCoords[0].first == shipCoords[1].first) {
				orientation = 'h';
			} else {
				orientation = 'v';
			}
		};
	private:
		
};

#endif
