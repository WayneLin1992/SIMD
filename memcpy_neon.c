#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <arm_neon.h>

void* memcpy_fast(int32_t* dst, int32_t* src){
    int32x4_t m0 = vld1q_s32(src)
    vst1q_s32(dst, m0);
    return dst;
}

unsigned int gettime()
{
	#if (defined(_WIN32) || defined(WIN32))
	return timeGetTime();
	#else
	static struct timezone tz={ 0,0 };
	struct timeval time;
	gettimeofday(&time,&tz);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
	#endif
}

void benchmark(int dstalign, int srcalign, size_t size, int times)
{
	char *DATA1 = (char*)malloc(size + 64);
	char *DATA2 = (char*)malloc(size + 64);
	size_t LINEAR1 = ((size_t)DATA1);
	size_t LINEAR2 = ((size_t)DATA2);
	char *ALIGN1 = (char*)(((64 - (LINEAR1 & 63)) & 63) + LINEAR1);
	char *ALIGN2 = (char*)(((64 - (LINEAR2 & 63)) & 63) + LINEAR2);
	char *dst = (dstalign)? ALIGN1 : (ALIGN1 + 1);
	char *src = (srcalign)? ALIGN2 : (ALIGN2 + 3);
	unsigned int t1, t2;
	int k;

	sleepms(100);
	t1 = gettime();
	for (k = times; k > 0; k--) {
		memcpy(dst, src, size);
	}
	t1 = gettime() - t1;
	sleepms(100);
	t2 = gettime();
	for (k = times; k > 0; k--) {
		memcpy_fast(dst, src);
	}
	t2 = gettime() - t2;

	free(DATA1);
	free(DATA2);

	printf("result(dst %s, src %s): memcpy_fast=%dms memcpy=%d ms\n",
		dstalign? "aligned" : "unalign",
		srcalign? "aligned" : "unalign", (int)t2, (int)t1);
}

void bench(int copysize, int times)
{
	printf("benchmark(size=%d bytes, times=%d):\n", copysize, times);
	benchmark(1, 1, copysize, times);
	benchmark(1, 0, copysize, times);
	benchmark(0, 1, copysize, times);
	benchmark(0, 0, copysize, times);
	printf("\n");
}


int main(void)
{
	bench(16, 0x1000000);


	return 0;
}
