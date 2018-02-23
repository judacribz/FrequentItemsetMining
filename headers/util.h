#pragma once

#include <map>
#include <vector>
using namespace std;

#define SUPP_THRESH 1000
#define FILE "retail.dat"
#define DIM_PAIRS 3
#define DIM_TRIPS 4

extern map<int, int> itemCount;
extern vector<int>::iterator i, j, k;
extern vector<int> freqItems, basketItems;
extern vector<vector<int>> freqArr;

extern long getItemsetSize(long n, int dim);

extern void clearScreen();
extern int printItemsets(vector<vector<int>> freqArr, int dim, int thresh, int numItemsets);