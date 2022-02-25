/*   
/////////////////////////////////////////////////////////////////////////////////////////////////
In this file there the following classes:
	CLASS grafo: Implements a graph with n nodes 
				 The method PrimAlgorithm performs MST calculation with Prim Algorithm 
	CLASS MinPath: This is class derived from the grafo class that calculates the min path 

	CLASS KruskalGraph: Implements a graph for MST calculation with Kruskal algoritm 
/////////////////////////////////////////////////////////////////////////////////////////////////
*/

#include <iostream>
#include <iterator>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <ctime>
#include <list>
#include <climits>


using namespace std;


//////////////////////////////////////////
// CLASS GRAFO 
//////////////////////////////////////////
class grafo
{
protected:
	int num_nodi = 0;
	int **pMatrix;
	int* parent;

public:

	grafo() 
	{
		num_nodi = 0;  pMatrix	= nullptr; 
	}

	////////////////////////////////////////////////
	// returns the number of vertices in the graph
	////////////////////////////////////////////////
	int Vertice() { return num_nodi; }

	////////////////////////////////////////////////
	// returns the number of edges in the graph
	////////////////////////////////////////////////
	int Edges()
	{
		int num_archi = 0;
		for (int i = 0; i < num_nodi; ++i)
		{
			for (int j = 0; j < num_nodi; ++j)
				if (pMatrix[i][j] != 0)
					num_archi++;
		}
		return num_archi;
	}
	
	////////////////////////////////////////////////
	// tests whether there is an edge from node x to node y.
	////////////////////////////////////////////////
	bool adjacent(int i, int j)
	{
		if (i<num_nodi && j<num_nodi)
		{
			if (pMatrix[i][j] != 0)
				return true;
			else
				return false;
		}
		return false;

	}

	////////////////////////////////////////////////
	// removes the edge from x to y, if it is there.
	////////////////////////////////////////////////
	void remove(int i, int j)
	{
		if (i < num_nodi && j < num_nodi)
		{
			pMatrix[i][j] = 0;
		}
	}

	////////////////////////////////////////////////////////////////////////////////
	// get_edge_value( x, y) : returns the value associated to the edge(x, y).
	////////////////////////////////////////////////////////////////////////////////
	int get_edge_value(int i, int j)
	{
		if (i < num_nodi && j < num_nodi)
		{
			return pMatrix[i][j];
		}
	}

	////////////////////////////////////////////////////////////////////////////////
	// set_edge_value(x, y, v) : sets the value associated to the edge(x, y) to v.
	////////////////////////////////////////////////////////////////////////////////
	void  set_edge_value(int i, int j, int v)
	{
		if (i < num_nodi && j < num_nodi)
		{
			pMatrix[i][j] = v;
		}
	}

	// neighbors( x) : lists all nodes y such that there is an edge from x to y.
	void neighbors(int x)
	{
		if (x < num_nodi)
		{
			cout << "Neighbors of " << x << " = ";
			for (int j = 0; j < num_nodi; j++)
			{
				if (pMatrix[x][j] != 0)
				{
					cout << j << " ";
				}
			}
			cout << endl;
		}
	}

	//////////////////////////////////////////////////
	// Constructor: Create a graph of num nodes 
	//////////////////////////////////////////////////
	grafo(int num) 
	{ 
		num_nodi = num; 
		pMatrix = new int*[num_nodi]; 

		for (int i = 0; i < num_nodi; i++)
		{			
			pMatrix[i] = new int[num_nodi];
		}

		for (int i = 0; i < num_nodi; i++)
		{
			for (int j = 0; j < num_nodi; j++)
				pMatrix[i][j] = 0;
		}
	}

