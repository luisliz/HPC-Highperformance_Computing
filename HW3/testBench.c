#include <stdio.h> 
#include <stdlib.h> 

#define INF 99999
#define V 20 

void printDistances(int dist[V][V]) {
				printf("\nShortest distances between vertices\n"); 

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

void readFromArray(int graph[V][V]) {
				FILE *myFile; 
				myFile = fopen("graph.txt", "r"); 

				int i, j; 

				for(i =  0; i < V; i++) {
								for(j = 0; j<V; j++) {
												fscanf(myFile, "%d, ", &graph[i][j]); 
								}
				}
				
				fclose(myFile); 

}

void floydAlgo(int graph[V][V]) {
				int distances[V][V], sum, i, j, k; 

				for(i = 0; i<V; i++)
								for(j=0; j< V; j++)
												distances[i][j] = graph[i][j]; 

				for(k=0; k<V; k++) {
								for(i = 0; i<V; i++) {
												for(j=0; j< V; j++) {
																sum = distances[i][k]+distances[k][j]; 
																if(sum < distances[i][j]) {
																				distances[i][j] = sum; 
																}
																		
												}
								}
				}
				printDistances(distances); 
}



int main() {
				int graph[V][V] = {0}; 
				readFromArray(graph); 
				floydAlgo(graph); 

				return 0; 
}
