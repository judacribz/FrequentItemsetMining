
#pragma once
#include <map>
#include <vector>
using namespace std;

#pragma once
extern map<int, int> itemCount;
extern vector<int>::iterator i, j, k;
extern vector<int> freqItems;

long getItemsetSize(long n, int dim);

void clearScreen();