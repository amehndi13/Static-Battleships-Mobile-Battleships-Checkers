# Lines starting with # are comments

# Some variable definitions to save typing later on
CC = g++
CONSERVATIVE_FLAGS = -std=c++11 -Wall -Wextra -pedantic
DEBUGGING_FLAGS = -g -O0
CFLAGS = $(CONSERVATIVE_FLAGS) $(DEBUGGING_FLAGS)

test_games: test_games.cpp
	$(CC) $(CFLAGS) -c test_games.cpp

# Links the test_hw4b executable
games: main.o User.o BattleshipPlayer.o battleships.o Mbattleship.o checkers.o
	$(CC) $(CFLAGS) $^ -o games 

# Compiles main.cpp into an object file
main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

# Compiles User.cpp into an object file
User.o: User.cpp User.h game.h Mbattleship.h checkers.h battleships.h Ship.h BattleshipPlayer.h
	$(CC) $(CFLAGS) -c User.cpp

Piece.o: Piece.h
	$(CC) $(CFLAGS) -c Piece.h

game.o: game.h
	$(CC) $(CFLAGS) -c game.h

Ship.o: Ship.h
	$(CC) $(CFLAGS) -c Ship.h

# Compiles BattleshipPlayer.cpp into an object file
BattleshipPlayer.o: BattleshipPlayer.cpp BattleshipPlayer.h game.h Ship.h Player.h
	$(CC) $(CFLAGS) -c BattleshipPlayer.cpp

# Compiles battleships.cpp into an object file
battleships.o: battleships.cpp battleships.h game.h Ship.h BattleshipPlayer.h Piece.h BattleshipPlayer.cpp
	$(CC) $(CFLAGS) -c battleships.cpp

# Compiles Mbattleship.cpp into an object file
Mbattleship.o: Mbattleship.cpp Mbattleship.h game.h battleships.h battleships.cpp Ship.h BattleshipPlayer.h Piece.h BattleshipPlayer.cpp
	$(CC) $(CFLAGS) -c Mbattleship.cpp

# Compiles checkers into an object file
checkers.o: checkers.cpp checkers.h checkerPlayer.h game.h
	$(CC) $(CFLAGS) -c checkers.cpp

# 'make clean' will remove intermediate & executable files
clean:
	rm -f *.o games test_games *.gcov

