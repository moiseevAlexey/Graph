#include <vector>


using namespace std;


class Graph
{
private:
	vector<vector<int>> adjacency_matrix;
	vector<int> connected_components;
public:
	int connected_components_count;
	int order;
	Graph();
	~Graph();
	void set_with_adjacency_matrix(char* file_name);
	void set_with_incidence_matrix(char* file_name);
	void set_with_adjacency_list(char* file_name);
	void print_adjacency_matrix(void);
	void print_incidence_matrix(void);
	void print_adjacency_list(void);
	void get_adjacency_matrix(char* file_name);
	void get_incidence_matrix(char* file_name);
	void get_adjacency_list(char* file_name);
	int get_order(void);
	int get_edges_count(void);
	int get_vertex_degree(int vertex);
	void get_sequence_vertex_degree(int* sequence);
	void add_vertex(int count);
	int delete_vertex(int vertex);
	int add_edge(int v1, int v2, int count);
	int delete_edge(int v1, int v2, int count);
	int edge_subdivision(int v1, int v2);
	Graph get_graph_addition(void);
	int matching_vertex(int v1, int v2);
	int pull_off_edge(int v1, int v2);
	int vertex_duplicate(int vertex);
	int vertex_reproduction(int vertex);
	Graph operator |(Graph graph);
	Graph operator +(Graph graph);
	Graph operator *(Graph graph);
	bool is_vertex_coherence(int v1, int v2);
	int get_vertex_distance(int v1, int v2);
	bool is_vertex_disconnect(int v);
	bool is_vertex_hanging(int v);
	int get_vertex_eccentricity(int v);
	int get_graph_diameter(int component);
	int get_graph_radius(int component);
	int is_vertex_central(int v);
	int is_vertex_peripheral(int v);
	Graph get_frame(void);
	Graph get_min_frame_by_Prim(void);
	void get_Dijkstra_shortest_path(int v);
	void get_connected_components(void);
	void mark(int v, int number);
};

