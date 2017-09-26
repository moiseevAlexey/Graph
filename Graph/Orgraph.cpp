#include "Orgraph.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <stdarg.h>
#include <iomanip>


#define MAX(a, b) (a > b ? a : b)
#define INF 1000


using namespace std;


struct job
{
	int v_s;
	int v_f;
	int t_min_start;
	int t_min_finish;
	int t_max_start;
	int t_max_finish;
	int r;
	int w;
};





Orgraph::Orgraph()
{
	order = 0;
}





Orgraph::~Orgraph()
{
}






void Orgraph::set_with_adjacency_matrix(char* file_name)
{
	ifstream file(file_name);
	char buff;
	int N = 0;
	//vector<vector<string>> tmp_adjacency_matrix;
	vector<vector<int>> tmp_adjacency_matrix;
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
		//tmp_adjacency_matrix[i] = vector<string>();
		tmp_adjacency_matrix[i] = vector<int>();
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
			/*if (tmp_adjacency_matrix[i][j] != "i") */adjacency_matrix[i][j] = /*stoi(*/tmp_adjacency_matrix[i][j]/*, &trash, 10)*/;
			//else adjacency_matrix[i][j] = INF;
		}
	}
}





void Orgraph::set_with_incidence_matrix(char* file_name)
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


	int c1, c2;
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
				c1 = i;
			}
			else if (incidence_matrix[i][j] == -1)
			{
				c2 = i;
			}
		}
		if (c1 != c2) adjacency_matrix[c1][c2] += 1;
		else adjacency_matrix[c1][c2] += 2;
	}
	file.close();
}





void Orgraph::set_with_adjacency_list(char* file_name)
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





void Orgraph::print_adjacency_matrix()
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





