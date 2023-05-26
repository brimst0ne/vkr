#include <cstdlib>
#include <ctime>
#include <iostream>
#include <queue>
#include <vector>
#include <random>
#include <fstream>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

vvi generateGraph(int n, int m) {
  srand(time(NULL));

  vvi adjMatrix(n, vi(n, 0));  // ������� ������ ������� ���������
  queue<int> q;
  q.push(0);  // �������� ����� ����� � ������� 0
  vi visited(n, false);  // ������ ��� ������������ ���������� ������
  visited[0] = true;
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int v = u + 1; v < n; v++) {
      if (rand() % 2 == 0) {
        adjMatrix[u][v] = adjMatrix[v][u] = 1;
        if (!visited[v]) {
          visited[v] = true;
          q.push(v);
        }
        if (--m == 0) break;  // ���� �������� ��� �����, ������� �� �����
      }
    }
  }
  return adjMatrix;
}

vector<vector<int>> removeIsolatedVertices(
    vector<vector<int>> adjacencyMatrix) {
  vector<int> isolatedVertices;
  int n = adjacencyMatrix.size();

  // ����� ������������� ������
  for (int i = 0; i < n; i++) {
    bool hasNeighbors = false;
    for (int j = 0; j < n; j++) {
      if (adjacencyMatrix[i][j] == 1) {
        hasNeighbors = true;
        break;
      }
    }

    if (!hasNeighbors) {
      isolatedVertices.push_back(i);
    }
  }

  // �������� ������������� ������
  for (int i = isolatedVertices.size() - 1; i >= 0; i--) {
    adjacencyMatrix.erase(adjacencyMatrix.begin() + isolatedVertices[i]);
    for (int j = 0; j < adjacencyMatrix.size(); j++) {
      adjacencyMatrix[j].erase(adjacencyMatrix[j].begin() +
                               isolatedVertices[i]);
    }
  }

  return adjacencyMatrix;
}

int countEdges(vvi adjMatrix) { 
  
  int res = 0;

  for (int i = 0; i < adjMatrix.size(); i++) {
    for (int j = i; j < adjMatrix.size(); j++) {
      if (adjMatrix[i][j] == 1) {
        res++;
      }
    }
  }

  return res;
}

vector<int> getVerticesAtDistanceK(vector<vector<int>> adjacencyMatrix,
                                   int startVertex, int k) {
  int n = adjacencyMatrix.size();
  vector<int> visited(n, 0);
  queue<pair<int, int>> bfsQueue;

  bfsQueue.push(make_pair(startVertex, 0));
  visited[startVertex] = 1;

  vector<int> verticesAtDistanceK;

  while (!bfsQueue.empty()) {
    int currentVertex = bfsQueue.front().first;
    int currentDistance = bfsQueue.front().second;

    bfsQueue.pop();

    if (currentDistance == k) {
      verticesAtDistanceK.push_back(currentVertex);
    } else if (currentDistance > k) {
      break;
    }

    for (int i = 0; i < n; i++) {
      if (adjacencyMatrix[currentVertex][i] == 1 && !visited[i]) {
        bfsQueue.push(make_pair(i, currentDistance + 1));
        visited[i] = 1;
      }
    }
  }

  return verticesAtDistanceK;
}

vector<int> getVerticesAtDistanceKOrLess(vector<vector<int>> adjacencyMatrix,
                                   int startVertex, int k) {
  int n = adjacencyMatrix.size();
  vector<int> visited(n, 0);
  queue<pair<int, int>> bfsQueue;

  bfsQueue.push(make_pair(startVertex, 0));
  visited[startVertex] = 1;

  vector<int> verticesAtDistanceK;

  while (!bfsQueue.empty()) {
    int currentVertex = bfsQueue.front().first;
    int currentDistance = bfsQueue.front().second;

    bfsQueue.pop();

    if (currentDistance > k) {
      break;
    }

    if (currentDistance <= k) {
      verticesAtDistanceK.push_back(currentVertex);
    }

    for (int i = 0; i < n; i++) {
      if (adjacencyMatrix[currentVertex][i] == 1 && !visited[i]) {
        bfsQueue.push(make_pair(i, currentDistance + 1));
        visited[i] = 1;
      }
    }
  }

  return verticesAtDistanceK;
}

void generateGraphvizFile(vector<vector<int>> adjacencyMatrix,
                          string graphName) {
  int n = adjacencyMatrix.size();

  ofstream ofile;
  ofile.open(graphName + ".gv");

  // ��������� �����
  ofile << "graph " << graphName << " {\n";

  // ����� ������
  for (int i = 0; i < n; i++) {
    ofile << "\t" << i << ";\n";
  }

  // ����� �����
  for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) {
      if (adjacencyMatrix[i][j] == 1) {
        ofile << "\t" << i << " -- " << j << ";\n";
      }
    }
  }

  // �������� �����
  ofile << "}\n";
  ofile.close();

  // ������� ��� ��������� ����������� �����
  system(("dot -Tpng " + graphName + ".gv -o " + graphName + ".png").c_str());
  system((graphName + ".png").c_str());
}

// ������� ��� ���������� ��������� ������
void dfs(vvi adjMatrix, vector<bool> visited, int u, vvi treeAdjMatrix) {
  int n = adjMatrix.size();
  visited[u] = true;

  for (int v = 0; v < n; v++) {
    if (adjMatrix[u][v] && visited[v] == false) {
      // ��������� ����� (u, v) � �������� ������
      treeAdjMatrix[u][v] = 1;
      treeAdjMatrix[v][u] = 1;
      dfs(adjMatrix, visited, v, treeAdjMatrix);
    }
  }
}

