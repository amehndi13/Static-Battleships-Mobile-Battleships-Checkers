//checkers.h
//Anuj Mehndiratta (amehndi1)
//Brennan Schneider (bschne20)
//Garren Angacian (gangaci1)
//April 20, 2016
//CS120 Intermediate Programming

#ifndef CHECKERS_H
#define CHECKERS_H
#include "game.h"
#include "checkerPlayer.h"
#include <vector>
#include <iostream>
#include <array>
#include <map>
#include <string>
#include <ostream>
using std::ostream;
using std::map;
using std::array;
using std::cout;
using std::endl;



class CheckersGame : public Game {
	public:
		//create two player objects for us player 1 is player 2
		//player2 is player 1 bc we started them on opposite sides

		//according to the doc player 1 is supposed to start at bottom
		//player 2 is suppoed to start at top
		//we made it so player1 starts at top and player2 at bottom
		//to fix this we made player2 go first and if player2 wins
		//we return RESULT_PLAYER2_WINS but then if we get this result
		//we print out player1 wins, so the user of the game is never
		//the wiser
		//therefore despite it being confusing in the code since
		//ourplayer 1 is the rules player 2 and our player2 is the rules
		//player 1 the user will see no difference in the game play
		//and the right player will be output to win as the rules say
		Player player1;
		Player player2;

		//Checkers constructor
		CheckersGame();

		//puts all the chips out on the board at the right coordinates
		//player1.chips corresponds to the user player2
		void setupPlayers();

		//prints the location and type of chips for the given player
		void printChips(Player player); //this should take in type player and then use that for the printing

		//move a certain players chips from one Coord to a new Coord
		void moveChip(Player &player, Coord currentSpot, Coord newSpot);

		//delete a players chips at a given Coord
		void deleteChip(Player &player, Coord deadGuy);

		//this was to swithch the xy of a given Coord, used at first but now not used
		Coord switchXY(Coord oldXY);

		//sees if a piece exists for that player at that coordinate
		bool piece_exists(Player player, Coord location); //gonna need a player

		//makes the given player a king at teh given xy
		void makeKing(Player &player, int x, int y) ;

		//assumes all chips are kings
		//this function will take in the offense and defense player
		//if the offense player has any chip that is located on the border of the board then it will go through

		bool jumpAvailableKing(Player &playerDefense, Player &playerOffense);

		//assumesthe chips is a king
		//this function will take in the offense and defense player
		//if the offense player has any chip that is located on the border or center of the board then it will go through and see if it has a jump available from the spot
		bool jumpAvailableOneKing(Player &playerDefense, Player &playerOffense,int x, int y);

		//see if there is an open space to the top left of the given xy
		//whenever you call checkstructure x and y are mixed up
		bool topLeftOpen(int x, int y);

		//see if there is an open space to the top right of the given xy
		//whenever you call checkstructure x and y are mixed up
		bool topRightOpen(int x, int y);

		//see if there is an open space to the bot left of the given xy
		//whenever you call checkstructure x and y are mixed up
		bool botLeftOpen(int x, int y);

		//see if there is an open space to the bot right of the given xy
		//whenever you call checkstructure x and y are mixed up
		bool botRightOpen(int x, int y);

		//check if there is the given players chip to the top left of the given xy
		bool topLeftOtherGuy(Player player, int x, int y);

		//check if there is the given players chip to the top right of the given xy
		bool topRightOtherGuy(Player player, int x, int y);

		//check if there is the given players chip to the top left of the given xy
		bool botLeftOtherGuy(Player player, int x, int y);

		//check if there is the given players chip to the bottom right of the given xy
		bool botRightOtherGuy(Player player, int x, int y);

		//this function will see if there are any jumps open
		//within one move for a king
		//should get called if the king is at x=0
		bool leftSideCheckOpenKing(Player &playerDefense, int OffenseX, int OffenseY);

		//this function will see if there are any jumps open
		//within one move for a king
		//should get called if the king is at x=7
		bool rightSideCheckOpenKing(Player &playerDefense, int OffenseX, int OffenseY);

		//this function will see if there are any jumps open
		//within one move for a king
		//should get called if the king is at y=7
		bool bottomCheckOpenKing(Player playerDefense, int OffenseX, int OffenseY);

		//this function will see if there are any jumps open
		//within one move for a king piece
		//should get called if the king is at y=0
		bool topCheckOpenKing(Player playerDefense, int OffenseX, int OffenseY);

		//will return true if the given move takes the chip to a space -
		//also checks if the piece exists
		// pass in the x and y from the user
		bool validMoveToSpace(Player player, int x, int y, std::string ss);

		//return true if he has a jump available for our guy called player 1 regular guy at a certain xy
                bool nextJumpAvailablePlayer1(Player Dplayer, int x, int y );

		//return true if he has a jump available for our guy called player 2 regular guy at a certain xy
                bool nextJumpAvailablePlayer2(Player Dplayer, int x, int y);

		//loop trhough player1s chips and see if there are any jumps avail
                bool jumpAvailablePlayer1(Player Oplayer, Player Dplayer);

		//loop through all player2s chips and see if there are any jumps avail
                 bool jumpAvailablePlayer2(Player Oplayer, Player Dplayer);

		//pass in the postition that the user gives you and the string the user gives you
		//aka input = xyss
		//position = make_pair(x,y)       ss=ss
		virtual GameResult attack_square(Coord position, std::string ss);

		//Method to print the board. I just used this for debugging purposes
		void printBoard();

	private:
		std::vector<std::vector<char>> checkstructure;
		std::array<Coord, 12> player1_chips;
		std::array<Coord, 12> player2_chips;
};

	const ostream &operator << (const ostream &os, CheckersGame c);

#endif

