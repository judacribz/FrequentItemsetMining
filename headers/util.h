#pragma once

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <map>
#include <iostream>
#include <iterator>
#include <sstream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <vector>

#include "../headers/config.h"

using namespace std;

extern const string CONT_POMPT;

extern map<int, int> itemCount;
extern vector<int>::iterator i, j, k;
extern vector<int> freqItems, basketItems;
extern vector<vector<int>> freqArr;
extern vector<pair<int, int>> freqPairs; // only used byPCY

extern string filename;
extern int threshold;

extern void clearScreen();
extern void clearMemory();
extern long getItemsetSize(long n, int dim);
extern int printItemsets(vector<vector<int>> &freqArr, int dim, int thresh, int numItemsets);
extern void populateTuples(vector<vector<int>> &freqArr, vector<int> &items, int numItemsets, int dim);