	//////////////////////////////////////////////////////////////
	// Constructor: Create a graph reading information from file 
	/////////////////////////////////////////////////////////////
	grafo(string filename)
	{
		ifstream myfile(filename);

		istream_iterator<string> start(myfile), end;

		vector<string> words(start, end);

		int num_row = words.size()-1;

		if (num_row <= 0)
			return;

		num_nodi = stoi(words[0]);

		pMatrix = new int* [num_nodi];

		for (int i = 0; i < num_nodi; i++)
		{
			pMatrix[i] = new int[num_nodi];
		}
		for (int i = 0; i < num_nodi; i++)
		{
			for (int j = 0; j < num_nodi; j++)
				pMatrix[i][j] = 0;
		}

		int k = 1;
		int x = 0;
		int y = 0;

		while (k < num_row)
		{
			x = stoi(words[k]);
			k++;
			y = stoi(words[k]);
			k++;
			//printf("Inserisco elemento i:%d, j:%d\n", x, y);
			pMatrix[x][y] = stoi(words[k]);
			k++;
		}
	}
	//////////////////////////////////////////////////
	// distructor
	//////////////////////////////////////////////////
	~grafo()
	{
		for (int i = 0; i < num_nodi; i++)
		{
			delete pMatrix[i];
		}
		num_nodi = 0;
	}

	////////////////////////////////////////////////////////////////////////////////
	// assign vector with costs to a node and his neighbors  (if 0 no link)
	///////////////////////////////////////////////////////////////////////////////
	int AddVector(int *vec, int ind) 
	{ 
		for (int j = 0; j < num_nodi; ++j)
			pMatrix[ind][j] = vec[j];

		return 0; 
	}

	////////////////////////////////////////////////////////
	// Generate a graph with density and distance in input 
	////////////////////////////////////////////////////////
	void GenerateRandomGraph(float density, int maxDistance)
	{
		srand(time(NULL));

		for (int i = 0; i < num_nodi; ++i)
		{
			for (int j = 0; j < num_nodi; ++j)
			{
				if (i == j)
					pMatrix[i][j] = 0;
				else
				{ 
					int dummy = (rand() % 10);
					float prob = (float)dummy/10.0;
					int value = (rand() % maxDistance)+1;
					//printf("probability %f\n", prob);
					//printf("valore generato %d\n", value);

					if (prob <= density)
						pMatrix[i][j] = value;
					else
						pMatrix[i][j] = 0;
				}
			}
		}
		cout << "GenerateRandomGraph density:" << density << "  maxDistance=" << maxDistance << endl;
	}

	
	////////////////////////////////////////////////////////
	//  Print graph 
	////////////////////////////////////////////////////////
	void PrintGraph()
	{
		int num_archi = 0;
		for (int i = 0; i < num_nodi; ++i)
		{
			for (int j = 0; j < num_nodi; ++j)
				if (pMatrix[i][j] != 0)
				{
					cout << i << " --> " << j << "   " << pMatrix[i][j] << endl;
					num_archi++;
				}
		}
		cout << " num archi = " << num_archi << endl;

		float density = (float)(num_archi) / (float)(num_nodi * (num_nodi - 1));
		cout << " graph density=" << density << endl;
	}

	void CalculateMinPathFromTo(int first, int last);


	// The function finds the vertex with minimum key value, from the set of vertices not yet included in MST
	int minKey(int key[], bool mstSet[])
	{
		// Initialize min value
		int min = INT_MAX;
		int min_index=-1;

		for (int v = 0; v < num_nodi; v++)
			if (mstSet[v] == false && key[v] < min)
			{
				min = key[v];
				min_index = v;
			}

		return min_index;
	}

