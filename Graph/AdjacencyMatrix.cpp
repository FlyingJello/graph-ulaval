#include "stdafx.h"
#include "AdjacencyMatrix.h"

AdjacencyMatrix::AdjacencyMatrix(int size)
{
	AdjacencyMatrix::size = size;
	//set infinite for everything
	vector<int> row = vector<int>(size, inf);
	matrix = vector<vector<int>>(size, row);

	//set zeros to diagonal
	for (size_t i = 0; i < size; i++)
	{
		matrix.at(i).at(i) = 0;
	}
}

AdjacencyMatrix::AdjacencyMatrix(AdjacencyMatrix * mat)
{
	size = mat->size;
	matrix = mat->matrix;
}

void AdjacencyMatrix::transpose()
{
	for (size_t i = 0; i < size; i++)
	{
		for (size_t o = i; o < size; o++)
		{
			int temp = matrix[i][o];
			matrix[i][o] = matrix[o][i];
			matrix[o][i] = temp;
		}
	}
}

void AdjacencyMatrix::drawMatrix()
{
	for (size_t i = 0; i < size; i++)
	{
		cout << "  " << i << "  ";
	}
	cout << endl;
	for (size_t i = 0; i < size; i++)
	{
		cout << "=====";
	}
	cout << endl;
	for (size_t i = 0; i < size; i++)
	{
		for (size_t o = 0; o < size; o++)
		{
			if (matrix.at(i).at(o) == inf)
				cout << "inf";
			else cout << matrix.at(i).at(o) << "  ";

			if (o < size - 1) cout << ", ";
		}
		cout << endl;
	}
}

list<int> AdjacencyMatrix::getInputs(int node)
{
	list<int> inputs;
	for (size_t i = 0; i < size; i++)
	{
		if (matrix[i][node] != inf && i != node)
		{
			inputs.push_back(i);
		}
	}
	return inputs;
}

list<int> AdjacencyMatrix::getOutputs(int node)
{
	list<int> outputs;
	for (size_t i = 0; i < size; i++)
	{
		if (matrix[node][i] != inf && i != node)
		{
			outputs.push_back(i);
		}
	}
	return outputs;
}

list<list<int>> AdjacencyMatrix::kosaraju()
{
	AdjacencyMatrix transposed = this; //call to the copy constructor
	transposed.transpose();
	stack<int> abandoned = transposed.depthFirstSearch(); //abandoned nodes in order G^-1
	list<list<int>> composantes;
	vector<bool> visitedNodes = vector<bool>(size, false);

	while (!abandoned.empty())
	{
		int node = abandoned.top();
		abandoned.pop();
		if (!visitedNodes[node])
		{
			vector<int> first = vector<int>(size, 0);
			vector<int> end = vector<int>(size, 0);
			stack<int> abandoned;
			int clock;
			list<int> connexes;
			exploreDFS(node, connexes, visitedNodes, abandoned, first, end, clock);
			composantes.push_back(connexes);
		}
	}
	return composantes;
}

vector<int> AdjacencyMatrix::breathFirstSearch()
{
	vector<bool> visitedNodes = vector<bool>(size, false);
	vector<int> previousNodes = vector<int>(size, inf);
	queue<int> toVisit;

	for (size_t i = 0; i < size; i++)
	{
		if (!visitedNodes[i])
			toVisit.emplace(i);

		while (!toVisit.empty())
		{
			int node = toVisit.front();
			toVisit.pop();
			visitedNodes[node] = true;
			list<int> outputs = getOutputs(node);
			for each (int out in outputs)
			{
				if (!visitedNodes[out])
				{
					visitedNodes[out] = true;
					previousNodes[out] = node;
					toVisit.emplace(out);
				}
			}
		}
	}	
	return previousNodes;
}

stack<int> AdjacencyMatrix::depthFirstSearch()
{
	vector<bool> visitedNodes = vector<bool>(size, false);
	vector<int> first = vector<int>(size, 0);
	vector<int> end = vector<int>(size, 0);
	stack<int> abandoned;
	list<int> connexes;
	int clock = 0;
	for (size_t i = 0; i < size; i++)
	{
		if (!visitedNodes[i])
			exploreDFS(i, connexes, visitedNodes, abandoned, first, end, clock);
	}
	return abandoned;
}

