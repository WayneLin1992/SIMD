#include <immintrin.h>
#include <stdio.h>
#include <time.h>
#include <arm_neon.h>
#define ARRAY_LENGTH 4

int main(int argc, char* argv[]) {
    struct timespec start = {0,0}, end = {0,0};
    clock_gettime(CLOCK_MONOTONIC, &start);
    int32x4_t first = vmovq_n_s32(40);
    int32x4_t second = vmovq_n_s32(5);
    int32x4_t result = vaddq_s32(first, second);
    clock_gettime(CLOCK_MONOTONIC, &end);
    int* values = (int*) &result;

    for (int i = 0; i < ARRAY_LENGTH; i ++){
        printf("%d ", values[i]);
    }

    printf("\n %.5f", ((double)end.tv_nsec + 1.0e-9*end.tv_nsec) -((double)start.tv_nsec + 1.0e-9*start.tv_nsec));
    struct timespec tstart = {0,0}, tend = {0,0};
    clock_gettime(CLOCK_MONOTONIC, &tstart);
    int arr[8] = {40, 40, 40, 40};
    int arr1[8] = {5, 5, 5, 5};
    int tot[8] = {0};
    for(int i = 0; i < 4; i++){
        tot[i] = arr[i] + arr1[i];
    }
    clock_gettime(CLOCK_MONOTONIC, &tend);
    printf("\n %.5f", ((double)tend.tv_nsec + 1.0e-9*tend.tv_nsec) -((double)tstart.tv_nsec + 1.0e-9*tstart.tv_nsec));

    return 0;
}
