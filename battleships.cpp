//battleship.cpp
//Anuj Mehndiratta (amehndi1)
//Brennan Schneider (bschne20)
//Garren Angacian (gangaci1)
//April 20, 2016
//CS120 Intermediate Programming

#include "game.h"
#include "battleships.h"
using namespace std;

BattleshipGame::BattleshipGame(BPlayer playerx, BPlayer playery) { 
	player1 = playerx; 
	player2 = playery;
}

GameResult BattleshipGame::attack_square(Coord position, string ss) {
	player1.printBoard();
	player2.printBoard();
	string useless = ss;
	//Checking if the coordinates of the move are valid
	if (position.first > 9 || position.second > 9 || position.first < 0 || position.second < 0) {
		cout << "INVALID MOVE" << endl;
		return RESULT_INVALID;
	} else {
		//player1 attaacking player2 board
		if (turn % 2 == 0){
			if (player2.playerBoard.boardstructure.at(position.second).at(position.first) != '-') {
				char temp = player2.playerBoard.boardstructure.at(position.second).at(position.first);
				if (temp == 'O') {
					cout << "HIT" << endl;
					turn++;
					return RESULT_KEEP_PLAYING;
				}
				player2.playerBoard.boardstructure.at(position.second).at(position.first) = 'O';
				numships2--;
				turn++;
				//all ships have been sunk. winner!
				if (numships2 == 0) {
					cout << "PLAYER 1 WON" << endl;
					return RESULT_PLAYER1_WINS;
				} else {
					checkSunkShip(temp);
					return RESULT_KEEP_PLAYING;
				}
			} else {
				turn++;	
				cout << "MISS" << endl;
				return RESULT_KEEP_PLAYING;
			}
		} 
		//player2 attacking player1 board
		else {
			if (player1.playerBoard.boardstructure.at(position.second).at(position.first) != '-') {
				char temp = player1.playerBoard.boardstructure.at(position.second).at(position.first);
				if (temp == 'O') {
					cout << "HIT" << endl;
					turn++;
					return RESULT_KEEP_PLAYING;
				}
				player1.playerBoard.boardstructure.at(position.second).at(position.first) = 'O';
				numships1--;
				turn++;
				//all ships have been sunk. winner!
				if (numships1 == 0) {
					cout << "PLAYER 2 WON" << endl;
					return RESULT_PLAYER2_WINS;
				} else {
					checkSunkShip(temp);
					return RESULT_KEEP_PLAYING;
				}
			} else {
				turn++;	
				cout << "MISS" << endl;
				return RESULT_KEEP_PLAYING;
			}
		}
	}
	return RESULT_KEEP_PLAYING;
}

void BattleshipGame::checkSunkShip(char s) {
	if (turn % 2 == 0) {
		if (s == 'A') {
			player2.ships[0].shipSize--;
			if (player2.ships[0].shipSize == 0) {
				cout << "SUNK AIRCRAFT CARRIER" << endl;
				array<Coord, 5> temp = player1.ships[0].shipCoords;
				for (int i = 0; i < 5; i++) {
					player1.playerBoard.boardstructure.at(temp[i].first).at(temp[i].second) = '-';
				}
			} else {
				cout << "HIT" << endl;
			}
		} else if (s == 'B') {
			player2.ships[1].shipSize--;
			if (player2.ships[1].shipSize == 0) {
				cout << "SUNK BATTLESHIP" << endl;
				array<Coord, 5> temp = player1.ships[1].shipCoords;
				for (int i = 0; i < 4; i++) {
					player1.playerBoard.boardstructure.at(temp[i].first).at(temp[i].second) = '-';
				}
			} else {
				cout << "HIT" << endl;
			}
		} else if (s == 'C') {
			player2.ships[2].shipSize--;
			if (player2.ships[2].shipSize == 0) {
				array<Coord, 5> temp = player1.ships[2].shipCoords;
				for (int i = 0; i < 3; i++) {
					player1.playerBoard.boardstructure.at(temp[i].first).at(temp[i].second) = '-';
				}
				cout << "SUNK CRUISER" << endl;
			} else {
				cout << "HIT" << endl;
			}
		} else if (s == 'S') {
			player2.ships[3].shipSize--;
			if (player2.ships[3].shipSize == 0) {
				array<Coord, 5> temp = player1.ships[3].shipCoords;
				for (int i = 0; i < 3; i++) {
					player1.playerBoard.boardstructure.at(temp[i].first).at(temp[i].second) = '-';
				}
				cout << "SUNK SUBMARINE" << endl;
			} else {
				cout << "HIT" << endl;
			}
		} else if (s == 'D') {
			player2.ships[4].shipSize--;
			if (player2.ships[4].shipSize == 0) {
				array<Coord, 5> temp = player1.ships[4].shipCoords;
				for (int i = 0; i < 2; i++) {
					player1.playerBoard.boardstructure.at(temp[i].first).at(temp[i].second) = '-';
				}
				cout << "SUNK DESTROYER" << endl;
			} else {
				cout << "HIT" << endl;
			}
		} 
	} else {
		if (s == 'A') {
			player1.ships[0].shipSize--;
			if (player1.ships[0].shipSize == 0) {
				cout << "SUNK AIRCRAFT CARRIER" << endl;
				array<Coord, 5> temp = player2.ships[0].shipCoords;
				for (int i = 0; i < 5; i++) {
					player2.playerBoard.boardstructure.at(temp[i].first).at(temp[i].second) = '-';
				}
			} else {
				cout << "HIT" << endl;
			}
		} else if (s == 'B') {
			player1.ships[1].shipSize--;
			if (player1.ships[1].shipSize == 0) {
				cout << "SUNK BATTLESHIP" << endl;
				array<Coord, 5> temp = player2.ships[1].shipCoords;
				for (int i = 0; i < 4; i++) {
					player2.playerBoard.boardstructure.at(temp[i].first).at(temp[i].second) = '-';
				}
			} else {
				cout << "HIT" << endl;
			}
		} else if (s == 'C') {
			player1.ships[2].shipSize--;
			if (player1.ships[2].shipSize == 0) {
				cout << "SUNK CRUISER" << endl;
				array<Coord, 5> temp = player2.ships[2].shipCoords;
				for (int i = 0; i < 3; i++) {
					player2.playerBoard.boardstructure.at(temp[i].first).at(temp[i].second) = '-';
				}
			} else {
				cout << "HIT" << endl;
			}
		} else if (s == 'S') {
			player1.ships[3].shipSize--;
			if (player1.ships[3].shipSize == 0) {
				cout << "SUNK SUBMARINE" << endl;
				array<Coord, 5> temp = player2.ships[3].shipCoords;
				for (int i = 0; i < 3; i++) {
					player2.playerBoard.boardstructure.at(temp[i].first).at(temp[i].second) = '-';
				}
			} else {
				cout << "HIT" << endl;
			}
		} else if (s == 'D') {
			player1.ships[4].shipSize--;
			if (player1.ships[4].shipSize == 0) {
				cout << "SUNK DESTROYER" << endl;
				array<Coord, 5> temp = player2.ships[4].shipCoords;
				for (int i = 0; i < 2; i++) {
					player2.playerBoard.boardstructure.at(temp[i].first).at(temp[i].second) = '-';
				}
			} else {
				cout << "HIT" << endl;
			}
		}
	}
}
