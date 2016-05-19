//User.cpp
//Anuj Mehndiratta (amehndi1)
//Brennan Schneider (bschne20)
//Garren Angacian (gangaci1)
//April 20, 2016
//CS120 Intermediate Programming

#include "User.h"
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

using namespace std;

        User::User(){}
        //Building each of the ships for the battleship game.
        //Getting the input from the user and making sure its
        //in the appropriate format and using that to make the
        //corresponding ship.
        MBattleshipGame User :: battleshipSetup(string type) {
            array<Ship, 5> playerxships;
            array<Ship, 5> playeryships;
            BPlayer playerx;
            BPlayer playery;

            string aircraft;
            cout << "PLAYER 1 PLACE AIRCRAFT CARRIER:";
            cin >> aircraft;
            if (aircraft == "q") {
                exit(0);
            } 
            while (aircraft.length() != 3) {
                cout << "PLAYER 1 PLACE AIRCRAFT CARRIER:";
                cin >> aircraft;
                if (aircraft == "q") {
                    exit(0);
                } 
            }
            Ship a = playerx.makeAircraft(aircraft);
            while (!playerx.fillBoard(a)) {
                cout << "PLAYER 1 PLACE AIRCRAFT CARRIER:";
                cin >> aircraft;
                while (aircraft.length() != 3) {
                    cout << "PLAYER 1 PLACE AIRCRAFT CARRIER:";
                    cin >> aircraft;
                    if (aircraft == "q") {
                        exit(0);
                    } 
                }
                a = playerx.makeAircraft(aircraft);
                if (playerx.fillBoard(a)) {
                    break;
                }
            }
            playerxships[0] = a;


            string battleship;
            cout << "PLAYER 1 PLACE BATTLESHIP:";
            cin >> battleship;
            if (battleship == "q") {
                exit(0);
            } 
            while (battleship.length() != 3) {
                cout << "PLAYER 1 PLACE BATTLESHIP:";
                cin >> battleship;
                if (battleship == "q") {
                    exit(0);
                }
            }
            a = playerx.makeBattle(battleship);
            while (!playerx.fillBoard(a)) {
                cout << "PLAYER 1 PLACE BATTLESHIP:";
                cin >> battleship;
                if (battleship == "q") {
                    exit(0);
                }
                while (battleship.length() != 3) {
                    cout << "PLAYER 1 PLACE BATTLESHIP:";
                    cin >> battleship;
                    if (battleship == "q") {
                        exit(0);
                    }
                }
                a = playerx.makeBattle(battleship);
                if (playerx.fillBoard(a)) {
                    break;
                }
            }
            playerxships[1] = a;

            
            string cruiser;
            cout << "PLAYER 1 PLACE CRUISER:";
            cin >> cruiser;
            if (cruiser == "q") {
                exit(0);
            }
            while (cruiser.length() != 3) {
                cout << "PLAYER 1 PLACE CRUISER:";
                cin >> cruiser;
                if (cruiser == "q") {
                    exit(0);
                }
            }
            a = playerx.makeCruiser(cruiser);
            while (!playerx.fillBoard(a)) {
                cout << "PLAYER 1 PLACE CRUISER:";
                cin >> cruiser;
                if (cruiser == "q") {
                    exit(0);
                }
                while (cruiser.length() != 3) {
                    cout << "PLAYER 1 PLACE CRUISER:";
                    cin >> cruiser;
                    if (cruiser == "q") {
                        exit(0);
                    }
                }
                a = playerx.makeCruiser(cruiser);
                if (playerx.fillBoard(a)) {
                    break;
                }
            }
            playerxships[2] = a;


            string submarine;
            cout << "PLAYER 1 PLACE SUBMARINE:";
            cin >> submarine;
            if (submarine == "q") {
                exit(0);
            }
            while (submarine.length() != 3) {
                cout << "PLAYER 1 PLACE SUBMARINE:";
                cin >> submarine;
                if (submarine == "q") {
                    exit(0);
                }
            }
            a = playerx.makeSub(submarine);
            while (!playerx.fillBoard(a)) {
                cout << "PLAYER 1 PLACE SUBMARINE:";
                cin >> submarine;
                if (submarine == "q") {
                    exit(0);
                }
                while (submarine.length() != 3) {
                    cout << "PLAYER 1 PLACE SUBMARINE:";
                    cin >> submarine;
                    if (submarine == "q") {
                        exit(0);
                    }
                }
                a = playerx.makeSub(submarine);
                if (playerx.fillBoard(a)) {
                    break;
                }
            }
            playerxships[3] = a;


            string destroyer;
            cout << "PLAYER 1 PLACE DESTROYER:";
            cin >> destroyer;
            if (destroyer == "q") {
                exit(0);
            }
            while (destroyer.length() != 3) {
                cout << "PLAYER 1 PLACE DESTROYER:";
                cin >> destroyer;
                if (destroyer == "q") {
                    exit(0);
                }
            }
            a = playerx.makeDestroyer(destroyer);
            while (!playerx.fillBoard(a)) {
                cout << "PLAYER 1 PLACE DESTROYER:";
                cin >> destroyer;
                if (destroyer == "q") {
                    exit(0);
                }
                while (destroyer.length() != 3) {
                    cout << "PLAYER 1 PLACE DESTROYER:";
                    cin >> destroyer;
                    if (destroyer == "q") {
                        exit(0);
                    }
                }
                a = playerx.makeDestroyer(destroyer);
                if (playerx.fillBoard(a)) {
                    break;
                }
            }
            playerxships[4] = a;


            string air;
            cout << "PLAYER 2 PLACE AIRCRAFT CARRIER:";
            cin >> air;
            if (air == "q") {
                exit(0);
            }
            while (air.length() != 3) {
                cout << "PLAYER 2 PLACE AIRCRAFT CARRIER:";
                cin >> air;
                if (air == "q") {
                    exit(0);
                }
            }
            a = playery.makeAircraft(air);
            while (!playery.fillBoard(a)) {
                cout << "PLAYER 2 PLACE AIRCRAFT CARRIER:";
                cin >> air;
                if (air == "q") {
                    exit(0);
                }
                while (air.length() != 3) {
                    cout << "PLAYER 2 PLACE AIRCRAFT CARRIER:";
                    cin >> air;
                    if (air == "q") {
                        exit(0);
                    }
                }
                a = playery.makeAircraft(air);
                if (playery.fillBoard(a)) {
                    break;
                }
            }
            playeryships[0] = a;

            
            string battle;
            cout << "PLAYER 2 PLACE BATTLESHIP:";
            cin >> battle;
            if (battle == "q") {
                exit(0);
            }
            while (battle.length() != 3) {
                cout << "PLAYER 2 PLACE BATTLESHIP:";
                cin >> battle;
                if (battle == "q") {
                    exit(0);
                }
            }
            a = playery.makeBattle(battle);
            while (!playery.fillBoard(a)) {
                cout << "PLAYER 2 PLACE BATTLESHIP:";
                cin >> battle;
                if (battle == "q") {
                    exit(0);
                }
                while (battle.length() != 3) {
                    cout << "PLAYER 2 PLACE BATTLESHIP:";
                    cin >> battle;
                    if (battle == "q") {
                        exit(0);
                    }
                }
                a = playery.makeBattle(battle);
                if (playery.fillBoard(a)) {
                    break;
                }
            }
            playeryships[1] = a;

            
            string cruise;
            cout << "PLAYER 2 PLACE CRUISER:";
            cin >> cruise;
            if (cruise == "q") {
                exit(0);
            }
            while (cruise.length() != 3) {
                cout << "PLAYER 2 PLACE CRUISER:";
                cin >> cruise;
                if (cruise == "q") {
                    exit(0);
                }
            }
            a = playery.makeCruiser(cruise);
            while (!playery.fillBoard(a)) {
                cout << "PLAYER 2 PLACE CRUISER:";
                cin >> cruise;
                if (cruise == "q") {
                    exit(0);
                }
                while (cruise.length() != 3) {
                    cout << "PLAYER 2 PLACE CRUISER:";
                    cin >> cruise;
                    if (cruise == "q") {
                        exit(0);
                    }
                }
                a = playery.makeCruiser(cruise);
                if (playery.fillBoard(a)) {
                    break;
                }
            }
            playeryships[2] = a;

            
            string sub;
            cout << "PLAYER 2 PLACE SUBMARINE:";
            cin >> sub;
            if (sub == "q") {
                exit(0);
            }
            while (sub.length() != 3) {
                cout << "PLAYER 2 PLACE SUBMARINE:";
                cin >> sub;
                if (sub == "q") {
                    exit(0);
                }
            }
            a = playery.makeSub(sub);
            while (!playery.fillBoard(a)) {
                cout << "PLAYER 2 PLACE SUBMARINE:";
                cin >> sub;
                if (sub == "q") {
                    exit(0);
                }
                while (sub.length() != 3) {
                    cout << "PLAYER 2 PLACE SUBMARINE:";
                    cin >> sub;
                    if (sub == "q") {
                        exit(0);
                    }
                }
                a = playery.makeSub(sub);
                if (playery.fillBoard(a)) {
                    break;
                }
            }
            playeryships[3] = a;


            string dest;
            cout << "PLAYER 2 PLACE DESTROYER:";
            cin >> dest;
            if (dest == "q") {
                exit(0);
            }
            while (dest.length() != 3) {
                cout << "PLAYER 2 PLACE DESTROYER:";
                cin >> dest;
                if (dest == "q") {
                    exit(0);
                }
            }
            a = playery.makeDestroyer(dest);
            while (!playery.fillBoard(a)) {
                cout << "PLAYER 2 PLACE DESTROYER:";
                cin >> dest;
                if (dest == "q") {
                    exit(0);
                }
                while (dest.length() != 3) {
                    cout << "PLAYER 2 PLACE DESTROYER:";
                    cin >> dest;
                    if (dest == "q") {
                        exit(0);
                    }
                }
                a = playery.makeDestroyer(dest);
                if (playery.fillBoard(a)) {
                    break;
                }
            }
            playeryships[4] = a;

            
            playerx.setShips(playerxships);
            playery.setShips(playeryships);

            if (type == "static") {
                MBattleshipGame bsg(playerx, playery);
                return bsg;
            } else if (type == "mobile") {
                MBattleshipGame bsg(playerx, playery);
                return bsg;
            }
            MBattleshipGame bsg(playerx, playery);
            return bsg;
        }

        //This is the main for the static battleships
        void User :: staticBattleshipMain(BattleshipGame staticbsg) {
            string input = "anuj";
            cout << "BEGIN" << endl;
            while (input != "q") {
                if (staticbsg.turn % 2 == 0) {
                    cout << "PLAYER 1:";
                    cin >> input;
                    if (input == "q") {
                        exit(0);
                    } 
                    while (input.length() != 2) {
                        cout << "INVALID MOVE" << endl;
                        cout << "PLAYER 1:";
                        cin >> input;
                        if (input == "q") {
                            exit(0);
                        } 
                    }
                    int x = input[0] - '0';
                    int y = input[1] - '0';
                    string attack = "attack";
                    Coord pair = make_pair(x,y);
                    GameResult result = staticbsg.attack_square(pair, attack);
                    if (result == RESULT_PLAYER1_WINS) {
                        exit(0);
                    }
                } else {
                    cout << "PLAYER 2:";
                    cin >> input;
                    if (input == "q") {
                        exit(0);
                    }
                    while (input.length() != 2) {
                        cout << "INVALID MOVE" << endl;
                        cout << "PLAYER 2:";
                        cin >> input;
                        if (input == "q") {
                            exit(0);
                        } 
                    }
                    int x = input[0] - '0';
                    int y = input[1] - '0';
                    Coord pair = make_pair(x,y);
                    string attack = "attack";
                    GameResult result = staticbsg.attack_square(pair, attack);
                    if (result == RESULT_PLAYER2_WINS) {
                        exit(0);
                    }
                }
            }
        }
        //This is the main for the mobile version of battleships
        void User :: mobileBattleshipMain(MBattleshipGame mobilebsg) {
            string input = "anuj";
            cout << "BEGIN" << endl;
            while (input != "q") {
                if (mobilebsg.turn % 2 == 0) {
                    cout << "PLAYER 1:";
                    cin >> input;
                    if (input == "q") {
                        exit(0);
                    } 
                    while (input.length() != 2 && input.length() != 4) {
                        cout << "INVALID MOVE" << endl;
                        cout << "PLAYER 1:";
                        cin >> input;
                        if (input == "q") {
                            exit(0);
                        } 
                    }
                    if (input.length() == 2) {
                        int x = input[0] - '0';
                        int y = input[1] - '0';
                        string attack = "attack";
                        Coord pair = make_pair(x,y);
                        GameResult result = mobilebsg.attack_square(pair, attack);
                        if (result == RESULT_PLAYER1_WINS) {
                            exit(0);
                        }
                    } else if (input.length() == 4) {
                        mobilebsg.moveShip(input);
                    }
                } else {
                    cout << "PLAYER 2:";
                    cin >> input;
                    if (input == "q") {
                        exit(0);
                    }
                    while (input.length() != 2 && input.length() != 4) {
                        cout << "INVALID MOVE" << endl;
                        cout << "PLAYER 2:";
                        cin >> input;
                        if (input == "q") {
                            exit(0);
                        } 
                    }
                    if (input.length() == 2) {
                        int x = input[0] - '0';
                        int y = input[1] - '0';
                        Coord pair = make_pair(x,y);
                        string attack = "attack";
                        GameResult result = mobilebsg.attack_square(pair, attack);
                        if (result == RESULT_PLAYER2_WINS) {
                            exit(0);
                        } 
                    } else if (input.length() == 4) {
                        mobilebsg.moveShip(input);
                    }         
                }
            }
        }

        //This is the main for the checkers game
    	void User :: checkersmain(CheckersGame static_cg) {
    		string input = "Garren"; //initialize a string to be changed later
    		cout << "BEGIN" << endl;
    		while (input != "q") {
    			if (static_cg.turn % 2 == 0) { //if player 1!
    				cout << "PLAYER 1:";
    				cin >> input;          //take in input from board (or passed input file)
    				if (input == "q") exit(0);
                    while (input.length() != 4) { //should be 'xyss'
    				    cout << "INVALID MOVE" << endl; //if not 4 chars
    				    cout << "PLAYER 1:"; //let them go again!
    				    cin >> input;
    				    if (input == "q") exit(0);
                    }
        			int x = input[0] - '0'; //conversion of first two chars into ints
        			int y = input[1] - '0';
        			Coord pair = make_pair(x,y); //make a Coord for attack_square function
        			string ss = input.substr(2,2); //make a substring for last two chars in input
        			GameResult result = static_cg.attack_square(pair, ss);
        			if (result == RESULT_INVALID) {
        				cout << "INVALID MOVE" << endl;
        			}
        			if (result == RESULT_PLAYER1_WINS) 
        				 exit(0);
    			} else { //same stuff for other player
    				cout << "PLAYER 2:";
    				cin >> input;
    				if (input == "q") exit(0);
    				while (input.length() != 4) {
    					cout << "INVALID MOVE" << endl;
    					cout << "PLAYER 2:";
    					cin >> input;
    					if (input == "q") exit(0);
    				}
    				int x = input[0] - '0';
    				int y = input[1] - '0';
    				Coord pair = make_pair(x,y);
    				string ss = input.substr(2,2);
    				GameResult result = static_cg.attack_square(pair, ss);
    				if (result == RESULT_PLAYER2_WINS) exit(0);
    				if (result == RESULT_INVALID) {
                        		cout << "INVALID MOVE" << endl;
                    		}
    			} //end else
    		} //end while
    	} //end method



