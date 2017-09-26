#include "Graph.h"
#include "Orgraph.h"
#include <iostream>
#include <string>
#include <clocale>


using namespace std;



Graph graphs[20];
int graphs_count = 1;
Orgraph orgraphs[20];
int orgraphs_count = 1;








int set_orgraph(void)
{
	cout << "\n������� ��� �����:" << endl;
	char name[1000];
	cin >> name;
	cout << "\n�������� ���:\n1. ������� ���������.\n2. ������� �������������\n3. ������ ���������." << endl;
	int c1;
	cin >> c1;
	switch (c1)
	{
	case 1:
		orgraphs[orgraphs_count].set_with_adjacency_matrix(name);
		break;
	case 2:
		orgraphs[orgraphs_count].set_with_incidence_matrix(name);
		break;
	case 3:
		orgraphs[orgraphs_count].set_with_adjacency_list(name);
		break;
	default:
		cout << "\n����������� ���." << endl;
		return 0;
		break;
	}
	cout << "\n������ ���� ��� ������� " << orgraphs_count << "." << endl;
	orgraphs_count++;
	return 1;
}





int print_orgraph(int N)
{
	cout << "\n�������� ���:\n1. ������� ���������.\n2. ������� �������������\n3. ������ ���������." << endl;
	int c1;
	cin >> c1;
	switch (c1)
	{
	case 1:
		cout << endl;
		orgraphs[N].print_adjacency_matrix();
		break;
	case 2:
		cout << endl;
		orgraphs[N].print_incidence_matrix();
		break;
	case 3:
		cout << endl;
		orgraphs[N].print_adjacency_list();
		break;
	default:
		cout << "\n�������� �������" << endl;
		return 0;
		break;
	}
	return 1;
}





int record_orgraph(int N)
{
	cout << "\n������� ��� �����:" << endl;
	char name[1000];
	cin >> name;
	cout << "\n�������� ���:\n1. ������� ���������.\n2. ������� �������������\n3. ������ ���������." << endl;
	int c1;
	cin >> c1;
	switch (c1)
	{
	case 1:
		orgraphs[N].get_adjacency_matrix(name);
		break;
	case 2:
		orgraphs[N].get_incidence_matrix(name);
		break;
	case 3:
		orgraphs[N].get_adjacency_list(name);
		break;
	default:
		cout << "\n�������� �������" << endl;
		return 0;
		break;
	}
	cout << "\n������ ������ ��� ������� " << orgraphs_count << "." << endl;
	return 1;
}





int out_orgraph(int N)
{
	cout << "\n���� �������?\n1. �����.\n2. ����." << endl;
	int c1;
	cin >> c1;
	switch (c1)
	{
	case 1:
		print_orgraph(N);
		break;
	case 2:
		record_orgraph(N);
		break;
	default:
		cout << "\n�������� �������" << endl;
		return 0;
		break;
	}
	return 1;
}





