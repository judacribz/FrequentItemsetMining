// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <map>

using namespace std;

int main()
{
  map<int, int> itemCount;
  vector<int>::iterator itemIt;
  vector<int> basketItems, freqItems; 

  string line;
  int supThresh = 1000;

  // Read in file
  ifstream myfile("retail.dat");
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
  int numItems = 1;
  uint k = 1;
  for (k; k < freqItems.size(); k++) {
    numItems *= k;
  }
  int freqPairs[numItems][3];

  k = 0;
  for (i = freqItems.begin(); i != freqItems.end(); i++)
  {
    for (j = (i + 1); j != freqItems.end(); j++)
    {
        freqPairs[k][1] = *i;
        freqPairs[k++][2] = *j;
    }
  }

  cout << "Count: " << itemCount.size() << endl;
  cout << "Count: " << freqItems.size() << endl;

  return 0;
}