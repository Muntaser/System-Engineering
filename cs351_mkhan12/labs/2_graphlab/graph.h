typedef struct vertex vertex_t;
typedef struct adj_vertex adj_vertex_t;

struct vertex {
	char *name;
	adj_vertex_t *adj_list;
	vertex_t *next;
};

struct adj_vertex {
	vertex_t *vertex;
	int edge_weight;
	adj_vertex_t *next;	
};

/* This is the one function you really should implement as part of your 
 *  * graph data structure's public API. 
 *   *
 *    * `add_edge` adds the specified edge to the graph passed in via the first
 *     * argument. If either of the edge's vertices are not already in the graph,
 *      * they are added before their adjacency lists are updated. If the graph
 *       * is currently empty (i.e., *vtxhead == NULL), a new graph is created
 *        * and the caller's vtxhead pointer is modified. 
 *         *
 *          * `vtxhead`: the pointer to the graph (more specifically, the head of the
 *           *            list of vertex_t structures)
 *            * `v1_name`: the name of the first vertex of the edge to add
 *             * `v2_name`: the name of the second vertex of the edge to add
 *              * `weight` : the weight of the edge to add
 *               */

adj_vertex_t* add_edge(vertex_t *fir, adj_vertex_t *header, vertex_t *vtxhead, char *v1_name, char *v2_name, int weight);

vertex_t* add_vertex(vertex_t *header, char *pl);
adj_vertex_t* add_adjvertex(vertex_t *first, adj_vertex_t *header, char *pl, int weight);

adj_vertex_t* find_vertex(vertex_t *header, char *pl, adj_vertex_t *addver);

int mat_vertex(vertex_t *header, char *pl);

void free_list (vertex_t *nq);

void free_adj_list (vertex_t *q);

adj_vertex_t* add_adjvertex_at(vertex_t *first, adj_vertex_t *header, char *pl, int weight);

vertex_t* add_vertex_aux(char *pl);

int city_counter(vertex_t *header);

vertex_t* mat2(vertex_t *vl_head, char *argv);

vertex_t* traverse(vertex_t *header);

void setWeight(int w);

void setTour_path(int t);

int getWeight();

int getTour_path();









