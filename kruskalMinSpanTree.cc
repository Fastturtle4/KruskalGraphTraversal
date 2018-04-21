/*
Paul Barrett
NAME: kruskalMinSpanTree.cc
COMPILATION: g++ -std=c++11 -o kruskalMST kruskalMinSpanTree.cc
DESCRIPTION: reads in  an adjacency (distance) matrix of an undirected weighted graph
and calculates its MST
AUTHOR: modified from the below listed source (References)
REFERENCES: This code uses
https://github.com/luisfcofv/competitive-programming-book/blob/master/ch4/ch4_03_kruskal_prim.cpp
Changes are described in the corresponding diff file. The main changes: reading an adjacency
matrix rather than an adjacency list, allowing for real-valued weights.
*/
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef pair<int, int> ii; //the name could be better, e.g., intPair
typedef vector<double> vi; //the name could be better, e.g., doubleVector
typedef vector<ii> vii; //the name could be better, e.g., intPairVector

// Union-Find Disjoint Sets Library written in OOP manner, using both path compression and union by rank heuristics
class UnionFind {                                              // OOP style
private:
    vi p, rank, setSize;                       // remember: vi is vector<int>
    int numSets;
public:
    UnionFind(int N) {
        setSize.assign(N, 1);
        numSets = N;
        rank.assign(N, 0);
        p.assign(N, 0);
        for (int i = 0; i < N; i++) p[i] = i;
    }
    int findSet(int i) {
        return (p[i] == i) ? i : (p[i] = findSet(p[i]));
    }
    bool isSameSet(int i, int j) {
        return findSet(i) == findSet(j);
    }
    void unionSet(int i, int j) {
        if (!isSameSet(i, j)) {
            numSets--;
            int x = findSet(i), y = findSet(j);
            // rank is used to keep the tree short
            if (rank[x] > rank[y]) {
                p[y] = x;
                setSize[x] += setSize[y];
            }
            else                   {
                p[x] = y;
                setSize[y] += setSize[x];
                if (rank[x] == rank[y]) rank[y]++;
            }
        }
    }
    int numDisjointSets() {
        return numSets;
    }
    int sizeOfSet(int i) {
        return setSize[findSet(i)];
    }
};

vector<vii> AdjList;

int main(void) {
    int num_verts = 0;
    std::cin >> num_verts;

    // Pre-allocate a vector of num_verts rows, each of which is a vector of
    // num_verts copies of 0.0
    std::vector<std::vector<double> > matrix(num_verts, std::vector<double>(num_verts, 0.0));

    // Requires C++11 or higher (g++ -std=c++11)
    for (auto &row : matrix) { // row is a reference to a vector of doubles
        for (auto &entry : row) { // entry is a reference to a double
            std::cin >> entry;
        }
    }

    // Kruskal's algorithm merged
    AdjList.assign(num_verts, vii());
    vector< pair<double, ii> > EdgeList;   // (weight, two vertices) of the edge
    for (int row=0; row<num_verts; ++row) {
        for (int col=0; col<num_verts; ++col) {
            EdgeList.push_back(make_pair(matrix[row][col], ii(row, col)));
            AdjList[row].push_back(ii(row, matrix[row][col]));
            AdjList[col].push_back(ii(col, matrix[row][col]));
        }
    }

    sort(EdgeList.begin(), EdgeList.end()); // sort by edge weight O(E log E)
    // note: pair object has built-in comparison function
    std::vector<std::vector<double> > MSTmatrix(num_verts, std::vector<double>(num_verts, 0.0));
    double mst_cost = 0.0;
    UnionFind UF(num_verts);                     // all V are disjoint sets initially
    for (int i = 0; i < num_verts * num_verts; i++) {                      // for each edge, O(E)
        pair<double, ii> front = EdgeList[i];
        if (!UF.isSameSet(front.second.first, front.second.second)) {  // check
            mst_cost += front.first;                // add the weight of e to MST
            UF.unionSet(front.second.first, front.second.second);    // link them
            MSTmatrix[front.second.second][front.second.first]=front.first;
            MSTmatrix[front.second.first][front.second.second]=front.first;
        }
    }                       // note: the runtime cost of UFDS is very light
    
    //Print MST matrix
    cout << mst_cost << endl;
    cout << num_verts << endl;
    for (int mstrow=0; mstrow<num_verts; ++mstrow) {
        for (int mstcol=0; mstcol<num_verts; ++mstcol) {
            cout << MSTmatrix[mstrow][mstcol] << "\t";
        }
        cout << endl;
    }

    return 0;
}
