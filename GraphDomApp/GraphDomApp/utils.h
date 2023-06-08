#pragma once

#include <cstdlib>
#include <ctime>
#include <cmath>
#include <utility>
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
#include <random>
#include <fstream>
#include <unordered_set>
#include <limits>

using namespace std;

typedef vector<int> vi;
typedef vector<vector<int>> vvi;

const int INF = std::numeric_limits<int>::max();

bool hasDuplicate(vector<int> vec1, vector<int> vec2);
vvi generateGraph(int n, int m);
vector<vector<int>> removeIsolatedVertices(vector<vector<int>> adjacencyMatrix);
int countEdges(vvi adjMatrix);
vector<int> getVerticesAtDistanceKOrLess(vector<vector<int>> adjacencyMatrix,
                                         int startVertex, int k);
void generateGraphvizFile(vector<vector<int>> adjacencyMatrix, string graphName,
                          vector<int> domSet);
vector<int> sortVerticesByDegree(const vector<vector<int>>& adjacencyMatrix);
vector<int> sortVerticesByKNeighbors(const vvi& adjMatrix, vector<int> domSet, int k);
vector<int> HEU1(vvi adjMatrix, int n, int k);
vector<int> HEU2(vvi adjMatrix, int n, int k, int alpha, double loopTime);
vector<int> redundantRemoval(vvi adjMatrix, vector<int> domSet, int k);
vector<vector<int>> BA_graph(int n, int m);
pair<int, int> calculateGraphRadius(const std::vector<std::vector<int>>& adjacencyMatrix);
vector<int> splitGraph(const std::vector<std::vector<int>>& adjacencyMatrix);
void generatePartitionGraphvizFile(vector<vector<int>> adjacencyMatrix, string graphName,
                          vector<int> partition);
vector<int> splitGraphNew(const std::vector<std::vector<int>>& adjacencyMatrix);

vector<int> romanKDomSet(vvi adjMatrix, int k);
std::vector<std::vector<int>> buildAdjacencyMatrix(
    const std::vector<std::vector<int>>& adjacencyMatrix,
    const std::vector<int>& partition, int part);
void multilevelGraphPartitioning(
    const std::vector<std::vector<int>>& adjacencyMatrix,
    std::vector<int>& partition);
int computeCutSize(const std::vector<std::vector<int>>& adjacencyMatrix,
                   const std::vector<int>& partition);
void graphCut(const std::vector<std::vector<int>>& adjacencyMatrix,
              std::vector<int>& partition);
