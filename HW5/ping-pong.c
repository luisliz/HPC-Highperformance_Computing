#include <stdio.h> 
#include <mpi.h> 
#include <stdlib.h> 

int main(int argc, char** argv) {

				const int PING_PONG_LIMIT = 3; 
				MPI_Init(NULL, NULL); 
				int world_rank; 
				MPI_Comm_rank(MPI_COMM_WORLD, &world_rank); 
				int world_size;
				MPI_Comm_size(MPI_COMM_WORLD, &world_size); 

				int pingPongCount = 0; 
				int partnerRank = (world_rank + 1) % 2; 

				while(pingPongCount < PING_PONG_LIMIT) {
								if(world_rank == pingPongCount % 2) {
												pingPongCount++; 
												MPI_Send(&pingPongCount, 1, MPI_INT, partnerRank, 0, MPI_COMM_WORLD); 
												printf("Sent ping: %d\n", pingPongCount);
								} else {
MPI_Recv(&pingPongCount, 1, MPI_INT, partnerRank, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE); 

printf("Received pong: %d", pingPongCount);
								}
				}

				MPI_Finalize(); 
}

