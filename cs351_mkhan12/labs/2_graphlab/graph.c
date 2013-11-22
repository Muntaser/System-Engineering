#include <stdlib.h>
#include <string.h>
#include "graph.h"

static int weight=0;
static int tour_path=0;

adj_vertex_t* add_edge(vertex_t *fir, adj_vertex_t *header, vertex_t *vtxhead, char *v1_name, char *v2_name, int weight) {
	vertex_t *temporary=vtxhead;
	if(!strcmp(v1_name,temporary->name))
		header = add_adjvertex(fir,header,v2_name,weight);
	else if(!strcmp(v2_name,temporary->name))
		header = add_adjvertex(fir,header,v1_name,weight);
	return header;
}


vertex_t* add_vertex(vertex_t *header, char *pl){
	if (header!=NULL){
		vertex_t* tale;
		if(!mat_vertex(header, pl)){
			for (tale=header; tale->next!=NULL; tale=tale->next){}
			tale->next=add_vertex_aux(pl);
		}
		return header;
	}
	else
		header=add_vertex_aux(pl);
	return header;
}

vertex_t* add_vertex_aux(char *pl){
		vertex_t* temporary= malloc(sizeof(vertex_t));
		temporary->name=pl;
		temporary->next=NULL;
		temporary->adj_list=NULL;
		return temporary;
}

adj_vertex_t* add_adjvertex(vertex_t *fir, adj_vertex_t *header, char *pl, int weight){
	if(header==NULL)
		header=add_adjvertex_at(fir, header, pl, weight);
	else{
		adj_vertex_t *addver;
		for (addver=header; addver->next!=NULL; addver=addver->next){}
			addver=addver->next=add_adjvertex_at(fir, header, pl, weight);
	}	
	return header;
}

adj_vertex_t* add_adjvertex_at(vertex_t *fir, adj_vertex_t *header, char *pl, int weight){
	adj_vertex_t* temporary= malloc(sizeof(adj_vertex_t));
	temporary=find_vertex(fir, pl, temporary);
	temporary->next=NULL;
	temporary->edge_weight=weight;
	return temporary;
}

/*find adjecent vertices to  vertex */
adj_vertex_t* find_vertex(vertex_t *header, char *pl, adj_vertex_t *addver){
	vertex_t *p;
	for(p=header;p!=NULL;p=p->next) {
		if(!strcmp(pl,p->name))
			addver->vertex=p;
	}
	return addver;
}

/*Checks if vertex is alreday in exist or not.*/
int mat_vertex(vertex_t *header, char *pl){
	vertex_t *temporary;
	for(temporary=header;temporary!=NULL;temporary=temporary->next){
		if(!strcmp(temporary->name,pl))
			return 1;
	}
	return 0;
} 

/*Free memory */
void free_list (vertex_t *nq) {
    vertex_t *adjv, *tmpt;
    adjv = nq;
    while (adjv != NULL) {
        tmpt = adjv->next;
        free(adjv);
        adjv = tmpt;
    }
}

void free_adj_list (vertex_t *q) {
    adj_vertex_t *adjv, *tmpt;
    adjv = q->adj_list;
    while (adjv != NULL) {
        tmpt = adjv->next;
        free(adjv);
        adjv = tmpt;
    }
}

int city_counter(vertex_t *header){
	vertex_t *z=header;
	int count=0;
	while(z!=NULL){
		count++;
		z=z->next;
	}
	return count;
}

vertex_t* mat2(vertex_t *vl_head, char *argv){
	vertex_t *curr = vl_head;
	int f = 0;
	while (curr!=NULL && f!=1){
		if (strcmp(argv, curr->name)==0)
			f = 1;
		else
			curr = curr->next;
	}
	return curr;
}

vertex_t* traverse(vertex_t *header){
	vertex_t* vp1=header, *head=NULL, *path=NULL, *temporary;
	adj_vertex_t* adj_v=vp1->adj_list;
	int count=city_counter(header);
	adj_vertex_t *tmpt[count];
	tmpt[0]=vp1->adj_list;
	int m1, m2=0;
	int weight=0, tour_path=0;
	while (tour_path<count && vp1!=NULL && adj_v!=NULL){
		if (tour_path==0){
			free_list(head);
			path=malloc(sizeof(vertex_t));
			path->name = vp1->name;
			head = path;
			path->next=malloc(sizeof(vertex_t));
			path->next->name=tmpt[0]->vertex->name;
			weight = weight + tmpt[0]->edge_weight;
			setWeight(weight);
			path=path->next;
			path->next=NULL;
			tour_path=2;
			setTour_path(tour_path);
			temporary=header;
			m1=0;
			temporary = mat2(temporary, path->name);
			tmpt[1] = temporary->adj_list;
		}
		else{
			m1 = 0;
			m1 = mat_vertex(head, tmpt[tour_path-1]->vertex->name);
			if (m1==0){
				path->next=malloc(sizeof(vertex_t));
				path->next->name=tmpt[tour_path-1]->vertex->name;
				weight = weight + tmpt[tour_path-1]->edge_weight;
				setWeight(weight);
				path=path->next;
				path->next=NULL;
				tour_path++;
				setTour_path(tour_path);
				temporary=header;
				temporary = mat2(temporary, path->name);
				tmpt[tour_path-1] = temporary->adj_list;
			}
			else{
				tmpt[tour_path-1]=tmpt[tour_path-1]->next;
				if (tmpt[tour_path-1]==NULL && tour_path>0 && tour_path<count){
					int l=1;
					m2=0;
					int posit=0;
					while (l<=tour_path-1 && m1!=1){
						if (tmpt[tour_path-1-l]->next!=NULL){
							posit = tour_path-1-l;
							m2=1;
						}
						l++;
					}
		
					if (m2==1){
						tmpt[posit]=tmpt[posit]->next;
						weight=0;
						setWeight(weight);
						tour_path=0;
						setTour_path(tour_path);
						temporary=head;
						vertex_t *iter=head;
						int n=0;
						while (n<posit){
							iter=iter->next;
							n++;
						}
						temporary = mat2(temporary, path->name);
						tour_path=posit+1;
						setTour_path(tour_path);
					}
					else{
						vp1=vp1->next;	
						tmpt[0]=vp1->adj_list;
						weight=0;
						setWeight(weight);
						tour_path=0;
						setTour_path(tour_path);
					}
				}
		}
	}
	if (adj_v==NULL && tour_path<count)
		head=NULL;
	}
	return head;
}

void setWeight(int w){
	weight=w;
}

void setTour_path(int t){
	tour_path=t;
}

int getWeight(){
	return weight;
}

int getTour_path(){
	return tour_path;
}




