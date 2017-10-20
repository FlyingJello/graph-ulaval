#include "stdafx.h"

using namespace std;

int main()
{
	AdjacencyMatrix graph = AdjacencyMatrix(8);
	graph.matrix[0][2] = 2;
	graph.matrix[1][2] = 4;
	graph.matrix[2][3] = 3;
	graph.matrix[2][7] = 5;
	graph.matrix[4][2] = 1;
	graph.matrix[4][0] = 5;
	graph.matrix[5][3] = 1;
	graph.matrix[5][4] = 2;
	graph.matrix[6][0] = 4;
	graph.matrix[6][1] = 2;
	graph.matrix[7][5] = 3;
	graph.drawMatrix();

	cout << endl;
	cout << "DFS result :" << endl;
	stack<int> ordre = graph.depthFirstSearch();
	while (ordre.size() != 0)
	{
		cout << ordre.top();
		ordre.pop();
	}
	cout << endl;

	cout << "BFS result : " << endl;
	vector<int> prev = graph.breathFirstSearch();
	for (size_t i = 0; i < prev.size(); i++)
	{
		if (prev[i] == inf)
			cout << "-";
		else
			cout << prev[i];
	}
	cout << endl;

	cout << "Kosaraju result : " << endl;
	list<list<int>> composantes = graph.kosaraju();
	for each (auto list in composantes)
	{
		cout << "(";
		for each (auto node in list)
		{
			cout << node;
		}
		cout << ")";
	}
	cout << endl << endl;

	graph = AdjacencyMatrix(8);
	graph.matrix[0][1] = 4;
	graph.matrix[0][2] = 7;
	graph.matrix[2][6] = 3;
	graph.matrix[3][2] = 6;
	graph.matrix[3][5] = 2;
	graph.matrix[4][1] = 3;
	graph.matrix[4][3] = 4;
	graph.matrix[4][7] = 2;
	graph.matrix[5][4] = 3;
	graph.matrix[6][3] = 1;
	graph.matrix[6][5] = 4;
	graph.matrix[6][7] = 9;
	graph.matrix[7][5] = 3;
	graph.matrix[7][6] = 2;
	graph.drawMatrix();

	cout << endl << "Dijkstra result (0 -> 7): " << endl;
	vector<int> length;
	vector<int> previousNodes;
	graph.dijkstra(0, length, previousNodes);
	cout << "length : " << length[7] << endl;
	int prv = 7;
	stack<int> trace;
	trace.push(prv);
	while (prv != 0)
	{
		prv = previousNodes[prv];
		trace.push(prv);
	}
	cout << "trace : ";
	while (trace.size() != 0)
	{
		if (trace.size() != 1)
			cout << trace.top() << " -> ";
		else
			cout << trace.top() << endl;
		trace.pop();
	}
	cout << endl << endl;

	graph = AdjacencyMatrix(4);
	graph.matrix[0][1] = 4;
	graph.matrix[1][2] = 3;
	graph.matrix[1][3] = -2;
	graph.matrix[2][0] = 2;
	graph.matrix[2][3] = -6;
	graph.matrix[3][2] = 8;
	graph.drawMatrix();

	cout << endl << "Bellman-Ford result (0 -> 3): " << endl;
	length.clear();
	previousNodes.clear();
	cout << "success (1) or failure (0) : " << graph.bellmanford(0, length, previousNodes) << endl;
	cout << "length : " << length[3] << endl;
	prv = 3;
	trace.push(prv);
	while (prv != 0)
	{
		prv = previousNodes[prv];
		trace.push(prv);
	}
	cout << "trace : ";
	while (trace.size() != 0)
	{
		if (trace.size() != 1)
			cout << trace.top() << " -> ";
		else
			cout << trace.top() << endl;
		trace.pop();
	}
	cout << endl << endl;

	graph = AdjacencyMatrix(5);
	graph.matrix[0][1] = 3;
	graph.matrix[0][4] = -3;
	graph.matrix[1][3] = -6;
	graph.matrix[1][4] = 5;
	graph.matrix[2][0] = 5;
	graph.matrix[2][1] = -1;
	graph.matrix[2][4] = 5;
	graph.matrix[3][4] = -1;
	graph.drawMatrix();

	cout << endl << "Topological sort result : " << endl;
	vector<int> order;
	cout << "success (1) or failure (0) : " << graph.topologicalSort(order) << endl;
	cout << "order : ";
	for (size_t i = 0; i < order.size(); i++)
	{
		if (i == order.size() - 1)
			cout << order[i];
		else
			cout << order[i] << " -> ";

	}
	cout << endl << endl;

	cout << "Bellman-Ford acyclic result (2 -> 4): " << endl;
	length.clear();
	previousNodes.clear();
	cout << "success (1) or failure (0) : " << graph.bellmanfordAcyclic(2, length, previousNodes) << endl;
	cout << "length : " << length[4] << endl;
	prv = 4;
	trace.push(prv);
	while (prv != 2)
	{
		prv = previousNodes[prv];
		trace.push(prv);
	}
	cout << "trace : ";
	while (trace.size() != 0)
	{
		if (trace.size() != 1)
			cout << trace.top() << " -> ";
		else
			cout << trace.top() << endl;
		trace.pop();
	}
	cout << endl << endl;

	graph = AdjacencyMatrix(4);
	graph.matrix[0][3] = 8;
	graph.matrix[0][1] = 1;
	graph.matrix[1][2] = 4;
	graph.matrix[2][1] = 7;
	graph.matrix[2][3] = 9;
	graph.matrix[3][0] = 0;
	graph.matrix[3][1] = 2;
	graph.drawMatrix();

	cout << endl << "Floyd-Warshall result : " << endl;
	vector<vector<int>> distMat;
	vector<vector<int>> prevMat;
	graph.floydwarshall(distMat, prevMat);
	cout << "length matrix : " << endl;
	for (size_t i = 0; i < distMat.size(); i++)
	{
		for (size_t o = 0; o < distMat.size(); o++)
		{
			if (distMat.at(i).at(o) == inf)
				cout << "inf";
			else cout << distMat.at(i).at(o) << "  ";

			if (o < distMat.size() - 1) cout << ", ";
		}
		cout << endl;
	}
	cout << endl;
	for (size_t i = 0; i < prevMat.size(); i++)
	{
		for (size_t o = 0; o < prevMat.size(); o++)
		{
			if (prevMat.at(i).at(o) == inf)
				cout << "inf";
			else cout << prevMat.at(i).at(o) << "  ";

			if (o < prevMat.size() - 1) cout << ", ";
		}
		cout << endl;
	}

	string f;
	cin >> f;
	return 0;
}

