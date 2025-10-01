#include "edu_search.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UNIMPLEMENTED \
    do { \
        fprintf(stderr, "[ERROR] function %s is unimplemented\n", __func__); \
        abort(); \
    } while (0)

#define UNUSED(x) (void)(x)

size_t edu_linear_search(const void *ptr, size_t count, size_t size, const void *key, edu_cmp cmp) {
    const char *arr = (const char*)ptr;
    for (size_t i = 0; i < count; i++) {
        if (cmp(arr + i*size, key) == 0) return i;
    }
    return count; 
}

size_t edu_binary_search(const void *ptr, size_t count, size_t size, const void *key, edu_cmp cmp) {
    size_t left = 0, right = count;
    const char *arr = (const char*)ptr;
    while (left < right) {
        size_t mid = left + (right - left)/2;
        int c = cmp(arr + mid*size, key);
        if (c == 0) return mid;
        else if (c < 0) left = mid + 1;
        else right = mid;
    }
    return count; 
}