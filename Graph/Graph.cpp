#include "Graph.h"
#include "Orgraph.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <stdarg.h>


#define MAX(a, b) (a > b ? a : b)
#define INF INT_MAX


using namespace std;


Graph::Graph()
{
	order = 0;
}





Graph::~Graph()
{
}





void Graph::set_with_adjacency_matrix(char* file_name)
{
	ifstream file(file_name);
	char buff;
	int N = 0;
	vector<vector<string>> tmp_adjacency_matrix;
	size_t trash;


	while ((buff = file.get()) != EOF)
	{
		if (buff == '\n') N++;
	}
	order = N;


	adjacency_matrix.resize(N);
	for (int i = 0; i < N; i++)
	{
		adjacency_matrix[i] = vector<int>();
		adjacency_matrix[i].resize(N);
	}
	tmp_adjacency_matrix.resize(N);
	for (int i = 0; i < N; i++)
	{
		tmp_adjacency_matrix[i] = vector<string>();
		tmp_adjacency_matrix[i].resize(N);
	}


	file.clear();
	file.seekg(0, file.beg);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			file >> tmp_adjacency_matrix[i][j];
		}
	}
	file.close();


	for (int i = 0; i < order; i++)
	{
		for (int j = 0; j < order; j++)
		{
			if (tmp_adjacency_matrix[i][j] != "i") adjacency_matrix[i][j] = stoi(tmp_adjacency_matrix[i][j], &trash, 10);
			else adjacency_matrix[i][j] = INF;
		}
	}
}





void Graph::set_with_incidence_matrix(char* file_name)
{
	int elements_count = 0;
	int edges_count;
	int N = 0;
	vector<vector<int>> incidence_matrix;
	char buff;
	ifstream file(file_name);


	while ((buff = file.get()) != EOF)
	{
		if (buff == '\n') N++;
	}
	order = N;


	file.clear();
	file.seekg(0, file.beg);
	while (!file.eof())
	{
		file >> N;
		elements_count++;
	}
	edges_count = elements_count / order;


	incidence_matrix.resize(order);
	for (int i = 0; i < order; i++)
	{
		incidence_matrix[i] = vector<int>();
		incidence_matrix[i].resize(edges_count);
	}


	file.clear();
	file.seekg(0, file.beg);
	for (int i = 0; i < order; i++)
	{
		for (int j = 0; j < edges_count; j++)
		{
			file >> incidence_matrix[i][j];
		}
	}


	adjacency_matrix.resize(order);
	for (int i = 0; i < order; i++)
	{
		adjacency_matrix[i] = vector<int>();
		adjacency_matrix[i].resize(order);
	}


	int c1 = -1;
	int c2 = -1;
	for (int j = 0; j < edges_count; j++)
	{
		for (int i = 0; i < order; i++)
		{
			if (incidence_matrix[i][j] == 2)
			{
				c1 = i;
				c2 = i;
			}
			else if (incidence_matrix[i][j] == 1)
			{
				if (c1 == -1) c1 = i;
				else c2 = i;
			}
		}
		adjacency_matrix[c1][c2] += 1;
		adjacency_matrix[c2][c1] += 1;
		c1 = -1;
		c2 = -1;
	}
	file.close();
}





void Graph::set_with_adjacency_list(char* file_name)
{
	ifstream file(file_name);
	char buff;
	int N = 0;
	char a[10];
	char* end;


	while ((buff = file.get()) != EOF)
	{
		if (buff == '{') N++;
	}
	order = N;


	adjacency_matrix.resize(N);
	for (int i = 0; i < N; i++)
	{
		adjacency_matrix[i] = vector<int>();
		adjacency_matrix[i].resize(N);
	}


	file.clear();
	file.seekg(0, file.beg);
	int i = 0;
	while (!file.eof())
	{
		file >> a;
		if (a[0] == '{')
		{
			file >> a;
		}
		else if (a[0] == '}')
		{
			i++;
		}
		else if (strtol(a, &end, 10) != 0)
		{
			if ((strtol(a, &end, 10) - 1 == i)) adjacency_matrix[i][strtol(a, &end, 10) - 1] += 2;
			else adjacency_matrix[i][strtol(a, &end, 10) - 1] += 1;
		}
	}
	file.close();
}





