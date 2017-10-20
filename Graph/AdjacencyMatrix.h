#pragma once

using namespace std;

class AdjacencyMatrix
{
public:
	vector<vector<int>> matrix;
	int size;

	AdjacencyMatrix(int size); // prend une taille de matrice en entree
	AdjacencyMatrix(AdjacencyMatrix* mat); //copy
	void transpose(); 

	void drawMatrix();

	list<int> getInputs(int node); // retourne une liste des sommets d'arite d'entree du noeud d'un graphe oriente
	list<int> getOutputs(int node); // retourne une liste des sommets d'arite de sortie du noeud d'un graphe oriente

	list<list<int>> kosaraju(); // retourne la liste des composantes connexes
	vector<int> breathFirstSearch(); // retourne un vecteur des predecesseurs
	stack<int> depthFirstSearch(); // retourne l'ordre d'abandon de la recherche 

	void dijkstra(int source, vector<int>& length, vector<int>& prev);
	bool bellmanford(int source, vector<int>& length, vector<int>& prev);
	bool bellmanfordAcyclic(int source, vector<int>& length, vector<int>& prev);
	bool topologicalSort(vector<int>& order);
	void floydwarshall(vector<vector<int>>& dist, vector<vector<int>>& prev);

private:
	void exploreDFS(int node, list<int>& connexes, vector<bool>& visitedNodes, stack<int>& abandoned, vector<int>& first, vector<int>& end, int& clock);
};