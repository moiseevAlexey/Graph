#include "Orgraph.h"
#include "Graph.h"
#include <iostream>
#include <stdio.h>
#include <string>
#include <clocale>



using namespace std;



int mainTemp(void)
{
	Graph graph_1;
	Graph graph_2;
	Orgraph or_1;
	//graph_1.set_with_adjacency_matrix("C:\\Users\\John\\Documents\\Visual Studio 2013\\Projects\\Graf\\G5.txt");
	//graph_1.print_adjacency_matrix();
	//graph_1.get_connected_components();
	//graph_2 = graph_1.get_frame();
	//graph_2.print_adjacency_matrix();
	or_1.set_with_adjacency_matrix("C:\\Games\\перенос\\Projects\\Graf\\lab3_test_2.txt");
	or_1.print_adjacency_matrix();

	//or_1.get_Dijkstra_shortest_path(0);
	or_1.get_critical_way();
	//or_1.get_max_flow(0, 6);
	/*graph_1.set_with_adjacency_matrix("C:\\Users\\John\\Documents\\Visual Studio 2013\\Projects\\Graf\\G6.txt");
	graph_1.print_adjacency_matrix();


	cout << "Hanging vertex: ";
	for (int i = 0; i < graph_1.get_order(); i++)
	{
		if (graph_1.is_vertex_hanging(i)) cout << i << ' ';
	}
	cout << endl;


	cout << "Isolated vertex: ";
	for (int i = 0; i < graph_1.get_order(); i++)
	{
		if (graph_1.is_vertex_disconnect(i)) cout << i << ' ';
	}
	cout << endl;

	graph_1.get_connected_components();
	for (int i = 0; i < graph_1.connected_components_count; i++)
	{
		cout << "Radius: of " << i + 1 << " component: " << graph_1.get_graph_radius(i) << endl << "Diameter: of " << i + 1 << " component: " << graph_1.get_graph_diameter(i) << endl;
	}

	cout << "Central vertex: ";
	for (int i = 0; i < graph_1.get_order(); i++)
	{
		if (graph_1.is_vertex_central(i)) cout << i << ' ';
	}
	cout << endl;


	cout << "Peripheral vertex: ";
	for (int i = 0; i < graph_1.get_order(); i++)
	{
		if (graph_1.is_vertex_peripheral(i)) cout << i << ' ';
	}
	cout << endl << endl;*/


	//graph_2 = graph_1.get_min_frame_by_Prim();
	//graph_2.print_adjacency_matrix();
	//or_1.get_max_flow(7, 6);
	//or_1.get_sources();
	//or_1.get_drains();
	//or_1.get_critical_way();
	//or_1.get_Dijkstra_shortest_path(0);
	getchar();
	return 1;
}






