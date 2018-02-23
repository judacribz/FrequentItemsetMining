#include "../headers/a_priori.h"
#include "../headers/pcy.h"
#include "../headers/util.h"

using namespace std;

int main()
{

  clock_t start, end;
  clearScreen();
  start = clock();
  aPriori(FILE_1, SUPP_THRESH);
  end = clock();
  cout << (end - start) / (double)(CLOCKS_PER_SEC) << " seconds" << endl;

  return 0;
}
