#include "../headers/util.h"

using namespace std;

const string CONT_POMPT = "\nPress any key to continue...";

vector<int>::iterator i, j, k;
vector<int> freqItems;
vector<int> basketItems;

map<int, int> itemCount;

vector<vector<int>> freqArr;
vector<pair<int, int>> freqPairs; // only used byPCY

string filename;
int threshold;

long getItemsetSize(long n, int dim)
{
    int size = 1, div = 1;
    for (int i = n; i > (n - dim); --i)
    {
        size *= i;
        div *= i - (n - dim);
    }

    return size / div;
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