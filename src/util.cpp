#include "../headers/util.h"

using namespace std;

const string CONT_POMPT = "\nPress Enter to continue...";

vector<int>::iterator i, j, k;
vector<int> freqItems, basketItems;

map<int, int> itemCount;

vector<vector<int>> freqArr, freqPairs, freqTrips;
vector<pair<int, int>> hashPairs; // only used by PCY and MultiHash

string filename;
int threshold;

int bucketsArr2[BUCKET_NUM2];
int bucketsArr[BUCKET_NUM];
bitset<BUCKET_NUM> bitmap1;
bitset<BUCKET_NUM2> bitmap2;
pair<int, int> pairObj;
int bucketNum;
long freqPairCount2;

long getItemsetSize(long n, int dim)
{
    int size = 1, diviser = 1;
    for (int i = n; i > (n - dim); --i)
    {
        size *= i;
        diviser *= i - (n - dim);
    }

    return size / diviser;
}

void clearScreen()
{
    system(CLEAR);
}

template <typename T>
void clearMem(T &t)
{
    t.clear();
}

void clearMemory()
{
    clearMem(itemCount);
    clearMem(freqItems);
    clearMem(basketItems);
    clearMem(freqArr);
    clearMem(freqPairs);
    clearMem(freqTrips);
    clearMem(hashPairs);
}

int printItemsets(vector<vector<int>> &freqArr, int dim, int thresh, int numItemsets)
{
    int count = 0;
    for (int i = 0; i < numItemsets; i++)
    {
        if (freqArr[i][0] >= thresh)
        {
            count++;
            cout << "Count(";
            for (int j = 1; j < dim; j++)
            {
                cout << freqArr[i][j];

                cout << ((j < dim - 1) ? ", " : ")=");
            }
            cout << freqArr[i][0] << endl;
        }
    }

    return count;
}

int printItemsets(vector<pair<int, int>> &freqArr)
{
    int count = 0;
    for (vector<pair<int, int>>::iterator it = freqArr.begin(); it != freqArr.end(); it++)
    {
        cout << "(" << it->first << ", " << it->second << ")" << endl;
    }

    return count;
}

void populateTuples(vector<vector<int>> &freqArr, vector<int> &items, int numItemsets, int dim)
{
    int l = 0;

    freqArr.resize(numItemsets);
    for (int i = 0; i < numItemsets; i++)
        freqArr[i].resize(dim);

    for (i = items.begin(); i != items.end(); i++)
    {
        for (j = i + 1; j != items.end(); j++)
        {
            switch (dim)
            {
            case DIM_PAIRS:
                freqArr[l][0] = 0;
                freqArr[l][1] = *i;
                freqArr[l++][2] = *j;
                break;

            case DIM_TRIPS:
                for (k = j + 1; k != freqItems.end(); k++)
                {
                    freqArr[l][0] = 0;
                    freqArr[l][1] = *i;
                    freqArr[l][2] = *j;
                    freqArr[l++][3] = *k;
                }
                break;
            }
        }
    }
}

int hashFunc(int item1, int item2, int bucketNum)
{
    return (item1 ^ item2) % bucketNum;
}

bool findItems(int item1, int item2)
{
    return (find(freqItems.begin(), freqItems.end(), item1) != freqItems.end() &&
            find(freqItems.begin(), freqItems.end(), item2) != freqItems.end());
}

bool findPair(int item1, int item2, vector<int> &pair)
{
    return (find(pair.begin(), pair.end(), item1) != pair.end() &&
            find(pair.begin(), pair.end(), item2) != pair.end());
}