#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "pcy.h"
#include "util.h"

using namespace std;

#define SUPP_THRESH 1000
#define FILE "retail.dat"
#define DIM_PAIRS 3
#define DIM_TRIPS 4

// GLOBAL VARS
// ============================================================================
map<int, int> itemCount;
vector<int>::iterator i, j, k;
vector<int> freqItems;
// ============================================================================

void pcy()
{
}

int passThroughData(int dim, int numItemsets)
{
}