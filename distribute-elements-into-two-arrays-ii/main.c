#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "uthash.h"

typedef struct
{
    int *tree;
    int  tree_size;
} binary_indexed_tree_t;

binary_indexed_tree_t *create_binary_indexed_tree(int n)
{
    binary_indexed_tree_t *obj =
        (binary_indexed_tree_t *)malloc(sizeof(binary_indexed_tree_t));
    obj->tree = (int *)malloc(sizeof(int) * (n + 1));
    memset(obj->tree, 0, sizeof(int) * (n + 1));
    obj->tree_size = n + 1;

    return obj;
}

void add(binary_indexed_tree_t *obj, int i)
{
    while (i < obj->tree_size) {
        obj->tree[i] += 1;
        i += i & -i;
    }
}

int get(binary_indexed_tree_t *obj, int i)
{
    int res = 0;
    while (i > 0) {
        res += obj->tree[i];
        i &= i - 1;
    }

    return res;
}

static int cmp(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

typedef struct
{
    int            key;
    int            val;
    UT_hash_handle hh;
} hash_item_t;

hash_item_t *hash_find_item(hash_item_t **obj, int key)
{
    hash_item_t *pEntry = NULL;
    HASH_FIND_INT(*obj, &key, pEntry);

    return pEntry;
}

bool hash_add_item(hash_item_t **obj, int key, int val)
{
    if (hash_find_item(obj, key)) {
        return false;
    }
    hash_item_t *pEntry = (hash_item_t *)malloc(sizeof(hash_item_t));
    pEntry->key         = key;
    pEntry->val         = val;
    HASH_ADD_INT(*obj, key, pEntry);

    return true;
}

bool hash_set_item(hash_item_t **obj, int key, int val)
{
    hash_item_t *pEntry = hash_find_item(obj, key);
    if (!pEntry) {
        hash_add_item(obj, key, val);
    } else {
        pEntry->val = val;
    }
    return true;
}

int hash_get_item(hash_item_t **obj, int key, int default_val)
{
    hash_item_t *pEntry = hash_find_item(obj, key);
    if (!pEntry) {
        return default_val;
    }
    return pEntry->val;
}

void hash_free(hash_item_t **obj)
{
    hash_item_t *curr = NULL, *tmp = NULL;
    HASH_ITER(hh, *obj, curr, tmp)
    {
        HASH_DEL(*obj, curr);
        free(curr);
    }
}

int *resultArray(int *nums, int nums_size, int *return_size)
{
    int n = nums_size;
    int sorted_nums[n];
    memcpy(sorted_nums, nums, sizeof(int) * nums_size);
    qsort(sorted_nums, nums_size, sizeof(int), cmp);
    hash_item_t *index = NULL;
    for (int i = 0; i < n; ++i) {
        hash_set_item(&index, sorted_nums[i], i + 1);
    }

    int arr1[n], arr2[n];
    int arr1_size = 0, arr2_size = 0;
    arr1[arr1_size++]            = nums[0];
    arr2[arr2_size++]            = nums[1];
    binary_indexed_tree_t *tree1 = create_binary_indexed_tree(n);
    binary_indexed_tree_t *tree2 = create_binary_indexed_tree(n);
    add(tree1, hash_get_item(&index, nums[0], 0));
    add(tree2, hash_get_item(&index, nums[1], 0));
    for (int i = 2; i < n; ++i) {
        int count1 = arr1_size - get(tree1, hash_get_item(&index, nums[i], 0));
        int count2 = arr2_size - get(tree2, hash_get_item(&index, nums[i], 0));
        if (count1 > count2 || (count1 == count2 && arr1_size <= arr2_size)) {
            arr1[arr1_size++] = nums[i];
            add(tree1, hash_get_item(&index, nums[i], 0));
        } else {
            arr2[arr2_size++] = nums[i];
            add(tree2, hash_get_item(&index, nums[i], 0));
        }
    }
    int *res = (int *)malloc(sizeof(int) * (arr1_size + arr2_size));
    memcpy(res, arr1, sizeof(int) * arr1_size);
    memcpy(res + arr1_size, arr2, sizeof(int) * arr2_size);
    *return_size = arr1_size + arr2_size;
    hash_free(&index);

    return res;
}
