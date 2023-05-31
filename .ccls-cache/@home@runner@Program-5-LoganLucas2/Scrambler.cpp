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
#include <sstream>
#include <algorithm>
#include "Scrambler.h"
#include "Functions.h"

using namespace std;

// constructor
Scrambler::Scrambler(const string& path, const int size) {
    this->path = path;
    this->size = size;
	this->words = get_words();
	this->startingBoard = GetBoardChars(this->words);
	this->charsOnBoard = JumbleBoard();
	this->jumbledStartBoard = this->charsOnBoard;
}

// adds chars on board into a vector and adds spaces
vector<char> Scrambler::GetBoardChars(vector<string> words) const {
	vector<char> charsOnBoard;
	
	int charInRow = 0;
	for (int i = 0; i < words.size(); i++) {
		for (int j = 0; j < words.at(i).size(); j++) {
			charsOnBoard.push_back(words.at(i).at(j));
			charInRow++;
		}
		if (size - charInRow > 2) {
			charsOnBoard.push_back(' ');
			charInRow++;
		}
		else {
			for (int j = 0; j < size - charInRow; j++)
				charsOnBoard.push_back(' ');
			charInRow = 0;
		}
	}
	return charsOnBoard;
}

// returns the entire board as a string
string Scrambler::str() const {
	string gameBoard = PrintBoard(this->charsOnBoard, this->size);
	return gameBoard;
}

// accepts the user move and attempts it
// case-insensitive and checks for valid input
void Scrambler::try_move(const string& cmd) {
	vector<char> boardAfterMove;
	if (cmd == "r" || cmd == "R") {
		cout << "RESET\n\n";
		this->charsOnBoard = this->jumbledStartBoard;
	}
	else {
    boardAfterMove = TryMove(cmd, this->charsOnBoard, this->size);
	this->charsOnBoard = boardAfterMove;
	}
	
	cout << PrintBoard(this->charsOnBoard, this->size) << "\n\n";
}

// returns true if game is over (user won or quit)
// returns false if game is not over
bool Scrambler::is_over() const {
	vector<string> tempWords = this->words;
	
	for (int i = 0; i < this->size; i++) {
		string word = "";
		for (int j = 0; j <= this->size; j ++) {
			if (i * size + j < size * size && this->charsOnBoard.at(i * size + j) != ' ' && j != this->size)
				word += string(1, this->charsOnBoard.at(i * size + j));
			else {
				if (find(this->words.begin(), this->words.end(), word) == this->words.end() && word != "") 
					return false;
				word = "";
			}
		}
	}
    return true;
}

// returns a string showing the solution to the game
string Scrambler::display_solution() const {
	string gameBoard = PrintBoard(this->charsOnBoard, this->size);
	int numMoves = this->pastMoves.size();
	vector<char> afterMove = this->charsOnBoard;
	vector<string> movesToSolve;

	// reverses each correct move to show the path to solution
	string move;
	for (int i = 0; i < numMoves; i++) {
		string reverseMove = "";
		move = this->pastMoves.at(numMoves - i - 1);
		char rowOrCol = toupper(move.at(0));
		char dir = toupper(move.at(2));
		if (rowOrCol == 'R') {
			reverseMove += "r" + to_string(move.at(1) - 48);
			if (dir == 'L')
				reverseMove += "r";
			else if (dir == 'R') 
				reverseMove += "l";
		}
		else if (rowOrCol == 'C') {
			reverseMove += "c" + to_string(move.at(1) - 48);
			if (dir == 'U')
				reverseMove += "d";
			else if (dir == 'D')
				reverseMove += "u";
		}
		movesToSolve.push_back(reverseMove);
	}

	// outputs board after each correct move
	for (int i = 0; i < movesToSolve.size(); i++) {
		gameBoard += "\n*** Move " + to_string(i + 1) + " (";
		gameBoard += string(1, movesToSolve.at(i).at(0)) + ",";
		gameBoard += to_string(movesToSolve.at(i).at(1) - 48) + ",";
		gameBoard += string(1, movesToSolve.at(i).at(2)) + ")\n";
		
		afterMove = TryMove(movesToSolve.at(i), afterMove, this->size);
		gameBoard += PrintBoard(afterMove, this->size);
	}
	
	return gameBoard;
}

// returns vector<string> containing
// all words on the jumbled board
vector<string> Scrambler::get_words() const {
	if (this->words.size() == 0) {
		vector<string> fullDict = ExtractDict(this->path);
    	vector<string>randomWords = ScramblerInit(this->size, fullDict);
		return randomWords;
	}
	return this->words;
}

// JUMBLE-BOARD in doc
// returns vector<char> of jumbled characters
vector<char> Scrambler::JumbleBoard() {
	vector<char> jumbledBoard = this->startingBoard;
	
	int x = rand() % 8;
	int nmoves = x + 3;
	
	int idx;
	int rowColNum;
	for (int i = 0; i < nmoves; i++) {
		idx = rand() % jumbledBoard.size();
		// gets row/col that contains random index
		while (idx - this->size >= 0)
			idx -= this->size;
		rowColNum = idx + 1;

		string rowOrCol;
		string dir;
		int temp = rand() % 2;
		// column shift
		if (i % 2 == 0) {
			rowOrCol = "C";
			if (temp == 0)
				dir = "U";
			else
				dir = "D";
		}
		// row shift
		else {
			rowOrCol = "R";
			if (temp == 0) {
				dir = "R";
			}
			else
				dir = "L";
		}
		string cmd = rowOrCol + to_string(rowColNum) + dir;
		this->pastMoves.push_back(cmd);
		jumbledBoard = TryMove(cmd, jumbledBoard, this->size);
	}
	
	return jumbledBoard;
}