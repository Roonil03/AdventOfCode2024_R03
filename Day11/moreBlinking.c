#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct {
    long long num;
    int blinks;
    long long res;
} Memo;

Memo *mt;
int memoSize;
int memCap;

void initMemo(int cap) {
    mt = (Memo *)malloc(sizeof(Memo) * cap);
    memoSize = 0;
    memCap = cap;
}

void freeMemo() {
    free(mt);
}

void addMemo(long long num, int blinks, long long res) {
    if (memoSize == memCap)
    {
        memCap *= 2;
        mt = (Memo *)realloc(mt, sizeof(Memo) * memCap);
    }
    mt[memoSize].num = num;
    mt[memoSize].blinks = blinks;
    mt[memoSize].res = res;
    memoSize++;
}

long long getMemo(long long num, int blinks) {
    for (int i = 0; i < memoSize; i++)
    {
        if (mt[i].num == num && mt[i].blinks == blinks)
        {
            return mt[i].res;
        }
    }
    return -1;
}

long long countStones(long long num, int blinks) {
    if (blinks == 0)
    {
        return 1;
    }
    long long memoResult = getMemo(num, blinks);
    if (memoResult != -1)
    {
        return memoResult;
    }
    long long res = 0;
    if (num == 0)
    {
        res = countStones(1, blinks - 1);
    }
    else if ((int)log10(num) % 2 == 1) 
    {
        int len = (int)log10(num) + 1;
        long long power = pow(10, len / 2);
        long long left = num / power;
        long long right = num % power;
        res = countStones(left, blinks - 1) + countStones(right, blinks - 1);
    }
    else {
        res = countStones(num * 2024, blinks - 1);
    }
    addMemo(num, blinks, res);
    return res;
}

long long* fileInput(int* arrLen) {
    char filename[] = "input11.txt";
    // char filename[] = "test11.txt" ;
    FILE* file = fopen(filename, "r");
    char buffer[128];
    fgets(buffer, sizeof(buffer), file);
    int len = strlen(buffer);
    *arrLen = 0;
    for (int i = 0; i < len; i++) {
        if (buffer[i] == ' ') {
            (*arrLen)++;
        }
    }
    (*arrLen)++;
    long long* res = (long long*)malloc(sizeof(long long) * (*arrLen));
    fclose(file);
    file = fopen(filename, "r");
    int i = 0;
    while (fscanf(file, "%lld", &res[i]) == 1) {
        i++;
    }
    fclose(file);
    return res;
}

int main() {
    initMemo(1024);
    int numStones = 0;
    long long* stones = fileInput(&numStones);
    int blinks = 75;
    long long totalStones = 0;
    for (int i = 0; i < numStones; i++) {
        totalStones += countStones(stones[i], blinks);
    }
    printf("Total stones after %d blinks: %lld\n", blinks, totalStones);
    free(stones);
    freeMemo();
    return EXIT_SUCCESS;
}

