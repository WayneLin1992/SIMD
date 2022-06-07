#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <arm_neon.h>

void memcpy_neon_32x4(void* dst, void* src){
    int32x4_t m0 = vld1q_s32((int32_t*) src);
    vst1q_s32((int32_t *)dst, m0);
}

void memcpy_neon_32x4x4(void* dst, void* src){
    int32x4x4_t m0 = vld4q_s32((int32_t*) src);
    vst4q_s32((int32_t *)dst, m0);
}

void memcpy_fast(void* dst, void* src, size_t size){
    switch(size){
    	case 16:
    	    memcpy_neon_32x4(dst, src);
    	    break;
        case 64:
            memcpy_neon_32x4x4(dst, src);
            break;
    }
}

void benchmark(int dstalign, int srcalign, size_t size, int times)
{
	int *DATA1 = malloc(size + 16);
	int *DATA2 = malloc(size + 16);
	srand(time(NULL));
	for(int i = 0; i < (size/4); i++){
	    DATA1[i] = rand() % 100;
	}
	int *dst = (dstalign)? DATA1 : (DATA1 + 1);
	int *src = (srcalign)? DATA2 : (DATA2 + 3);
	//unsigned int t1, t2;
	int k;
	struct timespec start = {0,0}, end = {0,0};
	struct timespec tstart = {0,0}, tend = {0,0};

	sleep(100);
    	clock_gettime(CLOCK_MONOTONIC, &start);
	for (k = times; k > 0; k--) {
		memcpy(dst, src, size);
	}
	clock_gettime(CLOCK_MONOTONIC, &end);
	double t1 = ((double)end.tv_nsec + 1.0e-9*end.tv_nsec) -((double)start.tv_nsec + 1.0e-9*start.tv_nsec);
	sleep(100);
	clock_gettime(CLOCK_MONOTONIC, &tstart);
	for (k = times; k > 0; k--) {
		memcpy_fast(dst, src, size);
	}
	clock_gettime(CLOCK_MONOTONIC, &tend);
	double t2 = ((double)tend.tv_nsec + 1.0e-9*tend.tv_nsec) -((double)tstart.tv_nsec + 1.0e-9*tstart.tv_nsec);

	free(DATA1);
	free(DATA2);

	printf("result(dst %s, src %s): memcpy_fast=%.5fms memcpy=%.5f ms\n",
		dstalign? "aligned" : "unalign",
		srcalign? "aligned" : "unalign", (double)t2, (double)t1);
}

void bench(int copysize, int times)
{
	printf("benchmark(size=%d bytes, times=%d):\n", copysize, times);
	benchmark(1, 1, copysize, times);
	//benchmark(1, 0, copysize, times);
	//benchmark(0, 1, copysize, times);
	//benchmark(0, 0, copysize, times);
	printf("\n");
}


int main(void)
{
	bench(16, 0x100);
	bench(64, 0x100);


	return 0;
}
