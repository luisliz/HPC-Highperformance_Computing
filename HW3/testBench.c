#include <stdio.h> 
#include <stdlib.h> 

#define INF 99999
#define MAX 500 

//HELPER FUNCTIONS 
void printDistances(int dist[MAX][MAX], int n) {
				printf("\nShortest distances between vertices\n"); 

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
void dijkstra(int G[MAX][MAX],int n,int startnode) {
				int cost[MAX][MAX],distance[MAX],pred[MAX];
				int visited[MAX],count,mindistance,nextnode,i,j;

				//pred[] stores the predecessor of each node
				//count gives the number of nodes seen so far
				//create the cost matrix
				for(i=0;i<n;i++)
								for(j=0;j<n;j++)
												if(G[i][j]==0)
																cost[i][j]=INF;
												else
																cost[i][j]=G[i][j];

				//initialize pred[],distance[] and visited[]
				for(i=0;i<n;i++)
				{
								distance[i]=cost[startnode][i];
								pred[i]=startnode;
								visited[i]=0;
				}

				distance[startnode]=0;
				visited[startnode]=1;
				count=1;

				while(count<n-1)
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

				//print the path and distance of each node
				for(i=0;i<n;i++)
								if(i!=startnode)
								{
												printf("\nDistance of node%d=%d",i,distance[i]);
												printf("\nPath=%d",i);

												j=i;
												do
												{
																j=pred[j];
																printf("<-%d",j);
												}while(j!=startnode);
								}
}

void floydAlgo(int graph[MAX][MAX], int n) {
				int distances[MAX][MAX], sum, i, j, k; 

				for(i = 0; i<n; i++)
								for(j=0; j< n; j++)
												distances[i][j] = graph[i][j]; 

				for(k=0; k<n; k++) {
								for(i = 0; i<n; i++) {
												for(j=0; j< n; j++) {
																sum = distances[i][k]+distances[k][j]; 
																if(sum < distances[i][j]) {
																				distances[i][j] = sum; 
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
				dijkstra(graph,n,0);
				return 0; 
}