void Graph::print_adjacency_matrix()
{
	vector<vector<string>> tmp_adjacency_matrix;
	tmp_adjacency_matrix.resize(order);
	for (int i = 0; i < order; i++)
	{
		tmp_adjacency_matrix[i] = vector<string>();
		tmp_adjacency_matrix[i].resize(order);
	}


	char buff[16];
	for (int i = 0; i < order; i++)
	{
		for (int j = 0; j < order; j++)
		{
			if (adjacency_matrix[i][j] != INF) tmp_adjacency_matrix[i][j] = itoa(adjacency_matrix[i][j], buff, 10);
			else tmp_adjacency_matrix[i][j] = "i";
		}
	}


	for (int i = 0; i < order; i++)
	{
		for (int j = 0; j < order; j++)
		{
			cout << tmp_adjacency_matrix[i][j] << ' ';
		}
		cout << '\n';
	}
	cout << '\n';
}





void Graph::print_incidence_matrix(void)
{
	int edges_count = get_edges_count();
	vector<int> buff(order, 0);
	vector<int> empty_buff(order, 0);
	vector<vector<int>> incidence_matrix;


	for (int i = 0; i < order; i++)
	{
		for (int j = i; j < order; j++)
		{
			if (adjacency_matrix[i][j] != 0)
			{
				if (i != j)
				{
					buff[i] = 1;
					buff[j] = 1;
					for (int k = 0; k < adjacency_matrix[i][j]; k++)
					{
						incidence_matrix.push_back(buff);
					}
					buff = empty_buff;
				}
				else
				{
					buff[i] = 2;
					for (int k = 0; k < adjacency_matrix[i][j] / 2; k++)
					{
						incidence_matrix.push_back(buff);
					}
					buff = empty_buff;
				}
			}
		}
	}


	for (int i = 0; i < order; i++)
	{
		for (int j = 0; j < edges_count; j++)
		{
			cout << incidence_matrix[j][i] << ' ';
		}
		cout << '\n';
	}
	cout << '\n';
}





void Graph::print_adjacency_list()
{
	for (int i = 0; i < order; i++)
	{
		cout << "{ " << i + 1;
		for (int j = 0; j < order; j++)
		{
			if (i != j)
			for (int k = 0; k < adjacency_matrix[i][j]; k++)
			{
				cout << ' ' << j + 1;
			}
			else 
			for (int k = 0; k < adjacency_matrix[i][j] / 2; k++)
			{
				cout << ' ' << j + 1;
			}
		}
		cout << " }\n";
	}
	cout << '\n';
}





void Graph::get_adjacency_matrix(char* file_name)
{
	ofstream file(file_name);
	for (int i = 0; i < order; i++)
	{
		for (int j = 0; j < order; j++)
		{
			file << adjacency_matrix[i][j] << ' ';
		}
		file << '\n';
	}
	file.close();
}





void Graph::get_incidence_matrix(char* file_name)
{
	int edges_count = get_edges_count();
	vector<int> buff(order, 0);
	vector<int> empty_buff(order, 0);
	vector<vector<int>> incidence_matrix;


	for (int i = 0; i < order; i++)
	{
		for (int j = i; j < order; j++)
		{
			if (adjacency_matrix[i][j] == 1)
			{
				buff[i] = 1;
				buff[j] = 1;
				incidence_matrix.push_back(buff);
				buff = empty_buff;
			}
			else if (adjacency_matrix[i][j] == 2)
			{
				buff[i] = 2;
				incidence_matrix.push_back(buff);
				buff = empty_buff;
			}
		}
	}


	ofstream file(file_name);


	for (int i = 0; i < order; i++)
	{
		for (int j = 0; j < edges_count; j++)
		{
			file << incidence_matrix[j][i] << ' ';
		}
		file << '\n';
	}
	file.close();
}





