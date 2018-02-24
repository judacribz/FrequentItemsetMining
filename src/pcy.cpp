#include "../headers/pcy.h"

const string BUCKET_THRESH_PROMPT = "\nEnter support threshold for buckets: ";

inline int passThroughPcy(int dim, int numItemsets);
inline int hashPcy(int item1, int item2, int bucketNum);
inline bool findItems(int item1, int item2);
inline bool findPair(int item1, int item2, vector<int> &pair);

int arr[BUCKET_NUM];
bitset<BUCKET_NUM> bitmap;
pair<int, int> pairObj;

long pcy(string file, int thresh)
{
    clock_t startTime, endTime;
    bool reEnter;
    int bucketThresh;
    long numItemsets;
    int freqPairCount, freqTripCount;
    filename = file;
    threshold = thresh;

    // 1st pass
    passThroughPcy(0, 1);

    // 2nd pass
    freqPairCount = passThroughPcy(DIM_PAIRS, numItemsets);

    cout << "Buckets: " << endl;
    long sum = 0;
    for (int i = 0; i < BUCKET_NUM; i++)
    {
        cout << arr[i] << "\t";
        sum += arr[i];
    }

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

    bitmap.set();
    for (int i = 0; i < BUCKET_NUM; i++)
    {
        if (arr[i] < bucketThresh)
            bitmap.set(i, 0);
    }

    // 3rd pass
    freqPairCount = passThroughPcy(DIM_TRIPS, numItemsets);

    cout << "Bitmap: " << bitmap << endl;
    printf("Frequent Pairs: %d\n", freqPairCount);

    return endTime - startTime;
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

            // memset(arr, 0, sizeof(arr));

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
                        arr[hashPcy(freqArr[i][1], freqArr[i][2], BUCKET_NUM)]++;
                    }
                }
                else
                {
                    for (int i = 0; i < numItemsets; i++)
                    {
                        if (bitmap[hashPcy(freqArr[i][1], freqArr[i][2], BUCKET_NUM)] && findItems(freqArr[i][1], freqArr[i][2]))
                        {

                            pairObj = make_pair(freqArr[i][1], freqArr[i][2]);
                            if (find(freqPairs.begin(), freqPairs.end(), pairObj) == freqPairs.end())
                            {
                                freqCount++;
                                freqPairs.push_back(pairObj);
                            }
                        }
                    }

                    break;
                }
                break;
            }
        }
        ifs.close();
    }
    else
        cout << "Unable to open file";

    // if (dim != 0)
    //     printItemsets(freqArr, dim, threshold, numItemsets);

    return freqCount;
}

inline int hashPcy(int item1, int item2, int bucketNum)
{
    return (item1 ^ item2) % bucketNum;
}

inline bool findItems(int item1, int item2)
{
    return (find(freqItems.begin(), freqItems.end(), item1) != freqItems.end() &&
            find(freqItems.begin(), freqItems.end(), item2) != freqItems.end());
}

inline bool findPair(int item1, int item2, vector<int> &pair)
{
    return (find(pair.begin(), pair.end(), item1) != pair.end() &&
            find(pair.begin(), pair.end(), item2) != pair.end());
}