// ������� ��� ���������� ��������� ������
void getSpanningTree(vvi adjMatrix, vvi treeAdjMatrix) {
  int n = adjMatrix.size();
  vector<bool> visited(n);

  // �������������� ������ visited
  for (int i = 0; i < n; i++) visited[i] = false;

  // ���������� ��������� ������
  for (int u = 0; u < n; u++) {
    if (visited[u] == false) {
      dfs(adjMatrix, visited, u, treeAdjMatrix);
    }
  }
}

void findMinDomSet(vvi adjMatrix, int n, int k) {
  vector<int> domSet;  // ��� �������� k-������������� ���������

  // ���� ��� ������� �� ��������
  while (true) {
    vector<bool> unmarked(n, true);  // ��� �������� ������������� ������

    // �������� ������� � ������������ ��������� � ������������ ��������
    int maxDegree = -1;
    int maxDegreeVertex = -1;
    for (int i = 0; i < n; i++) {
      if (!unmarked[i]) continue;

      int degree = 0;
      for (int j = 0; j < n; j++) {
        if (adjMatrix[i][j] && !unmarked[j]) degree++;
      }

      if (degree > maxDegree) {
        maxDegree = degree;
        maxDegreeVertex = i;
      }
    }

    if (maxDegreeVertex == -1) break;  // ���������� ������ ���������

    domSet.push_back(maxDegreeVertex);  // ��������� ��������� ������� �
                                        // �-������������ ���������
    unmarked[maxDegreeVertex] = false;  // �������� ��������� �������

    // �������� ���� ������� ��������� ������� ��� ����������
    for (int i = 0; i < n; i++) {
      if (adjMatrix[maxDegreeVertex][i]) unmarked[i] = false;
    }

    if (domSet.size() >= k)
      break;  // ������� ����������� ���������� ������ ��� �-�������������
              // ���������
  }

  // ����� ��������� �� �����
  cout << "Minimal " << k << "-dominating set: ";
  for (int i = 0; i < domSet.size(); i++) {
    if (i > 0) cout << ", ";
    cout << domSet[i];  // +1 - ��� ������ ������ ������� � 1
  }
}


int main() {
  srand(time(NULL));  // ���������� ������� ����� � �������� ����� ���
                      // ���������� ��������� �����
  //int n = rand() % 10 + 2;  // ���������� ����� ������ � ��������� �� 1 �� 500
  //int m = rand() % (n * (n - 1) / 2) + 1;  // ���������� ����� ����� � ��������� �� 1 �� n * (n - 1) / 2
  int n = 4 + rand() % (10 - 4 + 1);
  int m = rand() % (n * (n - 1) / 2) + 1;
  vvi adjMatrix = generateGraph(n, m);
  // ������� ���� � ���� ������� ���������
  cout << "Generated matrix: " << endl;
  cout << endl;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cout << adjMatrix[i][j] << " ";
    }
    cout << endl;
  }

  //cout << "Number of vertices: " << n << endl;
  //cout << "Number of edges: " << m << endl;
  cout << endl;

  cout << "Final matrix: " << endl;
  cout << endl;

  vvi newAdjMatrix = removeIsolatedVertices(adjMatrix);
  for (int i = 0; i < newAdjMatrix.size(); i++) {
    for (int j = 0; j < newAdjMatrix.size(); j++) {
      cout << newAdjMatrix[i][j] << " ";
    }
    cout << endl;
  }

  cout << endl;

  int nn = newAdjMatrix.size();
  int nm = countEdges(newAdjMatrix);

  cout << "Number of vertices: " << nn << endl;
  cout << "Number of edges: " << nm << endl;
  cout << endl;

  int k = 2;
  cout << "Vertices at distance " << k << " from vertex 0: " << endl;
  vi verticesAtDistanceK = getVerticesAtDistanceK(newAdjMatrix, 0, k);
  for (int i = 0; i < verticesAtDistanceK.size(); i++) {
    cout << verticesAtDistanceK[i] << " ";
  }
  cout << endl;

  cout << "Vertices at distance " << k << " or less from vertex 0: " << endl;
  vi verticesAtDistanceKOrLess = getVerticesAtDistanceKOrLess(newAdjMatrix, 0, k);
  for (int i = 0; i < verticesAtDistanceKOrLess.size(); i++) {
    cout << verticesAtDistanceKOrLess[i] << " ";
  }
  cout << endl;
  cout << endl;

  /*vvi treeAdjMatrix(nn, vi(nn, 0));
  getSpanningTree(newAdjMatrix, treeAdjMatrix);
  cout << "Adjacency matrix for the spanning tree: " << endl;
  cout << endl;
  for (int i = 0; i < treeAdjMatrix.size(); i++) {
    for (int j = 0; j < treeAdjMatrix.size(); j++) {
      cout << treeAdjMatrix[i][j] << " ";
    }
    cout << endl;
  }*/
  cout << endl;

  string graphName = "exampleGraph";
  //string treeName = "exampleTree";

  generateGraphvizFile(newAdjMatrix, graphName);
  //generateGraphvizFile(treeAdjMatrix, treeName);

  findMinDomSet(newAdjMatrix, nn, 2);

  return 0;
}