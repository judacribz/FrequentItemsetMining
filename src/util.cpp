#include <cstdlib>
#include "../headers/util.h"

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

map<int, int> itemCount;
vector<int>::iterator i, j, k;
vector<int> freqItems;

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