#include <stdlib.h>
#include <stdio.h>
#include "graph.h"

int main (int argc, char *argv[]) {
/* 
 * * Programatically constructing the following simple graph:
 * *
 * *     10         5
 * * A <-----> B <-----> C
 * *
 * * Delete this code and add your own!
 * */

	vertex_t *header=NULL, *vp;
	int i;
	for(i=1;i<argc-1;i++){
		if (i%3==0)
			i++;
		header=add_vertex(header,argv[i]);
	}

	for (vp=header; vp!=NULL; vp=vp->next){
		adj_vertex_t *adjhead=NULL;
		for (i=1;i<argc;i=i+3)
			adjhead = add_edge(header, adjhead, vp, argv[i], argv[i+1], atoi(argv[i+2]));
		vp->adj_list=adjhead;
	}

	printf("Adjacency list:\n");
	for (vp = header; vp != NULL; vp = vp->next) {
		printf("  %s: ", vp->name);
		adj_vertex_t *adj_v;
		for (adj_v = vp->adj_list; adj_v != NULL; adj_v = adj_v->next)
			printf("%s(%d) ", adj_v->vertex->name, adj_v->edge_weight);
		printf("\n");
	}

	vertex_t *head=traverse(header);

	if (getTour_path()== city_counter(header)){
		printf("\n \n TOUR PATH: \n");
		while(head!=NULL){
			printf("%s ", head->name);
			head=head->next;
		}
		printf("\n");
		printf("\n \n TOUR LENGTH: \n");
		printf("%d \n",getWeight());
	}
	else
		printf("\n NOT POSSS \n");

	free_list (head);

	for (vp = header; vp!= NULL; vp= vp->next)
		free_adj_list (vp);

	free_list (header);
	free(head);

	return 0;
}





