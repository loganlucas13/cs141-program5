/*
------------------------------
| Program 5                  |
| Logan Lucas                |
| CS 141 Spring 2023         |
| Instructor: George Maratos |
------------------------------
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Scrambler.h"
#include "Functions.h"

using namespace std;

int main() {
	srand(0);
    string filename = "dictionary.txt";

    int size;
	cout << "Enter size of board: ";
	cin >> size;
	cout << "\n";

	Scrambler game(filename, size);
	
	cout << "MAIN MENU\n"
		 << "A - Play Game\n"
		 << "B - Display Solution\n";

	char menuOption;
	cout << "\nSelect a menu option: ";
	cin >> menuOption;
	cout << "\n\n";
	switch (toupper(menuOption)) {
		case 'A': {
			cout << game.str() << "\n\n";
	
			string userMove;
			cout << "Enter move (Enter 'X' to quit game): ";
			cin >> userMove;
			cout << "\n";
			while (userMove != "x" && userMove != "X") {
				game.try_move(userMove);
				if (game.is_over()) {
					cout << "You win!\n";
					exit(0);
				}
				cout << "Enter move: ";
				cin >> userMove;
				cout << "\n";
			}
			break;
		}
		
		case 'B': {
			cout << game.display_solution();
			break;
		}
		default: {
			cout << "Invalid menu option\n";
			exit(0);
		}
	}
	return 0;
}