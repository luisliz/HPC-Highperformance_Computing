#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define THREADS 1024
#define BLOCKS 65536
#define NUM_VALS THREADS*BLOCKS

void rand_nums(int *values, int length) {
				int i;
				for (i = 0; i < length; ++i) {
								values[i] = rand() % INT_MAX + 1;;
				}
}


__global__ void bitonicMinorSort(int *innerValues, int j, int k) {
				unsigned int i, ixj;
				i = threadIdx.x + blockDim.x * blockIdx.x;

				ixj = i ^ j;

				if ((ixj) > i) {
								if ((i & k) == 0) {
												if (innerValues[i] > innerValues[ixj]) {
																int temp = innerValues[i];
																innerValues[i] = innerValues[ixj];
																innerValues[ixj] = temp;
												}
								}


								if ((i & k) != 0) {
												if (innerValues[i] < innerValues[ixj]) {
																int temp = innerValues[i];
																innerValues[i] = innerValues[ixj];
																innerValues[ixj] = temp;
												}
								}
				}
}

void bitonicSort(int *values, int n) {
				int *innerValues;

				size_t size = n * sizeof(int);

				cudaMalloc((void **) &innerValues, size);
				cudaMemcpy(innerValues, values, size, cudaMemcpyHostToDevice);

				int blockSize;
				if(n < THREADS) {
								blockSize = 1;
				} else {
								blockSize = ceil(n/THREADS);
				}

				printf("%d BLOCKS", blockSize);
				dim3 blocks(blockSize, 1);
				dim3 threads(THREADS, 1);



				int j, k;

				for (k = 2; k <= n; k <<= 1) {
								for (j = k >> 1; j > 0; j = j >> 1) {
												bitonicMinorSort<<<blocks, threads>>> (innerValues, j, k);
								}
				}

				cudaMemcpy(values, innerValues, size, cudaMemcpyDeviceToHost);
				cudaFree(innerValues);
}

int main(int argc, char *argv[]) {
				int *values = (int *) malloc(NUM_VALS * sizeof(int));
				int *origValues = (int *) malloc(NUM_VALS * sizeof(int));
				int k = 10;  
				if(argc==2) {
								k = atoi(argv[1]); 
								printf("%d\n", k); 

				} else {
								printf("Please input a correct value for k. Default k = 10 will be used.\n"); 
				}

				int n = pow(2,k); 
				printf("%d\n", n); 
				rand_nums(values, n);

				for (int i = 0; i < n; i++) {
								origValues[i] = values[i];
				}
				double time_spent = 0.0; 
				clock_t begin = clock(); 

				bitonicSort(values, n);
				cudaDeviceSynchronize();
				clock_t end = clock();

				time_spent += (double)(end-begin) / CLOCKS_PER_SEC; 
				printf("Elapsed time is %f seconds", time_spent); 
				//printf("\nAfter:\n ");
				//for (int i = 0; i < n; i++) {
				//    printf("%d\t|%d\n ", values[i], origValues[i]);
				//}
				//printf("\n");
}