	////////////////////////////////////////////////////////
	// Prim Algorithm
	////////////////////////////////////////////////////////
	void PrimAlgorithm()
	{
		cout << "********************************* \n";
		cout << "Prim Algorithm                    \n";
		cout << "********************************* \n";

		parent = new int [num_nodi] {0};  // Array to store constructed MST
		for (int j = 0; j < num_nodi; ++j)
			parent[j] = 0;

		int* key = new int [num_nodi];  // Key values for minimum weight edge, Initialized to INFINITE
		for (int j = 0; j < num_nodi; ++j)
			key[j] = INT_MAX;

		bool* mst = new bool [num_nodi] {false};   // To set if vertices are included or not in the MST
		for (int j = 0; j < num_nodi; ++j)
			mst[j] = 0;

		
		// Always include first 1st vertex in MST.
		key[0] = 0; // Make key 0 so that this vertex is picked as first vertex
		parent[0] = -1; // First node is always root of MST

		
		for (int count = 0; count < num_nodi - 1; count++)
		{
			// Find the minimum key vertex from the set of vertices not yet included in MST
			int u = minKey(key, mst);  

			// set the vertex is included in the MST 
			mst[u] = true;

			// Update key value and parent index of the adjacent vertices of the find vertex. 
			// Consider only those vertices which are not yet included in MST
			for (int v = 0; v < num_nodi; v++)
			{
				// graph[u][v] is non zero only for adjacent vertices of m
				// mst[v] is false for vertices not yet included in MST
				// Update the key only if graph[u][v] is smaller than key[v]
				if (pMatrix[u][v] && mst[v] == false && pMatrix[u][v] < key[v])
				{					
					parent[v] = u;
					key[v] = pMatrix[u][v];
				}
			}

		}
	}
	////////////////////////////////////////////////////////
	// Print the constructed MST stored in parent
	////////////////////////////////////////////////////////
	void printMST()
	{
		cout << "Prim Algorithm Result\n";
		
		int weight = 0;
		cout << "Edge   Weight \n";
		for (int i = 1; i < num_nodi; i++)
		{
			printf("%d - %d    %d \n", parent[i], i, pMatrix[i][parent[i]]);
			weight += pMatrix[i][parent[i]];
		}
		cout << "\nWeight of MST is " << weight;
		cout << "\n";
	}

};



//////////////////////////////////////////
// CLASS MinPath
// Class for the min path calculation 
//
// Methods:
//  CalculatePath  
//		find shortest path between first node and last node 
//		print the sequence of vertices representing shorest path 	
//
//		Description:
//		while there are nodes to visit
//			select a node
//			set node visited
//			update distance of visitable nodes adjacent to the node
//			(distance = sum of previous distance node and cost current path if value is minor of previous value)
//			select, between visitable nodes, the one at minor distance
//
//  PrintMinPath
//		print the min path
//		reorder the min path
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////
class MinPath : public grafo
{
private:
	int* P = nullptr;
	int* S = nullptr;
	int* Prec = nullptr;
	int numNodi = 0;
	int** pM;

public:
	////////////////////////////////////////////////////////
	// Constructor
	////////////////////////////////////////////////////////
	MinPath(int num_nodi, int **pMatrix)
	{
		numNodi = num_nodi;
		pM = pMatrix;
		P = new int [num_nodi] {INT_MAX};  // distance 
		S = new int [num_nodi] { 0};       // node status  (1= visited, 0=not visited)
		Prec = new int [num_nodi] {-1};    // 

		for (int i = 0; i < num_nodi; ++i)
		{
			S[i] = 0;
			P[i] = INT_MAX;
		}
	}
	////////////////////////////////////////////////////////
	//  GetNextNode: return node with minor distance
	////////////////////////////////////////////////////////
	int GetNextNode(const int N, int* p, int* s)
	{
		int min = INT_MAX;
		int index = -1;

		for (int i = 0; i < N; ++i)
		{
			if (s[i] == 0 && p[i] != INT_MAX)
			{
				if (min == -1 || p[i] < min)
				{
					min = p[i];
					index = i;
				}
			}
		}
		return index;
	}
	////////////////////////////////////////////////////////
	// CalculatePath
	////////////////////////////////////////////////////////
	void CalculatePath(int first, int last)
	{
		int k = first;

		while (k != -1)    // while there are nodes to visit (1)
		{
			S[k] = 1;   // set node visited 
			cout << "node selected " << k << endl;

			// AGGIORNA I NODI VISITABILI ADIACENTI AL NODO SELEZIONATO
			for (int i = 0; i < numNodi; i++)
			{
				int val = pM[k][i];

				if (val != 0 && S[i] == 0)
				{
					if (P[k] == INT_MAX)
					{
						if (val < P[i])
						{
							P[i] = val;
							Prec[i] = k;
							//cout << "node definitivo  " << i << endl;
						}
					}
					else if (P[k] + val < P[i])
					{
						P[i] = P[k] + val;
						Prec[i] = k;
						cout << "aggiorno " << i << " P= " << P[i] << "prec=" << k << endl;
					}
				}
			}

			// select node with minor distance between all visitable node  
			k = GetNextNode(numNodi, P, S);
		}
	}
	////////////////////////////////////////////////////////
	// PrintMinPath
	////////////////////////////////////////////////////////
	void PrintMinPath(int first, int last)
	{
		cout << "path cost=" << P[last] << endl;
		cout << "Shortest path from node " << first << " to node " << last << " :" << endl;

		int nodo = last;
		int* result = new int [numNodi] { 0};       // node status  (1= visited, 0=not visited)
		int i = 0;

		while (nodo != first)
		{
			cout << nodo << " ";
			result[i] = nodo;
			i++;
			nodo = Prec[nodo];
		}
		cout << nodo << endl;
		result[i] = nodo;


		cout << "Shortest path reordered:\n";
		for (; i >= 0; i--)
			cout << result[i] << " ";
		cout << endl;
	}
};

