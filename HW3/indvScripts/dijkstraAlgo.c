#include "heap.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

double* distances;

int compare(graph* g, unsigned int i, unsigned int j) {
				if(g->nodes[i].distance == g->nodes[j].distance) { return 0; }
				if(g->nodes[i].distance > g->nodes[j].distance) { return 1; }
				return -1;
}

void dijkstra(graph* g, unsigned int source) {
				unsigned int u, v, edge_count;
				node *n, *d;
				edge *e;
				heap *Q;

				g->nodes[source].distance = 0;
				Q = heap_make(compare, g);

				while(!heap_is_empty(Q)) {
								u = heap_delete_min(Q);
								n = &g->nodes[u];
								edge_count = n->edge_count;
								for(v = 0; v < edge_count; v++) {	
												e = &n->edges[v];	
												d = &g->nodes[e->destination];
												if(d->distance > n->distance + e->weight) {
																/* 
																	 Relajo los vertices 
																	 */			
																d->distance = n->distance + e->weight;
																/* 
																	 Actualizo el nodo con la distancia optima a este 
																	 */
																d->previous = u;
																/* 
																	 Actualizo la cola de prioridad (el vertice solo puede 
																	 haber subido en prioridad, entonces solo hago heapify-up 
																	 */
																heap_heapify_up(Q, d->heap_index);				
												}
								}
				}
				heap_destroy(Q);
}

int main() {

    graph* g;

	FILE *f;
	char buffer[100], ciudad[100], *ciudad_tmp;
	bool started_vertices;
	int src, dest;
	double distance;

	started_vertices = false;
	g = graph_make();
	f = fopen("grafo.txt", "r");

	while(fgets(buffer, 100, f) != NULL) {
		if(!started_vertices) {
			if(*buffer == '\n') { continue; }
			if(strcmp(buffer, "---\n") == 0) {
				started_vertices = true;
				continue;
			}
			sscanf(buffer, "%d) %[^\n]", &src, ciudad);
			ciudad_tmp = malloc(strlen(ciudad)+1);
			strcpy(ciudad_tmp, ciudad);
			graph_add_node(g, ciudad_tmp);
		} else {
			if(*buffer == '\n') { continue; }
			sscanf(buffer, "%d -> %d %lf\n", &src, &dest, &distance);
			graph_add_edge(g, src, dest, distance);
		}

	}

    dijkstra(g, 0); /* buscar partiendo de Buenos Aires */
    graph_dump(g, 3); /* colorear el camino a Roma. Sabemos que existe pues todos los caminos llevan a Roma. */
    graph_destroy(g);

    return 0;
}