void AdjacencyMatrix::dijkstra(int source, vector<int>& length, vector<int>& prev)
{
	length = vector<int>(size, inf);
	prev = vector<int>(size, inf);
	length[source] = 0;
	list<int> solved;
	list<int> unsolved;
	for (size_t i = 0; i < size; i++)
	{
		unsolved.push_back(i);
	}

	for (size_t i = 0; i < size; i++)
	{
		int smallestLength = inf;
		int node;
		for each (int unsolvedNode in unsolved)
		{
			if (length[unsolvedNode] < smallestLength)
			{
				smallestLength = length[unsolvedNode];
				node = unsolvedNode;
			}
		}

		unsolved.remove(node);
		solved.push_back(node);
		list<int> outputs = getOutputs(node);
		for each (int out in outputs)
		{
			int totalLength = smallestLength + matrix[node][out];
			if (totalLength < length[out]) {
				length[out] = totalLength;
				prev[out] = node;
			}
		}
	}

}

bool AdjacencyMatrix::bellmanford(int source, vector<int>& length, vector<int>& prev)
{
	length = vector<int>(size, inf);
	prev = vector<int>(size, inf);
	length[source] = 0;

	for (size_t i = 0; i < size - 1; i++)
	{
		for (size_t u = 0; u < size; u++)
		{
			list<int> outputs = getOutputs(u);
			for each (int out in outputs)
			{
				int totalLength = 0;
				if (length[u] == inf)
					totalLength = inf;
				else 
					totalLength = length[u] + matrix[u][out];

				if (totalLength < length[out])
				{
					length[out] = totalLength;
					prev[out] = u;
				}
			}
		}
	}
	for (size_t i = 0; i < size; i++)
	{
		list<int> outputs = getOutputs(i);
		for each (int out in outputs)
		{
			if (length[out] > length[i] + matrix[i][out])
				return false;
		}
	}
	return true;
}

bool AdjacencyMatrix::bellmanfordAcyclic(int source, vector<int>& length, vector<int>& prev)
{
	length = vector<int>(size, inf);
	prev = vector<int>(size, inf);
	length[source] = 0;

	vector<int> order;
	bool success = topologicalSort(order);
	if (!success)
		return false;

	for (size_t i = 0; i < size; i++)
	{
		int node = order[i];

		list<int> outputs = getOutputs(node);
		for each (int out in outputs)
		{
			int totalLength = 0;
			if (length[node] == inf)
				totalLength = inf;
			else
				totalLength = length[node] + matrix[node][out];

			if (totalLength < length[out])
			{
				length[out] = totalLength;
				prev[out] = node;
			}
		}
	}
	return true;
}

bool AdjacencyMatrix::topologicalSort(vector<int>& order)
{
	order = vector<int>(size);
	queue<int> sourceNodes;
	vector<int> inputCount = vector<int>(size);
	for (size_t i = 0; i < size; i++)
	{
		inputCount[i] = getInputs(i).size();
		if (inputCount[i] == 0)
			sourceNodes.push(i);
	}
	if (sourceNodes.empty())
		return false;

	int i = 0;
	while (!sourceNodes.empty())
	{
		int node = sourceNodes.front();
		sourceNodes.pop();
		order[i++] = node;
		list<int> outputs = getOutputs(node);
		for each (int out in outputs)
		{
			inputCount[out] --;
			if (inputCount[out] == 0)
				sourceNodes.push(out);
		}
	}
	return i == size;
}

void AdjacencyMatrix::floydwarshall(vector<vector<int>>& dist, vector<vector<int>>& prev)
{
	dist = prev = matrix;
	for (size_t i = 0; i < size; i++)
	{
		for (size_t j = 0; j < size; j++)
		{
			if (i != j && dist[i][j] != inf)
				prev[i][j] = i;
			else
				prev[i][j] = inf;
		}
	}

	for (size_t k = 0; k < size; k++)
	{
		for (size_t i = 0; i < size; i++)
		{
			for (size_t j = 0; j < size; j++)
			{
				int interNodeLength;
				if (dist[i][k] == inf || dist[k][j] == inf)
					interNodeLength = inf;
				else
					interNodeLength = dist[i][k] + dist[k][j];

				if (dist[i][j] > interNodeLength)
				{
					dist[i][j] = interNodeLength;
					prev[i][j] = prev[k][j];
				}
			}
		}
	}
}

void AdjacencyMatrix::exploreDFS(int node, list<int>& connexes, vector<bool>& visitedNodes, stack<int>& abandoned, vector<int>& first, vector<int>& end, int& clock)
{
	first[node] = clock;
	clock++;
	visitedNodes[node] = true;
	connexes.push_back(node);
	for (size_t i = 0; i < size; i++)
	{
		list<int> outputs = getOutputs(node);
		for each (int out in outputs)
		{
			if (!visitedNodes[out])
				exploreDFS(out, connexes, visitedNodes, abandoned, first, end, clock);
		}
	}
	end[node] = clock;
	clock++;
	abandoned.emplace(node);
}
