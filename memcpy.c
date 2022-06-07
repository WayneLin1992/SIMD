#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <arm_neon.h>

void memcpy_fast(void* dst, void* src){
    int32x4_t m0 = vld1q_s32((int32_t*) src);
    vst1q_s32((int32_t *)dst, m0);
}

int main(){
   int32x4_t first = {10,20,30,40};
   int* dst = malloc(4*4);
   memcpy_fast((void*)dst, &first);
   for(int i = 0; i < 4; i++){
   	printf("%d \n",dst[i]);
   }
   printf("\n");
   free(dst);
   return 0;
}
