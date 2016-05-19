//User.h
//Anuj Mehndiratta (amehndi1)
//Brennan Schneider (bschne20)
//Garren Angacian (gangaci1)
//April 20, 2016
//CS120 Intermediate Programming

#ifndef USER_H
#define USER_H
#include <vector>
#include <iostream>
#include <string>
#include <array>
#include "game.h"
#include "Ship.h"
#include "BattleshipPlayer.h"
#include "battleships.h"
#include "Mbattleship.h"
#include "checkers.h"


class User {
    public:
        User();
        //Building each of the ships for the battleship game.
        //Getting the input from the user and making sure its
        //in the appropriate format and using that to make the
        //corresponding ship.
        MBattleshipGame battleshipSetup(std::string type);
        //The main interface for static battleships 
        void staticBattleshipMain(BattleshipGame staticbsg);
        //The main interface for mobile battleships
        void mobileBattleshipMain(MBattleshipGame mobilebsg); 
        //The main for checkers.
    	void checkersmain(CheckersGame static_cg);
    private:
        
};

#endif
