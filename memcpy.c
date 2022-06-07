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

int main(){
   struct timespec start = {0,0}, end = {0,0}; 
   struct timespec tstart = {0,0}, tend = {0,0};
   int32x4_t first = {10,20,30,40};
   int* dst = malloc(4*4);
   clock_gettime(CLOCK_MONOTONIC, &start);
   memcpy_neon_32x4((void*)dst, &first);
   clock_gettime(CLOCK_MONOTONIC, &end);
   for(int i = 0; i < 4; i++){
   	printf("%d \n",dst[i]);
   }
   printf("\n");
   double t1 = ((double)end.tv_nsec + 1.0e-9*end.tv_nsec) -((double)start.tv_nsec + 1.0e-9*start.tv_nsec);
   memset(dst, 0, 16);
   clock_gettime(CLOCK_MONOTONIC, &tstart);
   memcpy(dst, &first, 16);
   clock_gettime(CLOCK_MONOTONIC, &tend);
   double t2 = ((double)tend.tv_nsec + 1.0e-9*tend.tv_nsec) -((double)tstart.tv_nsec + 1.0e-9*tstart.tv_nsec);
   
   printf("memcpy_neon_32x4=%.5fms memcpy=%.5f ms\n",(double)t1, (double)t2);
   
   struct timespec start64 = {0,0}, end64 = {0,0};
   struct timespec tstart64 = {0,0}, tend64 = {0,0};
   int32x4x4_t src_32x4x4 = {10,20,30,40,10,20,30,40,10,20,30,40,10,20,30,40};
   int* dst_32x4x4 = malloc(4*4*4);
   clock_gettime(CLOCK_MONOTONIC, &start64);
   memcpy_neon_32x4x4((void*)dst_32x4x4, &src_32x4x4);
   clock_gettime(CLOCK_MONOTONIC, &end64);
   double t164 = ((double)end64.tv_nsec + 1.0e-9*end64.tv_nsec) -((double)start64.tv_nsec + 1.0e-9*start64.tv_nsec);
   memset(dst_32x4x4, 0,64);
   clock_gettime(CLOCK_MONOTONIC, &tstart64);
   memcpy(dst_32x4x4, &src_32x4x4, 64);
   clock_gettime(CLOCK_MONOTONIC, &tend64);
   double t264 = ((double)tend64.tv_nsec + 1.0e-9*tend64.tv_nsec) -((double)tstart64.tv_nsec + 1.0e-9*tstart64.tv_nsec);
   printf("memcpy_neon_32x4x4=%.5fms memcpy=%.5f ms\n",(double)t164, (double)t264);
   for(int i = 0; i < (4*4); i++){
   	printf("%d \n",dst_32x4x4[i]);
   }
   printf("\n");
   free(dst);
   free(dst_32x4x4);
   return 0;
}
