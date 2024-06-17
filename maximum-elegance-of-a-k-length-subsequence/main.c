#include <string.h>
#include <cstdio>
int cmp(const void *p0, const void *p1){
    return (*(const int **)p1)[0] - (*(const int **)p0)[0];
}

long long findMaximumElegance(int **items, int itemsSize, int *itemsColSize, int k){
    qsort(items, itemsSize, sizeof(int *), cmp);

    int *categorySet = (int *)malloc((itemsSize + 1) * sizeof(int));
    memset(categorySet, 0, (itemsSize + 1) * sizeof(int));
    long long res = 0, profit = 0;
    int *st = (int *)malloc(itemsSize * sizeof(int));
    long long ms = 0, mc = 0;
    for (int i = 0; i < itemsSize; i++){
        if (i < k){
            profit += items[i][0];
            if (categorySet[items[i][1]] == 0) {
                categorySet[items[i][1]] = 1;
                mc++;
            }else{
                st[ms++] = items[i][0];
            }
        }else if (categorySet[items[i][1]] == 0 && ms > 0) {
            profit += items[i][0] - st[--ms];
            categorySet[items[i][1]] = 1;
            mc++;
        }
        res = fmax(res, profit + mc * mc);
    }
    free(st);
    free(categorySet);
    return res;
}
