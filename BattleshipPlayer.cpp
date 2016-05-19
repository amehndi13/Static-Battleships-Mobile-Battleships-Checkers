//player.h
//Anuj Mehndiratta (amehndi1)
//Brennan Schneider (bschne20)
//Garren Angacian (gangaci1)
//April 20, 2016
//CS120 Intermediate Programming

#include "BattleshipPlayer.h"
#include <vector>
#include <iostream>
#include <string>
#include <array>
#include <map>
#include "game.h"
#include "Ship.h"
#include "Player.h"
using namespace std;

	BPlayer :: BPlayer(){}
	array<Ship, 5> ships;
	Board playerBoard = Board(10);

        void BPlayer :: setShips(array<Ship, 5> inputships) {
            ships = inputships;
        }
        //creates an aircraft ship
		Ship BPlayer :: makeAircraft(string input) {
			string aircraft1string = input;
			array<Coord, 5> airCoords1;
  			int aircraft1x = aircraft1string[0]-'0';
  			int aircraft1y = aircraft1string[1]-'0';
  			if (aircraft1string[2] == 'h') {
  				for (int i = 0; i < 5; i++) {
  					airCoords1[i] = make_pair(aircraft1y, aircraft1x + i);
  				}
  			} else if (aircraft1string[2] == 'v') {
  				for (int i = 0; i < 5; i++) {
  					airCoords1[i] = make_pair(aircraft1y + i, aircraft1x);
  				}
  			}
  			Ship aircraft1("AIRCRAFT CARRIER", airCoords1, 5);
  			return aircraft1;
        }

        //creates a battleship ship
        Ship BPlayer :: makeBattle(string input) {
  			string battleship1string = input;
			array<Coord, 5> battleCoords1;
  			int battle1x = battleship1string[0]-'0';
  			int battle1y = battleship1string[1]-'0';
  			if (battleship1string[2] == 'h') {
  				for (int i = 0; i < 5; i++) {
  					battleCoords1[i] = make_pair(battle1y, battle1x + i);
  				}
  			} else if (battleship1string[2] == 'v') {
  				for (int i = 0; i < 5; i++) {
  					battleCoords1[i] = make_pair(battle1y + i, battle1x);
  				}
  			}
  			Ship battleship1("BATTLESHIP", battleCoords1, 4);
  			return battleship1;
        }

        //creates a cruiser type ship
        Ship BPlayer :: makeCruiser(string input) {
  			string cruiser1string = input;
			array<Coord, 5> cruiserCoords1;
  			int cruiser1x = cruiser1string[0]-'0';
  			int cruiser1y = cruiser1string[1]-'0';
  			if (cruiser1string[2] == 'h') {
  				for (int i = 0; i < 5; i++) {
  					cruiserCoords1[i] = make_pair(cruiser1y, cruiser1x + i);
  				}
  			} else if (cruiser1string[2] == 'v') {
  				for (int i = 0; i < 5; i++) {
  					cruiserCoords1[i] = make_pair(cruiser1y + i, cruiser1x);
  				}
  			}
  			Ship cruiser1("CRUISER", cruiserCoords1, 3);
  			return cruiser1;
        }

        //creates submarine type ship
        Ship BPlayer :: makeSub(string input) {
  			string	sub1string = input;
			array<Coord, 5> subCoords1;
  			int sub1x = sub1string[0]-'0';
  			int sub1y = sub1string[1]-'0';
  			if (sub1string[2] == 'h') {
  				for (int i = 0; i < 5; i++) {
  					subCoords1[i] = make_pair(sub1y, sub1x + i);
  				}
  			} else if (sub1string[2] == 'v') {
  				for (int i = 0; i < 5; i++) {
  					subCoords1[i] = make_pair(sub1y + i, sub1x);
  				}
  			}
  			Ship submarine1("SUBMARINE", subCoords1, 3);
  			return submarine1;
        }

        //creates destroyer ship
        Ship BPlayer :: makeDestroyer(string input) {
  			string	destroyer1string = input;
			array<Coord, 5> destroyerCoords1;
  			int destroyer1x = destroyer1string[0]-'0';
  			int destroyer1y = destroyer1string[1]-'0';
  			if (destroyer1string[2] == 'h') {
  				for (int i = 0; i < 5; i++) {
  					destroyerCoords1[i] = make_pair(destroyer1y, destroyer1x + i);
  				}
  			} else if (destroyer1string[2] == 'v') {
  				for (int i = 0; i < 5; i++) {
  					destroyerCoords1[i] = make_pair(destroyer1y + i, destroyer1x);
  				}
  			}
  			Ship destroyer1("DESTROYER", destroyerCoords1, 2);
  			return destroyer1;
        }

        //fills the board with the ship objects
		bool BPlayer :: fillBoard(Ship filler) {
			Ship temp1 = filler;
			string type = temp1.piecetype;
			char val = type[0];
			array<Coord, 5> coordinates1 = temp1.shipCoords;
			for (int j = 0; j < temp1.shipSize; j++) {
				Coord current1 = coordinates1[j]; 
				if (current1.first > 9 || current1.second > 9 || current1.first < 0 || current1.second < 0) {
					return false;
				}
				if (playerBoard.boardstructure.at(current1.first).at(current1.second) != '-'){
                    return false;
				}
			}
            for (int j = 0; j < temp1.shipSize; j++) {
                Coord current1 = coordinates1[j];
                playerBoard.boardstructure.at(current1.first).at(current1.second) = val;
            }
            return true;
		}

		//Method to print the board of player1. I just used this for debugging purposes
		void BPlayer :: printBoard() {
			vector<vector<char>> :: iterator it1;
			for (it1 = playerBoard.boardstructure.begin(); it1 != playerBoard.boardstructure.end(); ++it1) {
				for (int i = 0; i < 10; i++) {
					cout << it1 -> at(i);
				} 
				cout << endl;
			}
		}