////////////////////////////////////////////////////////
// CalculateMinPathFromTo
////////////////////////////////////////////////////////
void grafo::CalculateMinPathFromTo(int first, int last)
{
	MinPath mycalc = MinPath(num_nodi, pMatrix);
	mycalc.CalculatePath(first, last);
	mycalc.PrintMinPath(first, last);
}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef pair<int, int> iPair;

//structure for graph
class DisjointSets
{
private:

	int* parent, * rnk;
	int n;

public:
	DisjointSets(int n)
	{
		this->n = n;
		parent = new int[n + 1];
		rnk = new int[n + 1];
		for (int i = 0; i <= n; i++) 
		{
			rnk[i] = 0;
			parent[i] = i;
		}
	}

	int find(int u)
	{
		if (u != parent[u])
			parent[u] = find(parent[u]);
		return parent[u];
	}

	void merge(int x, int y)
	{
		x = find(x), y = find(y);
		if (rnk[x] > rnk[y])
			parent[y] = x;
		else
			parent[x] = y;
		if (rnk[x] == rnk[y])
			rnk[y]++;
	}
};




//////////////////////////////////////////
// CLASS KruskalGraph 
//////////////////////////////////////////
class KruskalGraph
{
private:

	int num_nodi;
	int num_edges;
	vector< pair<int, iPair> > edges;
	vector< pair<int, iPair> > MST_edges;

public:
	///////////////////////////////////////////////////////////////////////
	// Constructor: Create a KruskalGraph reading information from file 
	/////////..........////////////////////////////////////////////////////
	KruskalGraph(string filename)
	{
		ifstream myfile(filename);

		istream_iterator<string> start(myfile), end;

		vector<string> words(start, end);

		int num_row = words.size() - 1;

		if (num_row <= 0)
			return;

		num_nodi = stoi(words[0]);

		int k = 1;
		int x = 0;
		int y = 0;

		while (k < num_row)
		{
			x = stoi(words[k]);
			k++;
			y = stoi(words[k]);
			k++;

			AddEdge(x, y, stoi(words[k]));
			//printf("Add Edge i:%d, j:%d\n", x, y);
			k++;
		}
	}
	///////////////////////////////////////////////////////////////////////
	// returns num od edges
	///////////////////////////////////////////////////////////////////////
	int GetNumEdges()
	{
		return edges.size();
	}

	///////////////////////////////////////////////////////////////////////
	// Constructor
	///////////////////////////////////////////////////////////////////////
	KruskalGraph(int V, int E)
	{
		this->num_nodi = V;
		this->num_edges = E;
	}

