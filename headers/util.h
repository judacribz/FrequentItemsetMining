#pragma once

#include <algorithm>
#include <bitset>
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
#include <utility>
#include <vector>

#include "../headers/config.h"

using namespace std;

extern const string CONT_POMPT;

extern map<int, int> itemCount;
extern vector<int>::iterator i, j, k;
extern vector<int> freqItems, basketItems;
extern vector<vector<int>> freqArr, freqPairs, freqTrips;
extern vector<pair<int, int>> hashPairs; // only used byPCY

extern string filename;
extern int threshold;

extern int bucketsArr2[BUCKET_NUM2];
extern int bucketsArr[BUCKET_NUM];
extern bitset<BUCKET_NUM> bitmap1;
extern bitset<BUCKET_NUM2> bitmap2;
extern pair<int, int> pairObj;
extern int bucketNum;
extern long freqPairCount2;

extern void clearScreen();
extern void clearMemory();
extern long getItemsetSize(long n, int dim);
extern int printItemsets(vector<vector<int>> &freqArr, int dim, int thresh, int numItemsets);
extern int printItemsets(vector<pair<int, int>> &freqArr);
extern void populateTuples(vector<vector<int>> &freqArr, vector<int> &items, int numItemsets, int dim);

extern int hashFunc(int item1, int item2, int bucketNum);

extern bool findItems(int item1, int item2);

extern bool findPair(int item1, int item2, vector<int> &pair);