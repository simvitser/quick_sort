#define DEBUG       if (1)
#define DEBUG_SWAP  if (0)
#define DEBUG_COMP  if (0)
#define DEBUG_STEP  if (1)
#define DEBUG_ENTER if (0)

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


void myqsort(
    void *data,
    const size_t arr_len,
    const size_t element_size,
    int (*comp)(const void *a, const void *b)
);

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

    myqsort(arr,     arr_len, sizeof(arr_ans[0]), ccomp);
    qsort  (arr_ans, arr_len, sizeof(arr_ans[0]), ccomp);

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


void *getVoidShift(void *data, size_t element_size, int shift) {
    assert(data);
    assert(element_size > 0);
    assert(shift >= 0);

    // return (void*)(((size_t)data) + shift * element_size);
    return (void*)((char*)data + shift * element_size);
}

// TODO: написать и сюда копирование буффером, реализация уже есть, см string_sort/main.c
void qsort_swap(void *a, void *b, size_t element_size) {
    assert(a);
    assert(b);
    assert(element_size > 0);

    char *A = (char*)a, *B = (char*)b;
    for (int i = 0; i < element_size; i++) {
        char tmp = *A;
        *A = *B;
        *B = tmp;
        A++;
        B++;
    }
}

void myqsort(void *data, const size_t arr_len, const size_t element_size, int (*comp)(const void *a, const void *b)) {
    assert(data);
    assert(comp);
    assert(arr_len > 0);
    assert(element_size > 0);
 
    ssize_t left  = 0;
    ssize_t right = arr_len - 1;

    DEBUG printf("start left: %zd, right: %zd, len: %zd, element_size: %zd, array: ", left, right, arr_len, element_size);
    for (int i = 0; i < arr_len; i++) {
        DEBUG printf("%d ", *((int*)getVoidShift(data, element_size, i)));
    }
    DEBUG printf("\n"); 

    if (arr_len <= 2) {
        if (comp(data, getVoidShift(data, element_size, 1)) == 1) {
            qsort_swap(data, getVoidShift(data, element_size, 1), element_size);
        }
        return;
    }

    size_t mid = (left + right) / 2;
    DEBUG printf("mid_value: %d\n", ((int*)data)[mid]);

    while (left <= right) {
        while (left <= right && comp(getVoidShift(data, element_size, mid), getVoidShift(data, element_size, left))  ==  1) left++;
        while (left <= right && comp(getVoidShift(data, element_size, mid), getVoidShift(data, element_size, right)) == -1) right--;

        if (left > right) {
            DEBUG_STEP printf(GREEN);
            for (int i = 0; i < left; i++) {
                DEBUG_STEP printf("%3d ", ((int*)data)[i]);
            }
            DEBUG_STEP printf(RED);
            for (int i = left; i < arr_len; i++) {
                DEBUG_STEP printf("%3d ", ((int*)data)[i]);
            }
            DEBUG_STEP printf(STANDART "\n");
            break;
        }

        printf("left: %zd, right: %zd\n", left, right);

        DEBUG_STEP printf(GREEN);
        for (int i = 0; i < left; i++) {
            DEBUG_STEP printf("%3d ", ((int*)data)[i]);
        }

        printf(BLUE "%3d ", ((int*)data)[left]);

        DEBUG_STEP printf(YELLOW);
        for (int i = left + 1; i < right; i++) {
            DEBUG_STEP printf("%3d ", ((int*)data)[i]);
        }
        
        printf(BLUE "%3d ", ((int*)data)[right]);

        DEBUG_STEP printf(RED);
        for (int i = right + 1; i < arr_len; i++) {
            DEBUG_STEP printf("%3d ", ((int*)data)[i]);
        }

        DEBUG_STEP printf(STANDART "\n");

        if      (left  == mid) mid = right;
        else if (right == mid) mid = left;

        qsort_swap(getVoidShift(data, element_size, left), getVoidShift(data, element_size, right), element_size);
        left++;
        right--;
    }
    
    DEBUG printf("mid_value: %d\n", ((int*)data)[mid]);
    
    DEBUG_ENTER getchar();

    if (left)               myqsort(data, left, element_size, comp);
    if (arr_len - left) myqsort(getVoidShift(data, element_size, left), arr_len - left, element_size, comp);

    DEBUG printf("end qsort: ");
    for (int i = 0; i < arr_len; i++) {
        DEBUG printf("%d ", ((int*)data)[i]);
    }
    DEBUG printf("\n");
}
