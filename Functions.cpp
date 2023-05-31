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
#include "Functions.h"

using namespace std;

// extracts all words from src_file and 
// pushes into a vector<string>
vector<string> ExtractDict(const string& src_file) {
    vector<string> fullDict;
    ifstream src{src_file};
    
    if (!src.is_open()) {
        cout << "Error: File not Found\n";
        exit(0);
    }
    for (string line; getline(src, line);)
        fullDict.push_back(line);
	
    return fullDict;
}

// prints the entire board
string PrintBoard(vector<char> charsOnBoard, int size) {
	string gameBoard;
	stringstream s(gameBoard);
	
	// adds column labels
	s << "    ";
	for (int i = 1; i <= size; i++) {
		s << i;
		if (i != size)
			s << "   ";
	}
	s << "\n" << "   ";

	// adds dashed line
	for (int i = 0; i < size; i++)
		s << "----";
	s << "\n";

	// adds words to board
	int charsPassed = 0;
	for (int i = 0; i < size; i++) {
		s << i + 1 << " ";
		for (int j = 0; j < size; j++) {
			s << "| " << charsOnBoard.at(charsPassed) << " ";
			if (charsPassed + 1 == charsOnBoard.size())
				break;
			charsPassed++;
		}
		s << "|\n";

		s << "   ";
		for (int j = 0; j < size; j++)
			s << "----";
		if (i != size - 1)
			s << "\n";
	}
	return s.str();
}

// does error checking and attempts move
vector<char> TryMove(string cmd, vector<char> charsOnBoard, int size) {
	bool validMove = true;
	
	// checks for correct length
	if (cmd.size() != 3) {
		cout << "INVALID MOVE (LENGTH)\n";
		validMove = false;
	}

	char rowOrCol = toupper(cmd.at(0));
	int rowColNum = cmd.at(1) - 49;
	char direction = toupper(cmd.at(2));

	// checks for valid row/col num
	if (!(rowColNum >= 0 && rowColNum < size)) {
		cout << "INVALID MOVE (ROW/COL NUM)\n";
		validMove = false;
	}

	// row check
	if (rowOrCol == 'R') {
		if (direction != 'L' && direction != 'R') {
			cout << "INVALID MOVE (ROW DIRECTION)\n";
			validMove = false;
		}
	}
	// column check
	else if (rowOrCol == 'C') {
		if (direction != 'U' && direction != 'D') {
			cout << "INVALID MOVE (COL DIRECTION)\n";
			validMove = false;
		}
	}
	// checks for valid move
	else {
		cout << "INVALID MOVE (FIRST CHAR)\n";
		validMove = false;
	}

	// executes the move on the board
	if (validMove) {
		char temp;
		int startIndex;
		// row shifting
		if (rowOrCol == 'R') {
			// left shift
			if (direction == 'L') {
				startIndex = rowColNum * size;
				temp = charsOnBoard.at(startIndex);
				
				for (int i = 0; i < size - 1; i++) 
					charsOnBoard.at(i + startIndex) = charsOnBoard.at(i + 1 + startIndex);
				charsOnBoard.at(size - 1 + startIndex) = temp;
			}
			// right shift
			else if (direction == 'R') {
				startIndex = rowColNum * size + size - 1;
				temp = charsOnBoard.at(startIndex);

				for (int i = startIndex; i > max(startIndex - size, 0); i--)
					charsOnBoard.at(i) = charsOnBoard.at(i - 1);
				charsOnBoard.at(rowColNum * size) = temp;
			}
		}
		// column shifting
		else if (rowOrCol == 'C') {
			// up shift
			if (direction == 'U') {
				startIndex = rowColNum;
				temp = charsOnBoard.at(startIndex);
				
				for (int i = startIndex; i < size * (size - 1); i += size)
					charsOnBoard.at(i) = charsOnBoard.at(i + size);
				charsOnBoard.at(startIndex + size * (size - 1)) = temp;
			}
			// down shift
			else if (direction == 'D') {
				startIndex = rowColNum;
				temp = charsOnBoard.at(startIndex + (size * (size - 1)));

				for (int i = startIndex + (size * (size - 1)); i >= size; i -= size)
					charsOnBoard.at(i) = charsOnBoard.at(i - size);
				charsOnBoard.at(startIndex) = temp;
			}
		}
	}
	return charsOnBoard;
}

// SCRAMBLER-INIT in doc
vector<string> ScramblerInit(int size, vector<string> fullDict) {
	vector<string> randomWords;
	
    for (int i = 0; i < size; i++) { // for each row
        int rowLength = size;
        while (rowLength > 2) { // while row has more than two spaces
            string randomWord = fullDict.at(rand() % fullDict.size()); // picks random word
			if (randomWord.size() <= rowLength && rowLength - randomWord.size() != 3) { // if row has space
				if (rowLength < size) { // if not first word in row
					if (rowLength - randomWord.size() >= 1) {
						randomWords.push_back(randomWord);
						rowLength -= randomWord.size() + 1;
					}
				}
				else { // if first word in row
					randomWords.push_back(randomWord);
	                rowLength -= randomWord.size();
				}
			}
        }
    }
	return randomWords;
}