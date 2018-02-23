#include <cstdlib>
#include <iostream>
#include "../headers/util.h"

using namespace std;

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

map<int, int> itemCount;
vector<int>::iterator i, j, k;
vector<int> freqItems;
vector<int> basketItems;
vector<vector<int>> freqArr;

long getItemsetSize(long n, int dim)
{
    int size = 1, div = 1;
    for (int i = n; i > (n - dim); --i)
    {
        size *= i;
        div *= i - (n - dim);
    }

    // cout << (size / div) << endl;
    return size / div;
}

void clearScreen()
{
    system(CLEAR);
}

int printItemsets(vector<vector<int>> freqArr, int dim, int thresh, int numItemsets)
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

vector<vector<int>> populateTuples(int numItemsets, int dim)
{
    int l = 0;
    vector<vector<int>> freqArr;

    freqArr.resize(numItemsets);
    for (int i = 0; i < numItemsets; ++i)
        freqArr[i].resize(dim);

    for (i = freqItems.begin(); i != freqItems.end(); i++)
    {
        for (j = i + 1; j != freqItems.end(); j++)
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

    return freqArr;
}