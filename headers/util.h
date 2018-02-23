#pragma once

#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>
#include <ctime>
#include <iostream>
#include <fstream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#include "../headers/definitions.h"

using namespace std;

extern map<int, int> itemCount;
extern vector<int>::iterator i, j, k;
extern vector<int> freqItems, basketItems;
extern vector<vector<int>> freqArr;

extern void clearScreen();
extern long getItemsetSize(long n, int dim);
extern int printItemsets(vector<vector<int>> &freqArr, int dim, int thresh, int numItemsets);
extern void populateTuples(vector<vector<int>> &freqArr, int numItemsets, int dim);