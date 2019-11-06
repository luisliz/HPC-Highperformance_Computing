#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define THREADS 1024
#define BLOCKS 65536
#define NUM_VALS THREADS*BLOCKS

void rand_nums(int *values, unsigned long length) {
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

void bitonicSort(int *values, unsigned long n) {
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
	int k = 10;  

	if(argc==2)
		k = atoi(argv[1]); 

	int *values = (int *) malloc(NUM_VALS * sizeof(int));    
	int *origValues = (int *) malloc(NUM_VALS * sizeof(int));    
	
	unsigned long n;
	double time_spent;
	clock_t begin, end; 

	for(int i = 0; i < k; i++) {
		n = pow(2,k); 
		printf("\nk = %d, n = %ld\n", k, n); 
		
		rand_nums(values, n);

		for (unsigned long i = 0; i < n; i++)
			origValues[i] = values[i];
		

		time_spent = 0.0; 
		begin = clock(); 
		bitonicSort(values, n);
		end = clock();
		time_spent += (double)(end-begin) / CLOCKS_PER_SEC; 
		printf("\tElapsed time: %f seconds", time_spent); 
	}
}



