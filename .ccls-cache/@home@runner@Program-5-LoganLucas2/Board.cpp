// #include <iostream>
// #include <string>
// #include <vector>
// #include <fstream>
// #include <sstream>
// #include "Scrambler.h"
// #include "Functions.h"
// #include "Board.h"

// using namespace std;

// Board::Board() {
// 	this->size = 0;
// }

// // constructor
// Board::Board(int size) {
// 	this->size = size;
// }

// // sets the chars to be put on the board
// void Board::SetBoardChars(vector<string> words) {
// 	vector<char> charsOnBoard;
	
// 	int charInRow = 0;
// 	for (int i = 0; i < words.size(); i++) {
// 		for (int j = 0; j < words.at(i).size(); j++) {
// 			charsOnBoard.push_back(words.at(i).at(j));
// 			charInRow++;
// 		}
// 		if (size - charInRow > 2) {
// 			charsOnBoard.push_back(' ');
// 			charInRow++;
// 		}
// 		else {
// 			for (int j = 0; j < size - charInRow; j++)
// 				charsOnBoard.push_back(' ');
// 			charInRow = 0;
// 		}
// 	}
// 	this->charsOnBoard = charsOnBoard;
// }

// // returns the chars on the board (for use in Scrambler methods)
// vector<char> Board::GetBoardChars() const {
// 	return charsOnBoard;
// }