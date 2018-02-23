#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "../headers/a_priori.h"
#include "../headers/util.h"

using namespace std;

#define SUPP_THRESH 1000
#define FILE "retail.dat"
#define DIM_PAIRS 3
#define DIM_TRIPS 4

int passThroughPriori(int dim, int numItemsets);

void aPriori()
{
    int size;
    long numItemsets;
    int freqPairCount, freqTripCount;

    size = passThroughPriori(0, 1);

    numItemsets = getItemsetSize(size, DIM_PAIRS - 1);
    freqPairCount = passThroughPriori(DIM_PAIRS, numItemsets);

    numItemsets = getItemsetSize(size, DIM_TRIPS - 1);
    freqTripCount = passThroughPriori(DIM_TRIPS, numItemsets);
}

int passThroughPriori(int dim, int numItemsets)
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

    if (dim > 0)
    {
        for (int i = 0; i < numItemsets; i++)
        {
            if (freqArr[i][0] >= SUPP_THRESH)
            {
                freqCount++;
                cout << "Count(";
                for (int j = 1; j < dim; j++)
                {
                    cout << freqArr[i][j];

                    cout << ((j < dim - 1) ? ", " : ")=");
                }
                cout << freqArr[i][0] << endl;
            }
        }
    }

    return freqCount;
}