void Graph::get_adjacency_list(char* file_name)
{
	ofstream file(file_name);
	for (int i = 0; i < order; i++)
	{
		file << "{ " << i + 1;
		for (int j = 0; j < order; j++)
		{
			if (i != j)
			for (int k = 0; k < adjacency_matrix[i][j]; k++)
			{
				file << ' ' << j + 1;
			}
			else 
			for (int k = 0; k < adjacency_matrix[i][j] / 2; k++)
			{
				file << ' ' << j + 1;
			}
		}
		file << " } ";
	}
	file.close();
}





int Graph::get_order()
{
	return order;
}





int Graph::get_edges_count(void)
{
	int count = 0;
	for (int i = 0; i < order; i++)
	{
		for (int j = i; j < order; j++)
		{
			if (i != j) count += adjacency_matrix[i][j];
			else count += adjacency_matrix[i][j] / 2;
		}
	}
	return count;
}





int Graph::get_vertex_degree(int vertex)
{
	int degree = 0;
	for (int i = 0; i < order; i++)
	{
		degree += adjacency_matrix[vertex][i];
	}
	return degree;
}





void Graph::get_sequence_vertex_degree(int* sequence)
{
	for (int i = 0; i < order; i++)
	{
		sequence[i] = get_vertex_degree(i);
	}
}





void Graph::add_vertex(int count)
{
	vector<int> a(order);
	for (int i = 0; i < count; i++)
	{
		adjacency_matrix.push_back(a);
	}
	order += count;
	for (int i = 0; i < order; i++)
	{
		for (int j = 0; j < count; j++)
		{
			adjacency_matrix[i].push_back(0);
		}
	}
}





int Graph::delete_vertex(int vertex)
{
	if (vertex >= order)
	{
		cout << "invalid vertex!" << endl;
		return 0;
	}


	order--;
	adjacency_matrix.erase(adjacency_matrix.begin() + vertex);
	for (int i = 0; i < order; i++)
	{
		adjacency_matrix[i].erase(adjacency_matrix[i].begin() + vertex);
	}
	return 1;
}





int Graph::add_edge(int v1, int v2, int count)
{
	if (v1 >= order || v2 >= order)
	{
		cout << "invalid vertex!" << endl;
		return 0;
	}


	adjacency_matrix[v1][v2] += count;
	adjacency_matrix[v2][v1] += count;
	return 1;
}





int Graph::delete_edge(int v1, int v2, int count)
{
	if (v1 >= order || v2 >= order)
	{
		cout << "invalid vertex!" << endl;
		return 0;
	}
	if (count > adjacency_matrix[v1][v2])
	{
		cout << "invalid count!" << endl;
		return 0;
	}


	adjacency_matrix[v1][v2] -= count;
	adjacency_matrix[v2][v1] -= count;
	return 1;
}





int Graph::edge_subdivision(int v1, int v2)
{
	if (v1 >= order || v2 >= order)
	{
		cout << "invalid vertex!" << endl;
		return 0;
	}


	add_vertex(1);
	delete_edge(v1, v2, 1);
	add_edge(v1, order - 1, 1);
	add_edge(v2, order - 1, 1);
	return 1;
}





Graph Graph::get_graph_addition(void)
{
	Graph add_graph;
	add_graph.add_vertex(order);
	for (int i = 0; i < order; i++)
	{
		for (int j = 0; j < order; j++)
		{
			if (adjacency_matrix[i][j] == 0 && i != j) add_graph.adjacency_matrix[i][j] = 1;
		}
	}
	return add_graph;
}





int Graph::pull_off_edge(int v1, int v2)
{
	if (v1 >= order || v2 >= order)
	{
		cout << "range error!" << endl;
		return 0;
	}
	if (adjacency_matrix[v1][v2] == 0 || v1 == v2)
	{
		cout << "pull off error!" << endl;
		return 0;
	}


	for (int i = 0; i < order; i++)
	{
		if (i != v1)
		{
			adjacency_matrix[v1][i] = MAX(adjacency_matrix[v1][i], adjacency_matrix[v2][i]);
			adjacency_matrix[i][v1] = MAX(adjacency_matrix[i][v1], adjacency_matrix[i][v2]);
		}
	}


	delete_vertex(v2);
	return 1;
}





