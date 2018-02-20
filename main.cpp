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

int main()
{
  map<int, int> itemCount;
  vector<int>::iterator itemIt;
  vector<int>::iterator i, j, k;
  vector<int> basketItems, freqItems;
  bool oneItemExists, twoItemsExist, threeItemsExist;

  string line;
  int supThresh = 200;
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

      for (itemIt = basketItems.begin(); itemIt != basketItems.end(); itemIt++)
      {
        (itemCount.count(*itemIt) > 0) ? itemCount[*itemIt]++ : itemCount[*itemIt] = 1;

        if (itemCount[*itemIt] == supThresh)
        {
          freqItems.push_back(*itemIt);
        }
      }
    }

    ifs.close();
  }
  else
    cout << "Unable to open file";

  int size = freqItems.size();
  cout << size << endl;
  long numItemsets = getItemsetSize(size, PAIRS_DIM);
  cout << numItemsets << endl;

  // Create pairs from frequent items
  int freqPairs[numItemsets][3];
  int l = 0;
  for (int i = 0; i < size; i++)
  {
    for (int j = (i + 1); j < size; j++)
    {
      freqPairs[l][0] = 0;
      freqPairs[l][1] = freqItems[i];
      freqPairs[l][2] = freqItems[j];
      l++;
    }
  }

  // Read in file and get pair frequency
  ifs.open(FILE, ifstream::in);
  if (ifs.good())
  {

    while (getline(ifs, line))
    {
      // Split items in string line and store in vector
      istringstream iss(line);
      basketItems.assign(istream_iterator<int>{iss},
                         istream_iterator<int>());

      for (int i = 0; i < numItemsets; i++)
      {
        oneItemExists = false;
        twoItemsExist = false;

        for (itemIt = basketItems.begin(); itemIt != basketItems.end(); itemIt++)
        {
          if (*itemIt == freqPairs[i][1])
          {
            oneItemExists = true;
          }
          else if (*itemIt == freqPairs[i][2])
          {
            twoItemsExist = true;
          }

          if (oneItemExists && twoItemsExist)
          {
            freqPairs[i][0]++;
            break;
          }
        }
      }
    }

    ifs.close();
  }
  else
    cout << "Unable to open file";

  cout << "Count: " << itemCount.size() << endl;
  cout << "Count: " << freqItems.size() << endl;
  for (int i = 0; i < numItemsets; i++)
  {
    if (freqPairs[i][0] > supThresh)
    {
      cout << "Count(" << freqPairs[i][1] << ", " << freqPairs[i][2] << ")=" << freqPairs[i][0] << endl;
    }
  }

  numItemsets = getItemsetSize(size, TRIPLES_DIM);

  int freqTrips[numItemsets][4];
  l = 0;
  for (i = freqItems.begin(); i != freqItems.end(); i++)
  {
    for (j = i + 1; j != freqItems.end(); j++)
    {
      for (k = j + 1; k != freqItems.end(); k++)
      {
        freqTrips[l][0] = 0;
        freqTrips[l][1] = *i;
        freqTrips[l][2] = *j;
        freqTrips[l++][3] = *k;
      }
    }
  }

  // Read in file and get pair frequency
  ifs.open(FILE, ifstream::in);
  if (ifs.good())
  {
    while (getline(ifs, line))
    {
      // Split items in string line and store in vector
      istringstream iss(line);
      basketItems.assign(istream_iterator<int>{iss}, istream_iterator<int>());

      for (int i = 0; i < numItemsets; i++)
      {
        oneItemExists = false;
        twoItemsExist = false;
        threeItemsExist = false;

        for (itemIt = basketItems.begin(); itemIt != basketItems.end(); itemIt++)
        {
          if (*itemIt == freqTrips[i][1])
          {
            oneItemExists = true;
          }
          else if (*itemIt == freqTrips[i][2])
          {
            twoItemsExist = true;
          }
          else if (*itemIt == freqTrips[i][3])
          {
            threeItemsExist = true;
          }

          if (oneItemExists && twoItemsExist && threeItemsExist)
          {
            freqTrips[i][0]++;
            break;
          }
        }
      }
    }
    ifs.close();
  }
  else
    cout << "Unable to open file";

  for (int i = 0; i < numItemsets; i++)
  {
    if (freqTrips[i][0] > supThresh)
    {
      cout << "Count(" << freqTrips[i][1] << ", " << freqTrips[i][2] << ", " << freqTrips[i][3] << ")=" << freqTrips[i][0] << endl;
    }
  }
  return 0;
}