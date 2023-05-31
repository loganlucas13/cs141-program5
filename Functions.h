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

using namespace std;

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

vector<string> ScramblerInit(int size, vector<string> fullDict);
vector<string> ExtractDict(const string &src_file);

vector<char> JumbleBoard(vector<char> startingChars, int size);
vector<char> TryMove(string cmd, vector<char> charsOnBoard, int size);

string PrintBoard(vector<char> charsOnBoard, int size);

#endif