int orgraph_control(int N)
{
	int command;
	do
	{
		cout << "\n���������� �������� " << N << ":\n1. ������� ������.\n2. ������� ������� �������.\n3. ������� ������� �������.\n4. ������� ��������� ������������������.\n5. ������� ���������� ���.\n6. �������� ������� � ����.\n7. ������� ������� �� �����.\n8. �������� ����. \n9. ������� ����.\
		\n10. ������������ ����.\n11. ������� ���������� �����.\n12. ���������� ������.\n13. �������������� ������.\n14. ������������ �������.\n15. ����������� �������.\n0. ������� � ������� ����." << endl;
		cin >> command;
		switch (command)
		{
		case 0:
			break;
		case 1:
			out_orgraph(N);
			break;
		case 2:
			cout << "\n������� �������: " << orgraphs[N].get_order() << endl;
			break;
		case 3:
			cout << "\n�������� �������:" << endl;
			int c1;
			cin >> c1;
			cout << "\n������� ������:" << orgraphs[N].get_vertex_out_degree(c1 - 1) << endl;
			cout << "\n������� �����:" << orgraphs[N].get_vertex_in_degree(c1 - 1) << endl;
			break;
		case 4:
			int c_m1[1000];
			int c_m2[1000];
			orgraphs[N].get_sequence_vertex_out_degree(c_m1);
			orgraphs[N].get_sequence_vertex_in_degree(c_m2);
			cout << "\n��������� ������������������ ������:" << endl;
			for (int i = 0; i < orgraphs[N].get_order(); i++) cout << c_m1[i] << " ";
			cout << endl;
			cout << "\n��������� ������������������ ������:" << endl;
			for (int i = 0; i < orgraphs[N].get_order(); i++) cout << c_m2[i] << " ";
			cout << endl;
			break;
		case 5:
			cout << "\n���������� ���: " << orgraphs[N].get_edges_count() << endl;
			break;
		case 6:
			cout << "\n�������?" << endl;
			int c2;
			cin >> c2;
			orgraphs[N].add_vertex(c2);
			cout << "\n������� ���������." << endl;
			break;
		case 7:
			cout << "\n�����?" << endl;
			int c3;
			cin >> c3;
			orgraphs[N].delete_vertex(c3 - 1);
			cout << "\n������� �������." << endl;
			break;
		case 8:
			cout << "\n�����?" << endl;
			int c4, c5, c6;
			cin >> c4;
			cin >> c5;
			cout << "\n���������?" << endl;
			cin >> c6;
			orgraphs[N].add_edge(c4 - 1, c5 - 1, c6);
			cout << "\n���� ���������." << endl;
			break;
		case 9:
			cout << "\n�����?" << endl;
			int c7, c8, c9;
			cin >> c7;
			cin >> c8;
			cout << "\n�������?" << endl;
			cin >> c9;
			orgraphs[N].delete_edge(c7 - 1, c8 - 1, c9);
			cout << "\n���� �������." << endl;
			break;
		case 10:
			cout << "\n�����?" << endl;
			int c10, c11;
			cin >> c10;
			cin >> c11;
			orgraphs[N].edge_subdivision(c10 - 1, c11 - 1);
			cout << "\n���� ����������." << endl;
			break;
		case 11:
			cout << endl;
			orgraphs[N].get_orgraph_addition().print_adjacency_matrix();
			cout << endl;
			break;
		case 12:
			cout << "\n�����?" << endl;
			int c12, c13;
			cin >> c12;
			cin >> c13;
			orgraphs[N].edge_subdivision(c12 - 1, c13 - 1);
			cout << "\n������� �������." << endl;
			break;
		case 13:
			cout << "\n�����?" << endl;
			int c14, c15;
			cin >> c14;
			cin >> c15;
			orgraphs[N].edge_subdivision(c14 - 1, c15 - 1);
			cout << "\n������� �������������." << endl;
			break;
		case 14:
			cout << "\n�������� �������:" << endl;
			int c16;
			cin >> c16;
			orgraphs[N].vertex_duplicate(c16 - 1);
			cout << "\n������� �����������." << endl;
			break;
			break;
		case 15:
			cout << "\n�������� �������:" << endl;
			int c17;
			cin >> c17;
			orgraphs[N].vertex_reproduction(c17 - 1);
			cout << "\n������� ����������." << endl;
			break;
			break;
		default:
			cout << "\n�������� �������" << endl;
			break;
		}

	} while (command != 0);
	return 1;
}





int menu_o(int command)
{
	switch (command)
	{
	case 1:
		set_orgraph();
		break;
	case 2:
		cout << "\n������� ����� �������" << endl;
		int c1;
		cin >> c1;
		orgraph_control(c1);
		break;
	case 3:
		int c2, c3, c4, c5;
		cout << "\n�������: 1. ������ ������. 2. ������ ������. 3. ��������. 4. ����� ������ �������.\n��������: 1. �����������. 2. ����������. 3. ������������." << endl;
		cin >> c2;
		cin >> c3;
		cin >> c4;
		cin >> c5;
		switch (c4)
		{
		case 1:
			orgraphs[c5] = orgraphs[c2] | orgraphs[c3];
			break;
		case 2:
			orgraphs[c5] = orgraphs[c2] + orgraphs[c3];
			break;
		case 3:
			orgraphs[c5] = orgraphs[c2] * orgraphs[c3];
			break;
		default:
			break;
		}
	default:
		cout << "\n�������� �������" << endl;
		return 0;
		break;
	}
	return 1;
}













