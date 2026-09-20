#define DEBUG       if (1)
#define DEBUG_SWAP  if (0)
#define DEBUG_COMP  if (0)
#define DEBUG_STEP  if (1)
#define DEBUG_ENTER if (1)

#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#define BLACK     "\033[30m"
#define RED       "\033[31m"
#define GREEN     "\033[32m"
#define YELLOW    "\033[33m"
#define BLUE      "\033[34m"
#define PURPLE    "\033[35m"
#define LIGHTBLUE "\033[36m"
#define WHITE     "\033[37m"
#define STANDART  "\033[0m"

#define STATIC_LEN(arr) sizeof(arr) / sizeof(arr[0])

typedef int root_type;


void qsort_compare_index(
    void *data,
    size_t left,
    size_t right,
    bool (*comp)(void *data, size_t a, size_t b),
    void (*swap)(void *data, size_t a, size_t b)
);


void swapMY(void *data, size_t a, size_t b) {
    DEBUG_SWAP printf("swap:    %d, %d\n", ((root_type*)data)[a], ((root_type*)data)[b]);
    root_type tmp = ((root_type*)data)[a];
    ((root_type*)data)[a] = ((root_type*)data)[b];
    ((root_type*)data)[b] = tmp;
    DEBUG_SWAP printf("swapped: %d, %d\n", ((root_type*)data)[a], ((root_type*)data)[b]);
}

bool compMY(void *data, size_t a, size_t b) {
    DEBUG_COMP printf("comp: %d > %d: %d\n", ((root_type*)data)[a], ((root_type*)data)[b], ((root_type*)data)[a] > ((root_type*)data)[b]);
    return ((root_type*)data)[a] > ((root_type*)data)[b];
}

int ccomp(const void *a, const void *b) {
    root_type x = *(root_type*)a;
    root_type y = *(root_type*)b;

    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

int main() {
    root_type arr[]  = {12, 2, 4, 2, 1, 3, 55, 6, 34, 1, 5, 2, 10, 4, 11, 123, 32, 12, 3, 2, 3, 2, 3, 23, 23, 3, 23, 54, 5, 4, 34, 3, 5, 4, 4, 565, 45, 2};
    root_type arr1[] = {1, 2, 3, 4, 5, 6, 7, 8};
    
    size_t arr_len = STATIC_LEN(arr);

    root_type arr_ans[arr_len] = {};
    for (int i = 0; i < arr_len; i++) {
        arr_ans[i] = arr[i];
    }

    qsort_compare_index(arr, 0, arr_len - 1, compMY, swapMY);
    qsort(arr_ans, arr_len, sizeof(arr_ans[0]), ccomp);

    printf("answer:\n");
    for (size_t i = 0; i < arr_len; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    printf("right answer:\n");
    for (size_t i = 0; i < arr_len; i++) {
        printf("%d ", arr_ans[i]);
    }
    printf("\n");
    return 0;
}

void qsort_compare_index(void *data, size_t left, size_t right, bool (*comp)(void *data, size_t a, size_t b), void (*swap)(void *data, size_t a, size_t b)) {
    assert(data);
    assert(right >= left);
    
    size_t start_left  = left;
    size_t start_right = right;

    DEBUG printf("start l: %zd, r: %zd, qsort: ", left, right);
    for (int i = left; i < right + 1; i++) {
        DEBUG printf("%d ", ((int*)data)[i]);
    }
    DEBUG printf("\n"); 

    if (right - left <= 1) {
        if (comp(data, left, right)) {
            swap(data, left, right);
        }
        return;
    }

    size_t mid = (left + right) / 2;
    DEBUG printf("mid_value: %d\n", ((int*)data)[mid]);

    while (left <= right) {
        while (comp(data, mid, left) && left <= right) left++;
        while (comp(data, right, mid) && left <= right) right--;

        if (left > right) {
            DEBUG_STEP printf(GREEN);
            for (int i = start_left; i < left; i++) {
                DEBUG_STEP printf("%3d ", ((int*)data)[i]);
            }
            DEBUG_STEP printf(RED);
            for (int i = left; i < start_right + 1; i++) {
                DEBUG_STEP printf("%3d ", ((int*)data)[i]);
            }
            DEBUG_STEP printf(STANDART "\n");
            break;
        }

        DEBUG_STEP printf(GREEN);
        for (int i = start_left; i < left; i++) {
            DEBUG_STEP printf("%3d ", ((int*)data)[i]);
        }

        printf(BLUE "%3d ", ((int*)data)[left]);

        DEBUG_STEP printf(YELLOW);
        for (int i = left + 1; i < right; i++) {
            DEBUG_STEP printf("%3d ", ((int*)data)[i]);
        }
        
        printf(BLUE "%3d ", ((int*)data)[right]);

        DEBUG_STEP printf(RED);
        for (int i = right + 1; i < start_right + 1; i++) {
            DEBUG_STEP printf("%3d ", ((int*)data)[i]);
        }

        DEBUG_STEP printf(STANDART "\n");

        if      (left  == mid) mid = right;
        else if (right == mid) mid = left;

        swap(data, left, right);
        left++;
        right--;
    }

    // if (l > start_r) return;

    
    DEBUG printf("mid_value: %d\n", ((int*)data)[mid]);
    
    DEBUG_ENTER getchar();

    qsort_compare_index(data, start_left, left - 1, comp, swap);
    qsort_compare_index(data, left, start_right, comp, swap);

    DEBUG printf("end qsort: ");
    for (int i = 0; i < right + 1; i++) {
        DEBUG printf("%d ", ((int*)data)[i]);
    }
    DEBUG printf("\n");
}
