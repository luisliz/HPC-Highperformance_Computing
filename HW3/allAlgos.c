#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 

#define INF 99999
#define MAX 500 

//HELPER FUNCTIONS 
void printDistances(int dist[MAX][MAX], int n) { printf("\nShortest distances between vertices\n"); 

				for(int i = 0; i<n; i++) {
								for(int j=0; j< n; j++) {
												if(dist[i][j]==INF) printf("INF\t"); else 
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
void dijsk(int graph[MAX][MAX], int n, int startnode) { 
				int cost[MAX][MAX],distance[MAX],pred[MAX];
				int visited[MAX],count,mindistance,nextnode,i,j;

				for(i=0;i<n;i++)
								for(j=0;j<n;j++)
												if(graph[i][j]==0)
																cost[i][j]=INF;
												else
																cost[i][j]=graph[i][j];

				for(i=0;i<n;i++)
				{
								distance[i]=cost[startnode][i];
								pred[i]=startnode;
								visited[i]=0;
				}

				distance[startnode]=0;
				visited[startnode]=1;
				count=1;

				while(count<n)
				{
								mindistance=INF;

								//nextnode gives the node at minimum distance
								for(i=0;i<n;i++)
												if(distance[i]<mindistance&&!visited[i])
												{
																mindistance=distance[i];
																nextnode=i;
												}

								//check if a better path exists through nextnode			
								visited[nextnode]=1;
								for(i=0;i<n;i++)
												if(!visited[i])
																if(mindistance+cost[nextnode][i]<distance[i])
																{
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

void parDijsk(int graph[MAX][MAX], int n, int startnode) { 
				int cost[MAX][MAX],distance[MAX],pred[MAX];
				int visited[MAX],count,mindistance,nextnode,i,j;

				for(i=0;i<n;i++)
								for(j=0;j<n;j++)
												if(graph[i][j]==0)
																cost[i][j]=INF;
												else
																cost[i][j]=graph[i][j];

				for(i=0;i<n;i++)
				{
								distance[i]=cost[startnode][i];
								pred[i]=startnode;
								visited[i]=0;
				}

				distance[startnode]=0;
				visited[startnode]=1;
				count=1;

				while(count<n)
				{
								mindistance=INF;

								//nextnode gives the node at minimum distance
								for(i=0;i<n;i++)
												if(distance[i]<mindistance&&!visited[i])
												{
																mindistance=distance[i];
																nextnode=i;
												}

								//check if a better path exists through nextnode			
								visited[nextnode]=1;
								for(i=0;i<n;i++)
												if(!visited[i])
																if(mindistance+cost[nextnode][i]<distance[i])
																{
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
				//printDistances(distances, n); 
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
				//printDistances(distances, n); 
}

int main (int argc, char *argv[]) {
				int n = atoi(argv[1]); 
				int graph[MAX][MAX] = {0}; 
				clock_t t; 
				double time_taken; 
				readFromArray(graph, n); 
				
				printf("\nFloyd's Algo"); 
				t = clock(); 	
				floydAlgo(graph, n); 
				t = clock()-t; 
				time_taken = ((double)t)/CLOCKS_PER_SEC; 
				printf("\n\tSingle took: %f seconds", time_taken);

				t = clock(); 	
				parFloydAlgo(graph, n); 
				t = clock()-t; 
				time_taken = ((double)t)/CLOCKS_PER_SEC; 
				printf("\n\tParallel took: %f seconds\n", time_taken); 
				
				
				printf("\nDijkstra's Algo"); 
				t = clock(); 	
				for(int i = 0; i < n; i++) {
								dijsk(graph, n, i);
				}
				t = clock()-t; 
				time_taken = ((double)t)/CLOCKS_PER_SEC; 
				printf("\n\tSinlge took: %f seconds", time_taken);

				t = clock(); 	
				for(int i = 0; i < n; i++) {
								parDijsk(graph, n, i);
				}
				t = clock()-t; 
				time_taken = ((double)t)/CLOCKS_PER_SEC; 
				printf("\n\tParallel took: %f seconds\n", time_taken);

				
				

				return 0; 
}


