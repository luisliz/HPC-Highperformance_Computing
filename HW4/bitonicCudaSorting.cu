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

int main() {
    int *values = (int *) malloc(NUM_VALS * sizeof(int));
    int *origValues = (int *) malloc(NUM_VALS * sizeof(int));
    int n = 50;
    rand_nums(values, n);

    for (int i = 0; i < n; i++) {
        origValues[i] = values[i];
    }

    bitonicSort(values, n);
    cudaDeviceSynchronize();
    printf("\nAfter:\n ");
    for (int i = 0; i < n; i++) {
        printf("%d\t|%d\n ", values[i], origValues[i]);
    }
    printf("\n");
}


