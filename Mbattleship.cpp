#include "game.h"
#include "Ship.h"
#include "BattleshipPlayer.h"
#include "battleships.h"
#include "Mbattleship.h"
using namespace std;


GameResult MBattleshipGame::moveShip(string input) {
	player1.printBoard();
	player2.printBoard();
	int x = input[0] - '0';
	int y = input[1] - '0';
	Coord position = make_pair(x,y);
	char direction = input[2];
	int numSpots = input[3] - '0';
	if (numSpots > 4 || numSpots < 1) {
		cout << "INVALID MOVE" << endl;
		return RESULT_INVALID;
	}
	//Checking if the coordinates of the move are valid
	if (position.first > 9 || position.second > 9 || position.first < 0 || position.second < 0) {
		cout << "INVALID MOVE" << endl;
		return RESULT_INVALID;
	} else {
		//player1 moving
		if (turn % 2 == 0){
			if (player1.playerBoard.boardstructure.at(position.second).at(position.first) != '-') {
				if (player1.playerBoard.boardstructure.at(position.second).at(position.first) == 'O') {
					int type = 0;
					for (int i = 0; i < 5; i++) {
						array<Coord, 5> player1ships = player1.ships[i].shipCoords;
						for (int j = 0; j < 5; j++) {
							if (player1ships[j].second == position.first && player1ships[j].first == position.second) {
								type = i;
							}
						}
					}
					int size = getShipSizefromint(type);
					if (player1.ships[type].orientation == 'v' && (direction == 'l' || direction == 'r')) {
						cout << "INVALID MOVE" << endl;
						return RESULT_INVALID;
					} else if (player1.ships[type].orientation == 'h' && (direction == 'u' || direction == 'd')) {
						cout << "INVALID MOVE" << endl;
						return RESULT_INVALID;
					}
					array<Coord, 5> location = player1.ships[type].shipCoords;
					int top = location[0].first;
					int bottom = location[size - 1].first;
					int right = location[0].second;
					int left = location[size - 1].second;
					if (!checkValidMovePlayer1(top, bottom, right, left, size, location, direction, numSpots)){
						cout << "INVALID MOVE" << endl;
						return RESULT_INVALID;
					}
					for (int i = size - 1; i >= 0; i--) {
						int x = location[i].first;
						int y = location[i].second;
						int upx = location[size - 1 - i].first;
						int upy = location[size - 1 - i].second;
						if (direction == 'u') {
							player1.playerBoard.boardstructure.at(upx - numSpots).at(upy) = player1.playerBoard.boardstructure.at(upx).at(upy);
							player1.playerBoard.boardstructure.at(upx).at(upy) = '-';
							player1.ships[type].shipCoords[size - 1 - i] = make_pair(upx - numSpots, upy);
						} else if (direction == 'd') {
							player1.playerBoard.boardstructure.at(x + numSpots).at(y) = player1.playerBoard.boardstructure.at(x).at(y);
							player1.playerBoard.boardstructure.at(x).at(y) = '-';
							player1.ships[type].shipCoords[i] = make_pair(x + numSpots, y);
						} else if (direction == 'r') {
							player1.playerBoard.boardstructure.at(x).at(y + numSpots) = player1.playerBoard.boardstructure.at(x).at(y);
							player1.playerBoard.boardstructure.at(x).at(y) = '-';
							player1.ships[type].shipCoords[i] = make_pair(x, y + numSpots);
						} else if (direction == 'l') {
							player1.playerBoard.boardstructure.at(upx).at(upy - numSpots) = player1.playerBoard.boardstructure.at(upx).at(upy);
							player1.playerBoard.boardstructure.at(upx).at(upy) = '-';
							player1.ships[type].shipCoords[size - i - 1] = make_pair(upx, upy - numSpots);

						}
					}
					turn++;
					return RESULT_KEEP_PLAYING;

				} else {
					int type = getShipType(player1.playerBoard.boardstructure.at(position.second).at(position.first));
					int size = getShipSize(player1.playerBoard.boardstructure.at(position.second).at(position.first));
					if (player1.ships[type].orientation == 'v' && (direction == 'l' || direction == 'r')) {
						cout << "INVALID MOVE" << endl;
						return RESULT_INVALID;
					} else if (player1.ships[type].orientation == 'h' && (direction == 'u' || direction == 'd')) {
						cout << "INVALID MOVE" << endl;
						return RESULT_INVALID;
					}
					array<Coord, 5> location = player1.ships[type].shipCoords;
					int top = location[0].first;
					int bottom = location[size - 1].first;
					int right = location[size - 1].second;
					int left = location[0].second;
					if (!checkValidMovePlayer1(top, bottom, right, left, size, location, direction, numSpots)){
						cout << "INVALID MOVE" << endl;
						return RESULT_INVALID;
					}
					for (int i = size - 1; i >= 0; i--) {
						int x = location[i].first;
						int y = location[i].second;
						int upx = location[size - 1 - i].first;
						int upy = location[size - 1 - i].second;
						if (direction == 'u') {
							player1.playerBoard.boardstructure.at(upx - numSpots).at(upy) = player1.playerBoard.boardstructure.at(upx).at(upy);
							player1.playerBoard.boardstructure.at(upx).at(upy) = '-';
							player1.ships[type].shipCoords[size - 1 - i] = make_pair(upx - numSpots, upy);
						} else if (direction == 'd') {
							player1.playerBoard.boardstructure.at(x + numSpots).at(y) = player1.playerBoard.boardstructure.at(x).at(y);
							player1.playerBoard.boardstructure.at(x).at(y) = '-';
							player1.ships[type].shipCoords[i] = make_pair(x + numSpots, y);
						} else if (direction == 'r') {
							player1.playerBoard.boardstructure.at(x).at(y + numSpots) = player1.playerBoard.boardstructure.at(x).at(y);
							player1.playerBoard.boardstructure.at(x).at(y) = '-';
							player1.ships[type].shipCoords[i] = make_pair(x, y + numSpots);
						} else if (direction == 'l') {
							player1.playerBoard.boardstructure.at(upx).at(upy - numSpots) = player1.playerBoard.boardstructure.at(upx).at(upy);
							player1.playerBoard.boardstructure.at(upx).at(upy) = '-';
							player1.ships[type].shipCoords[size - i - 1] = make_pair(upx, upy - numSpots);
						}
					}
					turn++;
					return RESULT_KEEP_PLAYING;
				}

			} else {
				cout << "INVALID MOVE" << endl;
				return RESULT_INVALID;
			}

		} else { //player2 moving
			if (player2.playerBoard.boardstructure.at(position.second).at(position.first) != '-') {
				if (player2.playerBoard.boardstructure.at(position.second).at(position.first) == 'O') {
					int type = 0;
					for (int i = 0; i < 5; i++) {
						array<Coord, 5> player2ships = player2.ships[i].shipCoords;
						for (int j = 0; j < 5; j++) {
							if (player2ships[j].second == position.first && player2ships[j].first == position.second) {
								type = i;
							}
						}
					}
					int size = getShipSizefromint(type);
					if (player2.ships[type].orientation == 'v' && (direction == 'l' || direction == 'r')) {
						cout << "INVALID MOVE" << endl;
						return RESULT_INVALID;
					} else if (player2.ships[type].orientation == 'h' && (direction == 'u' || direction == 'd')) {
						cout << "INVALID MOVE" << endl;
						return RESULT_INVALID;
					}
					array<Coord, 5> location = player2.ships[type].shipCoords;
					int top = location[0].first;
					int bottom = location[size - 1].first;
					int right = location[size - 1].second;
					int left = location[0].second;
					if (!checkValidMovePlayer2(top, bottom, right, left, size, location, direction, numSpots)){
						cout << "INVALID MOVE" << endl;
						return RESULT_INVALID;
					}
					for (int i = size - 1; i >= 0; i--) {
						int x = location[i].first;
						int y = location[i].second;
						int upx = location[size - 1 - i].first;
						int upy = location[size - 1 - i].second;
						if (direction == 'u') {
							player2.playerBoard.boardstructure.at(upx - numSpots).at(upy) = player2.playerBoard.boardstructure.at(upx).at(upy);
							player2.playerBoard.boardstructure.at(upx).at(upy) = '-';
							player2.ships[type].shipCoords[size - 1 - i] = make_pair(upx - numSpots, upy);
						} else if (direction == 'd') {
							player2.playerBoard.boardstructure.at(x + numSpots).at(y) = player2.playerBoard.boardstructure.at(x).at(y);
							player2.playerBoard.boardstructure.at(x).at(y) = '-';
							player2.ships[type].shipCoords[i] = make_pair(x + numSpots, y);
						} else if (direction == 'r') {
							player2.playerBoard.boardstructure.at(x).at(y + numSpots) = player2.playerBoard.boardstructure.at(x).at(y);
							player2.playerBoard.boardstructure.at(x).at(y) = '-';
							player2.ships[type].shipCoords[i] = make_pair(x, y + numSpots);
						} else if (direction == 'l') {
							player2.playerBoard.boardstructure.at(upx).at(upy - numSpots) = player2.playerBoard.boardstructure.at(upx).at(upy);
							player2.playerBoard.boardstructure.at(upx).at(upy) = '-';
							player2.ships[type].shipCoords[size - i - 1] = make_pair(upx, upy - numSpots);
						}
					}
					turn++;
					return RESULT_KEEP_PLAYING;
				} else {
					int type = getShipType(player2.playerBoard.boardstructure.at(position.second).at(position.first));
					int size = getShipSize(player2.playerBoard.boardstructure.at(position.second).at(position.first));
					if (player2.ships[type].orientation == 'v' && (direction == 'l' || direction == 'r')) {
						cout << "INVALID MOVE" << endl;
						return RESULT_INVALID;
					} else if (player2.ships[type].orientation == 'h' && (direction == 'u' || direction == 'd')) {
						cout << "INVALID MOVE" << endl;
						return RESULT_INVALID;
					}
					array<Coord, 5> location = player2.ships[type].shipCoords;
					int top = location[0].first;
					int bottom = location[size - 1].first;
					int right = location[size - 1].second;
					int left = location[0].second;
					if (!checkValidMovePlayer2(top, bottom, right, left, size, location, direction, numSpots)){
						cout << "INVALID MOVE" << endl;
						return RESULT_INVALID;
					}
					for (int i = size - 1; i >= 0; i--) {
						int x = location[i].first;
						int y = location[i].second;
						int upx = location[size - 1 - i].first;
						int upy = location[size - 1 - i].second;
						if (direction == 'u') {
							player2.playerBoard.boardstructure.at(upx - numSpots).at(upy) = player2.playerBoard.boardstructure.at(upx).at(upy);
							player2.playerBoard.boardstructure.at(upx).at(upy) = '-';
							player2.ships[type].shipCoords[size - 1 - i] = make_pair(upx - numSpots, upy);
						} else if (direction == 'd') {
							player2.playerBoard.boardstructure.at(x + numSpots).at(y) = player2.playerBoard.boardstructure.at(x).at(y);
							player2.playerBoard.boardstructure.at(x).at(y) = '-';
							player2.ships[type].shipCoords[i] = make_pair(x + numSpots, y);
						} else if (direction == 'r') {
							player2.playerBoard.boardstructure.at(x).at(y + numSpots) = player2.playerBoard.boardstructure.at(x).at(y);
							player2.playerBoard.boardstructure.at(x).at(y) = '-';
							player2.ships[type].shipCoords[i] = make_pair(x, y + numSpots);
						} else if (direction == 'l') {
							player2.playerBoard.boardstructure.at(upx).at(upy - numSpots) = player2.playerBoard.boardstructure.at(upx).at(upy);
							player2.playerBoard.boardstructure.at(upx).at(upy) = '-';
							player2.ships[type].shipCoords[size - i - 1] = make_pair(upx, upy - numSpots);
						}
					}
					turn++;
					return RESULT_KEEP_PLAYING;
				}

			} else {
				cout << "INVALID MOVE" << endl;
				return RESULT_INVALID;
			}
		}
	}
	return RESULT_KEEP_PLAYING;
}

