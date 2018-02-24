#pragma once

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

// pcy and a-priori
#define DIR_DATA "data/"
#define FILE_1 DIR_DATA "retail.dat"
#define FILE_2 DIR_DATA "netflix.data"
#define DIM_PAIRS 3
#define DIM_TRIPS 4

// pcy only
#define BUCKET_NUM 100