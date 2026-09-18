#define DEBUG if (1)

#define BLACK     "\033[30m"
#define RED       "\033[31m"
#define GREEN     "\033[32m"
#define YELLOW    "\033[33m"
#define BLUE      "\033[34m"
#define PURPLE    "\033[35m"
#define LIGHTBLUE "\033[36m"
#define WHITE     "\033[37m"
#define STANDART  "\033[0m"

#include <stdio.h>
#include <assert.h>
#include <stdbool.h>


typedef int root_type;


void qsort(void *data, size_t left, size_t right);


void swap(void *data, size_t a, size_t b) {
    DEBUG printf("swap:    %d, %d\n", ((root_type*)data)[a], ((root_type*)data)[b]);
    root_type tmp = ((root_type*)data)[a];
    ((root_type*)data)[a] = ((root_type*)data)[b];
    ((root_type*)data)[b] = tmp;
    DEBUG printf("swapped: %d, %d\n", ((root_type*)data)[a], ((root_type*)data)[b]);
}

bool comp(void *data, size_t a, size_t b) {
    DEBUG printf("comp: %d > %d: %d\n", ((root_type*)data)[a], ((root_type*)data)[b], ((root_type*)data)[a] > ((root_type*)data)[b]);
    return ((root_type*)data)[a] > ((root_type*)data)[b];
}


int main() {
    root_type arr[]  = {12, 2, 4, 2, 1, 3, 55, 6, 34, 1, 5, 2, 10, 4, 11, 123, 32, 12, 3, 2, 3, 2, 3, 23, 23, 3, 23, 54, 5, 4, 34, 3, 5, 4, 4, 565, 45, 2};
    root_type arr1[] = {1, 2, 3, 4, 5, 6, 7, 8};

    qsort(arr, 0, sizeof(arr) / sizeof(arr[0]) - 1);
    for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}

void qsort(void *data, size_t left, size_t right) {
    assert(data);
    assert(right >= left);
    
    size_t start_l = left;
    size_t start_r = right;

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
        if (left > right) break;
        if (left == mid)      mid = right;
        else if (right == mid) mid = left;
        swap(data, left, right);
        left++;
        right--;
    }

    // if (l > start_r) return;

    DEBUG printf(GREEN);
    for (int i = start_l; i < left; i++) {
        DEBUG printf("%d ", ((int*)data)[i]);
    }
    DEBUG printf(RED);
    for (int i = left; i < start_r; i++) {
        DEBUG printf("%d ", ((int*)data)[i]);
    }
    DEBUG printf(STANDART "\n");
    DEBUG printf("mid_value: %d\n", ((int*)data)[mid]);
    
    DEBUG getchar();

    qsort(data, start_l, left - 1);
    qsort(data, left, start_r);

    DEBUG printf("end qsort: ");
    for (int i = 0; i < right + 1; i++) {
        DEBUG printf("%d ", ((int*)data)[i]);
    }
    DEBUG printf("\n");
}
