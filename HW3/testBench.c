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
void dijsk(int graph[MAX][MAX], int n, int src) { 
				int dist[MAX]; 
				int sptSet[MAX]; 

				for (int i = 0; i < n; i++) 
								dist[i] = INF, sptSet[i] = 0; 

				dist[src] = 0; 

				for (int count = 0; count < n - 1; count++) { 
								int min = INF, min_index; 
								for (int v = 0; v < n; v++) 
												if (sptSet[v] == 0 && dist[v] <= min) 
																min = dist[v], min_index = v; 

								int u = min_index; 

								sptSet[u] = 1; 

								for (int v = 0; v < n; v++) 
												if (!sptSet[v] && graph[u][v] && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) 
																dist[v] = dist[u] + graph[u][v]; 
				} 

				printf("\n");
				for(int i = 0; i<n; i++) {
								printf("%d\t", dist[i]); 
				}
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



int main() {
				int n = 20; 
				int graph[MAX][MAX] = {0}; 
				readFromArray(graph, n); 
				printf("\nRunning Floyd's Algo"); 
				floydAlgo(graph, n); 
				printf("\nRunning Dijkstra's Algo"); 
				for(int i=0; i<n; i++) 
								dijsk(graph, n, i);

				return 0; 
}


