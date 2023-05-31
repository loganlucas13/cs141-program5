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
#include <algorithm>

using namespace std;

#ifndef SCRAMBLER_H
#define SCRAMBLER_H

class Scrambler {
    private:
        string path;
        int size;
		vector<string> words;
		vector<char> charsOnBoard;
		vector<char> startingBoard;
		vector<char> jumbledStartBoard;
		vector<string> pastMoves;

    public:
        // constructor
        Scrambler(const string& path, const int size);

        // required member functions
        string str() const;
        void try_move(const string& cmd);
        bool is_over() const;
        string display_solution() const;
        vector<string> get_words() const;

        // additional member functions
		vector<char> GetBoardChars(vector<string> words) const;
		vector<char> JumbleBoard();
};

#endif