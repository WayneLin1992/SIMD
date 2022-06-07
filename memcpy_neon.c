#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <arm_neon.h>

void* memcpy_fast(void* dst, void* src){
    int32x4_t m0 = vld1q_s32((int32_t*) src);
    vst1q_s32((int32_t *)dst, m0);
    return (void*)dst;
}

void benchmark(int dstalign, int srcalign, size_t size, int times)
{
	char *DATA1 = (char*)malloc(size + 32);
	char *DATA2 = (char*)malloc(size + 32);
	size_t LINEAR1 = ((size_t)DATA1);
	size_t LINEAR2 = ((size_t)DATA2);
	char *ALIGN1 = (char*)(((32 - (LINEAR1 & 31)) & 31) + LINEAR1);
	char *ALIGN2 = (char*)(((32 - (LINEAR2 & 31)) & 31) + LINEAR2);
	char *dst = (dstalign)? ALIGN1 : (ALIGN1 + 1);
	char *src = (srcalign)? ALIGN2 : (ALIGN2 + 3);
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
		memcpy_fast(dst, src);
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
	bench(16, 0x1000);


	return 0;
}
