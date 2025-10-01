#include "edu_sort.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define UNIMPLEMENTED \
    do { \
        fprintf(stderr, "[ERROR] function %s is unimplemented\n", __func__); \
        abort(); \
    } while (0)

#define UNUSED(x) (void)(x)

static void edu_swap(void *a, void *b, size_t size) {
    char tmp[size];
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
}

void edu_bubble_sort(void *ptr, size_t count, size_t size, edu_cmp cmp) {
    int swapped = 1;

    while (swapped) {
        swapped = 0;
        for (size_t i = 0; i < count - 1; ++i) {
            void *val1 = (char *) ptr + i * size;
            void *val2 = (char *) ptr + (i + 1) * size;
            if (cmp(val1, val2) > 0) {
                edu_swap(val1, val2, size);
                swapped = 1;
            }
        }
        --count;
    }
}

void edu_selection_sort(void *ptr, size_t count, size_t size, edu_cmp cmp) {
    for (size_t i = 0; i < count - 1; ++i) {
        size_t min_idx = i;
        for (size_t j = i + 1; j < count; ++j) {
            void *a = (char *)ptr + min_idx * size;
            void *b = (char *)ptr + j * size;
            if (cmp(a, b) > 0) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            void *a = (char *)ptr + i * size;
            void *b = (char *)ptr + min_idx * size;
            edu_swap(a, b, size);
        }
    }
}

void edu_insertion_sort(void *ptr, size_t count, size_t size, edu_cmp cmp) {
    for (size_t i = 1; i < count; ++i) {
        char buffer[size];
        memcpy(buffer, (char *)ptr + i * size, size);
        size_t j = i;
        while (j > 0 && cmp((char *)ptr + (j - 1) * size, buffer) > 0) {
            memcpy((char *)ptr + j * size, (char *)ptr + (j - 1) * size, size);
            --j;
        }
        memcpy((char *)ptr + j * size, buffer, size);
    }
}

void edu_shell_sort(void *ptr, size_t count, size_t size, edu_cmp cmp) {
    for (size_t gap = count / 2; gap > 0; gap /= 2) {
        for (size_t i = gap; i < count; ++i) {
            char buffer[size];
            memcpy(buffer, (char *)ptr + i * size, size);
            size_t j = i;
            while (j >= gap && cmp((char *)ptr + (j - gap) * size, buffer) > 0) {
                memcpy((char *)ptr + j * size, (char *)ptr + (j - gap) * size, size);
                j -= gap;
            }
            memcpy((char *)ptr + j * size, buffer, size);
        }
    }
}

static void quick_sort_helper(char *ptr, size_t left, size_t right, size_t size, edu_cmp cmp) {
    if (left >= right) return;
    size_t i = left, j = right;
    char pivot[size];
    memcpy(pivot, ptr + (left + right) / 2 * size, size);
    while (i <= j) {
        while (cmp(ptr + i * size, pivot) < 0) i++;
        while (cmp(ptr + j * size, pivot) > 0) j--;
        if (i <= j) {
            edu_swap(ptr + i * size, ptr + j * size, size);
            i++;
            if (j > 0) j--;
        }
    }
    if (j > left) quick_sort_helper(ptr, left, j, size, cmp);
    if (i < right) quick_sort_helper(ptr, i, right, size, cmp);
}

void edu_quick_sort(void *ptr, size_t count, size_t size, edu_cmp cmp) {
    if (count > 0) quick_sort_helper((char *)ptr, 0, count - 1, size, cmp);
}

static void heapify(char *ptr, size_t n, size_t i, size_t size, edu_cmp cmp) {
    size_t largest = i;
    size_t l = 2 * i + 1;
    size_t r = 2 * i + 2;
    if (l < n && cmp(ptr + l * size, ptr + largest * size) > 0) largest = l;
    if (r < n && cmp(ptr + r * size, ptr + largest * size) > 0) largest = r;
    if (largest != i) {
        edu_swap(ptr + i * size, ptr + largest * size, size);
        heapify(ptr, n, largest, size, cmp);
    }
}
void edu_heap_sort(void *ptr, size_t count, size_t size, edu_cmp cmp) {
    for (size_t i = count / 2; i > 0; --i) {
        heapify((char *)ptr, count, i - 1, size, cmp);
    }
    for (size_t i = count - 1; i > 0; --i) {
        edu_swap((char *)ptr, (char *)ptr + i * size, size);
        heapify((char *)ptr, i, 0, size, cmp);
    }
}


void edu_counting_sort(void *ptr, size_t count, size_t size, edu_counting_sort_order_e order) {
    if (size != sizeof(int)) return; 
    int *arr = (int *)ptr;
    int min = arr[0], max = arr[0];
    for (size_t i = 1; i < count; i++) {
        if (arr[i] < min) min = arr[i];
        if (arr[i] > max) max = arr[i];
    }

    int range = max - min + 1;
    int *freq = calloc(range, sizeof(int));

    for (size_t i = 0; i < count; i++) freq[arr[i] - min]++;

    size_t idx = 0;
    if (order == EDU_COUNTING_SORT_ASC) {
        for (int v = min; v <= max; v++) {
            while (freq[v - min]-- > 0) arr[idx++] = v;
        }
    } else {
        for (int v = max; v >= min; v--) {
            while (freq[v - min]-- > 0) arr[idx++] = v;
        }
    }

    free(freq);
}