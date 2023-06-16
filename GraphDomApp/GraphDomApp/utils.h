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
vector<int> getVerticesAtDistanceKOrLess(vector<vector<int>> adjacencyMatrix,
                                         int startVertex, int k);
vector<int> sortVerticesByDegree(const vector<vector<int>>& adjacencyMatrix);
pair<int, int> calculateGraphRadius(const std::vector<std::vector<int>>& adjacencyMatrix);
vector<int> romanKDomSetHEU1(vvi adjMatrix, int k, vector<int>& weights);
vector<int> romanKDomSetHEU2(vvi adjMatrix, int k, vector<int>& weights, int alpha, double loopTime);
void generateWeightsGraphvizFile(vector<vector<int>> adjacencyMatrix, string graphName,
                          vector<int> domSet, vector<int>& weights);
