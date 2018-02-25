#include "../headers/a_priori.h"
#include "../headers/pcy.h"
#include "../headers/multi_hash.h"
#include "../headers/util.h"

using namespace std;

#define A_PRIORI '1'
#define PCY '2'
#define MULTI_HASH '3'

#define SUPP_THRESHOLD '1'
#define SUPP_PERCENT '2'
#define EXIT_PROG 'x'

const string PERCENT = "percent";
const string THRESHOLD = "threshold";

const string MAIN_PROMPT = "Frequent Itemset Mining Techniques:\n"
                           "\t1 - A-Priori\n"
                           "\t2 - Park-Chen-Yu\n"
                           "\t3 - Multi-Hash\n\n"
                           "\tx - Exit Program\n"
                           "\nEnter choice : ";

const string THRESH_PROMPT = "Support Types:\n"
                             "\t1 - Support Threshold\n"
                             "\t2 - Support Percent\n\n"
                             "\tx - Exit Program\n"
                             "\nEnter choice : ";

const string THRESH_VAL_PROMPT = "Enter support ";

const string PRINT_PROMPT = "Print pairs?\n"
                            "\t1 - Yes\n"
                            "\t2 - No\n\n"
                            "\nEnter choice : ";

clock_t startTime, endTime;

inline void runAlg(long (*func)(string, int), string file, int thresh);

int main()
{
  long (*algFunc)(string, int);
  char choice;
  long support;
  string suppType;
  bool reEnter;

  do
  {
    do
    {
      reEnter = false;
      clearScreen();
      cout << MAIN_PROMPT;
      scanf(" %c", &choice);
      getchar();

      switch (choice)
      {
      case A_PRIORI:
        algFunc = aPriori;
        break;
      case PCY:
        algFunc = pcy;
        break;
      case MULTI_HASH:
        algFunc = multi_hash;
        break;
      case EXIT_PROG:
        exit(0);
      default:
        reEnter = true;
        cout << "Invalid Entry: Please enter number associated with menu item above";
        cout << CONT_POMPT;
        getchar();
        break;
      }

    } while (reEnter);

    // do
    // {

    //   reEnter = false;
    //   clearScreen();
    //   cout << THRESH_PROMPT;
    //   scanf(" %c", &choice);

    //   switch (choice)
    //   {
    //   case SUPP_THRESHOLD:
    //     suppType = THRESHOLD;
    //     break;
    //   case SUPP_PERCENT:
    //     suppType = PERCENT;
    //     break;
    //   default:

    //     reEnter = true;
    //     cout << "Invalid Entry: Please enter number associated with menu item above";
    //     cout << CONT_POMPT;
    //     getchar();

    //     break;
    //   }
    // } while (reEnter);
    suppType = THRESHOLD;
    do
    {
      reEnter = false;
      clearScreen();
      cout << THRESH_VAL_PROMPT << suppType << ": ";
      scanf("%ld", &support);
      getchar();

      if (support < 1)
      {
        reEnter = true;
        cout << "Invalid Entry: Please enter a support above 0\n";
        cout << CONT_POMPT;
        getchar();
        continue;
      }

      if (suppType == PERCENT)
      {
        if (support > 100)
        {
          reEnter = true;
          cout << "Invalid Entry: Please enter a support percent between 0-100\n";
          cout << CONT_POMPT;
          getchar();
        }
      }
    } while (reEnter);

    runAlg(algFunc, FILE_1, support);

    do
    {
      reEnter = false;
      cout << PRINT_PROMPT;
      int choice;
      cin >> choice;
      getchar();

      switch (choice)
      {
      case 1:
        if (algFunc == aPriori)
        {
          printItemsets(freqPairs, DIM_PAIRS, support, freqPairs.size());
          printItemsets(freqTrips, DIM_TRIPS, support, freqTrips.size());
        }
        else
        {
          printItemsets(hashPairs);
        }
        cout << CONT_POMPT;
        getchar();
        break;
      case 2:
        break;
      default:
        reEnter = true;
        cout << "Invalid Entry: Please enter number associated with menu item above";
        cout << CONT_POMPT;
        getchar();
        clearScreen();
        break;
      }

    } while (reEnter);

    clearMemory();

  } while (true);

  return 0;
}

inline void runAlg(long (*func)(string, int), string file, int thresh)
{
  startTime = clock();
  long promptTime = func(file, thresh);
  endTime = clock();

  cout << (endTime - startTime - promptTime) / (double)(CLOCKS_PER_SEC) << " seconds" << endl;
}
