#include <stdio.h> 
#include <stdlib.h> 

#define INF 99999
#define MAX 500 

//HELPER FUNCTIONS 
void printDistances(int dist[MAX][MAX], int n) { printf("\nShortest distances between vertices\n"); 

				for(int i = 0; i<n; i++) {
								for(int j=0; j< n; j++) {
												if(dist[i][j]==INF)
																printf("INF\t"); 
												else 
																printf("%d\t", dist[i][j]); 
								}
								printf("\n"); 
				}
}

void readFromArray(int graph[MAX][MAX], int n) {
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
void dijsk(int graph[MAX][MAX], int n) { 
				int dist[MAX][MAX]; 
				int sptSet[MAX][MAX]; 

				for (int i = 0; i < n; i++) 
								dist[i][i] = INF, sptSet[i][i] = 0; 

				for (int src = 0; src < n; src++)  {
								dist[src][src] = 0; 

								for (int count = 0; count < n - 1; count++) { 
												int min = INF, min_index; 
												for (int v = 0; v < n; v++) 
																if (sptSet[count][v] == 0 && dist[count][v] <= min) 
																				min = dist[count][v], min_index = v; 

												int u = min_index; 

												sptSet[count][u] = 1; 

												for (int v = 0; v < n; v++) 
																if (!sptSet[count][v] && graph[u][v] && dist[count][u] != INF && dist[count][u] + graph[u][v] < dist[count][v]) 
																				dist[count][v] = dist[count][u] + graph[u][v]; 
								} 
				}
				printDistances(dist, n); 
}

void parDijsk(int graph[MAX][MAX], int n) { 
				int dist[MAX][MAX]; 
				int sptSet[MAX][MAX]; 

				for (int i = 0; i < n; i++) 
								dist[i][i] = INF, sptSet[i][i] = 0; 

				for (int src = 0; src < n; src++)  {
								dist[src][src] = 0; 

								for (int count = 0; count < n - 1; count++) { 
												int min = INF, min_index; 
												for (int v = 0; v < n; v++) 
																if (sptSet[count][v] == 0 && dist[count][v] <= min) 
																				min = dist[count][v], min_index = v; 

												int u = min_index; 

												sptSet[count][u] = 1; 

												for (int v = 0; v < n; v++) 
																if (!sptSet[count][v] && graph[u][v] && dist[count][u] != INF && dist[count][u] + graph[u][v] < dist[count][v]) 
																				dist[count][v] = dist[count][u] + graph[u][v]; 
								} 
				}
				printDistances(dist, n); 
}

void floydAlgo(int graph[MAX][MAX], int n) {
				int distances[MAX][MAX], sum, i, j, k; 

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
				printDistances(distances, n); 
}

void parFloydAlgo(int graph[MAX][MAX], int n) {
				int distances[MAX][MAX], sum, i, j, k; 

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
				printDistances(distances, n); 
}

int main (int argc, char *argv[]) {
				int n = atoi(argv[1]); 
				int graph[MAX][MAX] = {0}; 
				readFromArray(graph, n); 

				printf("\nParallel Running Floyd's Algo"); 
				parFloydAlgo(graph, n); 
				printf("\nParallel Running Dijkstra's Algo"); 
				parDijsk(graph, n);
				
				/*printf("\nRunning Floyd's Algo"); 
				floydAlgo(graph, n); 
				printf("\nRunning Dijkstra's Algo"); 
				dijsk(graph, n);*/

				return 0; 
}