int Graph::matching_vertex(int v1, int v2)
{
	if (v1 >= order || v2 >= order)
	{
		cout << "matching error!" << endl;
		return 0;
	}
	

	for (int i = 0; i < order; i++)
	{
		if (i != v1)
		{
			adjacency_matrix[v1][i] = MAX(adjacency_matrix[v1][i], adjacency_matrix[v2][i]);
			adjacency_matrix[i][v1] = MAX(adjacency_matrix[i][v1], adjacency_matrix[i][v2]);
		}
	}


	delete_vertex(v2);
	return 1;
}





int Graph::vertex_duplicate(int vertex)
{
	if (vertex >= order)
	{
		cout << "invalid vertex!" << endl;
		return 0;
	}


	add_vertex(1);
	for (int i = 0; i < order - 1; i++)
	{
		if (adjacency_matrix[vertex][i] != 0)
		{
			if (i != vertex)
			{
				adjacency_matrix[order - 1][i] = adjacency_matrix[vertex][i];
				adjacency_matrix[i][order - 1] = adjacency_matrix[i][vertex];
			}
			else adjacency_matrix[order - 1][order - 1] = adjacency_matrix[vertex][vertex];
		}
	}
	return 1;
}





int Graph::vertex_reproduction(int vertex)
{
	if (vertex >= order)
	{
		cout << "invalid vertex!" << endl;
		return 0;
	}


	add_vertex(1);
	for (int i = 0; i < order - 1; i++)
	{
		if (adjacency_matrix[vertex][i] != 0)
		{
			if (i != vertex)
			{
				adjacency_matrix[order - 1][i] = adjacency_matrix[vertex][i];
				adjacency_matrix[i][order - 1] = adjacency_matrix[i][vertex];
			}
			else adjacency_matrix[order - 1][order - 1] = adjacency_matrix[vertex][vertex];
		}
	}
	adjacency_matrix[order - 1][vertex] = 1;
	adjacency_matrix[vertex][order - 1] = 1;
	return 1;
}





Graph Graph::operator |(Graph graph)
{
	Graph n_graph;
	n_graph.add_vertex(order + graph.order);
	for (int i = 0; i < order; i++)
	{
		for (int j = 0; j < order; j++)
		{
			n_graph.adjacency_matrix[i][j] = adjacency_matrix[i][j];
		}
	}
	for (int i = 0; i < graph.order; i++)
	{
		for (int j = 0; j < graph.order; j++)
		{
			n_graph.adjacency_matrix[i + order][j + order] = graph.adjacency_matrix[i][j];
		}
	}
	return n_graph;
}




Graph Graph::operator +(Graph graph)
{
	Graph n_graph;
	n_graph.add_vertex(order + graph.order);
	for (int i = 0; i < order; i++)
	{
		for (int j = 0; j < order; j++)
		{
			n_graph.adjacency_matrix[i][j] = adjacency_matrix[i][j];
		}
	}
	for (int i = 0; i < graph.order; i++)
	{
		for (int j = 0; j < graph.order; j++)
		{
			n_graph.adjacency_matrix[i + order][j + order] = graph.adjacency_matrix[i][j];
		}
	}
	for (int i = 0; i < order + graph.order; i++)
	{
		for (int j = 0; j < order + graph.order; j++)
		{
			if (((i >= order) && (j < order)) || ((i < order) && (j >= order))) n_graph.adjacency_matrix[i][j] = 1;
		}
	}
	return n_graph;
}





Graph Graph::operator *(Graph graph)
{
	Graph n_graph;
	n_graph.add_vertex(order * graph.order);
	for (int k = 0; k < graph.order; k++)
	{
		for (int i = 0; i < order; i++)
		{
			for (int j = 0; j < order; j++)
			{
				if (adjacency_matrix[i][j] != 0) n_graph.adjacency_matrix[i + k * order][j + k * order] += adjacency_matrix[i][j];
			}
		}
	}
	for (int k = 0; k < order; k++)
	{
		for (int i = 0; i < graph.order; i++)
		{
			for (int j = 0; j < graph.order; j++)
			{
				if (graph.adjacency_matrix[i][j] != 0) n_graph.adjacency_matrix[i * order + k][j * order + k] += graph.adjacency_matrix[i][j];
			}
		}
	}
	return n_graph;
}





