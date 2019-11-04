#include <stdlib.h> 
#include <stdio.h> 
#include <time.h> 

#define THREADS 512 
#define BLOCKS 32768
#define NUM_VALS THREADS*BLOCKS

void rand_nums(int *values, int length) {
				int i; 
				for(i = 0; i< length; ++i) {
								values[i] = (int)rand()/(int)INT_MAX;
				}
}



__global__ void bitonicMinorSort(int *innerValues, int j, int k) {
				unsigned int i, ixj; 
				i = threadIdx.x + blockDim.x * blockIdx.x; 

				ixj = i^j; 

				if ((ixj)>i) {
								if((i&k)==0) {
												if(innerValues[i]> innerValues[ixj]) {
																int temp = innerValues[i]; 
																innerValues[i] = innerValues[ixj]; 
																innerValues[ixj] = temp; 
												}
								}


								if((i&k)!=0) {
												if(innerValues[i] < innerValues[ixj]) {
																int temp = innerValues[i];
																innerValues[i]	 = innerValues[ixj]; 
																innerValues[ixj] = temp; 
												}
								}
				}
}
void bitonicSort(int *values) {
				int *innerValues	; 

				size_t size = NUM_VALS * sizeof(int); 

				cudaMalloc((void **) &innerValues, size); 
				cudaMemcpy(innerValues, values, size, cudaMemcpyHostToDevice); 

				dim3 blocks(BLOCKS, 1); 
				dim3 threads(THREADS, 1); 

				int j, k; 

				for(k = 2; k <= NUM_VALS; k <<= 1) {
								for(j = k >>1; j>0; j=j>>1) {
												bitonicMinorSort<<<blocks, threads>>>(innerValues, j, k); 
								}
				}

				cudaMemcpy(values, innerValues, size, cudaMemcpyDeviceToHost); 
				cudaFree(innerValues); 
}

int main() {
				int *values = (int *) malloc(NUM_VALS * sizeof(int)); 
				rand_nums(values, NUM_VALS); 
				for(int i = 0; i < NUM_VALS; i++) {
								printf("%d ", values[i]); 
				}
				bitonicSort(values); 

				for(int i = 0; i < NUM_VALS; i++) {
								printf("%d ", values[i]); 
				}
}