int set_graph(void)
{
	cout << "\n������� ��� �����:" << endl;
	char name[1000];
	cin >> name;
	cout << "\n�������� ���:\n1. ������� ���������.\n2. ������� �������������\n3. ������ ���������." << endl;
	int c1;
	cin >> c1;
	switch (c1)
	{
	case 1: 
		graphs[graphs_count].set_with_adjacency_matrix(name);
		break;
	case 2: 
		graphs[graphs_count].set_with_incidence_matrix(name);
		break;
	case 3: 
		graphs[graphs_count].set_with_adjacency_list(name);
		break;
	default:
		cout << "\n����������� ���." << endl;
		return 0;
		break;
	}
	cout << "\n������ ���� ��� ������� " << graphs_count << "." << endl;
	graphs_count++;
	return 1;
}





int print_graph(int N)
{
	cout << "\n�������� ���:\n1. ������� ���������.\n2. ������� �������������\n3. ������ ���������." << endl;
	int c1;
	cin >> c1;
	switch (c1)
	{
	case 1:
		cout << endl;
		graphs[N].print_adjacency_matrix();
		break;
	case 2:
		cout << endl;
		graphs[N].print_incidence_matrix();
		break;
	case 3:
		cout << endl;
		graphs[N].print_adjacency_list();
		break;
	default:
		cout << "\n�������� �������" << endl;
		return 0;
		break;
	}
	return 1;
}





int record_graph(int N)
{
	cout << "\n������� ��� �����:" << endl;
	char name[1000];
	cin >> name;
	cout << "\n�������� ���:\n1. ������� ���������.\n2. ������� �������������\n3. ������ ���������." << endl;
	int c1;
	cin >> c1;
	switch (c1)
	{
	case 1:
		graphs[N].get_adjacency_matrix(name);
		break;
	case 2:
		graphs[N].get_incidence_matrix(name);
		break;
	case 3:
		graphs[N].get_adjacency_list(name);
		break;
	default:
		cout << "\n�������� �������" << endl;
		return 0;
		break;
	}
	cout << "\n������ ���� ��� ������� " << graphs_count << "." << endl;
	return 1;
}





int out_graph(int N)
{
	cout << "\n���� �������?\n1. �����.\n2. ����." << endl;
	int c1;
	cin >> c1;
	switch (c1)
	{
	case 1:
		print_graph(N);
		break;
	case 2:
		record_graph(N);
		break;
	default:
		cout << "\n�������� �������" << endl;
		return 0;
		break;
	}
	return 1;
}





