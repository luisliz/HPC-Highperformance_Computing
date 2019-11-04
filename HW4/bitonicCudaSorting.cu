#include <stdio.h> 

int[] arr;
#define ASCENDING = 1
#define DESCENDING = 0

void exchange (int i, int j) {
				int t = a[i]; 
				a[i] = a[j]; 
				a[j] = t; 
}

void compare(int i, int j, boolean dir) {
				if (dir == (a[i]>a[j]))
								exchange(i, j); 
}
void bitonicMerge(int lo, int n, boolean dir) {
				int (n>1) {
								int m = n/2; 
								for (int i = lo; i < lo+m; i++)
												compare(i, i+m, dir); 
								bitonicMerge(lo, m, dir); 
								bitonicMerge(lo+m, m, dir); 
				}
}

void bitonicSort(int lo, int n, boolean dir) {
	if(n>1) {
					int m = n/2; 
					bitonicSort(lo, m, ASCENDING); 
					bitonicSort(lo+m, m, DESCENDING); 
					bitonicMerge(lo, n, dir); 
	}
}

void sort(int[] a) {
				arr = a; 
				bitonicSort(0, a.length, ASCENDING);
}

int main() {
				int n = 6; 
	int[n] arr = {5, 6, 7, 2, 1, 0}; 
	bitonicSort(0, n, ASCENDING); 
}