bool MBattleshipGame::checkValidMovePlayer2(int top, int bottom, int right, int left, int size, array<Coord, 5> location, char direction, int numSpots) {
	if (direction == 'r') {
		if (right + numSpots > 9) {
			return false;
		}
		for (int i = 1; i < numSpots + 1; i++) {
			char check = player2.playerBoard.boardstructure.at(location[size - 1].first).at(location[size - 1].second + i);
			if (check != '-') {
				return false;
			}
		}
	} else if (direction == 'l') {
		if (left - numSpots < 0) {
			return false;
		}
		for (int i = 1; i < numSpots + 1; i++) {
			char check = player2.playerBoard.boardstructure.at(location[0].first).at(location[0].second - i);
			if (check != '-') {
				return false;
			}
		}
	} else if (direction == 'u') {
		if (top - numSpots < 0) {
			return false;
		}
		for (int i = 1; i < numSpots + 1; i++) {
			char check = player2.playerBoard.boardstructure.at(location[0].first - i).at(location[0].second);
			if (check != '-') {
				return false;
			}
		}
	} else if (direction == 'd') {
		if (bottom + numSpots > 9) {
			return false;
		}
		for (int i = 1; i < numSpots + 1; i++) {
			char check = player2.playerBoard.boardstructure.at(location[size - 1].first + i).at(location[size - 1].second);
			if (check != '-') {
				return false;
			}
		}
	} 
	return true;
}

