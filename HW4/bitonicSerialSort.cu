#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define THREADS 1024
#define BLOCKS 65536
#define NUM_VALS THREADS*BLOCKS
#define ASCENDING 1
#define DESCENDING 0

void rand_nums(int *values, unsigned long length) {
	int i;
	for (i = 0; i < length; ++i) {
		values[i] = rand() % INT_MAX + 1;;
	}
}

void compAndSwap(int *a, int i, int j, int dir)
{
    int temp;
    if (dir==(a[i]>a[j])) {
        temp = a[j];
        a[j] = a[i];
        a[i] = temp;
        //swap(a[i], a[j]);
    }
}

void bitonicMerge(int *a, int low, int cnt, int dir) {
    if (cnt > 1) {
        int k = cnt / 2;
        for (int i = low; i < low + k; i++)
            compAndSwap(a, i, i + k, dir);
        bitonicMerge(a, low, k, dir);
        bitonicMerge(a, low + k, k, dir);
    }
}

void bitonicSort(int *values, int low, unsigned long n, int dir) {
    if(n>1) {
        int k = n/2;

        bitonicSort(values, low, k, ASCENDING);
        bitonicSort(values, low+k, k, DESCENDING);

        bitonicMerge(values, low, n, dir);
    }

}

int main(int argc, char *argv[]) {
    unsigned long n;
    double time_spent;
    clock_t begin, end;

    int k = 10;
	if(argc==2)
		k = atoi(argv[1]);

	n = pow(2,k);

	int *values = (int *) malloc(NUM_VALS * sizeof(int));
	int *origValues = (int *) malloc(NUM_VALS * sizeof(int));

	printf("\nk = %d, n = %ld\n", k, n); 

	rand_nums(values, n);

	for (unsigned long i = 0; i < n; i++)
		origValues[i] = values[i];

	time_spent = 0.0; 
	begin = clock(); 
	bitonicSort(values, 0, n, ASCENDING);
	end = clock();
	time_spent += (double)(end-begin) / CLOCKS_PER_SEC; 
	printf("\tElapsed time: %f seconds\n", time_spent); 
	
	free(values); 
	free(origValues); 
}




