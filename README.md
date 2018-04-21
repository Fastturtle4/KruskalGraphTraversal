Kruskal Graph Traversal

Files:
kruskalMinSpanTree.cc
kruskalTraverse.cc

kruskalMinSpanTree.cc:
input: consists of n+1 lines. The first line includes n, the size of undirected distance matrix M, and is followed by n lines listing the entries, row by row, of M. The matrix is symmetric.
output: the first line is the weight (length) of the MST T. The second line is n, the size of the matrix, and it is followed by n lines representing T

kruskalTraverse.cc:
input: A n x n distance matrix M representing a weighted tree T with n vertices, and the starting vertex v
output: list of vertices of T visited in preorder, starting at v
sample input:
4	//weight of t
4	//# of lines in matrix of MST
0 0 2 0 //matrix
0 0 0 1
2 0 0 1
0 1 1 0
3	//starting vertex
sample output:
3 1 4 2

code modified from original at:
https://github.com/luisfcofv/competitive-programming-book/blob/master/ch4/ch4_03_kruskal_prim.cpp
