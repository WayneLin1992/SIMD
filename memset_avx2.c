#include <immintrin.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

int main(){
    char *ptr =  malloc(256);
    struct timespec start = {0,0}, end = {0,0};
    clock_gettime(CLOCK_MONOTONIC, &start);
    memset(ptr, 'a', 256);
    clock_gettime(CLOCK_MONOTONIC, &end);
    printf("\nmemset : %.5f", ((double)end.tv_nsec + 1.0e-9*end.tv_nsec) -((double)start.tv_nsec + 1.0e-9*start.tv_nsec));
    struct timespec tstart = {0,0}, tend = {0,0};
    srand(time(NULL));
    for(int i = 0; i < 8; i++){
    	printf("%c \n",ptr[rand() % 256]);
    }
    memset(ptr, 0, 256);
    char *p = ptr;
    clock_gettime(CLOCK_MONOTONIC, &tstart);
    __m128i first = _mm_set_epi8('a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a');
    for(int i = 0; i < 16; i++){
        _mm_store_si128((__m128i*)p, first);
        p += 16;
    }
    clock_gettime(CLOCK_MONOTONIC, &tend);
    printf("\nmemset_mavx2 : %.5f", ((double)tend.tv_nsec + 1.0e-9*tend.tv_nsec) -((double)tstart.tv_nsec + 1.0e-9*tstart.tv_nsec));
    for(int i = 0; i < 8; i++){
    	printf("%c \n",ptr[rand() % 256]);
    }
    free(ptr);
    return 0;
}