bool MBattleshipGame::checkValidMovePlayer1(int top, int bottom, int right, int left, int size, array<Coord, 5> location, char direction, int numSpots) {
	if (direction == 'r') {
		if (right + numSpots > 9) {
			return false;
		}
		for (int i = 1; i < numSpots + 1; i++) {
			char check = player1.playerBoard.boardstructure.at(location[size - 1].first).at(location[size - 1].second + i);
			if (check != '-') {
				return false;
			}
		}
	} else if (direction == 'l') {
		if (left - numSpots < 0) {
			return false;
		}
		for (int i = 1; i < numSpots + 1; i++) {
			char check = player1.playerBoard.boardstructure.at(location[0].first).at(location[0].second - i);
			if (check != '-') {
				return false;
			}
		}
	} else if (direction == 'u') {
		if (top - numSpots < 0) {
			return false;
		}
		for (int i = 1; i < numSpots + 1; i++) {
			char check = player1.playerBoard.boardstructure.at(location[0].first - i).at(location[0].second);
			if (check != '-') {
				return false;
			}
		}
	} else if (direction == 'd') {
		if (bottom + numSpots > 9) {
			return false;
		}
		for (int i = 1; i < numSpots + 1; i++) {
			char check = player1.playerBoard.boardstructure.at(location[size - 1].first + i).at(location[size - 1].second);
			if (check != '-') {
				return false;
			}
		}
	} 
	return true;
}

int MBattleshipGame::getShipType(char s) {
	if (s == 'A') {
		return 0;
	} else if (s == 'B') {
		return 1;	
	} else if (s == 'C') {
		return 2;	
	} else if (s == 'S') {
		return 3;	
	} else if (s == 'D') {
		return 4;
	}
	return 0;
}

int MBattleshipGame::getShipSize(char s) {
	if (s == 'A') {
		return 5;
	} else if (s == 'B') {
		return 4;	
	} else if (s == 'C') {
		return 3;	
	} else if (s == 'S') {
		return 3;	
	} else if (s == 'D') {
		return 2;
	}
	return 0;
}

int MBattleshipGame::getShipSizefromint(int s) {
	if (s == 0) {
		return 5;
	} else if (s == 1) {
		return 4;	
	} else if (s == 2) {
		return 3;	
	} else if (s == 3) {
		return 3;	
	} else if (s == 3) {
		return 2;
	}
	return 0;
}
