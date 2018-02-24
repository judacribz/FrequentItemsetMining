#include "../headers/a_priori.h"
#include "../headers/pcy.h"
#include "../headers/util.h"

using namespace std;

#define A_PRIORI 1
#define PCY 2
#define EXIT_PROG -1

clock_t startTime, endTime;

void runAlg(void (*func)(string, int), string file, int thresh)
{

  startTime = clock();
  func(file, thresh);
  endTime = clock();

  cout << (endTime - startTime) / (double)(CLOCKS_PER_SEC) << " seconds" << endl;
}

int main()
{

  int algChoice = A_PRIORI;
  clearScreen();

  do
  {
    scanf("%d", &algChoice);

    switch (algChoice)
    {
    case A_PRIORI:
      runAlg(aPriori, FILE_1, SUPP_THRESH);

      break;
    case PCY:
      runAlg(pcy, FILE_1, SUPP_THRESH);

      break;
    }

  } while (algChoice != EXIT_PROG);

  return 0;
}
