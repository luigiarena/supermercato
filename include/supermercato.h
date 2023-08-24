#define BUF_SIZE 128

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

typedef struct param {
    int K, C, E, T, P, S1, S2, TP, Q, R;
} param;
