
#include <immintrin.h>
#include <stdio.h>
#include <time.h>
#define ARRAY_LENGTH 8

int main(int argc, char* argv[]) {
    struct timespec start = {0,0}, end = {0,0};
    clock_gettime(CLOCK_MONOTONIC, &start);
    __m256i first = _mm256_set_epi32(10, 20, 30, 40, 50, 60, 70, 80);
    __m256i second = _mm256_set_epi32(5, 5, 5, 5, 5, 5, 5, 5);
    __m256i result = _mm256_add_epi32(first, second);
    clock_gettime(CLOCK_MONOTONIC, &end); 
    int* values = (int*) &result;

    for (int i = 0; i < ARRAY_LENGTH; i ++){
        printf("%d ", values[i]);
    }
   
    printf("\n %.5f", ((double)end.tv_nsec + 1.0e-9*end.tv_nsec) -((double)start.tv_nsec + 1.0e-9*start.tv_nsec));
    struct timespec tstart = {0,0}, tend = {0,0};
    clock_gettime(CLOCK_MONOTONIC, &tstart);
    int arr[8] = {10, 20, 30, 40, 50, 60, 70, 80};
    int arr1[8] = {5, 5, 5, 5, 5, 5, 5, 5};
    int tot[8] = {0};
    for(int i = 0; i < 8; i++){
        tot[i] = arr[i] + arr1[i];
    }
    clock_gettime(CLOCK_MONOTONIC, &tend);
    printf("\n %.5f", ((double)tend.tv_nsec + 1.0e-9*tend.tv_nsec) -((double)tstart.tv_nsec + 1.0e-9*tstart.tv_nsec));

    return 0;
}
