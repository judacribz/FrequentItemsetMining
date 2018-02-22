// reading a text file
#include <ctime>
#include <iostream>
#include "a_priori.h"
#include "util.h"

using namespace std;

// ============================================================================

// ============================================================================

// GLOBAL VARS
// ============================================================================

// ============================================================================

// FUNCTIONS
// ============================================================================

long getItemsetSize(long n, int dim);

// ============================================================================

int main()
{

  clock_t start, end;
  clearScreen();
  start = clock();
  aPriori();
  end = clock();
  cout << (end - start) / (double)(CLOCKS_PER_SEC) << " seconds" << endl;

  return 0;
}