	//////////////////////////////////////////////////////
	// AddEdge: the function add a Edge to current graph
	//////////////////////////////////////////////////////
	void AddEdge(int u, int v, int w)
	{
		edges.push_back({ w, {u, v} });
		num_edges++;
	}

	/////////////////////////////////////////////////////////////
	// AddMSTEdge: the function add a Edge to MST graph
	/////////////////////////////////////////////////////////////
	void AddMSTEdge(int u, int v, int w)
	{
		MST_edges.push_back({ w, {u, v} });
	}

	////////////////////////////////////////////////////////
	//  Print graph 
	////////////////////////////////////////////////////////
	void PrintGraph()
	{
		vector< pair<int, iPair> >::iterator it;
		for (it = edges.begin(); it != edges.end(); it++)
		{
			int u = it->second.first;
			int v = it->second.second;
			int p = it->first;
			
			cout << u << " --> " << v << "   " << p << endl;
		}
		
		cout << " num edges= " << num_edges << endl;

		float density = (float)(num_edges) / (float)(num_nodi * (num_nodi - 1));
		cout << " graph density=" << density << endl;
	}
	////////////////////////////////////////////////////////
	//  Print MST graph 
	////////////////////////////////////////////////////////
	void PrintMSTGraph()
	{
		cout << "Kruskal Algorithm Result\n";
		int weight = 0;

		cout << "Edge    Weight \n";
		vector< pair<int, iPair> >::iterator it;
		for (it = MST_edges.begin(); it != MST_edges.end(); it++)
		{
			int u = it->second.first;
			int v = it->second.second;
			int p = it->first;
			weight += p;
			cout << u << " --> " << v << "   " << p << endl;
		}
		cout << "\nWeight of MST is " << weight;
		cout << "\n";
	}

	///////////////////////////////////////////////////////////////////////
	// KruskalMST: the function calculate MST with Kruskal Algorithm 
	///////////////////////////////////////////////////////////////////////
	int KruskalMST()
	{
		cout << "********************************* \n";
		cout << "Kruskal Algorithm                 \n";
		cout << "********************************* \n";
		int mst_wt = 0;
		sort(edges.begin(), edges.end());

		DisjointSets ds(num_nodi);

		vector< pair<int, iPair> >::iterator it;

		for (it = edges.begin(); it != edges.end(); it++)
		{
			int u = it->second.first;
			int v = it->second.second;
			int set_u = ds.find(u);
			int set_v = ds.find(v);
			if (set_u != set_v)
			{

				//cout << u << " - " << v << " - " << it->first << endl;
				AddMSTEdge(u, v, it->first);
				mst_wt += it->first;
				ds.merge(set_u, set_v);
			}
		}
		return mst_wt;
	}
};