int graph_control(int N)
{
	int command;
	do
	{
		cout << "\n���������� ������ " << N << ":\n1. ������� ����.\n2. ������� ������� �����.\n3. ������� ������� �������.\n4. ������� ��������� ������������������.\
			\n5. ������� ���������� �����.\n6. �������� ������� � ����.\n7. ������� ������� �� �����.\n8. �������� �����. \n9. ������� �����.\
			\n10. ������������ �����.\n11. ������� ���������� �����.\n12. ���������� ������.\n13. �������������� ������.\n14. ������������ �������.\n15. ����������� �������.\n0. ������� � ������� ����." << endl;
		cin >> command;
		switch (command)
		{
		case 0:
			break;
		case 1:
			out_graph(N);
			break;
		case 2:
			cout << "\n������� �����: " << graphs[N].get_order() << endl;
			break;			
		case 3:
			cout << "\n�������� �������:" << endl;
			int c1;
			cin >> c1;
			cout << "\n������� �������:" << graphs[N].get_vertex_degree(c1 - 1) << endl;
			break;
		case 4:
			int c_m[1000];
			graphs[N].get_sequence_vertex_degree(c_m);
			cout << "\n��������� ������������������:" << endl;
			for (int i = 0; i < graphs[N].get_order(); i++) cout << c_m[i] << " ";
			cout << endl;
			break;
		case 5:
			cout << "\n���������� �����: " << graphs[N].get_edges_count() << endl;
			break;
		case 6:
			cout << "\n�������?" << endl;
			int c2;
			cin >> c2;
			graphs[N].add_vertex(c2);
			cout << "\n������� ���������." << endl;
			break;
		case 7:
			cout << "\n�����?" << endl;
			int c3;
			cin >> c3;
			graphs[N].delete_vertex(c3 - 1);
			cout << "\n������� �������." << endl;
			break;
		case 8:
			cout << "\n�����?" << endl;
			int c4, c5, c6;
			cin >> c4;
			cin >> c5;
			cout << "\n���������?" << endl;
			cin >> c6;
			graphs[N].add_edge(c4 - 1, c5 - 1, c6);
			cout << "\n����� ���������." << endl;
			break;
		case 9:
			cout << "\n�����?" << endl;
			int c7, c8, c9;
			cin >> c7;
			cin >> c8;
			cout << "\n�������?" << endl;
			cin >> c9;
			graphs[N].delete_edge(c7 - 1, c8 - 1, c9);
			cout << "\n����� �������." << endl;
			break;
		case 10:
			cout << "\n�����?" << endl;
			int c10, c11;
			cin >> c10;
			cin >> c11;
			graphs[N].edge_subdivision(c10 - 1, c11 - 1);
			cout << "\n����� ����������." << endl;
			break;
		case 11:

			cout << "����?" << endl;
			int n;
			cin >> n;
			graphs[n] = graphs[N].get_graph_addition();
			cout << endl;
			break;
		case 12:
			cout << "\n�����?" << endl;
			int c12, c13;
			cin >> c12;
			cin >> c13;
			graphs[N].edge_subdivision(c12 - 1, c13 - 1);
			cout << "\n������� �������." << endl;
			break;
		case 13:
			cout << "\n�����?" << endl;
			int c14, c15;
			cin >> c14;
			cin >> c15;
			graphs[N].edge_subdivision(c14 - 1, c15 - 1);
			cout << "\n������� �������������." << endl;
			break;
		case 14:
			cout << "\n�������� �������:" << endl;
			int c16;
			cin >> c16;
			graphs[N].vertex_duplicate(c16 - 1);
			cout << "\n������� �����������." << endl;
			break;
			break;
		case 15:
			cout << "\n�������� �������:" << endl;
			int c17;
			cin >> c17;
			graphs[N].vertex_reproduction(c17 - 1);
			cout << "\n������� ����������." << endl;
			break;
			break;
		default:
			cout << "\n�������� �������" << endl;
			break;
		}

	} while (command != 0);
		return 1;
}





int menu(int command)
{
	switch (command)
	{
	case 1:
		set_graph();
		break;
	case 2:
		cout << "\n������� ����� �����" << endl;
		int c1;
		cin >> c1;
		graph_control(c1);
		break;
	case 3:
		int c2, c3, c4, c5;
		cout << "\n�������: 1. ������ ����. 2. ������ ����. 3. ��������. 4. ����� ������ �����.\n��������: 1. �����������. 2. ����������. 3. ������������." << endl;
		cin >> c2;
		cin >> c3;
		cin >> c4;
		cin >> c5;
		switch (c4)
		{
		case 1:
			graphs[c5] = graphs[c2] | graphs[c3];
			break;
		case 2:
			graphs[c5] = graphs[c2] + graphs[c3];
			break;
		case 3:
			graphs[c5] = graphs[c2] * graphs[c3];
			break;
		default:
			break;
		}
		break;
	default:
		cout << "\n�������� �������" << endl;
		return 0;
		break;
	}
	return 1;
}






int main(void)
{
	setlocale(LC_CTYPE, "rus");
	while (1){
		cout << "\n���:\n1. ����.\n2. ������." << endl;
		int c;
		cin >> c;
		int command;
		if (c == 1){
			do
			{
				cout << "\n������� ����:\n1. ������� ����� ����.\n2. ���������� ������.\n3. �������� ��� �������.\n0. �����." << endl;
				cin >> command;
				menu(command);

			} while (command != 0);
		}
		else if (c == 2)
		{
			do
			{
				cout << "\n������� ����:\n1. ������� ����� ������.\n2. ���������� ��������.\n3. �������� ��� ���������.\n0. �����." << endl;
				cin >> command;
				menu_o(command);

			} while (command != 0);
		}
		else
		{
			cout << "��" << endl;
		}
	}
	return 1;
}



