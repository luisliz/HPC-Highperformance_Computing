#include <stdio.h> 

#define INF 99999
#define V 4 

void printDistances(int dist[V][V]) {
				printf("Shortest distances between vertices\n"); 

				for(int i = 0; i<V; i++) {
								for(int j=0; j< V; j++) {
												if(dist[i][j]==INF)
																printf("INF\t"); 
												else 
																printf("%d\t", dist[i][j]); 
								}
								printf("\n"); 
				}
}

void floydAlgo(int graph[V][V]) {
				int distances[V][V], i, j, k, sum; 

				for(i = 0; i<V; i++)
								for(j=0; j< V; j++)
												distances[i][j] = graph[i][j]; 

				for(k=0; k<V; k++) {
								for(i = 0; i<V; i++) {
												for(j=0; j< V; j++) {
																sum = distances[i][k]+distances[k][j]; 
																if(sum < distances[i][j])
																				distances[i][j] = sum; 
												}
								}
				}
				printDistances(distances); 
}

int main() {
				int graph[V][V] = {{0,   5,  INF, 10}, 
								{INF, 0,   3, INF}, 
								{INF, INF, 0,   1}, 
								{INF, INF, INF, 0}}; 

				floydAlgo(graph); 
				return 0; 
}