///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
int Esercizio4()
{

/*
	const int N = 7;

	/*                           c  A  B  C  D  E  U
	vector <int>  MATRIX[N] = { {0, 2, 0, 0, 8, 0, 0},
								{2, 0, 2, 2, 0, 0, 0 },
								{0, 6, 0, 0, 0, 0, 2},
								{0, 2, 0, 0, 2, 9, 0},
								{8, 0, 0, 2, 0, 3, 0},
								{0, 0, 0, 0, 3, 0, 1},
								{0, 0, 5, 0, 0, 1, 0 } };


	vector <int>  MATRIX[N] = { {0, 2, 0, 0, 8, 0, 0},
								{2, 0, 6, 2, 0, 0, 0 },
								{0, 6, 0, 0, 0, 0, 5},
								{0, 2, 0, 0, 2, 9, 0},
								{8, 0, 0, 2, 0, 3, 0},
								{0, 0, 0, 0, 3, 0, 1},
								{0, 0, 5, 0, 0, 1, 0 } };

	*/
	printf("**********************************************************\n");
	printf("Create 'grafo' reading data from file data.txt            \n");
	printf("**********************************************************\n");
	grafo* MyGrafoFromFile = new grafo("c:\\cristina\\data.txt");
	MyGrafoFromFile->PrintGraph();

	MyGrafoFromFile->PrimAlgorithm();
	MyGrafoFromFile->printMST();

	printf("**********************************************************\n");
	printf("Create 'KruskalGraph' reading data from file data.txt     \n");
	printf("**********************************************************\n");
	KruskalGraph* MyKruskalGraphromFile = new KruskalGraph("c:\\cristina\\data.txt");
	MyKruskalGraphromFile->PrintGraph();
	int mst_wt = MyKruskalGraphromFile->KruskalMST();
	MyKruskalGraphromFile->PrintMSTGraph();


	printf("**********************************************************\n");
	printf("Create 'grafo' reading data from file data1.txt           \n");
	printf("**********************************************************\n");
	grafo* MyGrafoFromFile1 = new grafo("c:\\cristina\\data1.txt");
	MyGrafoFromFile1->PrintGraph();
	MyGrafoFromFile1->PrimAlgorithm();
	MyGrafoFromFile1->printMST();


	printf("**********************************************************\n");
	printf("Create 'KruskalGraph' reading data from file data1.txt     \n");
	printf("**********************************************************\n");
	KruskalGraph* MyKruskalGraphromFile1 = new KruskalGraph("c:\\cristina\\data1.txt");
	MyKruskalGraphromFile1->PrintGraph();
	int mst_wt1 = MyKruskalGraphromFile1->KruskalMST();
	MyKruskalGraphromFile1->PrintMSTGraph();
		

	//grafo* MyGrafo = new grafo(10);
	//MyGrafo->GenerateRandomGraph(1, 10);
	//MyGrafo->PrintGraph();
	//delete MyGrafo;

	//MyGrafo = new grafo(10);
	//MyGrafo->GenerateRandomGraph(0.5, 10);
	//MyGrafo->PrintGraph();
	//delete MyGrafo;

	//MyGrafo = new grafo(10);
	//MyGrafo->GenerateRandomGraph(0.1, 10);
	//MyGrafo->PrintGraph();
	//delete MyGrafo;

	//MyGrafo = new grafo(50);
	//MyGrafo->GenerateRandomGraph(0.2, 10);
	//MyGrafo->PrintGraph();


	//MyGrafo = new grafo(7);
	//int riga_0[] = { 0, 3, 0, 0, 9, 0, 0 };
	//int riga_1[] = { 3, 0, 6, 2, 0, 0, 0 };
	//int riga_2[] = { 0, 6, 0, 0, 0, 0, 5 };
	//int riga_3[] = { 0, 2, 0, 0, 2, 9, 0 };
	//int riga_4[] = { 9, 0, 0, 2, 0, 3, 0 };
	//int riga_5[] = { 0, 0, 0, 0, 3, 0, 1 };
	//int riga_6[] = { 0, 0, 5, 0, 0, 1, 0 };

	//MyGrafo->AddVector(riga_0, 0);
	//MyGrafo->AddVector(riga_1, 1);
	//MyGrafo->AddVector(riga_2, 2);
	//MyGrafo->AddVector(riga_3, 3);
	//MyGrafo->AddVector(riga_4, 4);
	//MyGrafo->AddVector(riga_5, 5);
	//MyGrafo->AddVector(riga_6, 6);
	//
	//MyGrafo->PrintGraph();

	//MyGrafo->CalculateMinPathFromTo(6,0);
	//MyGrafo->CalculateMinPathFromTo(0,6);
	//MyGrafo->CalculateMinPathFromTo(5,2);
	//delete MyGrafo;


	//MyGrafo = new grafo(50);
	//MyGrafo->GenerateRandomGraph(0.2, 10);
	//MyGrafo->PrintGraph();
	//MyGrafo->CalculateMinPathFromTo(0, 49);
	//delete MyGrafo;

	return 0;

}



