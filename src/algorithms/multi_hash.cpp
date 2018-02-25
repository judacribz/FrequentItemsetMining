#include "../../headers/multi_hash.h"

#define DIM_PAIRS2 201

const string BUCKET_THRESH_PROMPT = "\nEnter support threshold for buckets: ";

inline int passThroughMultiHash(int dim, int numItemsets);

long multi_hash(string file, int thresh)
{
    clock_t startTime, endTime, pauseTime = 0;
    bool reEnter;
    int bucketThresh;
    long numItemsets;
    int freqPairCount, freqTripCount;
    filename = file;
    threshold = thresh;

    memset(bucketsArr, 0, sizeof(bucketsArr));
    memset(bucketsArr2, 0, sizeof(bucketsArr2));

    // 1st pass
    // =============================================================
    passThroughMultiHash(0, 1);

    // 2nd pass
    // =============================================================
    bucketNum = BUCKET_NUM;
    freqPairCount = passThroughMultiHash(DIM_PAIRS, numItemsets);

    cout << "Buckets: " << endl;
    long sum = 0;
    for (int i = 0; i < bucketNum; i++)
    {
        cout << bucketsArr[i] << "\t";
        sum += bucketsArr[i];
    }

    // Buckets thresh input (since not using percent yet)
    cout << "\nMean: " << (float)sum / (float)bucketNum << endl;
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
    for (int i = 0; i < bucketNum; i++)
    {
        if (bucketsArr[i] < bucketThresh)
            bitmap1.set(i, 0);
    }

    // 3rd pass
    // =============================================================
    bucketNum = BUCKET_NUM2;
    freqPairCount2 = passThroughMultiHash(DIM_PAIRS2, numItemsets);

    cout << "Buckets2: " << endl;
    sum = 0;
    for (int i = 0; i < bucketNum; i++)
    {
        cout << bucketsArr2[i] << "\t";
        sum += bucketsArr2[i];
    }

    // Buckets thresh input (since not using percent yet)
    cout << "\nMean: " << (float)sum / (float)bucketNum << endl;
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
    bitmap2.set();
    for (int i = 0; i < bucketNum; i++)
    {
        if (bucketsArr2[i] < bucketThresh)
            bitmap2.set(i, 0);
    }

    // 4th pass
    // =============================================================
    freqPairCount = passThroughMultiHash(DIM_TRIPS, numItemsets);

    cout << "Bitmap 1: " << bitmap1 << endl;
    cout << "Bitmap 2: " << bitmap2 << endl;
    printf("Frequent Pairs: %d\n", freqPairCount);

    return pauseTime;
}

inline int passThroughMultiHash(int dim, int numItemsets)
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

                numItemsets = getItemsetSize(basketItems.size(), DIM_PAIRS - 1);

                // Populate 2D array with pairs
                populateTuples(freqArr, basketItems, numItemsets, DIM_PAIRS);

                // Get and store pair count

                if (dim == DIM_PAIRS)
                {
                    for (int i = 0; i < numItemsets; i++)
                    {
                        bucketsArr[hashFunc(freqArr[i][1], freqArr[i][2], bucketNum)]++;
                    }
                }
                else if (dim == DIM_PAIRS2)
                {
                    for (int i = 0; i < numItemsets; i++)
                    {
                        bucketsArr2[hashFunc(freqArr[i][1], freqArr[i][2], bucketNum)]++;
                    }
                }
                else
                {
                    for (int i = 0; i < numItemsets; i++)
                    {
                        if (bitmap1[hashFunc(freqArr[i][1], freqArr[i][2], BUCKET_NUM)] == 1 &&
                            bitmap2[hashFunc(freqArr[i][1], freqArr[i][2], BUCKET_NUM2)] == 1 &&
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
