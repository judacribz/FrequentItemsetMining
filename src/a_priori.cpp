#include "../headers/a_priori.h"

inline int passThroughPriori(int dim, int numItemsets);

long aPriori(string file, int thresh)
{
    int size;
    long numItemsets;
    int freqPairCount, freqTripCount;
    filename = file;
    threshold = thresh;

    // 1st pass
    size = passThroughPriori(0, 1);

    // Populate 2D array with pairs
    numItemsets = getItemsetSize(size, DIM_PAIRS - 1);
    populateTuples(freqArr, freqItems, numItemsets, DIM_PAIRS);

    // 2nd pass
    freqPairCount = passThroughPriori(DIM_PAIRS, numItemsets);

    // Populate 2D array with triples
    numItemsets = getItemsetSize(size, DIM_TRIPS - 1);
    populateTuples(freqArr, freqItems, numItemsets, DIM_TRIPS);

    // 3rd pass
    freqTripCount = passThroughPriori(DIM_TRIPS, numItemsets);

    printf("Frequent Pairs: %d\nFrequent Triples: %d\n", freqPairCount, freqTripCount);

    return 0;
}

inline int passThroughPriori(int dim, int numItemsets)
{
    int freqCount = 0;
    // Read in file and get item frequency
    ifstream ifs(filename, ifstream::in);

    if (ifs.good())
    {
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

                    if (itemCount[*itemIt] == threshold)
                    {
                        freqCount++;
                        freqItems.push_back(*itemIt);
                    }
                }

                break;

                // Check if pair or triple exists in each basket, add to pair count in array
            default:
                int count;

                // Get and store pair count
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

    if (dim != 0)
        freqCount = printItemsets(freqArr, dim, threshold, numItemsets);

    return freqCount;
}