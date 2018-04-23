/*
Paul Barrett
FILE: kruskalTraverse.cc
DESCRIPTION: Given output in the form of an adjacency matrix for a MST from kruskalMinSpanTree.cc
and a vertext to begin at, uses depth first search to find the preorder traversal for the tree
USE: ./kruskalMinSpanTree | ./kruskalTraverse
COMPILATION: g++ -o kruskalTraverse kruskalTraverse.cc
*/

#include <iostream>
#include <vector>
#include <stdlib.h>
using namespace std;

vector <int> remembervisited;
bool visited(int rowv){
	bool remembered = false;
	for(int v = 0; v < remembervisited.size(); v++){
		if (remembervisited[v] == rowv)
			remembered = true;
	}
	if (remembered == false)
		remembervisited.push_back(rowv);
	return remembered;
}

void DFS(vector <int> rowvec, int vertex, vector <int> &destination){
	visited(vertex);
	destination.push_back(vertex);
	for (int k = 0; k < rowvec.size(); k++){
		if (visited(rowvec[k]) == false)
			DFS(rowvec, rowvec[k], destination);
	}
}

int main(int argc, char *argv[]){

if (argc != 2){
	cout << "Specify start vertex: ./kruskalTravers [start vertex]" << endl;
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
		if (edgevalue != 0 && col > row){
			rowvector.push_back(row);
			colvector.push_back(col);
		}
	}	
}
rowvector.push_back(numverts);
/*for (int j = 0; j < numverts*numverts - 1; j++){
	cin >> edgevalue;
}*/

/*cout << "startvert = "<<startvert;
cout << endl;

for (int i = 0; i < numverts-1; i++){
                cout << "(" << rowvector[i] << ", " <<
		colvector[i] << ")" << endl;
}*/
vector <int> preorder;
DFS(rowvector, startvert, preorder);
for(int t = 0; t < numverts; t++){
	cout << preorder[t] + 1 << endl;
}

return 0;
}
