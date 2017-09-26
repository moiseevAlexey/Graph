#include <vector>


using namespace std;



class Orgraph
{
private:
	vector<vector<int>> adjacency_matrix;
	int order;
public:
	Orgraph();
	~Orgraph();
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
	int get_vertex_out_degree(int vertex);
	int get_vertex_in_degree(int vertex);
	void get_sequence_vertex_out_degree(int* sequence);
	void get_sequence_vertex_in_degree(int* sequence);
	void add_vertex(int count);
	int delete_vertex(int vertex);
	int add_edge(int v_out, int v_in, int count);
	int delete_edge(int v_out, int v_in, int count);
	int edge_subdivision(int v_out, int v_in);
	Orgraph get_orgraph_addition(void);
	int matching_vertex(int v1, int v2);
	int pull_off_edge(int v1, int v2);
	int vertex_duplicate(int vertex);
	int vertex_reproduction(int vertex);
	Orgraph operator |(Orgraph graph);
	Orgraph operator +(Orgraph graph);
	Orgraph operator *(Orgraph graph);
	bool is_vertex_coherence(int v_out, int v_in);
	int get_vertex_distance(int v_out, int v_in);
	bool is_vertex_disconnect(int v);
	bool is_vertex_source(int v);
	bool is_vertex_drain(int v);
	void get_sources();
	void get_drains();
	int get_vertex_eccentricity(int v);
	int get_graph_diameter(void);
	int get_graph_radius(void);
	int is_vertex_central(int v);
	int is_vertex_peripheral(int v);
	void get_Dijkstra_shortest_path(int v);
	void get_critical_way(void);
	int get_short_way(int s, int t, Orgraph* f_graph);
	int get_max_flow(int s, int t);
};

