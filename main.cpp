// reading a text file
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "a_priori.h"

using namespace std;

// ============================================================================

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif
// ============================================================================

// FUNCTIONS
// ============================================================================

long getItemsetSize(long n, int dim);

void clearScreen()
{
  system(CLEAR);
}
// ============================================================================

int main()
{

  clock_t start, end;
  clearScreen();
  start = clock();
  a_priori();
  end = clock();
  cout << (end - start) / (double)(CLOCKS_PER_SEC) << " seconds" << endl;

  return 0;
}

void pcy()
{
  // int size;
  // long numItemsets;
  // int freqPairCount, freqTripCount;

  // size = passThroughData(0, 1);
  // numItemsets = getItemsetSize(size, DIM_PAIRS - 1);
  // freqPairCount = passThroughData(DIM_PAIRS, numItemsets);

  // numItemsets = getItemsetSize(size, DIM_TRIPS - 1);
  // freqTripCount = passThroughData(DIM_TRIPS, numItemsets);
}