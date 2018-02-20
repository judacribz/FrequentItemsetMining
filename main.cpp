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

int factorial(int n) {
  return (n == 1) ? 1 : n * factorial(n - 1);
}

int main()
{
  map<int, int> itemCount;
  vector<int>::iterator itemIt;
  vector<int>::iterator i, j, k;
  vector<int> basketItems, freqItems; 
      bool oneItemExists, twoItemsExist;

  string line;
  int supThresh = 1000;

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
  else cout << "Unable to open file";



  int numItemsets = freqItems.size();
  numItemsets = factorial(numItemsets) / (factorial(2) * factorial(numItemsets - 2));
  uint l = 1;

  // Create pairs from frequent items
  int freqPairs[numItemsets][3];
  l = 0;
  for (i = freqItems.begin(); i != freqItems.end(); i++)
  {
    for (j = i + 1; j != freqItems.end(); j++)
    {
        freqPairs[l][0] = 0;
        freqPairs[l][1] = *i;
        freqPairs[l++][2] = *j;
    }
  }


  // Read in file and get pair frequency
  ifs.open (FILE, ifstream::in);
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
        oneItemExists = false;
        for (int i = 0; i < numItemsets; i++) {
            if (*itemIt == freqPairs[i][1] || *itemIt == freqPairs[i][2]) {
                if (!oneItemExists) {
                    oneItemExists = true;
                } else {
                    freqPairs[i][0]++; 
                    break;
                }
            }
        }
      }
    }

    ifs.close();
  }
  else cout << "Unable to open file";


  cout << "Count: " << itemCount.size() << endl;
  cout << "Count: " << freqItems.size() << endl;
  for (int i = 0; i < numItemsets; i++) {
      if (freqPairs[i][0] > supThresh) {
      cout << "Count(" << freqPairs[i][1] << ", " << freqPairs[i][2] << ")=" << freqPairs[i][0] << endl;
    }
  }

  numItemsets = freqItems.size();
  numItemsets = factorial(numItemsets) / (factorial(3) * factorial(numItemsets - 3));

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
      basketItems.assign(istream_iterator<int>{iss},
                         istream_iterator<int>());


      for (itemIt = basketItems.begin(); itemIt != basketItems.end(); itemIt++)
      {
        oneItemExists = false;
        twoItemsExist = false;
        for (int i = 0; i < numItemsets; i++) {
            if (*itemIt == freqTrips[i][1] || *itemIt == freqTrips[i][2] || *itemIt == freqTrips[i][3]) {
                if (!oneItemExists) {
                  oneItemExists = true;
                } else if (!twoItemsExist) {
                  twoItemsExist = true;
                } else {
                    freqTrips[i][0]++; 
                    break;
                }
            }
        }
      }
    }
    ifs.close();
  }
  else cout << "Unable to open file";


  cout << "Count: " << itemCount.size() << endl;
  cout << "Count: " << freqItems.size() << endl;
  for (int i = 0; i < numItemsets; i++) {
      if (freqTrips[i][0] > supThresh) {
      cout << "Count(" << freqTrips[i][1] << ", " << freqTrips[i][2] << ", " << freqTrips[i][3] <<  ")=" << freqTrips[i][0] << endl;
    }
  }
  return 0;
}