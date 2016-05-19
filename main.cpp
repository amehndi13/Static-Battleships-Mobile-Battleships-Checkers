//main.cpp
//Anuj Mehndiratta (amehndi1)
//Brennan Schneider (bschne20)
//Garren Angacian (gangaci1)
//April 20, 2016
//CS120 Intermediate Programming

#include <vector>
#include <iostream>
#include <array>
#include <cstdlib>
#include <string>
#include "User.h"


int main(void) {
	User user;
	char gametype;
	std::cout << "CHOOSE A GAME:";
	std::cin >> gametype;
	int type = gametype - '0';
	if (gametype == 'q') {
		exit(0);
	}
	while (type != 1 && type != 2 && type != 3) {
		std::cout << "CHOOSE A GAME:";
		std::cin >> gametype;
		type = gametype - '0';
		if (gametype == 'q') {
			exit(0);
		}
	}
	if (type == 1) {
		BattleshipGame game = user.battleshipSetup("static");
		user.staticBattleshipMain(game);
	} else if (type == 2) {
		MBattleshipGame game = user.battleshipSetup("mobile");
		user.mobileBattleshipMain(game);
	} else if (type == 3) {
		CheckersGame game;
		user.checkersmain(game);
	}
}

