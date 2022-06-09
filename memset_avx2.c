#include <immintrin.h>
#include <stdio.h>


int main(){
    int *ptr =  malloc(256);
    struct timespec start = {0,0}, end = {0,0};
    clock_gettime(CLOCK_MONOTONIC, &start);
    memset(ptr, 10, 256);
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("\n %.5f", ((double)end.tv_nsec + 1.0e-9*end.tv_nsec) -((double)start.tv_nsec + 1.0e-9*start.tv_nsec));
    struct timespec tstart = {0,0}, tend = {0,0};
    clock_gettime(CLOCK_MONOTONIC, &tstart);
    int *p = ptr;
    __m256i first = _mm256_set_epi32(10, 10, 10, 10, 10, 10, 10, 10);
    for(int i = 0; i < 16; i++){
        _mm_store_si256((__m128i*)p, first);
        p += 16;
    }
    clock_gettime(CLOCK_MONOTONIC, &tend);
    printf("\n %.5f", ((double)tend.tv_nsec + 1.0e-9*tend.tv_nsec) -((double)tstart.tv_nsec + 1.0e-9*tstart.tv_nsec))
    return 0;
}
