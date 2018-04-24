/*
Paul Barrett
FILE: kruskalTraverse.cc
DESCRIPTION: Given output in the form of an adjacency matrix for a MST from kruskalMinSpanTree.cc and a vertext to begin at, uses depth first search to find the preorder traversal for the tree

USE: $ ./kruskalMinSpanTree | ./kruskalTraverse [starting vertex]
input format:
4	<= number of vertices
0 2 2 6 <= adjacency matrix
2 0 5 1
2 5 0 1
6 1 1 0

note: you can also use just $ ./kruskalTraverse [starting vertex] and input with format:
4	<= cost of tree
4	<= number of vertices
0 0 2 0 <= adjacency matrix of MST
0 0 0 1 
2 0 0 1 
0 1 1 0 

COMPILATION: g++ -o kruskalTraverse kruskalTraverse.cc
*/

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <list>
using namespace std;

// Graph class represents a directed graph
// using adjacency list representation
// this code was borrowed from:
// https://www.geeksforgeeks.org/depth-first-search-or-dfs-for-a-graph/
// and modified to work correctly with new input
class Graph
{
    int V;    // No. of vertices
 
    // Pointer to an array containing
    // adjacency lists
    list<int> *adj;
 
    // A recursive function used by DFS
    void DFSUtil(int v, bool visited[]);
public:
    Graph(int V);   // Constructor
 
    // function to add an edge to graph
    void addEdge(int v, int w);
 
    // DFS traversal of the vertices
    // reachable from v
    void DFS(int v);
};
 
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}
 
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.
}
 
void Graph::DFSUtil(int v, bool visited[])
{
    // Mark the current node as visited and
    // print it
    visited[v] = true;
    cout << v+1 << " ";
 
    // Recur for all the vertices adjacent
    // to this vertex
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            DFSUtil(*i, visited);
}
 
// DFS traversal of the vertices reachable from v.
// It uses recursive DFSUtil()
void Graph::DFS(int v)
{
    // Mark all the vertices as not visited
    bool *visited = new bool[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;
 
    // Call the recursive helper function
    // to print DFS traversal
    DFSUtil(v, visited);
}

int main(int argc, char *argv[]){

if (argc != 2){
	cout << "Specify start vertex: ./kruskalTraverse [start vertex]" << endl;
	return 1;
}
int numverts;
int weight;
int startvert = atoi(argv[1]) - 1;
int edgevalue;
vector <int> rowvector;
vector <int> colvector;
cin >> weight >> numverts;

for (int row = 0; row < numverts; row++){
	for (int col = 0; col < numverts; col++){
		cin >> edgevalue;
		if (edgevalue != 0){
			rowvector.push_back(row);
			colvector.push_back(col);
		}
	}	
}
Graph g(numverts);
for (int i = 0; i < 2*numverts - 2; i++){
	g.addEdge(rowvector[i], colvector[i]);
}

cout << "Traversal (DFS):" << endl;
g.DFS(startvert);
cout << endl;

return 0;
}
