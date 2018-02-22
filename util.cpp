
#include "util.h"

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