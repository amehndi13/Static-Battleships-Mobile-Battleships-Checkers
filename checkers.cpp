//checkers.h
//Anuj Mehndiratta (amehndi1)
//Brennan Schneider (bschne20)
//Garren Angacian (gangaci1)
//April 20, 2016
//CS120 Intermediate Programming

//#ifndef CHECKERS_H
//#define CHECKERS_H
#include "checkers.h"
#include "game.h"
#include "checkerPlayer.h"
#include <vector>
#include <iostream>
#include <array>
#include <map>
#include <string>

using namespace std;


		//Checkers constructor
		CheckersGame :: CheckersGame() {
			Board checkboard(8);
			checkstructure = checkboard.boardstructure;
			player1_chips = {{std::make_pair(1,0), std::make_pair(3,0), std::make_pair(5,0), std::make_pair(7,0),
				std::make_pair(0,1), std::make_pair(2,1), std::make_pair(4,1), std::make_pair(6,1), std::make_pair(1,2), 
				std::make_pair(3,2),std::make_pair(5,2),std::make_pair(7,2)}};
			player2_chips= {{std::make_pair(0,7),std::make_pair(2,7),std::make_pair(4,7),std::make_pair(6,7),
				std::make_pair(1,6),std::make_pair(3,6), std::make_pair(5,6),std::make_pair(7,6),std::make_pair(0,5),
				std::make_pair(2,5),std::make_pair(4,5),std::make_pair(6,5)}};
			vector<vector<char>> :: iterator iter;
			vector<char> :: iterator iter2;
			int j = 0;
			for (iter = checkstructure.begin(); iter != checkstructure.end(); ++iter) {
				int i = 0;
				for (iter2 = (*iter).begin(); iter2 != (*iter).end(); iter2++) {
		            if (j % 2 == 0) {
						if(i % 2 == 0) {
							*(iter2)='+';
						}
					}
					else {
						if (i % 2 == 0)
							*(iter2+1)='+';
					}
					i+=1;
				}//for ter2 loop
				j=j+1;
            }//for iter 1 loop


			for (int i = 0; i < 12; i++) {
               			Coord temp1 = player1_chips[i];
				Coord temp2 = player2_chips[i];
                		checkstructure.at(temp1.second).at(temp1.first) = 'X';
                		checkstructure.at(temp2.second).at(temp2.first) = 'O';
            		}
            		setupPlayers();
		} //end of constructor

		//puts all the chips out on the board at the right coordinates
		//player1.chips corresponds to the user player2
		void CheckersGame :: setupPlayers(){
			for (int i = 0; i < 12; i++) {
				player1.chips[player1_chips[i]]='r';
				player2.chips[player2_chips[i]]='r';
			}
		}

		//prints the location and type of chips for the given player
		void CheckersGame :: printChips(Player player){ //this should take in type player and then use that for the printing
			for(map<Coord, char>::iterator it=player.chips.begin();it!=player.chips.end();++it){
				cout << it->first.first << "," << it->first.second << " " << it->second << endl;//it->second;
			}
		}

		//move a certain players chips from one Coord to a new Coord
		void CheckersGame :: moveChip(Player &player, Coord currentSpot, Coord newSpot){
			char chipID;
			char status = player.chips[currentSpot];
			chipID=checkstructure.at(currentSpot.second).at(currentSpot.first);
			checkstructure.at(currentSpot.second).at(currentSpot.first) = '-';
			player.chips.erase(currentSpot); //kill chip in old location
			player.chips[newSpot] = status; //add chip in new location
			checkstructure.at(newSpot.second).at(newSpot.first)=chipID;
		}

		//delete a players chips at a given Coord
		void CheckersGame :: deleteChip(Player &player, Coord deadGuy){
			player.chips.erase(deadGuy);
			checkstructure.at(deadGuy.second).at(deadGuy.first) = '-';
		}

		//this was to swithch the xy of a given Coord, used at first but now not used
		Coord CheckersGame :: switchXY(Coord oldXY){
			int oldXcoord=oldXY.first;
			int oldYcoord=oldXY.second;
			Coord target=make_pair(oldYcoord, oldXcoord);
			return target;
		}

		//sees if a piece exists for that player at that coordinate
		bool CheckersGame :: piece_exists(Player player, Coord location){ //gonna need a player
			for(map<Coord, char>::iterator it=player.chips.begin();it!=player.chips.end();++it){
				if(location.first == it->first.first && location.second == it ->first.second) {
					return true;
				}
			}
			return false;
		}

		//makes the given player a king at teh given xy
		void CheckersGame :: makeKing(Player &player, int x, int y) {
			//deleteChip(player, make_pair(x, y));
			player.chips[make_pair(x, y)] = 'k';
		}

		//assumes all chips are kings
		//this function will take in the offense and defense player
		//if the offense player has any chip that is located on the border of the board then it will go through

		bool CheckersGame :: jumpAvailableKing(Player &playerDefense, Player &playerOffense){
			int y;
			int x;
			for(map<Coord, char>::iterator it=playerOffense.chips.begin();it!=playerOffense.chips.end();++it){
				x=it->first.first;
				y=it->first.second;

				if(playerOffense.chips[make_pair(x,y)]=='k'){ //if its a king

					//if you on the left side aka x=0 or one away from the left x=1
					//you can only go right
					if((x == 0) || (x == 1)){
						if(leftSideCheckOpenKing(playerDefense, x, y)){
							return true;
						}
					}

					//if you on the right side aka x=7 or one away from the right x=6
					//you can only go left
					if((x == 7) || (x == 6)){
						if(rightSideCheckOpenKing(playerDefense, x, y)){
							return true;
						}
					}

					//if you on the bottom aka y=7 or one away from the bottom y=6
					//you can only go up
					if((y == 7) || (y == 6)){
						if(bottomCheckOpenKing(playerDefense, x, y)){
							return true;
						}
					}

					//if you on the top aka y=0 or one away from the top y=1
					//you can only go down
					if((y == 0) || (y == 1)){
						if(topCheckOpenKing(playerDefense, x, y)){
							return true;
						}
					}

					if(!( (x==0) || (x==1) || (x==6) || (x==7) || (y==0) || (y==1) || (y==6) || (y==7) )){

						//if its not on any of the borders check all four directions
						if((topRightOtherGuy(playerDefense, x,y)) && (topRightOpen(x+1, y-1))){
							//moveChip(playerOffense, make_pair(x,y), make_pair(x + 2, y - 2));
							//deleteChip(playerDefense, make_pair(x + 1, y - 1));
							return true;
						}

						if((topLeftOtherGuy(playerDefense, x,y)) && (topLeftOpen(x-1, y-1))){
							//moveChip(playerOffense, make_pair(x,y), make_pair(x - 2, y - 2));
							//deleteChip(playerDefense, make_pair(x - 1, y - 1));
							return true;
						}

						if((botRightOtherGuy(playerDefense, x,y)) && (botRightOpen(x+1, y+1))){
							//moveChip(playerOffense, make_pair(x,y), make_pair(x + 2, y + 2));
							//deleteChip(playerDefense, make_pair(x + 1, y + 1));
							return true;
						}

						if((botLeftOtherGuy(playerDefense, x,y)) && (botLeftOpen(x-1, y-1))){
							//moveChip(playerOffense, make_pair(x,y), make_pair(x - 2, y + 2));
							//deleteChip(playerDefense, make_pair(x - 1, y + 1));
							return true;
						}
					} //if its not a special case loop
				}//end if its a king loop
			}//end for loop
			return false;
		}



		//assumesthe chips is a king
		//this function will take in the offense and defense player
		//if the offense player has any chip that is located on the border or center of the board then it will go through and see if it has a jump available from the spot
		bool CheckersGame :: jumpAvailableOneKing(Player &playerDefense, Player &playerOffense,int x, int y){

				if(playerOffense.chips[make_pair(x,y)]=='k'){ //if its a king

					//if you on the left side aka x=0 or one away from the left x=1
					//you can only go right
					if((x == 0) || (x == 1)){
						if(leftSideCheckOpenKing(playerDefense ,x, y)){
							return true;
						}
					}

					//if you on the right side aka x=7 or one away from the right x=6
					//you can only go left
					if((x == 7) || (x == 6)){
						if(rightSideCheckOpenKing(playerDefense, x, y)){
							return true;
						}
					}

					//if you on the bottom aka y=7 or one away from the bottom y=6
					//you can only go up
					if((y == 7) || (y == 6)){
						if(bottomCheckOpenKing(playerDefense, x, y)){
							return true;
						}
					}

					//if you on the top aka y=0 or one away from the top y=1
					//you can only go down
					if((y == 0) || (y == 1)){
						if(topCheckOpenKing(playerDefense, x, y)){
							return true;
						}
					}


					if(!( (x==0) || (x==1) || (x==6) || (x==7) || (y==0) || (y==1) || (y==6) || (y==7) )){

						//if its not on any of the borders check all four directions
						if((topRightOtherGuy(playerDefense, x,y)) && (topRightOpen(x+1, y-1))){
						//	moveChip(playerOffense, make_pair(x,y), make_pair(x + 2, y - 2));
						//	deleteChip(playerDefense, make_pair(x + 1, y - 1));
							return true;
						}

						if((topLeftOtherGuy(playerDefense, x,y)) && (topLeftOpen(x-1, y-1))){
						//	moveChip(playerOffense, make_pair(x,y), make_pair(x - 2, y - 2));
						//	deleteChip(playerDefense, make_pair(x - 1, y - 1));
							return true;
						}

						if((botRightOtherGuy(playerDefense, x,y)) && (botRightOpen(x+1, y+1))){
						//	moveChip(playerOffense, make_pair(x,y), make_pair(x + 2, y + 2));
						//	deleteChip(playerDefense, make_pair(x + 1, y + 1));
							return true;
						}

						if((botLeftOtherGuy(playerDefense, x,y)) && (botLeftOpen(x-1, y-1))){
						//	moveChip(playerOffense, make_pair(x,y), make_pair(x - 2, y + 2));
						//	deleteChip(playerDefense, make_pair(x - 1, y + 1));
							return true;
						}
					}//if its a non edge case loop
				}//end if its a king loop
			//}//end for loop
			return false;
		}


		//see if there is an open space to the top left of the given xy
		//whenever you call checkstructure x and y are mixed up
		bool CheckersGame :: topLeftOpen(int x, int y){
			if(checkstructure.at(y-1).at(x-1) == '-'){
				return true;
			}
			return false;
		}

		//see if there is an open space to the top right of the given xy
		//whenever you call checkstructure x and y are mixed up
		bool CheckersGame :: topRightOpen(int x, int y){
			if(checkstructure.at(y-1).at(x+1) == '-'){
				return true;
			}
			return false;
		}

		//see if there is an open space to the bot left of the given xy
		//whenever you call checkstructure x and y are mixed up
		bool CheckersGame :: botLeftOpen(int x, int y){
			if(checkstructure.at(y+1).at(x-1) == '-'){
				return true;
			}
			return false;
		}

		//see if there is an open space to the bot right of the given xy
		//whenever you call checkstructure x and y are mixed up
		bool CheckersGame :: botRightOpen(int x, int y){
			if(checkstructure.at(y+1).at(x+1) == '-'){
				return true;
			}
			return false;
		}

		//check if there is the given players chip to the top left of the given xy
		bool CheckersGame :: topLeftOtherGuy(Player player, int x, int y){
			return piece_exists(player, make_pair(x-1, y-1));
		}

		//check if there is the given players chip to the top right of the given xy
		bool CheckersGame :: topRightOtherGuy(Player player, int x, int y){
			return piece_exists(player, make_pair(x+1,y-1));
		}

		//check if there is the given players chip to the top left of the given xy
		bool CheckersGame :: botLeftOtherGuy(Player player, int x, int y){
			return piece_exists(player, make_pair(x-1, y+1));
		}

		//check if there is the given players chip to the bottom right of the given xy
		bool CheckersGame :: botRightOtherGuy(Player player, int x, int y){
			return piece_exists(player, make_pair(x+1, y+1));
		}



		//this function will see if there are any jumps open
		//within one move for a king
		//should get called if the king is at x=0
		bool CheckersGame :: leftSideCheckOpenKing(Player &playerDefense, int OffenseX, int OffenseY){
			//top left corner or one away
			if((OffenseY == 0) || (OffenseY==1)){
				if(botRightOtherGuy(playerDefense, OffenseX,OffenseY)){
					if(botRightOpen(OffenseX + 1,OffenseY + 1)){
						return true;
					}
				}
			}
			//bottom left corner or one away
			else if((OffenseY == 7) || (OffenseY == 6)){
				if(topRightOtherGuy(playerDefense, OffenseX,OffenseY)){
					if(topRightOpen(OffenseX + 1,OffenseY - 1)){
						return true;
					}
				}
			}
			//the rest of the left side
			else{
				if(topRightOtherGuy(playerDefense,OffenseX,OffenseY)){
					if(topRightOpen(OffenseX + 1,OffenseY - 1)){
						return true;
					}
				}
				if(botRightOtherGuy(playerDefense,OffenseX,OffenseY)){
					if(botRightOpen(OffenseX + 1,OffenseY + 1)){
						return true;
					}
				}
			}
			return false;
		}


		//this function will see if there are any jumps open
		//within one move for a king
		//should get called if the king is at x=7
		bool CheckersGame :: rightSideCheckOpenKing(Player &playerDefense, int OffenseX, int OffenseY){
			//top right corner or one away
			if((OffenseY == 0) || (OffenseY==1)){
				if(botLeftOtherGuy(playerDefense,OffenseX,OffenseY)){
					if(botLeftOpen(OffenseX - 1, OffenseY + 1)){
						return true;
					}
				}
			}
			//bottom right corner or one away
			else if((OffenseY == 7) || (OffenseY == 6)){
				if(topLeftOtherGuy(playerDefense,OffenseX,OffenseY)){
					if(topLeftOpen(OffenseX - 1,OffenseY - 1)){
						return true;
					}
				}
			}
			//rest of the right side
			else{
				if(botLeftOtherGuy(playerDefense,OffenseX,OffenseY)){
					if(botLeftOpen(OffenseX - 1, OffenseY + 1)){
						return true;
					}
				}
				if(topLeftOtherGuy(playerDefense,OffenseX,OffenseY)){
					if(topLeftOpen(OffenseX - 1,OffenseY - 1)){
						return true;
					}
				}
			}
			return false;
		}

		//this function will see if there are any jumps open
		//within one move for a king
		//should get called if the king is at y=7
		bool CheckersGame :: bottomCheckOpenKing(Player playerDefense, int OffenseX, int OffenseY){
			//bottom left corner
			if((OffenseX == 0)|| (OffenseX == 1)){
				if(topRightOtherGuy(playerDefense,OffenseX,OffenseY)){
					if(topRightOpen(OffenseX + 1,OffenseY - 1)){
						return true;
					}
				}
			}
			//bottom right corner
			else if((OffenseX == 7) || (OffenseX == 6)){
				if(topLeftOtherGuy(playerDefense,OffenseX,OffenseY)){
					if(topLeftOpen(OffenseX - 1,OffenseY - 1)){
						return true;
					}
				}
			}
			//anywhere else along bottom
			else{
				if(topRightOtherGuy(playerDefense,OffenseX,OffenseY)){
					if(topRightOpen(OffenseX + 1, OffenseY - 1)){
						return true;
					}
				}
				if(topLeftOtherGuy(playerDefense,OffenseX,OffenseY)){
					if(topLeftOpen(OffenseX - 1,OffenseY - 1)){
						return true;
					}
				}
			}
			return false;
		}


		//this function will see if there are any jumps open
		//within one move for a king piece
		//should get called if the king is at y=0
		bool CheckersGame :: topCheckOpenKing(Player playerDefense, int OffenseX, int OffenseY){
			//top left corner
			if((OffenseX == 0)|| (OffenseX == 1)){
				if(botRightOtherGuy(playerDefense,OffenseX,OffenseY)){
					if(botRightOpen(OffenseX + 1, OffenseY + 1)){
						return true;
					}
				}
			}
			//top right corner
			else if((OffenseX == 7) || (OffenseX == 6)){
				if(botLeftOtherGuy(playerDefense,OffenseX,OffenseY)){
					if(botLeftOpen(OffenseX - 1, OffenseY + 1)){
						return true;
					}
				}
			}
			//anywhere else on the top
			else{
				if(botRightOtherGuy(playerDefense,OffenseX,OffenseY)){
					if(botRightOpen(OffenseX + 1,OffenseY + 1)){
						return true;
					}
				}
				if(botLeftOtherGuy(playerDefense,OffenseX,OffenseY)){
					if(botLeftOpen(OffenseX - 1,OffenseY + 1)){
						return true;
					}
				}
			}
			return false;
		}

		//will return true if the given move takes the chip to a space -
		//also checks if the piece exists
		// pass in the x and y from the user
		bool CheckersGame :: validMoveToSpace(Player player, int x, int y, string ss){
			if(piece_exists(player,make_pair(x,y))){
				if(ss == "tr"){
					if ((y == 0) ||(x==7)) {
						return false;
					}
					else{
						if(topRightOpen(x,y)){
							return true;
						}
					}
					return false;
				}
				if (ss == "tl") {
					if((y == 0) || (x==0)){
						return false;
					} else {
						if (topLeftOpen(x,y)){
							return true;
						}
					}
					return false;
				}
				if (ss == "br"){
					if((y == 7) ||(x==7)){
						return false;
					}
					else{
						if(botRightOpen(x,y)){
							return true;
						}
					}
					return false;
				}
				if(ss == "bl"){
					if ((y == 7) || (x==0)){
						return false;
					} else {
						if(botLeftOpen(x,y)){
							return true;
						}
					}
					return false;
				}
			} //end if piece exits
			return false; //bc no piece there
		}




		//return true if he has a jump available for our guy called player 1 regular guy at a certain xy
                bool CheckersGame :: nextJumpAvailablePlayer1(Player Dplayer, int x, int y ) {
                        if ( (x==0) || (x==1) ) { //can only jump Right
                            if ( botRightOtherGuy(Dplayer, x, y) && (botRightOpen(x+1, y+1) )) {
                                return true;
                            }
                        }
                        if ( (x==7) || (x==6) ) { //can only jump Left
                            if ( botLeftOtherGuy(Dplayer, x, y) && (botLeftOpen(x-1, y+1) )) {
                                return true;
                            }
                        }
                        if ( (y==7) || (y==6) ) { //can not do a jump
                                return false;
                        }
                        if (!(x==0 || x==1 || x==7 || x==6 || y==7 || y==6)) {
	                        if (botRightOtherGuy(Dplayer, x, y) ) {
	                            if ( botRightOpen(x+1, y+1) ) {
	                                return true;
	                            }
	                        }
	                        if (botLeftOtherGuy(Dplayer, x, y) ) {
	                            if ( botLeftOpen(x-1, y+1) ) {
	                                return true;
	                            }
	                        }
	                    }
                        return false;
                } //end nextJumpAvailablePlayer1 function


		//return true if he has a jump available for our guy called player 2 regular guy at a certain xy
                bool CheckersGame :: nextJumpAvailablePlayer2(Player Dplayer, int x, int y) {
                        if ( (x==0) || (x==1) ) { //can only jump Right
                            if ( topRightOtherGuy(Dplayer, x, y) && (topRightOpen(x+1, y-1) ) ) {
                                return true;
                            }
                        }
                        if ( (x==7) || (x==6) ) { //can only jump Left
                            if ( topLeftOtherGuy(Dplayer, x, y) && (topLeftOpen(x-1, y-1) ) ) {
                                return true;
                            }
                        }
                        if ( (y==1) || (y==0) ) { //can not do a jump
                            return false;
                        }
                        if (!(y==1 ||y==0 || x==6 || x==7 || x==0 || x==1)){
	                        if (topRightOtherGuy(Dplayer, x, y) ) {
	                            if ( topRightOpen(x+1, y-1) ) {
	                                return true;
	                            }
	                        }
	                        if (topLeftOtherGuy(Dplayer, x, y) ) {
	                            if ( topLeftOpen(x-1, y-1) ) {
	                                return true;
	                            }
	                        }
	                    }
                        return false;
                } //end nextJumpAvailablePlayer2 function

		//loop trhough player1s chips and see if there are any jumps avail
                bool CheckersGame :: jumpAvailablePlayer1(Player Oplayer, Player Dplayer) {
                        int y;
                        int x;
                        for(map<Coord, char>::iterator it=Oplayer.chips.begin();it!=Oplayer.chips.end(); ++it){ //run through this player's chips
                                x=it->first.first;
                                y=it->first.second;
                                if (Oplayer.chips[make_pair(x,y)] == 'r') {
	                                if ( (x==0) || (x==1) ) { //can only go Right
	                                    if ((botRightOpen(x+1, y+1) && (botRightOtherGuy(Dplayer, x, y) ))) {
	                                        return true;
	                                    }
	                                }
	                                if ( (x==7) || (x==6) ) {
	                                    if (botLeftOpen(x-1, y+1) && (botLeftOtherGuy(Dplayer, x, y) )) {
	                                        return true;
	                                    }
									}
	                                if ( (y==7) || (y==6) ) {
	                                    return false;
	                                }
	                                if (!(x==0 || x==1 || x==7 || x==6 || y==7 || y==6)) {
		                                if (botRightOtherGuy(Dplayer, x, y) ) {
		                                    if ( botRightOpen(x+1, y+1) ) {
		                                        return true;
		                                    }
		                                }
		                                if (botLeftOtherGuy(Dplayer, x, y) ) {
		                                    if (botLeftOpen(x-1, y+1) ) {
		                                        return true;
		                                    }
		                                }
	                            	}
                           		}
                        } //end for loop
					return false;
                } //end jumpAvailablePlayer1

		//loop through all player2s chips and see if there are any jumps avail
                 bool CheckersGame :: jumpAvailablePlayer2(Player Oplayer, Player Dplayer) {
                        int y;
                        int x;
                        for(map<Coord, char>::iterator it=Oplayer.chips.begin();it!=Oplayer.chips.end(); ++it){ //run through this player's chips
                                x=it->first.first;
                                y=it->first.second;
                                if (Oplayer.chips[make_pair(x,y)] == 'r') {
	                                if ( (x==0) || (x==1) ) { //can only go Right
	                                    if ((topRightOpen(x+1, y-1) && (topRightOtherGuy(Dplayer, x, y) ))) {  
	                                        return true;
	                                    }
	                                }
	                                if ( (x==7) || (x==6) ) {
	                                    if (topLeftOpen(x-1, y-1) && (topLeftOtherGuy(Dplayer, x, y) )) {
	                                        return true;
	                                    }
	                                }
	                                if ( (y==1) || (y==0) ) {
	                                    return false;
	                                }
	                                if (!(y==1 ||y==0 || x==6 || x==7 || x==0 || x==1)){
										if (topRightOtherGuy(Dplayer, x, y) ) {
	                                   		if ( topRightOpen(x+1, y-1) ) {
	                                        	return true;
	                                    	}
	                                	}
	                                	if (topLeftOtherGuy(Dplayer, x, y) ) {
	                                    	if (topLeftOpen(x-1, y-1) ) {
	                                        	return true;
	                                    	}
	                                	}
	                                }
	                            }
                                
                        } //end for loop
					return false;
                } //end jumpAvailablePlayer2


		//pass in the postition that the user gives you and the string the user gives you
		//aka input = xyss
		//position = make_pair(x,y)       ss=ss
		GameResult CheckersGame :: attack_square(Coord position, string ss) {
			//make sure to increment turn if its not an invalid move
			//check position valid if its in the 8 by 8
			int x, y;
			x = position.first;
			y = position.second;
			string finalss=ss;  //just in case i change ss but dont want to
			//see if they chose an xy on the board
			if ((x>7) || (y>7) || (x<0) || (y<0)) {
				cout << "INVALID MOVE" << endl;
				return RESULT_INVALID;
			}
			//our local player 1 stuff(the rules player2)
			if (turn % 2 == 1) {
				//make sure player1 has a piece where they say
				if (!(piece_exists(player1, position))) {
					cout << "INVALID MOVE" << endl;
					return RESULT_INVALID;
				}
				if (player1.chips[position]=='r'){ //if its a normal piece
					if ((ss == "tr") || (ss == "tl")) {
						cout << "INVALID MOVE" << endl;
						return RESULT_INVALID;
					}
					//check if there are jumps available for the selected piece
					bool stillJumps = true;
					int jumpx = x;
					int jumpy = y;
					while (stillJumps) {
						if (ss == "br") {
							if ((botRightOtherGuy(player2, jumpx, jumpy)) && (botRightOpen(jumpx+1, jumpy+1))) {
								moveChip(player1, make_pair(jumpx,jumpy), make_pair(jumpx + 2, jumpy + 2));
								deleteChip(player2, make_pair(jumpx + 1, jumpy + 1));
								cout << "JUMPED" << endl;
								if (player2.chips.size() == 0) {
									cout << "PLAYER 2 WON" << endl;
									return RESULT_PLAYER1_WINS;
								}
								if((jumpy+2)==7){
									makeKing(player1, jumpx+2, jumpy+2);
									cout << "CROWNED" <<endl;
									turn++;
									return RESULT_KEEP_PLAYING;
								}

								if(nextJumpAvailablePlayer1(player2, jumpx + 2, jumpy + 2)){ //player1JumpAvailable not created yet
									cout << "PLAYER 2:";
									string newinput;
									cin >> newinput;
									if(newinput == "q"){
										exit(0);
									}
									int newjumpx=newinput[0]-'0';
									int newjumpy=newinput[1]-'0';
									string newss=newinput.substr(2,2);
									if((newjumpx>7) || (newjumpy>7) || (newjumpx<0) || (newjumpy<0)){
										cout << "INVALID MOVE" << endl;
										return RESULT_INVALID;
									}
									if(!((newjumpx==(jumpx+2))&&(newjumpy==(jumpy+2)))){
										cout << "INVALID MOVE" << endl;
										//cout << "test25" << endl;
										return RESULT_INVALID;
									}
									if ((newss == "tr") || (newss == "tl")) {
										cout << "INVALID MOVE" << endl;
										return RESULT_INVALID;
									}
									ss=newss;
									jumpx=newjumpx;
									jumpy=newjumpy;
									stillJumps=true;
								} //if player 1 jump available after an initial jump taken
								else{//if they didnt have another jump
									turn++;
									return RESULT_KEEP_PLAYING;
								}
							}//if bot right check so he chose br but there wasnt a jump there
							else{
								stillJumps=false;
							}
						}//if ss = br
						else if (ss == "bl"){
							if ((botLeftOtherGuy(player2, jumpx,jumpy)) && (botLeftOpen(jumpx-1, jumpy+1))){
								moveChip(player1, make_pair(jumpx,jumpy), make_pair(jumpx - 2, jumpy + 2));
								deleteChip(player2, make_pair(jumpx - 1, jumpy + 1));
								cout << "JUMPED" << endl;
								if(player2.chips.size() == 0){
									cout << "PLAYER 2 WON" << endl;
									return RESULT_PLAYER1_WINS;
								}
								if((jumpy+2)==7){
									makeKing(player1, jumpx-2, jumpy+2);
									cout << "CROWNED" <<endl;
									turn++;
									return RESULT_KEEP_PLAYING;
								}

								if(nextJumpAvailablePlayer1(player2, jumpx - 2, jumpy + 2)){
									cout << "PLAYER 2:";
									string newinput;
									cin >> newinput;
									if(newinput == "q"){
										exit(0);
									}
									int newjumpx=newinput[0]-'0';
									int newjumpy=newinput[1]-'0';
									string newss=newinput.substr(2,2);
									if((newjumpx>7) || (newjumpy>7) || (newjumpx<0) || (newjumpy<0)){
										cout << "INVALID MOVE" << endl;
										return RESULT_INVALID;
									}
									if(!((newjumpx==(jumpx-2))&&(newjumpy==(jumpy+2)))){
										cout << "INVALID MOVE" << endl;
										return RESULT_INVALID;
									}
									if((newss == "tr") || (newss == "tl")){
										cout << "INVALID MOVE" << endl;
										return RESULT_INVALID;
									}
									ss=newss;
									jumpx=newjumpx;
									jumpy=newjumpy;
									stillJumps=true;
								} //if player 1  jump available after an initial jump taken
								else{//if they didnt have another jump to take after the first one
									turn++;
									return RESULT_KEEP_PLAYING;
								}
							}//end if bot left stuff so he chose bl but there wasnt a jump there
							else{
								stillJumps=false;
							}
						}//end if ss = b1
					}//end while still jumps
				}//end if its a player 1 regular


				//as of now there are no jumps that player 1 could do as a regualr piece


				//if it is a king do king checks
				if(player1.chips[position]=='k'){ //if its a king
					//check if there are jumps available for the selected piece
					bool stillJumps = true;
					int jumpx = x;
					int jumpy = y;
					while (stillJumps) {
						if (ss == "br") {
							if ((botRightOtherGuy(player2, jumpx, jumpy)) && (botRightOpen(jumpx+1, jumpy+1))) {
								moveChip(player1, make_pair(jumpx,jumpy), make_pair(jumpx + 2, jumpy + 2));
								deleteChip(player2, make_pair(jumpx + 1, jumpy + 1));
								cout << "JUMPED" << endl;
								if (player2.chips.size() == 0) {
									cout << "PLAYER 1 WON" << endl;
									return RESULT_PLAYER1_WINS;
								}

								if(jumpAvailableOneKing(player2, player1,jumpx+2, jumpy+2)){ //use king jump available

									cout << "PLAYER 2:";
									string newinput;
									cin >> newinput;
									if(newinput == "q"){
										exit(0);
									}
									int newjumpx=newinput[0]-'0';
									int newjumpy=newinput[1]-'0';
									string newss=newinput.substr(2,2);
									if((newjumpx>7) || (newjumpy>7) || (newjumpx<0) || (newjumpy<0)){
										cout << "INVALID MOVE" << endl;
										return RESULT_INVALID;
									}
									if(!((newjumpx==(jumpx+2))&&(newjumpy==(jumpy+2)))){
										cout << "INVALID MOVE" << endl;
										return RESULT_INVALID;
									}
									ss=newss;
									jumpx=newjumpx;
									jumpy=newjumpy;
									stillJumps=true;
								} //if player 1 jump available after an initial jump taken
								else{//if they didnt have another jump
									turn++;
									return RESULT_KEEP_PLAYING;
								}
							}//if bot right check so he chose br but there wasnt a jump there
							else{
								stillJumps=false;
							}
						}//if ss = br
						else if(ss == "bl"){
							if((botLeftOtherGuy(player2, jumpx,jumpy)) && (botLeftOpen(jumpx-1, jumpy+1))){
								moveChip(player1, make_pair(jumpx,jumpy), make_pair(jumpx - 2, jumpy + 2));
								deleteChip(player2, make_pair(jumpx - 1, jumpy + 1));
								cout << "JUMPED" << endl;
								if(player2.chips.size() == 0){
									cout << "PLAYER 2 WON" << endl;
									return RESULT_PLAYER1_WINS;
								}

								if(jumpAvailableOneKing(player2, player1,jumpx-2, jumpy+2)){ //use next jump available king
									cout << "PLAYER 2:";
									string newinput;
									cin >> newinput;
									if(newinput == "q"){
										exit(0);
									}
									int newjumpx=newinput[0]-'0';
									int newjumpy=newinput[1]-'0';
									string newss=newinput.substr(2,2);
									if((newjumpx>7) || (newjumpy>7) || (newjumpx<0) || (newjumpy<0)){
										cout << "INVALID MOVE" << endl;
										return RESULT_INVALID;
									}
									if(!((newjumpx==(jumpx-2))&&(newjumpy==(jumpy+2)))){
										cout << "INVALID MOVE" << endl;
										return RESULT_INVALID;
									}
									ss=newss;
									jumpx=newjumpx;
									jumpy=newjumpy;
									stillJumps=true;
								} //if player 1  jump available after an initial jump taken
								else{//if they didnt have another jump to take after the first one
									turn++;
									return RESULT_KEEP_PLAYING;
								}
							}//end if bot left stuff so he chose bl but there wasnt a jump there
							else{
								stillJumps=false;
							}
						}//end if ss = b1

						else if(ss == "tr"){
							if((topRightOtherGuy(player2, jumpx,jumpy)) && (topRightOpen(jumpx+1, jumpy-1))){
								moveChip(player1, make_pair(jumpx,jumpy), make_pair(jumpx + 2, jumpy - 2));
								deleteChip(player2, make_pair(jumpx + 1, jumpy - 1));
								cout << "JUMPED" << endl;
								if(player2.chips.size() == 0){
									cout << "PLAYER 2 WON" << endl;
									return RESULT_PLAYER1_WINS;
								}

								if(jumpAvailableOneKing(player2, player1,jumpx+2, jumpy-2)){ //use next jump available king
									cout << "PLAYER 2:";
									string newinput;
									cin >> newinput;
									if(newinput == "q"){
										exit(0);
									}
									int newjumpx=newinput[0]-'0';
									int newjumpy=newinput[1]-'0';
									string newss=newinput.substr(2,2);
									if((newjumpx>7) || (newjumpy>7) || (newjumpx<0) || (newjumpy<0)){
										cout << "INVALID MOVE" << endl;
										return RESULT_INVALID;
									}
									if(!((newjumpx==(jumpx+2))&&(newjumpy==(jumpy-2)))){
										cout << "INVALID MOVE" << endl;
										return RESULT_INVALID;
									}
									ss = newss;
									jumpx = newjumpx;
									jumpy = newjumpy;
									stillJumps = true;
								} //if player 1  jump available after an initial jump taken
								else{//if they didnt have another jump to take after the first one
									turn++;
									return RESULT_KEEP_PLAYING;
								}
							}//end if top right stuff so he chose tr but there wasnt a jump there
							else{
								stillJumps=false;
							}
						}//end if ss = tr

						else if(ss == "tl"){
							if((topLeftOtherGuy(player2, jumpx,jumpy)) && (topLeftOpen(jumpx-1, jumpy-1))){
								moveChip(player1, make_pair(jumpx,jumpy), make_pair(jumpx - 2, jumpy - 2));
								deleteChip(player2, make_pair(jumpx - 1, jumpy - 1));
								cout << "JUMPED" << endl;
								if(player2.chips.size() == 0){
									cout << "PLAYER 2 WON" << endl;
									return RESULT_PLAYER1_WINS;
								}

								if(jumpAvailableOneKing(player2, player1,jumpx-2, jumpy-2)){ //use next jump available king
									cout << "PLAYER 2:";
									string newinput;
									cin >> newinput;
									if(newinput == "q"){
										exit(0);
									}
									int newjumpx=newinput[0]-'0';
									int newjumpy=newinput[1]-'0';
									string newss=newinput.substr(2,2);
									if((newjumpx>7) || (newjumpy>7) || (newjumpx<0) || (newjumpy<0)){
										cout << "INVALID MOVE" << endl;
										return RESULT_INVALID;
									}
									if(!((newjumpx == (jumpx-2)) && (newjumpy == (jumpy+2)))){
										cout << "INVALID MOVE" << endl;
										return RESULT_INVALID;
									}
									ss=newss;
									jumpx=newjumpx;
									jumpy=newjumpy;
									stillJumps=true;
								} //if player 1  jump available after an initial jump taken
								else{//if they didnt have another jump to take after the first one
									turn++;
									return RESULT_KEEP_PLAYING;
								}
							}//end if top left stuff so he chose tl but there wasnt a jump there
							else{
								stillJumps=false;
							}
						}//end if ss = tl
					}//end while still jumps
				}//end if its a king


				//you have just checked if his pick was a jump whether it was king or a regular
				//so now if he didnt pick a jump see if he should have seen one and if there is ajump
				//out there that he didnt pick then tell him to go again

				if (player1.chips[position] == 'k') {
					//if there are jumps he didnt pick
					if (jumpAvailableKing(player2, player1)) {
						return RESULT_INVALID;
					}
				}
				if (player1.chips[position]=='r') {
					if (jumpAvailablePlayer1(player1, player2)) {
						return RESULT_INVALID;
					}
				}

				//if there were no jumps available see if the move he gave us will do
				//a regualr move, if so do it, if not say go again
				if (validMoveToSpace(player1, x, y,finalss)) {
					//do the move
					if (finalss=="tr") {
						//do stuff
						moveChip(player1, make_pair(x,y), make_pair(x + 1, y - 1));
						turn++;
						return RESULT_KEEP_PLAYING;
					}

					if (finalss=="tl") {
						//do stuff
						moveChip(player1, make_pair(x,y), make_pair(x - 1, y - 1));
						turn++;
						return RESULT_KEEP_PLAYING;
					}

					if (finalss=="br") {
						//do stuff
						moveChip(player1, make_pair(x,y), make_pair(x + 1, y + 1));
						if(((y+1)== 7)){
							makeKing(player1, x+1, y+1);
							cout << "CROWNED" << endl;
						}
						turn++;
						return RESULT_KEEP_PLAYING;
					}

					if (finalss=="bl") {
						//do stuff
						moveChip(player1, make_pair(x,y), make_pair(x - 1, y + 1));
						if(((y+1)== 7)){
							makeKing(player1, x-1, y+1);
							cout << "CROWNED" << endl;
						}
						turn++;
						return RESULT_KEEP_PLAYING;
					}
				}//end if valid move to space
				else {
					cout << "INVALID MOVE" << endl;
					return RESULT_INVALID;
				}



			}//end if player 1 turn


		//below is the generic pseudocode for how we went through each player it may be useful to see our logic


		//if turn %2 ==0 then its player 1 and use his player thing
			//see if that piece exists at that coord
			//check ss is in the right direction if its not a king
			//if those pass see if that chip can do a jump with that ss
				//if so do the jump and print jumped
					//if there is amother jump available for that piece
						//say its their turn again
						//prompt them but stay in this loop until no more jumps are available
							//if they reach the end king them and end turn
					//if not see if its a king and king them and return end of turn

			//see if any jumps are available
				//if any are return invalid
				//they ahve to manually pick the jump no helping them

			//if no jumps available
				//see if the jump they gave you is good
					//if it is take it and see if they got kinged and return gameresult
					//if not say invalid

		//else do the same shit for player 2
			//player 2 stuff
			if (turn % 2 == 0) {
				//make sure player1 has a piece where they say
				if (!(piece_exists(player2, position))) {
					cout << "INVALID MOVE" << endl;
					return RESULT_INVALID;
				}
				if (player2.chips[position]=='r'){ //if its a normal piece
					if ((ss == "br") || (ss == "bl")) {
						cout << "INVALID MOVE" << endl;
						return RESULT_INVALID;
					}
					//check if there are jumps available for the selected piece
					bool stillJumps = true;
					int jumpx = x;
					int jumpy = y;
					while (stillJumps) {
						if (ss == "tr") {
							if ((topRightOtherGuy(player1, jumpx, jumpy)) && (topRightOpen(jumpx+1, jumpy-1))) {
								moveChip(player2, make_pair(jumpx,jumpy), make_pair(jumpx + 2, jumpy - 2));
								deleteChip(player1, make_pair(jumpx + 1, jumpy - 1));
								cout << "JUMPED" << endl;
								if (player1.chips.size() == 0) {
									cout << "PLAYER 1 WON" << endl;
									return RESULT_PLAYER2_WINS;
								}
								if((jumpy-2)==0){
									makeKing(player2, jumpx+2, jumpy-2);
									cout << "CROWNED" <<endl;
									turn++;
									return RESULT_KEEP_PLAYING;
								}

								if(nextJumpAvailablePlayer2(player1, jumpx + 2, jumpy - 2)){
									cout << "PLAYER 1:";
									string newinput;
									cin >> newinput;
									if(newinput == "q"){
										exit(0);
									}
									int newjumpx=newinput[0]-'0';
									int newjumpy=newinput[1]-'0';
									string newss=newinput.substr(2,2);
									if((newjumpx>7) || (newjumpy>7) || (newjumpx<0) || (newjumpy<0)){
										cout << "INVALID MOVE" << endl;
										return RESULT_INVALID;
									}
									if(!((newjumpx==(jumpx+2))&&(newjumpy==(jumpy-2)))){
										cout << "INVALID MOVE" << endl;
										return RESULT_INVALID;
									}
									if((newss == "br") || (newss == "bl")){
										cout << "INVALID MOVE" << endl;
										return RESULT_INVALID;
									}
									ss=newss;
									jumpx=newjumpx;
									jumpy=newjumpy;
									stillJumps=true;
								} //if player 2 jump available after an initial jump taken
								else{//if they didnt have another jump
									turn++;
									return RESULT_KEEP_PLAYING;
								}
							}//if top right check so he chose tr but there wasnt a jump there
							else{
								stillJumps=false;
							}
						}//if ss = tr
						else if(ss == "tl"){
							if((topLeftOtherGuy(player1, jumpx,jumpy)) && (topLeftOpen(jumpx-1, jumpy-1))){
								moveChip(player2, make_pair(jumpx,jumpy), make_pair(jumpx - 2, jumpy - 2));
								deleteChip(player1, make_pair(jumpx - 1, jumpy - 1));
								cout << "JUMPED" << endl;
								if(player1.chips.size() == 0){
									cout << "PLAYER 1 WON" << endl;
									return RESULT_PLAYER2_WINS;
								}
								if((jumpy-2)==0){
									makeKing(player2, jumpx-2, jumpy-2);
									cout << "CROWNED" <<endl;
									turn++;
									return RESULT_KEEP_PLAYING;
								}

								if(nextJumpAvailablePlayer2(player1, jumpx - 2, jumpy - 2)){
									cout << "PLAYER 1:";
									string newinput;
									cin >> newinput;
									if(newinput == "q"){
										exit(0);
									}
									int newjumpx=newinput[0]-'0';
									int newjumpy=newinput[1]-'0';
									string newss=newinput.substr(2,2);
									if ((newjumpx>7) || (newjumpy>7) || (newjumpx<0) || (newjumpy<0)) {
										cout << "INVALID MOVE" << endl;
										return RESULT_INVALID;
									}
									if (!((newjumpx == (jumpx-2)) && (newjumpy==(jumpy-2)))) {
										cout << newjumpy << " " << jumpy << endl;
										cout << newjumpx << " " << jumpx << endl;
 										cout << "INVALID MOVE" << endl;
										return RESULT_INVALID;
									}
									if ((newss == "br") || (newss == "bl")){
										cout << "INVALID MOVE" << endl;
										return RESULT_INVALID;
									}
									ss = newss;
									jumpx = newjumpx;
									jumpy = newjumpy;
									stillJumps = true;
								} //if player 2  jump available after an initial jump taken
								else {//if they didnt have another jump to take after the first one
									turn++;
									return RESULT_KEEP_PLAYING;
								}
							}//end if top left stuff so he chose tl but there wasnt a jump there
							else {
								stillJumps=false;
							}
						}//end if ss = t1
					}//end while still jumps
				}//end if its a player 2 regular


				//as of now there are no jumps that player 2 could do as a regualr piece


				//if it is a king do king checks
				if (player2.chips[position] == 'k') { //if its a king
					//check if there are jumps available for the selected piece
					bool stillJumps = true;
					int jumpx = x;
					int jumpy = y;
					while (stillJumps) {
						if (ss == "br") {
							if ((botRightOtherGuy(player1, jumpx, jumpy)) && (botRightOpen(jumpx+1, jumpy+1))) {
								moveChip(player2, make_pair(jumpx,jumpy), make_pair(jumpx + 2, jumpy + 2));
								deleteChip(player1, make_pair(jumpx + 1, jumpy + 1));
								cout << "JUMPED" << endl;
								if (player1.chips.size() == 0) {
									cout << "PLAYER 1 WON" << endl;
									return RESULT_PLAYER2_WINS;
								}

								if(jumpAvailableOneKing(player1, player2,jumpx+2, jumpy+2)){ //use king jump available
									cout << "PLAYER 1:";
									string newinput;
									cin >> newinput;
									if(newinput == "q"){
										exit(0);
									}
									int newjumpx=newinput[0]-'0';
									int newjumpy=newinput[1]-'0';
									string newss=newinput.substr(2,2);
									if((newjumpx>7) || (newjumpy>7) || (newjumpx<0) || (newjumpy<0)){
										cout << "INVALID MOVE" << endl;
										return RESULT_INVALID;
									}
									if(!((newjumpx==(jumpx+2))&&(newjumpy==(jumpy+2)))){
										cout << "INVALID MOVE" << endl;
										return RESULT_INVALID;
									}
									ss=newss;
									jumpx=newjumpx;
									jumpy=newjumpy;
									stillJumps=true;
								} //if player 2 jump available after an initial jump taken
								else{//if they didnt have another jump
									turn++;
									return RESULT_KEEP_PLAYING;
								}
							}//if bot right check so he chose br but there wasnt a jump there
							else{
								stillJumps=false;
							}
						}//if ss = br
						else if(ss == "bl"){
							if((botLeftOtherGuy(player1, jumpx,jumpy)) && (botLeftOpen(jumpx-1, jumpy+1))){
								moveChip(player2, make_pair(jumpx,jumpy), make_pair(jumpx - 2, jumpy + 2));
								deleteChip(player1, make_pair(jumpx - 1, jumpy + 1));
								cout << "JUMPED" << endl;
								if(player1.chips.size() == 0){
									cout << "PLAYER 1 WON" << endl;
									return RESULT_PLAYER2_WINS;
								}

								if(jumpAvailableOneKing(player1, player2,jumpx-2, jumpy+2)){ //use next jump available king
									cout << "PLAYER 1:";
									string newinput;
									cin >> newinput;
									if(newinput == "q"){
										exit(0);
									}
									int newjumpx=newinput[0]-'0';
									int newjumpy=newinput[1]-'0';
									string newss=newinput.substr(2,2);
									if((newjumpx>7) || (newjumpy>7) || (newjumpx<0) || (newjumpy<0)){
										cout << "INVALID MOVE" << endl;
										return RESULT_INVALID;
									}
									if(!((newjumpx==(jumpx-2))&&(newjumpy==(jumpy+2)))){
										cout << "INVALID MOVE" << endl;
										return RESULT_INVALID;
									}
									ss=newss;
									jumpx=newjumpx;
									jumpy=newjumpy;
									stillJumps=true;
								} //if player 2  jump available after an initial jump taken
								else{//if they didnt have another jump to take after the first one
									turn++;
									return RESULT_KEEP_PLAYING;
								}
							}//end if bot left stuff so he chose bl but there wasnt a jump there
							else{
								stillJumps=false;
							}
						}//end if ss = b1

						else if(ss == "tr"){
							if((topRightOtherGuy(player1, jumpx,jumpy)) && (topRightOpen(jumpx+1, jumpy-1))){
								moveChip(player2, make_pair(jumpx,jumpy), make_pair(jumpx + 2, jumpy - 2));
								deleteChip(player1, make_pair(jumpx + 1, jumpy - 1));
								cout << "JUMPED" << endl;
								if(player1.chips.size() == 0){
									cout << "PLAYER 1 WON" << endl;
									return RESULT_PLAYER2_WINS;
								}

								if(jumpAvailableOneKing(player1, player2,jumpx+2, jumpy-2)){ //use next jump available king
									cout << "PLAYER 1:";
									string newinput;
									cin >> newinput;
									if(newinput == "q"){
										exit(0);
									}
									int newjumpx=newinput[0]-'0';
									int newjumpy=newinput[1]-'0';
									string newss=newinput.substr(2,2);
									if((newjumpx>7) || (newjumpy>7) || (newjumpx<0) || (newjumpy<0)){
										cout << "INVALID MOVE" << endl;
										return RESULT_INVALID;
									}
									if(!((newjumpx==(jumpx+2))&&(newjumpy==(jumpy-2)))){
										cout << "INVALID MOVE" << endl;
										return RESULT_INVALID;
									}
									ss=newss;
									jumpx=newjumpx;
									jumpy=newjumpy;
									stillJumps=true;
								} //if player 2  jump available after an initial jump taken
								else{//if they didnt have another jump to take after the first one
									turn++;
									return RESULT_KEEP_PLAYING;
								}
							}//end if top right stuff so he chose tr but there wasnt a jump there
							else{
								stillJumps=false;
							}
						}//end if ss = tr

						else if(ss == "tl"){
							if((topLeftOtherGuy(player1, jumpx,jumpy)) && (topLeftOpen(jumpx-1, jumpy-1))){
								moveChip(player2, make_pair(jumpx,jumpy), make_pair(jumpx - 2, jumpy - 2));
								deleteChip(player1, make_pair(jumpx - 1, jumpy - 1));
								cout << "JUMPED" << endl;
								if(player1.chips.size() == 0){
									cout << "PLAYER 1 WON" << endl;
									return RESULT_PLAYER2_WINS;
								}

								if(jumpAvailableOneKing(player1, player2,jumpx-2, jumpy-2)){ //use next jump available king
									cout << "PLAYER 1:";
									string newinput;
									cin >> newinput;
									if(newinput == "q"){
										exit(0);
									}
									int newjumpx=newinput[0]-'0';
									int newjumpy=newinput[1]-'0';
									string newss=newinput.substr(2,2);
									if((newjumpx>7) || (newjumpy>7) || (newjumpx<0) || (newjumpy<0)){
										cout << "INVALID MOVE" << endl;
										return RESULT_INVALID;
									}
									if(!((newjumpx==(jumpx-2))&&(newjumpy==(jumpy+2)))){
										cout << "INVALID MOVE" << endl;
										return RESULT_INVALID;
									}
									ss=newss;
									jumpx=newjumpx;
									jumpy=newjumpy;
									stillJumps=true;
								} //if player 2  jump available after an initial jump taken
								else{//if they didnt have another jump to take after the first one
									turn++;
									return RESULT_KEEP_PLAYING;
								}
							}//end if top left stuff so he chose tl but there wasnt a jump there
							else{
								stillJumps=false;
							}
						}//end if ss = tl
					}//end while still jumps
				}//end if its a king


				//you have just checked if his pick was a jump whether it was king or a regular
				//so now if he didnt pick a jump see if he should have seen one and if there is ajump
				//out there that he didnt pick then tell him to go again

				if(player2.chips[position]=='k'){
					//if there are jumps he didnt pick
					if(jumpAvailableKing(player1, player2)){
						cout << "test17" << endl;
						return RESULT_INVALID;
					}
				}
				if(player2.chips[position]=='r'){
					if(jumpAvailablePlayer2(player2, player1)){
						cout << "test18" << endl;
						return RESULT_INVALID;
					}
				}

				//if there were no jumps available see if the move he gave us will do
				//a regualr move, if so do it, if not say go again
				if(validMoveToSpace(player2, x, y,finalss)){
					//do the move
					if(finalss=="tr"){
						//do stuff
						moveChip(player2, make_pair(x,y), make_pair(x + 1, y - 1));
						if(((y-1)== 0)){
							makeKing(player2, x+1, y-1);
							cout << "CROWNED" << endl;
						}
						turn++;
						return RESULT_KEEP_PLAYING;
					}

					if(finalss=="tl"){
						//do stuff
						moveChip(player2, make_pair(x,y), make_pair(x - 1, y - 1));
						if(((y-1)== 0)){
							makeKing(player2, x-1, y-1);
							cout << "CROWNED" << endl;
						}
						turn++;
						return RESULT_KEEP_PLAYING;
					}

					if(finalss=="br"){
						//do stuff
						moveChip(player2, make_pair(x,y), make_pair(x + 1, y + 1));
						turn++;
						return RESULT_KEEP_PLAYING;
					}

					if(finalss=="bl"){
						//do stuff
						moveChip(player2, make_pair(x,y), make_pair(x - 1, y + 1));
						turn++;
						return RESULT_KEEP_PLAYING;
					}
				}//end if valid move to space
				else{
					//cout << "test19" << endl;
					return RESULT_INVALID;
				}


			}//end if player 2 turn

			return RESULT_KEEP_PLAYING;
		}//end attack square

		//Method to print the board. I just used this for debugging purposes
		void CheckersGame :: printBoard() {
			vector<vector<char>> :: iterator it;
			for (it = checkstructure.begin(); it != checkstructure.end(); ++it) {
				for (int i = 0; i < 8; i++) {
					cout << it -> at(i);
				}
				cout << endl;
			}
		}


	const ostream &operator << (const ostream &os, CheckersGame c) {
		c.printBoard();
		return os;	
	}