void Orgraph::print_incidence_matrix(void)
{
	int edges_count = get_edges_count();
	vector<int> buff(order, 0);
	vector<int> empty_buff(order, 0);
	vector<vector<int>> incidence_matrix;


	for (int i = 0; i < order; i++)
	{
		for (int j = 0; j < order; j++)
		{
			if (adjacency_matrix[i][j] != 0)
			{
				if (j != i)
				{
					buff[i] = 1;
					buff[j] = -1;
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
			cout.width(2);
			cout << incidence_matrix[j][i] << ' ';
		}
		cout << '\n';
	}
	cout << '\n';
}





void Orgraph::print_adjacency_list()
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





void Orgraph::get_adjacency_matrix(char* file_name)
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





void Orgraph::get_incidence_matrix(char* file_name)
{
	int edges_count = get_edges_count();
	vector<int> buff(order, 0);
	vector<int> empty_buff(order, 0);
	vector<vector<int>> incidence_matrix;


	for (int i = 0; i < order; i++)
	{
		for (int j = 0; j < order; j++)
		{
			if (adjacency_matrix[i][j] != 0)
			{
				if (j != i)
				{
					buff[i] = 1;
					buff[j] = -1;
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





void Orgraph::get_adjacency_list(char* file_name)
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





int Orgraph::get_order()
{
	return order;
}





int Orgraph::get_edges_count(void)
{
	int count = 0;
	for (int i = 0; i < order; i++)
	{
		for (int j = 0; j < order; j++)
		{
			if (i != j) count += adjacency_matrix[i][j];
			else count += adjacency_matrix[i][j] / 2;
		}
	}
	return count;
}





int Orgraph::get_vertex_out_degree(int vertex)
{
	int degree = 0;
	for (int i = 0; i < order; i++)
	{
		degree += adjacency_matrix[vertex][i];
	}
	return degree;
}





int Orgraph::get_vertex_in_degree(int vertex)
{
	int degree = 0;
	for (int i = 0; i < order; i++)
	{
		degree += adjacency_matrix[i][vertex];
	}
	return degree;
}





void Orgraph::get_sequence_vertex_out_degree(int* sequence)
{
	for (int i = 0; i < order; i++)
	{
		sequence[i] = get_vertex_out_degree(i);
	}
}





void Orgraph::get_sequence_vertex_in_degree(int* sequence)
{
	for (int i = 0; i < order; i++)
	{
		sequence[i] = get_vertex_in_degree(i);
	}
	for (int i = 0; i < order - 1; i++) {
		for (int j = 0; j < order - i - 1; j++) {
			if (sequence[j] > sequence[j + 1]) {
				int b = sequence[j];
				sequence[j] = sequence[j + 1];
				sequence[j + 1] = b;
			}
		}
	}
}





void Orgraph::add_vertex(int count)
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





int Orgraph::delete_vertex(int vertex)
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





int Orgraph::add_edge(int v_in, int v_out, int count)
{
	if (v_out >= order || v_in >= order)
	{
		cout << "invalid vertex!" << endl;
		return 0;
	}


	adjacency_matrix[v_out][v_in] += count;
	return 1;
}





int Orgraph::delete_edge(int v_in, int v_out, int count)
{
	if (v_out >= order || v_in >= order)
	{
		cout << "invalid vertex!" << endl;
		return 0;
	}
	if (count > adjacency_matrix[v_in][v_out])
	{
		cout << "invalid count!" << endl;
		return 0;
	}


	adjacency_matrix[v_in][v_out] -= count;
	return 1;
}





int Orgraph::edge_subdivision(int v_in, int v_out)
{
	if (v_out >= order || v_in >= order)
	{
		cout << "invalid vertex!" << endl;
		return 0;
	}


	add_vertex(1);
	delete_edge(v_out, v_in, 1);
	add_edge(v_out, order - 1, 1);
	add_edge(v_in, order - 1, 1);
	return 1;
}





Orgraph Orgraph::get_orgraph_addition(void)
{
	Orgraph add_Orgraph;
	add_Orgraph.add_vertex(order);
	for (int i = 0; i < order; i++)
	{
		for (int j = 0; j < order; j++)
		{
			if (adjacency_matrix[i][j] == 0 && i != j) add_Orgraph.adjacency_matrix[i][j] = 1;
		}
	}
	return add_Orgraph;
}





int Orgraph::pull_off_edge(int v_in, int v_out)
{
	if (v_out >= order || v_in >= order)
	{
		cout << "range error!" << endl;
		return 0;
	}
	if (adjacency_matrix[v_out][v_in] == 0 || v_out == v_in)
	{
		cout << "pull off error!" << endl;
		return 0;
	}


	for (int i = 0; i < order; i++)
	{
		if (i != v_out)
		{
			adjacency_matrix[v_out][i] = MAX(adjacency_matrix[v_out][i], adjacency_matrix[v_in][i]);
			adjacency_matrix[i][v_out] = MAX(adjacency_matrix[i][v_out], adjacency_matrix[i][v_in]);
		}
	}


	delete_vertex(v_in);
	return 1;
}





int Orgraph::matching_vertex(int v_in, int v_out)
{
	if (v_out >= order || v_in >= order)
	{
		cout << "matching error!" << endl;
		return 0;
	}


	for (int i = 0; i < order; i++)
	{
		if (i != v_out)
		{
			adjacency_matrix[v_out][i] = MAX(adjacency_matrix[v_out][i], adjacency_matrix[v_in][i]);
			adjacency_matrix[i][v_out] = MAX(adjacency_matrix[i][v_out], adjacency_matrix[i][v_in]);
		}
	}


	delete_vertex(v_in);
	return 1;
}





int Orgraph::vertex_duplicate(int vertex)
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





int Orgraph::vertex_reproduction(int vertex)
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





Orgraph Orgraph::operator |(Orgraph orgraph)
{
	Orgraph n_orgraph;
	n_orgraph.add_vertex(order + orgraph.order);
	for (int i = 0; i < order; i++)
	{
		for (int j = 0; j < order; j++)
		{
			n_orgraph.adjacency_matrix[i][j] = adjacency_matrix[i][j];
		}
	}
	for (int i = 0; i < orgraph.order; i++)
	{
		for (int j = 0; j < orgraph.order; j++)
		{
			n_orgraph.adjacency_matrix[i + order][j + order] = orgraph.adjacency_matrix[i][j];
		}
	}
	return n_orgraph;
}




Orgraph Orgraph::operator +(Orgraph orgraph)
{
	Orgraph n_orgraph;
	n_orgraph.add_vertex(order + orgraph.order);
	for (int i = 0; i < order; i++)
	{
		for (int j = 0; j < order; j++)
		{
			n_orgraph.adjacency_matrix[i][j] = adjacency_matrix[i][j];
		}
	}
	for (int i = 0; i < orgraph.order; i++)
	{
		for (int j = 0; j < orgraph.order; j++)
		{
			n_orgraph.adjacency_matrix[i + order][j + order] = orgraph.adjacency_matrix[i][j];
		}
	}
	for (int i = 0; i < order + orgraph.order; i++)
	{
		for (int j = 0; j < order + orgraph.order; j++)
		{
			if (((i >= order) && (j < order)) || ((i < order) && (j >= order))) n_orgraph.adjacency_matrix[i][j] = 1;
		}
	}
	return n_orgraph;
}





Orgraph Orgraph::operator *(Orgraph orgraph)
{
	Orgraph n_orgraph;
	n_orgraph.add_vertex(order * orgraph.order);
	for (int k = 0; k < orgraph.order; k++)
	{
		for (int i = 0; i < order; i++)
		{
			for (int j = 0; j < order; j++)
			{
				if (adjacency_matrix[i][j] != 0) n_orgraph.adjacency_matrix[i + k * order][j + k * order] += adjacency_matrix[i][j];
			}
		}
	}
	for (int k = 0; k < order; k++)
	{
		for (int i = 0; i < orgraph.order; i++)
		{
			for (int j = 0; j < orgraph.order; j++)
			{
				if (orgraph.adjacency_matrix[i][j] != 0) n_orgraph.adjacency_matrix[i * order + k][j * order + k] += orgraph.adjacency_matrix[i][j];
			}
		}
	}
	return n_orgraph;
}





bool Orgraph::is_vertex_coherence(int v_out, int v_in)
{
	vector<int> coherence_mas(order);
	coherence_mas[v_out] = -1;
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
						if (j == v_in) return true;
						coherence_mas[j] = -1;
					}
				}
				flag = true;
			}
		}
	}
	return false;
}





int Orgraph::get_vertex_distance(int v_out, int v_in)
{
	if (is_vertex_coherence(v_out, v_in) == false) return -1;


	if (v_out == v_in) return 0;


	int dist = 1;
	vector<int> coherence_mas(order);
	coherence_mas[v_out] = -1;
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
						if (j == v_in) goto exit;
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





bool Orgraph::is_vertex_disconnect(int v)
{
	for (int i = 0; i < order; i++)
	{
		if ((adjacency_matrix[v][i] != 0) && (i != v)) return false;
		if ((adjacency_matrix[i][v] != 0) && (i != v)) return false;
	}
	return true;
}





bool Orgraph::is_vertex_source(int v)
{
	if (is_vertex_disconnect(v)) return false;
	for (int i = 0; i < order; i++)
	{
		if ((adjacency_matrix[i][v] != 0) && (i != v)) return false;
	}
	return true;
}





void Orgraph::get_sources()
{
	for (int i = 0; i < order; i++)
	{
		if (is_vertex_source(i)) cout << i << ' ';
	}
	cout << endl;
}





bool Orgraph::is_vertex_drain(int v)
{
	if (is_vertex_disconnect(v)) return false;
	for (int i = 0; i < order; i++)
	{
		if ((adjacency_matrix[v][i] != 0) && (i != v)) return false;
	}
	return true;
}





void Orgraph::get_drains()
{
	for (int i = 0; i < order; i++)
	{
		if (is_vertex_drain(i)) cout << i << ' ';
	}
	cout << endl;
}





int Orgraph::get_vertex_eccentricity(int v)
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





int Orgraph::get_graph_diameter(void)
{
	int max = 0;
	int tmp;
	for (int i = 0; i < order; i++)
	{
		tmp = get_vertex_eccentricity(i);
		if (tmp > max) max = tmp;
	}
	return max;
}





int Orgraph::get_graph_radius(void)
{
	int min = get_vertex_eccentricity(0);
	int tmp;
	for (int i = 1; i < order; i++)
	{
		tmp = get_vertex_eccentricity(i);
		if (tmp < min) min = tmp;
	}
	return min;
}





int Orgraph::is_vertex_central(int v)
{
	if (get_graph_radius() == get_vertex_eccentricity(v)) return true;
	else return false;
}





int Orgraph::is_vertex_peripheral(int v)
{
	if (get_graph_diameter() == get_vertex_eccentricity(v)) return true;
	else return false;
}





void Orgraph::get_Dijkstra_shortest_path(int v)
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
		cout << setw(2) << i + 1 << " ";
	}
	cout << endl;
	for (int i = 0; i < order; i++)
	{
		if (dist[i] != INF) cout << setw(2) << dist[i] << " ";
		else cout << setw(3) << "i ";
	}
	cout << endl;
	for (int i = 0; i < order; i++)
	{
		if (predec[i] != INF) cout << setw(2) << predec[i] + 1 << " ";
		else cout << setw(3) << "i ";
	}
	cout << endl;
}






void Orgraph::get_critical_way(void)
{
	//Инициализация списка работ
	vector<job> jobs; 
	int jobs_count = 0;
	job tmp;
	for (int i = 0; i < order; i++)
	{
		for (int j = 0; j < order; j++)
		{
			if ((adjacency_matrix[i][j] != INF) && (adjacency_matrix[i][j] != 0))
			{
				tmp.v_s = i;
				tmp.v_f = j;
				tmp.w = adjacency_matrix[i][j];
				jobs.push_back(tmp);
				jobs_count++;
			}
		}
	}


	//Поиск t_min_start и t_min_finish
	for (int i = 0; i < jobs_count; i++)
	{
		int t_max = 0;
		for (int j = 0; j < i; j++)
		{
			if ((jobs[j].v_f == jobs[i].v_s) && (jobs[j].t_min_finish > t_max)) t_max = jobs[j].t_min_finish;
		}
		jobs[i].t_min_start = t_max;
		jobs[i].t_min_finish = jobs[i].t_min_start + jobs[i].w;
	}


	//Поиск времени выполнения всех работ
	int t_critical = 0;
	for (int i = 0; i < jobs_count; i++)
	{
		if (jobs[i].t_min_finish > t_critical) t_critical = jobs[i].t_min_finish;
	}


	//Поиск t_max_start и t_max_finish
	for (int i = jobs_count - 1; i >= 0; i--)
	{
		int t_min = t_critical;
		for (int j = i; j < jobs_count; j++)
		{
			if ((jobs[j].v_s == jobs[i].v_f) && (jobs[j].t_max_start < t_min)) t_min = jobs[j].t_max_start;
		}
		jobs[i].t_max_finish = t_min;
		jobs[i].t_max_start = jobs[i].t_max_finish - jobs[i].w;
	}


	//Определение ресурса резерва
	for (int i = 0; i < jobs_count; i++) jobs[i].r = jobs[i].t_max_finish - jobs[i].t_min_finish;


	//Вывод
	
	printf("job|tmns|tmnf|tmxs|tmxf|  r\n");
	printf("------------------------------\n");
	/*for (int i = 0; i < jobs_count; i++)
	{
		printf("%2i-%2i | %2i | %2i | %2i | %2i | %2i\n", jobs[i].v_s, jobs[i].v_f, jobs[i].t_min_start, jobs[i].t_min_finish, jobs[i].t_max_start, jobs[i].t_max_finish, jobs[i].r);
	}
	printf("\n");
	printf("Critical jobs:\n");
	for (int i = 0; i < jobs_count; i++)
	{
		if (jobs[i].r == 0) printf("%2i - %2i\n", jobs[i].v_s, jobs[i].v_f);
	}
	*/
	int t_cr = 0;
	for (int i = 0; i < order; i++)
	{
		int tmns_max = 0;
		int tmnf_max = 0;
		int tmxs_max = 0;
		int tmxf_max = 0;
		for (int j = 0; j < jobs_count; j++)
		{
			if (jobs[j].v_f == i)
			{
				if (jobs[j].t_min_start > tmns_max) tmns_max = jobs[j].t_min_start;
				if (jobs[j].t_min_finish > tmnf_max) tmnf_max = jobs[j].t_min_finish;
				if (jobs[j].t_max_start > tmxs_max) tmxs_max = jobs[j].t_max_start;
				if (jobs[j].t_max_finish > tmxf_max) tmxf_max = jobs[j].t_max_finish;
			}
		}
		if (tmnf_max > t_cr) t_cr = tmnf_max;
		printf("%2i | %2i | %2i | %2i | %2i | %2i\n", i, tmns_max, tmnf_max, tmxs_max, tmxf_max, tmxs_max - tmns_max);
	}
	printf("T = %i", t_cr);
}





int Orgraph::get_short_way(int s, int t, Orgraph* f_graph)
{
	//Инициализация
	vector<int> short_way;
	vector<bool> choice(order);
	vector<int> pred(order);
	vector<int> att(order);
	att[s] = 1;
	bool flag = 1;
	for (int i = 0; i < order; i++) pred[i] = INF;


	//Обход в ширину
	while (flag == 1)
	{
		flag = 0;
		for (int i = 0; i < order; i++)
		{
			if (att[i] == 1)
			{
				for (int j = 0; j < order; j++)
				{
					if ((adjacency_matrix[i][j] != 0) && (att[j] == 0))
					{
						att[j] = 1;
						pred[j] = i;
						choice[j] = 1;
						flag = 1;
						if (j == t) goto exit;
					}
					else if ((f_graph->adjacency_matrix[j][i] != 0) && (att[j] == 0))
					{
						att[j] = 1;
						pred[j] = i;
						choice[j] = 0;
						flag = 1;
						if (j == t) goto exit;
					}
				}
				att[i] = 2;
			}
		}
	}
exit:


	//Выход с ошибкой
	if (flag == 0) return 0;


	//Поиск минимума
	short_way.push_back(t);
	int min = INF;
	int v = t;
	if (choice[t] == 1)
	{
		if (adjacency_matrix[pred[t]][t] < min) min = adjacency_matrix[pred[t]][t];
	}
	else
	{
		if (f_graph->adjacency_matrix[t][pred[t]] < min) min = f_graph->adjacency_matrix[t][pred[t]];
	}
	
	
	//Восстановление пути
	while (pred[v] != s)
	{
		v = pred[v];
		if (choice[v] == 1)
		{
			if (adjacency_matrix[pred[v]][v] < min) min = adjacency_matrix[pred[v]][v];
		}
		else
		{
			if (f_graph->adjacency_matrix[v][pred[v]] < min) min = f_graph->adjacency_matrix[v][pred[v]];
		}
		short_way.push_back(v);		
	}
	short_way.push_back(s);


	//Изменяем матрицы
	for (int i = 0; i < (short_way.size()) - 1; i++)
	{
		if (choice[short_way[i]] == 1)
		{
			f_graph->adjacency_matrix[short_way[i + 1]][short_way[i]] += min;
			adjacency_matrix[short_way[i + 1]][short_way[i]] -= min;
		}
		else
		{
			f_graph->adjacency_matrix[short_way[i]][short_way[i + 1]] -= min;
			adjacency_matrix[short_way[i]][short_way[i + 1]] += min;
		}
	}


	//Выход
	return min;
}





int Orgraph::get_max_flow(int s, int t)
{
	//Инициализация
	int max_flow = 0;
	Orgraph flow_graph;
	flow_graph.add_vertex(order);
	Orgraph tmp_graph;
	tmp_graph.add_vertex(order);
	tmp_graph.adjacency_matrix = adjacency_matrix;


	//Ищем все f-дополняющие цепи
	while (int tmp = get_short_way(s, t, &flow_graph))
	{
		max_flow += tmp;
	}


	//Вывод
	flow_graph.print_adjacency_matrix();
	printf("max_flow = %i\n", max_flow);
	return max_flow;
}