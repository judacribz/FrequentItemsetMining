// reading a text file
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

#define FILE "retail.dat"
#define PAIRS_DIM 2
#define TRIPLES_DIM 3
#define SUPP_THRESH 1000

#define RC_FREQ_ITEMS 1
#define RC_FREQ_PAIRS 2
#define RC_FREQ_TRIPS 3

map<int, int> itemCount;
vector<int>::iterator i, j, k;
vector<int> basketItems, freqItems;

bool oneItemExists, twoItemsExist, threeItemsExist;

long numItemsets = 0;

long getItemsetSize(long n, int dim)
{
  int size = 1, div = 1;
  for (int i = n; i > (n - dim); --i)
  {
    size *= i;
    div *= i - (n - dim);
  }

  return size / div;
}

void passThroughData(int dim)
{

  int l = 0;
  int freqArr[numItemsets][dim];

  if (dim > 0)
  {
    // Populate 2d array
    for (i = freqItems.begin(); i != freqItems.end(); i++)
    {
      for (j = i + 1; j != freqItems.end(); j++)
      {
        switch (dim)
        {
        case PAIRS_DIM:
          freqArr[l][0] = 0;
          freqArr[l][1] = *i;
          freqArr[l][2] = *j;

          break;

        case TRIPLES_DIM:

          for (k = j + 1; k != freqItems.end(); k++)
          {
            freqArr[l][0] = 0;
            freqArr[l][1] = *i;
            freqArr[l][2] = *j;
            freqArr[l][3] = *k;
          }

          break;
        }
        l++;
      }
    }
  }

  string line;
  // Read in file and get item frequency
  ifstream ifs;
  ifs.open(FILE, ifstream::in);

  if (ifs.good())
  {
    while (getline(ifs, line))
    {
      // Split items in string line and store in vector
      istringstream iss(line);
      basketItems.assign(istream_iterator<int>{iss},
                         istream_iterator<int>());

      if (dim > 0)
      {
        // Check if pair or triple exists in each basket, add to pair count in array
        int count = 0;
        for (int i = 0; i < numItemsets; i++)
        {

          for (vector<int>::iterator itemIt = basketItems.begin(); itemIt != basketItems.end(); itemIt++)
          {
            for (int j = 1; j <= dim; j++)
            {
              if (*itemIt == freqArr[i][j])
              {
                count++;
                break;
              }
            }

            if (count == 2)
            {
              freqArr[i][0]++;
              count = 0;
              break;
            }
          }
        }
      }
      else
      {
        for (vector<int>::iterator itemIt = basketItems.begin(); itemIt != basketItems.end(); itemIt++)
        {

          (itemCount.count(*itemIt) > 0) ? itemCount[*itemIt]++ : itemCount[*itemIt] = 1;

          if (itemCount[*itemIt] == SUPP_THRESH)
          {
            freqItems.push_back(*itemIt);
          }
        }
      }
    }
    ifs.close();
  }
  else
    cout << "Unable to open file";
}

int main()
{

  passThroughData(0);

  int size = freqItems.size();
  cout << size << endl;

  numItemsets = getItemsetSize(size, PAIRS_DIM);
  cout << numItemsets << endl;

  passThroughData(PAIRS_DIM);

  // for (int i = 0; i < numItemsets; i++)
  // {
  //   if (freqPairs[i][0] > SUPP_THRESH)
  //   {
  //     cout << "Count(" << freqPairs[i][1] << ", " << freqPairs[i][2] << ")=" << freqPairs[i][0] << endl;
  //   }
  // }

  numItemsets = getItemsetSize(size, TRIPLES_DIM);

  passThroughData(TRIPLES_DIM);

  // for (int i = 0; i < numItemsets; i++)
  // {
  //   if (freqTrips[i][0] > SUPP_THRESH)
  //   {
  //     cout << "Count(" << freqTrips[i][1] << ", " << freqTrips[i][2] << ", " << freqTrips[i][3] << ")=" << freqTrips[i][0] << endl;
  //   }
  // }
  return 0;
}