#define DEBUG if (1)

#include <stdio.h>
#include <assert.h>


void qsort(int *data_start, int *data_end);
void swap(int *a, int *b);


int main() {
    int arr[] = {2, 4, 2, 1, 5, 2, 5, 6, 1, 5, 2, 10, 4, 11, 123, 32, 12, 3, 2, 3, 2, 3, 23, 23, 2, 3, 23, 54, 5, 4, 34, 3, 5, 4, 4, 565, 45};
    qsort(arr, arr + sizeof(arr) / sizeof(arr[0]) - 1);
    for (size_t i = 0; i < sizeof(arr) / sizeof(arr[0]); i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}

void swap(int *a, int *b) {
    DEBUG printf("swap: %d, %d\n", *a, *b);
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void qsort(int *data_start, int *data_end) {
    assert(data_start);
    assert(data_end);
    assert(data_end >= data_start);

    DEBUG getchar();
    DEBUG printf("start qsort: ");
    for (int *i = data_start; i <= data_end; i++) {
        DEBUG printf("%d ", *i);
    }
    DEBUG printf("\n");

    size_t l = 0;
    size_t r = data_end - data_start;

    if (r - l <= 1) {
        if (*data_start > *data_end) {
            swap(data_start, data_end);
        }
        return;
    }

    int mid_value = data_start[(l + r) / 2];
    DEBUG printf("mid_value: %d\n\n", mid_value);

    while (l <= r) {
        while (data_start[l] < mid_value && l <= r) l++;
        while (data_start[r] > mid_value && l <= r) r--;
        if (l > r) break;
        swap(data_start + l, data_start + r);
        l++;
        r--;
    }

    qsort(data_start, data_start + l - 1);
    qsort(data_start + l, data_end);

    DEBUG printf("end qsort: ");
    for (int *i = data_start; i <= data_end; i++) {
        DEBUG printf("%d ", *i);
    }
    DEBUG printf("\n");
}