bool Graph::is_vertex_coherence(int v1, int v2)
{
	vector<int> coherence_mas(order);
	coherence_mas[v1] = -1;
	bool flag = true;
	while (flag == true)
	{
		flag = false;
		for (int i = 0; i < order; i++)
		{
			if (coherence_mas[i] == -1)
			{
				coherence_mas[i] = 1;
				for (int j = 0; j < order; j++)
				{
					if ((adjacency_matrix[i][j] != 0) && (coherence_mas[j] != 1))
					{
						if (j == v2) return true;
						coherence_mas[j] = -1;
					}
				}
				flag = true;
			}
		}
	}
	return false;
}





int Graph::get_vertex_distance(int v1, int v2)
{
	if (is_vertex_coherence(v1, v2) == false) return -1;


	if (v1 == v2) return 0;


	int dist = 1;
	vector<int> coherence_mas(order);
	coherence_mas[v1] = -1;
	while (true)
	{
		for (int i = 0; i < order; i++)
		{
			if (coherence_mas[i] == -dist)
			{
				coherence_mas[i] = dist;
				for (int j = 0; j < order; j++)
				{
					if ((adjacency_matrix[i][j] != 0) && (coherence_mas[j] == 0))
					{
						if (j == v2) goto exit;
						coherence_mas[j] = -(dist + 1);
					}
				}
			}
		}
		dist++;
	}
exit:
	return dist;
}





bool Graph::is_vertex_disconnect(int v)
{
	for (int i = 0; i < order; i++)
	{
		if ((adjacency_matrix[v][i] != 0) && (i != v)) return false;
	}
	return true;
}





bool Graph::is_vertex_hanging(int v)
{
	int k = 0;
	for (int i = 0; i < order; i++)
	{
		if ((adjacency_matrix[v][i] != 0) && (i != v)) k++;
	}
	if (k == 1) return true;
	else return false;
}





int Graph::get_vertex_eccentricity(int v)
{
	int max = 0;
	int tmp;
	for (int i = 0; i < order; i++)
	{
		tmp = get_vertex_distance(v, i);
		if (tmp > max) max = tmp;
	}
	return max;
}





int Graph::get_graph_diameter(int component)
{
	int max = 0;
	int tmp;
	for (int i = 0; i < order; i++)
	{
		if (connected_components[i] == component)
		{
			tmp = get_vertex_eccentricity(i);
			if (tmp > max) max = tmp;
		}
	}
	return max;
}





int Graph::get_graph_radius(int component)
{
	int min = get_vertex_eccentricity(0);
	int tmp;
	for (int i = 0; i < order; i++)
	{
		if (connected_components[i] == component)
		{
			tmp = get_vertex_eccentricity(i);
			if (tmp < min) min = tmp;
		}
	}
	return min;
}





int Graph::is_vertex_central(int v)
{
	if (get_graph_radius(connected_components[v]) == get_vertex_eccentricity(v)) return true;
	else return false;
}





int Graph::is_vertex_peripheral(int v)
{
	if (get_graph_diameter(connected_components[v]) == get_vertex_eccentricity(v)) return true;
	else return false;
}





Graph Graph::get_frame(void)
{
	Graph frame_graph;
	frame_graph.add_vertex(order);
	vector<int> levels(order);
	levels[0] = 1;
	int level = 1;
	bool flag = true;
	while (flag == true)
	{
		flag = false;
		for (int i = 0; i < order; i++)
		{
			if (levels[i] == level)
			{
				for (int j = 0; j < order; j++)
				{
					if ((adjacency_matrix[i][j] != 0) && (levels[j] == 0))
					{
						levels[j] = level + 1;
						frame_graph.adjacency_matrix[i][j] = 1;
						frame_graph.adjacency_matrix[j][i] = 1;
						cout << "add edge " << i << "-" << j << endl;
					}
				}
				flag = true;
			}
		}
		level++;
	}
	return frame_graph;
}





