#define DEBUG if (0)

#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>


typedef char* root_type;
const int MAX_FILE_LEN = 10000;


void myqsort(void *data, size_t l, size_t r);


void MYswap(void *data, size_t a, size_t b) {
    DEBUG printf("swap:    %s, %s\n", ((root_type*)data)[a], ((root_type*)data)[b]);
    root_type tmp = ((root_type*)data)[a];
    ((root_type*)data)[a] = ((root_type*)data)[b];
    ((root_type*)data)[b] = tmp;
    DEBUG printf("swapped: %s, %s\n", ((root_type*)data)[a], ((root_type*)data)[b]);
}

bool MYcomp(void *data, size_t a, size_t b) {
    // DEBUG printf("comp: %s > %s: %d\n", ((root_type*)data)[a], ((root_type*)data)[b], ((root_type*)data)[a] > ((root_type*)data)[b]);
    return strcmp(
        ( (root_type*)data )[a],
        ( (root_type*)data )[b]
    ) >= 0;
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
    DEBUG printf("%s%s%s", arr[1], arr[4], arr[6]);
    printf("[OK] read\n");
 
    myqsort(arr, 0, file_len - 1);
    
    for (size_t i = 0; i < file_len; i++) {
        printf("%s", arr[i]);
    }
    printf("\n");
    
    return 0;
}


void myqsort(void *data, size_t l, size_t r) {
    assert(data);
    assert(r >= l);

    size_t start_l = l;
    size_t start_r = r;

    DEBUG printf("start l: %zd, r: %zd, qsort: ", l, r);
    for (int i = l; i < r + 1; i++) {
        DEBUG printf("%s ", ((char**)data)[i]);
    }
    DEBUG printf("\n"); 

    if (r - l <= 1) {
        if (comp(data, l, r)) {
            swap(data, l, r);
        }
        return;
    }

    size_t mid = (l + r) / 2;
    DEBUG printf("mid_value: %s\n", ((char**)data)[mid]);

    while (l <= r) {
        while (comp(data, mid, l) && l <= r) l++;
        while (comp(data, r, mid) && l <= r) r--;
        DEBUG printf("now l: %zu, r: %zu\n", l, r);
        if (l > r) break;
        if      (l == mid) mid = r;
        else if (r == mid) mid = l;
        swap(data, l, r);
        l++;
        r--;
    }

    if (l >= start_r) return;
    if (r <= start_l) return;
   
    DEBUG printf("start_l: %zu, l: %zu, r: %zu, start_r: %zu\n", start_l, l, r, start_r);
    DEBUG printf("--------------------------QSORT-------------------\n");
    DEBUG getchar();


    if (start_l <= l - 1) myqsort(data, start_l, l - 1);
    if (l <= start_r)     myqsort(data, l, start_r);

    DEBUG printf("end qsort: ");
    for (int i = 0; i < r + 1; i++) {
        DEBUG printf("%s ", ((char**)data)[i]);
    }
    DEBUG printf("\n");
}
