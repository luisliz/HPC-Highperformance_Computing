#define NUM_BLOCKS 4 
#define BLOCK_WIDTH 8 

int main(void) {
				pringf("Hello Cuda!\n"); 

				hello<<<NUM_BLOCKS, BLOCK_WIDTH>>>(); 

				cudaDeviceSynchronize(); 

				printf("Welcome back to CPU\n"); 

				return(0); 
}

__global__ void hello(void) {
				printf("\t Hello fro GPU: thread %d and block %d\n", threadIdx.x, blockIdx.x); 
}
