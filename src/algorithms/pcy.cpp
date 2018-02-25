#include "../../headers/pcy.h"

const string BUCKET_THRESH_PROMPT = "\nEnter support threshold for buckets: ";

inline int passThroughPcy(int dim, int numItemsets);

long pcy(string file, int thresh)
{
    clock_t startTime, endTime, pauseTime = 0;
    bool reEnter;
    int bucketThresh;
    long numItemsets = 0;
    int freqPairCount;
    filename = file;
    threshold = thresh;

    memset(bucketsArr, 0, sizeof(bucketsArr));

    // 1st pass
    passThroughPcy(0, 1);

    // 2nd pass
    freqPairCount = passThroughPcy(DIM_PAIRS, numItemsets);

    cout << "Buckets: " << endl;
    long sum = 0;
    for (int i = 0; i < BUCKET_NUM; i++)
    {
        cout << bucketsArr[i] << "\t";
        sum += bucketsArr[i];
    }

    // Buckets thresh input (since not using percent yet)
    cout << "\nMean: " << (float)sum / (float)BUCKET_NUM << endl;
    startTime = clock();
    do
    {
        reEnter = false;
        cout << BUCKET_THRESH_PROMPT;

        scanf("%d", &bucketThresh);
        getchar();
        if (bucketThresh < 0)
        {

            reEnter = true;
            cout << "Invalid Entry: Please enter a positive number";
            cout << CONT_POMPT;
            getchar();
        }
    } while (reEnter);
    endTime = clock();
    pauseTime += endTime - startTime;

    //  Set the bit vector
    bitmap1.set();
    for (int i = 0; i < BUCKET_NUM; i++)
    {
        if (bucketsArr[i] < bucketThresh)
            bitmap1.set(i, 0);
    }

    // 3rd pass
    freqPairCount = passThroughPcy(DIM_TRIPS, numItemsets);

    cout << "bitmap1: " << bitmap1 << endl;
    printf("Frequent Pairs: %d\n", freqPairCount);

    return pauseTime;
}

inline int passThroughPcy(int dim, int numItemsets)
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

                numItemsets = getItemsetSize(basketItems.size(), DIM_PAIRS - 1);

                // Populate 2D array with pairs
                populateTuples(freqArr, basketItems, numItemsets, DIM_PAIRS);

                // Get and store pair count

                if (dim == DIM_PAIRS)
                {
                    for (int i = 0; i < numItemsets; i++)
                    {
                        bucketsArr[hashFunc(freqArr[i][1], freqArr[i][2], BUCKET_NUM)]++;
                    }
                }
                else
                {
                    for (int i = 0; i < numItemsets; i++)
                    {
                        if (bitmap1[hashFunc(freqArr[i][1], freqArr[i][2], BUCKET_NUM)] == 1 &&
                            findItems(freqArr[i][1], freqArr[i][2]))
                        {

                            pairObj = make_pair(freqArr[i][1], freqArr[i][2]);
                            if (find(hashPairs.begin(), hashPairs.end(), pairObj) == hashPairs.end())
                            {
                                freqCount++;
                                hashPairs.push_back(pairObj);
                            }
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
