#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *distributeCandies(int candies, int num_people, int *returnSize)
{
    int *ret = (int *)malloc(num_people * sizeof(int));
    memset(ret, 0, num_people * sizeof(int));

    int n = 0;
    for (n = 0; candies > n + 1; n++) {
        ret[n % num_people] += (n + 1);
        candies -= (n + 1);
    }
    ret[n % num_people] += candies;
    *returnSize = num_people;

    return ret;
}

int main()
{
    return 0;
}
