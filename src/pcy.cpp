#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "../headers/pcy.h"
#include "../headers/util.h"

using namespace std;

int passThroughPcy(int dim, int numItemsets);

int pcy_hash(int item1, int item2, int num);

void pcy()
{
    int size;
    long numItemsets;
    int freqPairCount, freqTripCount;

    size = passThroughPcy(0, 1);
}

int passThroughPcy(int dim, int numItemsets)
{
    int freqCount = 0;

    // Populate 2D array
    int freqArr[numItemsets][dim];
    if (dim > 0)
    {
        int l = 0;

        switch (dim)
        {
        case DIM_PAIRS:
            for (i = freqItems.begin(); i != freqItems.end(); i++)
            {

                for (j = i + 1; j != freqItems.end(); j++)
                {
                    freqArr[l][0] = 0;
                    freqArr[l][1] = *i;
                    freqArr[l++][2] = *j;
                }
            }

            break;

        case DIM_TRIPS:
            for (i = freqItems.begin(); i != freqItems.end(); i++)
            {
                for (j = i + 1; j != freqItems.end(); j++)
                {
                    for (k = j + 1; k != freqItems.end(); k++)
                    {
                        freqArr[l][0] = 0;
                        freqArr[l][1] = *i;
                        freqArr[l][2] = *j;
                        freqArr[l++][3] = *k;
                    }
                }
            }

            break;
        }
    }

    // Read in file and get item frequency
    ifstream ifs(FILE, ifstream::in);
    if (ifs.good())
    {
        vector<int> basketItems;
        string line;
        while (getline(ifs, line))
        {
            // Split items in string line and store in vector
            istringstream iss(line);
            basketItems.assign((istream_iterator<int>)iss,
                               istream_iterator<int>());
            switch (dim)
            {

            // Get frequent items
            case 0:

                for (vector<int>::iterator itemIt = basketItems.begin(); itemIt != basketItems.end(); itemIt++)
                {
                    (itemCount.count(*itemIt) > 0) ? itemCount[*itemIt]++ : itemCount[*itemIt] = 1;

                    if (itemCount[*itemIt] == SUPP_THRESH)
                    {
                        freqCount++;
                        freqItems.push_back(*itemIt);
                    }
                }

                break;

                // Check if pair or triple exists in each basket, add to pair count in array
            default:
                int count = 0;
                for (int i = 0; i < numItemsets; i++)
                {
                    count = 0;
                    for (vector<int>::iterator itemIt = basketItems.begin(); itemIt != basketItems.end(); itemIt++)
                    {
                        for (int j = 1; j < dim; j++)
                        {
                            if (*itemIt == freqArr[i][j])
                            {
                                count++;
                                break;
                            }
                        }

                        if (count == dim - 1)
                        {
                            freqArr[i][0]++;
                            break;
                        }
                    }
                }

                break;
            }
        }
        ifs.close();
    }
    else
        cout << "Unable to open file";

    return freqCount;
}

int pcy_hash(int item1, int item2, int num)
{
    return (item1 ^ item2) % num;
}