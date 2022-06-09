#include <immintrin.h>
#include <stdio.h>
#include <arm_neon.h>
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
    uint8_t *p = ptr;
    clock_gettime(CLOCK_MONOTONIC, &tstart);
     _uint8x16_t m0 =  vdupq_n_u8('a');
    uint8x16x2_t first = vuzpq_u8(m0, m0);
    for(int i = 0; i < 8; i++){
        vst2q_u8((uint8_t*)p, first);
        p += 32;
    }
    clock_gettime(CLOCK_MONOTONIC, &tend);
    printf("\nmemset_neon : %.5f", ((double)tend.tv_nsec + 1.0e-9*tend.tv_nsec) -((double)tstart.tv_nsec + 1.0e-9*tstart.tv_nsec));
    for(int i = 0; i < 8; i++){
    	printf("%c \n",ptr[rand() % 256]);
    }
    free(ptr);
    return 0;
}