Graph Graph::get_min_frame_by_Prim(void)
{
	Graph frame_graph;
	frame_graph.add_vertex(order);
	int min;
	int v_min;
	for (int i = 0; i < order; i++)
	{
		if ((adjacency_matrix[0][i] != 0) && (i != 0))
		{
			min = adjacency_matrix[0][i];
			v_min = i;
			break;
		}
	}
	for (int i = 0; i < order; i++)
	{
		if ((adjacency_matrix[0][i] != 0) && (i != 0) && (adjacency_matrix[0][i] < min))
		{
			min = adjacency_matrix[0][i];
			v_min = i;
		}
	}
	frame_graph.adjacency_matrix[0][v_min] = min;
	frame_graph.adjacency_matrix[v_min][0] = min;
	cout << "start from " << v_min << " vertex" << endl;


	for (int i = 0; i < order - 2; i++)
	{
		int min = INT_MAX;
		int v1_min;
		int v2_min;
		for (int j = 0; j < order; j++)
		{
			if (!frame_graph.is_vertex_disconnect(j))
			{
				for (int k = 0; k < order; k++)
				{
					if ((adjacency_matrix[j][k] != 0) && (frame_graph.is_vertex_disconnect(k)) && (adjacency_matrix[j][k] < min))
					{
						min = adjacency_matrix[j][k];
						v1_min = k;
						v2_min = j;
					}
				}
			}
		}
		frame_graph.adjacency_matrix[v1_min][v2_min] = min;
		frame_graph.adjacency_matrix[v2_min][v1_min] = min;
		cout << "add edge " << v1_min << "-" << v2_min << endl;
	}
	return frame_graph;
}





void Graph::get_Dijkstra_shortest_path(int v)
{
	vector<int> dist(order);
	vector<bool> flags(order);
	vector<int> predec(order);
	for (int i = 0; i < order; i++)
	{
		dist[i] = INF;
		flags[i] = 0;
		predec[i] = INF;
	}
	dist[v] = 0;
	int min;
	int min_v;
	for (int i = 0; i < order; i++)
	{
		min = INF;
		min_v;
		for (int j = 0; j < order; j++)
		{
			if ((dist[j] <= min) && (flags[j] == 0))
			{
				min = dist[j];
				min_v = j;
			}
		}
		if (min == INF) break;


		flags[min_v] = 1;
		for (int j = 0; j < order; j++)
		{
			if (adjacency_matrix[min_v][j] + dist[min_v] < dist[j])
			{
				dist[j] = adjacency_matrix[min_v][j] + dist[min_v];
				predec[j] = min_v;
			}
		}
	}
	for (int i = 0; i < order; i++)
	{
		if (dist[i] != INF) cout << dist[i] << " ";
		else cout << "i ";
	}
	cout << endl;
	for (int i = 0; i < order; i++)
	{
		if (predec[i] != INF) cout << predec[i] << " ";
		else cout << "i ";
	}
	cout << endl;
}





void Graph::get_connected_components(void)
{
	connected_components.resize(order);
	for (int i = 0; i < order; i++) connected_components[i] = -1;
	bool flag = 1;
	int number = 0;
	while (flag == 1)
	{
		flag = 0;
		for (int i = 0; i < order; i++)
		{
			if (connected_components[i] == -1)
			{
				flag = 1;
				mark(i, number);
				number++;
			}
		}
	}
	connected_components_count = number;
	/*for (int i = 0; i < order; i++)
	{
		cout << connected_components[i] << ' ';
	}
	cout << endl;*/
}





void Graph::mark(int v, int number)
{
	connected_components[v] = number;
	for (int i = 0; i < order; i++)
	{
		if ((adjacency_matrix[v][i] != 0) && (adjacency_matrix[v][i] != INF) && (i != v) && connected_components[i] == -1) mark(i, number);
	}
}