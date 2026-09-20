#define DEBUG       if (0)
#define DEBUG_SWAP  if (0)
#define DEBUG_COMP  if (0)
#define DEBUG_STEP  if (0)
#define DEBUG_ENTER if (0)

#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

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

#define MAX_FILE_LEN 10000

void myqsort(
    void *data,
    const size_t arr_len,
    const size_t element_size,
    int (*comp)(const void *a, const void *b)
);

int comp1(const void *a, const void *b) {
    char *s1 = *(char**)a;
    char *s2 = *(char**)b;

    return strcmp(s1, s2);
}

int main() {
    char *arr[MAX_FILE_LEN] = {};
    FILE *file = fopen("onegin_eng.txt", "r");
    if (file == NULL) {
        printf("[ERROR] file reading\n");
        return 1;
    } else {
        printf("[OK] file\n");
    }
    
    char *lineptr = NULL;
    size_t n = 0;

    int file_len = 0;
    while (getline(&lineptr, &n, file) > 0) {
        if (lineptr == NULL) {
            printf("[ERROR] lineptr is NULL\n");
        }

        char *dup = strdup(lineptr);
        
        if (dup == NULL) {
            printf("[ERROR] dup is NULL\n");
        }
        
        arr[file_len] = dup;
        file_len++;
    }
    printf("[OK] read, len: %d\n", file_len);
    fclose(file);
 
    myqsort(arr, file_len, sizeof(arr[0]), comp1);
    
    for (size_t i = 0; i < file_len; i++) {
        printf("%s", arr[i]);
    }
    printf("\n");

    for (int i = 0; i < file_len; i++) {
        free(arr[i]);
    }
    
    return 0;
}

void *getVoidShift(void *data, size_t element_size, int shift) {
    assert(data);
    assert(element_size > 0);
    assert(shift >= 0);

    return (void*)(((size_t)data) + shift * element_size);
    // return (void*)((char*)data + shift * element_size);
}

void qsort_swap_old(void *a, void *b, size_t element_size) {
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

void qsort_swap(void *a, void *b, size_t element_size) {
    char *a_ = (char*)a, *b_ = (char*)b;
    for (int i = 0; i < element_size / sizeof(uint64_t); i++) {
        uint64_t buffer1 = *((uint64_t*)a_);
        uint64_t buffer2 = *((uint64_t*)b_);

        *((uint64_t*)a_) = buffer2;
        *((uint64_t*)b_) = buffer1;

        a_ += sizeof(uint64_t);
        b_ += sizeof(uint64_t);
    }

    if ((element_size % sizeof(uint64_t)) / sizeof(uint32_t)) {
        uint32_t buffer1 = *((uint32_t*)a_);
        uint32_t buffer2 = *((uint32_t*)b_);

        *((uint32_t*)a_) = buffer2;
        *((uint32_t*)b_) = buffer1;

        a_ += sizeof(uint32_t);
        b_ += sizeof(uint32_t);
    }

    if ((element_size % sizeof(uint32_t)) / sizeof(uint16_t)) {
        uint16_t buffer1 = *((uint16_t*)a_);
        uint16_t buffer2 = *((uint16_t*)b_);

        *((uint16_t*)a_) = buffer2;
        *((uint16_t*)b_) = buffer1;

        a_ += sizeof(uint16_t);
        b_ += sizeof(uint16_t);
    }

    if ((element_size % sizeof(uint16_t)) / sizeof(uint8_t)) {
        char tmp = 0;
        tmp = *a_;
        *a_ = *b_;
        *b_ = tmp;
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
    
    if (arr_len < 2) return;
    if (arr_len <= 2) {
        if (comp(data, getVoidShift(data, element_size, 1)) > 0) {
            qsort_swap(data, getVoidShift(data, element_size, 1), element_size);
        }
        return;
    }

    size_t mid = (left + right) / 2;
    DEBUG printf("mid_value: %d\n", ((int*)data)[mid]);

    while (left <= right) {
        while (left <= right && comp(getVoidShift(data, element_size, mid), getVoidShift(data, element_size, left))  > 0) left++;
        while (left <= right && comp(getVoidShift(data, element_size, mid), getVoidShift(data, element_size, right)) < 0) right--;

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

        DEBUG_STEP printf("left: %zd, right: %zd\n", left, right);

        DEBUG_STEP printf(GREEN);
        for (int i = 0; i < left; i++) {
            DEBUG_STEP printf("%3d ", ((int*)data)[i]);
        }

        DEBUG_STEP printf(BLUE "%3d ", ((int*)data)[left]);

        DEBUG_STEP printf(YELLOW);
        for (int i = left + 1; i < right; i++) {
            DEBUG_STEP printf("%3d ", ((int*)data)[i]);
        }
        
        DEBUG_STEP printf(BLUE "%3d ", ((int*)data)[right]);

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
