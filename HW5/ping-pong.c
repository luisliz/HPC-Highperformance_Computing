#include <stdio.h> 
#include <mpi.h> 
#include <stdlib.h> 
#include <time.h> 

int main(int argc, char** argv) {

	const int PING_PONG_LIMIT = 2; 
	MPI_Init(NULL, NULL); 
	int world_rank; 
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank); 
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size); 

	if (world_size != 2) {
		fprintf(stderr, "World size must be two for %s\n", argv[0]);
		MPI_Abort(MPI_COMM_WORLD, 1);
	}
	int pingPongCount = 0; 
	int partnerRank = (world_rank + 1) % 2; 
	
	double total_time = 0.0; 
	time_t start = clock(); 
	while(pingPongCount < PING_PONG_LIMIT) {
		if(world_rank == pingPongCount % 2) {
			pingPongCount++; 
			MPI_Send(&pingPongCount, 1, MPI_INT, partnerRank, 0, MPI_COMM_WORLD); 
			printf("Process %d Sent ping: %d to process %d\n", world_rank, pingPongCount, partnerRank);
		} else {
			MPI_Recv(&pingPongCount, 1, MPI_INT, partnerRank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); 

			printf("Process %d Received pong: %d from %d\n", world_rank, pingPongCount, partnerRank);
		}
	}

	time_t end = clock(); 
	total_time = (double) (end-start)/CLOCKS_PER_SEC; 
	double avg_time = total_time/PING_PONG_LIMIT; 
	printf("\nProcess %d took %fs to complete.\n", world_rank, total_time); 
	printf("Avg. time per pingpong %fs.\n\n", avg_time); 
	MPI_Finalize(); 
}

