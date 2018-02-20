// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <map>

using namespace std;

#define FILE "retail.dat"

int main()
{
  map<int, int> itemCount;
  vector<int>::iterator itemIt;
  vector<int> basketItems, freqItems; 

  string line;
  int supThresh = 1000;

  // Read in file and get item frequency
  ifstream myfile(FILE);
  if (myfile.is_open())
  { 
    while (getline(myfile, line))
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

    myfile.close();
  }
  else cout << "Unable to open file";


  vector<int>::iterator i, j;
  int numItemsets = freqItems.size();
  numItemsets *= (numItemsets - 1) / 2;
  uint k = 1;

  // Create pairs from frequent items
  int freqPairs[numItemsets][3];
  k = 0;
  for (i = freqItems.begin(); i != freqItems.end(); i++)
  {
    for (j = i + 1; j != freqItems.end(); j++)
    {
        freqPairs[k][0] = 0;
        freqPairs[k][1] = *i;
        freqPairs[k++][2] = *j;
    }
  }


  // Read in file and get pair frequency
  ifstream myfile1(FILE);
  if (myfile1.is_open())
  { 
    bool oneItemExists;
    while (getline(myfile1, line))
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

    myfile1.close();
  }
  else cout << "Unable to open file";


  cout << "Count: " << itemCount.size() << endl;
  cout << "Count: " << freqItems.size() << endl;
  for (int i = 0; i < numItemsets; i++) {
      if (freqPairs[i][0] > 4000) {
      cout << "Count(" << freqPairs[i][1] << ", " << freqPairs[i][2] << ")=" << freqPairs[i][0] << endl;
    }
  }
  return 0;
}