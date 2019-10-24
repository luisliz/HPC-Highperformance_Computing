#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <omp.h> 

#define INF 99999

//HELPER FUNCTIONS 
void printdistances(int **dist, int n) { printf("\nShortest distances between vertices\n"); 

	for(int i = 0; i<n; i++) {
		for(int j=0; j< n; j++) {
			if(dist[i][j]==INF) printf("INF\t"); else 
				printf("%d\t", dist[i][j]); 
		}
		printf("\n"); 
	}
}

void readFromArray(int **graph, int n) {
	FILE *myFile; 
	myFile = fopen("graph.txt", "r"); 

	int i, j; 

	for(i =  0; i < n; i++) {
		for(j = 0; j<n; j++) {
			fscanf(myFile, "%d, ", &graph[i][j]); 
		}
	}
	fclose(myFile); 
}

//SHORTEST PATH ALGORITHMS 
void dijsk(int **graph, int n, int startnode) { 
	int **cost,*distance, *pred;
	int *visited;
	int count,mindistance,nextnode,i,j;

	cost = (int **) malloc(n*sizeof(int*)); 
	for(int i = 0; i<n; i++)
		cost[i] = (int *) malloc(n*sizeof(int)); 

	distance = (int *) malloc(n*sizeof(int)); 
	pred = (int *) malloc(n*sizeof(int)); 
	visited = (int *) malloc(n*sizeof(int)); 

	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			if(graph[i][j]==0)
				cost[i][j]=INF;
			else
				cost[i][j]=graph[i][j];

	for(i=0;i<n;i++) {
		distance[i]=cost[startnode][i];
		pred[i]=startnode;
		visited[i]=0;
	}

	distance[startnode]=0;
	visited[startnode]=1;
	count=1;

	while(count<n) {
		mindistance=INF;

		//nextnode gives the node at minimum distance
		for(i=0;i<n;i++)
			if(distance[i]<mindistance&&!visited[i]) {
				mindistance=distance[i];
				nextnode=i;
			}

		//check if a better path exists through nextnode			
		visited[nextnode]=1;
		for(i=0;i<n;i++)
			if(!visited[i])
				if(mindistance+cost[nextnode][i]<distance[i]) {
					distance[i]=mindistance+cost[nextnode][i];
					pred[i]=nextnode;
				}
		count++;
	}
	/*for(int i = 0; i < n; i++) {
	  if(distance[i]==INF)
	  printf("INF\t");
	  else 
	  printf("%d\t",distance[i]); 
	  }*/	
}

void floydAlgo(int **graph, int n) {
	int **distances, sum, i, j, k; 

	distances = (int **) malloc(n*sizeof(int*)); 
	for(int i = 0; i<n; i++)
		distances[i] = (int *) malloc(n*sizeof(int));

	for(i = 0; i<n; i++)
		for(j=0; j< n; j++)
			distances[i][j] = graph[i][j]; 

	for(k=0; k<n; k++) {
		for(i = 0; i<n; i++) {
			for(j=0; j < n; j++) {
				if(i==j) 
					distances[i][j] = 0; 
				else { 
					sum = distances[i][k]+distances[k][j]; 
					if(sum < distances[i][j]) {
						distances[i][j] = sum; 
					}
				}
			}
		}
	}
	//printdistances(distances, n); 
	free(distances); 
}

void parFloydAlgo(int **graph, int n) {
	int **distances, k, i, j, sum;
	
	distances = (int **) malloc(n*sizeof(int*)); 
	for(int i = 0; i<n; i++)
		distances[i] = (int *) malloc(n*sizeof(int));
	
	for(int i = 0; i<n; i++)
		for(int j=0; j< n; j++)
			distances[i][j] = graph[i][j]; 

	#pragma omp parallel shared(adyacencyMatrix, numberOfVertices, sqrtOfnumberOfThreads, blockSize) private(k,i,j, lengthFromItoK, lengthFromItoKAndFromKToJ, threadNumber, initialRow, lastRow, initialColumn, lastColumn) firstprivate(kthRow, kthColumn)
    {

	threadNumber = omp_get_thread_num();

        initialRow = (threadNumber / sqrtOfnumberOfThreads) * blockSize;
        lastRow = initialRow + blockSize;

        initialColumn = (threadNumber % sqrtOfnumberOfThreads) * blockSize;
        lastColumn = initialColumn + blockSize;

	
	for(k=0; k<n; k++) {
		#pragma omp barrier 

		for (i = 0; i < numberOfVertices; ++i) {
                	kthRow[i] = distances[k][i];
                	kthColumn[i] = distances[i][k];
            	}
		for(i = 0; i<n; i++) {
			for(j=0; j < n; j++) {
			//printf("%d - %d", omp_get_thread_num(), k);

				if(i==j) 
					distances[i][j] = 0; 
				else { 
					sum = distances[i][k]+distances[k][j]; 
					if(sum < distances[i][j]) {
						distances[i][j] = sum; 
					}
				}
			}
		}
	}
}

	printdistances(distances, n); 
	free(distances); 
}

int main (int argc, char *argv[]) {
	int n, **graph; 
	clock_t t; 
	double time_taken; 

	n = atoi(argv[1]);

	//Allocate all memory
	graph = (int **) malloc(n*sizeof(int*)); 
	for(int i = 0; i<n; i++)
		graph[i] = (int *) malloc(n*sizeof(int)); 

	readFromArray(graph, n); 

	/*printf("\nFloyd's Algo"); 
	clock_t begin = clock();
	floydAlgo(graph, n); 
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("\n\tSingle took: %f seconds", time_spent);*/

	clock_t begin2 = clock();
	parFloydAlgo(graph, n);
	//floydAlgo(graph, n); 
	clock_t end2 = clock();
	double time_spent2 = (double)(end2 - begin2) / CLOCKS_PER_SEC;
	printf("\n\tParallel took: %f seconds\n", time_spent2);


	/*printf("\nDijkstra's Algo"); 
	t = clock(); 	
	for(int i = 0; i < n; i++) {
		dijsk(graph, n, i);
	}
	t = clock()-t; 
	time_taken = ((double)t)/CLOCKS_PER_SEC; 
	printf("\n\tSinlge took: %f seconds\n", time_taken);*/

	/*t = clock(); 	
	  for(int i = 0; i < n; i++) {
	  parDijsk(graph, n, i);
	  }
	  t = clock()-t; 
	  time_taken = ((double)t)/CLOCKS_PER_SEC; 
	  printf("\n\tParallel took: %f seconds\n", time_taken);*/

	free(graph);
	return 0; 
}


