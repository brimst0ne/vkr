#include "utils.h"
#include <functional>

bool hasDuplicate(vector<int> vec1, vector<int> vec2) {
  unordered_set<int> uniqueNumbers;

  for (int num : vec1) {
    uniqueNumbers.insert(num);
  }

  for (int num : vec2) {
    if (uniqueNumbers.find(num) != uniqueNumbers.end()) {
      return true;
    }
  }

  return false;
}

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

    if (currentDistance <= k && currentVertex != startVertex) {
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

void generateGraphvizFile(vector<vector<int>> adjacencyMatrix, string graphName,
                          vector<int> domSet) {
  int n = adjacencyMatrix.size();

  ofstream ofile;
  ofile.open(graphName + ".gv");

  // ��������� �����
  ofile << "graph " << graphName << " {\n";

  // ����� ������
  for (int i = 0; i < n; i++) {
    ofile << "\t" << i+1 << ";\n";
  }

  // ����� �����
  for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) {
      if (adjacencyMatrix[i][j] == 1) {
        ofile << "\t" << i+1 << " -- " << j+1 << ";\n";
      }
    }
  }

  for (int vertex : domSet) {
    ofile << "    " << vertex+1 << " [style=filled, fillcolor=red];" << std::endl;
  }

  // �������� �����
  ofile << "}\n";
  ofile.close();

  // ������� ��� ��������� ����������� �����
  system(("fdp -Tpng " + graphName + ".gv -o " + graphName + ".png").c_str());
  //system((graphName + ".png").c_str());
}

vector<int> sortVerticesByDegree(const vector<vector<int>>& adjacencyMatrix) {
  std::vector<int> vertices;
  for (int i = 0; i < adjacencyMatrix.size(); ++i) {
    vertices.push_back(i);
  }

  sort(vertices.begin(), vertices.end(), [&adjacencyMatrix](int a, int b) {
    int degreeA = 0;
    int degreeB = 0;

    for (int i = 0; i < adjacencyMatrix.size(); ++i) {
      degreeA += adjacencyMatrix[a][i];
      degreeB += adjacencyMatrix[b][i];
    }

    return degreeA > degreeB;  // ���������� �� �������� �������
  });

  return vertices;
}

vector<int> sortVerticesByKNeighbors(const vvi& adjMatrix, vector<int> domSet,
                                     int k) {
  vector<int> vertices;
  for (int i = 0; i < domSet.size(); ++i) {
    vertices.push_back(domSet[i]);
  }

  for (int i = 0; i < vertices.size(); i++) {
    cout << vertices[i] << " ";
  }
  cout << endl;

  sort(vertices.begin(), vertices.end(),
       [&adjMatrix, &domSet, &k, &vertices](int a, int b) {
         vector<int> neighborsA = getVerticesAtDistanceKOrLess(adjMatrix, a, k);
         cout << "neighbors" << a << ": ";
         for (int j = 0; j < neighborsA.size(); j++) {
           cout << neighborsA[j] << " ";
         }
         cout << endl;
         vector<int> neighborsB = getVerticesAtDistanceKOrLess(adjMatrix, b, k);
         cout << "neighbors" << b << ": ";
         for (int j = 0; j < neighborsB.size(); j++) {
           cout << neighborsB[j] << " ";
         }
         cout << endl;

         return neighborsA.size() < neighborsB.size();
       });

  for (int i = 0; i < vertices.size(); i++) {
    cout << vertices[i] << " ";
  }
  cout << endl;

  return vertices;
}

vector<int> HEU1(vvi adjMatrix, int n, int k) {
  vector<int> domSet;
  vector<int> sortedVertices = sortVerticesByDegree(adjMatrix);

  for (int i = 0; i < sortedVertices.size(); i++) {
    cout << sortedVertices[i] << " ";
  }
  cout << endl;

  vector<bool> isCovered(n, false);

  for (int i = 0; i < sortedVertices.size(); i++) {
    if (!isCovered[sortedVertices[i]]) {
      domSet.push_back(sortedVertices[i]);
      isCovered[sortedVertices[i]] = true;
      vector<int> currentNeighbors =
          getVerticesAtDistanceKOrLess(adjMatrix, sortedVertices[i], k);
      for (int j = 0; j < currentNeighbors.size(); j++) {
        isCovered[currentNeighbors[j]] = true;
      }
    }
  }

  cout << k << "-dominating set by heuristic 1: ";
  for (int i = 0; i < domSet.size(); i++) {
    if (i > 0) cout << ", ";
    cout << domSet[i];
  }
  cout << endl;

  return domSet;
}

vector<int> HEU2(vvi adjMatrix, int n, int k, int alpha, double loopTime) {
  vector<int> domSet;
  vector<int> sortedVertices = sortVerticesByDegree(adjMatrix);

  for (int i = 0; i < sortedVertices.size(); i++) {
    cout << sortedVertices[i] << " ";
  }
  cout << endl;

  vector<bool> isCovered(n, false);
  double workTime = 0;

  for (int i = 0; i < sortedVertices.size(); i++) {
    double start = clock() / 1000.0;

    if (workTime >= loopTime ||
        find(isCovered.begin(), isCovered.end(), false) == isCovered.end()) {
      break;
    }

    vector<int> kNeighbors =
        getVerticesAtDistanceKOrLess(adjMatrix, sortedVertices[i], k);
    vector<int> notDominatedNeighbors;

    for (int k = 0; k < kNeighbors.size(); k++) {
      if (!isCovered[kNeighbors[k]]) {
        notDominatedNeighbors.push_back(kNeighbors[k]);
      }
    }

    if (!isCovered[sortedVertices[i]] ||
        notDominatedNeighbors.size() >= alpha) {
      domSet.push_back(sortedVertices[i]);
      isCovered[sortedVertices[i]] = true;
      for (int j = 0; j < kNeighbors.size(); j++) {
        isCovered[kNeighbors[j]] = true;
      }
    }
    double finish = clock() / 1000.0;
    workTime = finish - start;
    cout << workTime << endl;
  }

  for (int i = 0; i < sortedVertices.size(); i++) {
    if (!isCovered[sortedVertices[i]]) {
      cout << "HEU1 WORKING" << endl;
      domSet.push_back(sortedVertices[i]);
      isCovered[sortedVertices[i]] = true;
      vector<int> currentNeighbors =
          getVerticesAtDistanceKOrLess(adjMatrix, sortedVertices[i], k);
      for (int j = 0; j < currentNeighbors.size(); j++) {
        isCovered[currentNeighbors[j]] = true;
      }
    }
  }

  cout << k << "-dominating set by heuristic 2: ";
  for (int i = 0; i < domSet.size(); i++) {
    if (i > 0) cout << ", ";
    cout << domSet[i];
  }
  cout << endl;

  return domSet;
}

vector<int> redundantRemoval(vvi adjMatrix, vector<int> domSet, int k) {
  vector<int> reducedDomSet = domSet;

  vector<int> sortedVertices = sortVerticesByKNeighbors(adjMatrix, domSet, k);
  for (int i = 0; i < sortedVertices.size(); i++) {
    cout << sortedVertices[i] << " ";
  }
  cout << endl;

  int k1 = floor((k + 1) / 2);
  int k2 = k - k1;

  for (int i = 0; i < sortedVertices.size(); i++) {
    bool S = true;
    vector<int> kNeighbors =
        getVerticesAtDistanceKOrLess(adjMatrix, sortedVertices[i], k);
    for (int j = 0; j < kNeighbors.size(); j++) {
      bool T = false;
      vector<int> uKNeighbors =
          getVerticesAtDistanceKOrLess(adjMatrix, kNeighbors[j], k1);
      for (int k = 0; k < sortedVertices.size(); k++) {
        if (sortedVertices[k] != sortedVertices[i]) {
          vector<int> wKNeighbors =
              getVerticesAtDistanceKOrLess(adjMatrix, sortedVertices[k], k2);
          if (hasDuplicate(uKNeighbors, wKNeighbors)) {
            T = true;
            break;
          }
        }
      }
      if (!T) {
        S = false;
        break;
      }
    }
    if (S) {
      remove(reducedDomSet.begin(), reducedDomSet.end(), sortedVertices[i]);
    }
  }

  cout << "Reduced Dom Set: " << endl;
  for (int i = 0; i < reducedDomSet.size(); i++) {
    cout << reducedDomSet[i] << " ";
  }
  cout << endl;

  return reducedDomSet;
}

vector<vector<int>> BA_graph(int n, int m) {
  vector<vector<int>> graph(n, vector<int>(n));
  for (int i = 0; i < m; i++) {
    for (int j = i + 1; j < m; j++) {
      graph[i][j] = 1;
      graph[j][i] = 1;
    }
  }
  for (int i = m; i < n; i++) {
    int degree_sum = 0;
    vector<int> degree_list(i, 0);
    for (int j = 0; j < i; j++) {
      for (int k = 0; k < i; k++) {
        degree_sum += graph[j][k];
        degree_list[k] = degree_sum;
      }
      int rand_degree = rand() % degree_sum;
      int target_node = i;
      for (int k = 0; k < i; k++) {
        if (rand_degree < degree_list[k]) {
          target_node = k;
          break;
        }
      }
      graph[i][target_node] = 1;
      graph[target_node][i] = 1;
    }
  }
  return graph;
}

pair<int, int> calculateGraphRadius(const std::vector<std::vector<int>>& adjacencyMatrix) {
  int n = adjacencyMatrix.size();

  pair<int, int> res(INF, INF);

  // ������������� ������� ����������
  std::vector<std::vector<int>> distance(n, std::vector<int>(n, INF));

  // ���������� ���������� ���������� ����� ����� ������ ������ � �������
  // ��������� ������-��������
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (adjacencyMatrix[i][j] != 0) {
        distance[i][j] = adjacencyMatrix[i][j];
      }
    }
  }

  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (distance[i][k] != INF && distance[k][j] != INF &&
            distance[i][k] + distance[k][j] < distance[i][j]) {
          distance[i][j] = distance[i][k] + distance[k][j];
        }
      }
    }
  }

  // ������� ������������ ���������� � ������ ������ ������� ����������
  std::vector<int> maxDistances(n, 0);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (distance[i][j] > maxDistances[i]) {
        maxDistances[i] = distance[i][j];
      }
    }
  }

  // ������� ����������� �� ������������ ����������
  //int graphRadius = INF;
  //int center = INF;

  for (int i = 0; i < n; ++i) {
    if (maxDistances[i] < res.first) {
      res.first = maxDistances[i];
      res.second = i;
    }
  }

  //return graphRadius;
  return res;
}

vector<int> splitGraph(const std::vector<std::vector<int>>& adjacencyMatrix) {
  int numVertices = adjacencyMatrix.size();
  std::vector<int> partition(numVertices,
                             0);  // ������� ������ 0 � 1 ��� ���������
  std::vector<bool> visited(numVertices, false);  // ���� ��������� ������

  // ����������� ������� ��� ������� ������ � �� ���������
  std::function<void(int, int)> dfs = [&](int vertex, int part) {
    partition[vertex] = part;  // ������������� ��������� ��� ������� �������
    visited[vertex] = true;  // �������� ������� ��� ����������

    // ���������� ������� ������� �������
    for (int neighbor = 0; neighbor < numVertices; ++neighbor) {
      if (adjacencyMatrix[vertex][neighbor] == 1 && !visited[neighbor]) {
        dfs(neighbor, 1 - part);  // ���������� �������� ��� �������������
                                  // ������ � ������ ����������
      }
    }
  };

  // ��������� ����� � ������� ��� ������ �������
  for (int vertex = 0; vertex < numVertices; ++vertex) {
    if (!visited[vertex]) {
      dfs(vertex,
          0);  // ��������� ����� � ���������� 0 ��� ������ ������������ �������
    }
  }

  return partition;
}

void generatePartitionGraphvizFile(vector<vector<int>> adjacencyMatrix,
                                   string graphName, vector<int> partition) {
  int n = adjacencyMatrix.size();

  ofstream ofile;
  ofile.open(graphName + ".gv");

  // ��������� �����
  ofile << "graph " << graphName << " {\n";

  // ����� ������
  for (int i = 0; i < n; i++) {
    ofile << "\t" << i + 1 << ";\n";
  }

  // ����� �����
  for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) {
      if (adjacencyMatrix[i][j] == 1) {
        ofile << "\t" << i + 1 << " -- " << j + 1 << ";\n";
      }
    }
  }

  /*for (int vertex : partition) {
    ofile << "    " << vertex + 1 << " [style=filled, fillcolor=red];"
          << std::endl;
  }*/

  for (int i = 0; i < partition.size(); i++) {
    if (partition[i]) {
      ofile << "    " << i + 1 << " [style=filled, fillcolor=red];" << endl;
    } else {
      ofile << "    " << i + 1 << " [style=filled, fillcolor=green];" << endl;
    }
  }

  // �������� �����
  ofile << "}\n";
  ofile.close();

  // ������� ��� ��������� ����������� �����
  system(("fdp -Tpng " + graphName + ".gv -o " + graphName + ".png").c_str());
  // system((graphName + ".png").c_str());
}

vector<int> splitGraphNew(const std::vector<std::vector<int>>& adjacencyMatrix) {
  int numVertices = adjacencyMatrix.size();
  std::vector<int> partition(numVertices,
                             -1);  // ������� ������ 0 � 1 ��� ���������

  std::queue<int> bfsQueue;
  std::vector<bool> visited(numVertices, false);  // ���� ��������� ������

  int numPartitions = 2;
  int targetSize = numVertices / numPartitions;
  int currentSize = 0;
  int currentPartition = 0;

  // �������� ����� � ������ ��� ��������� �� ��� ������� ��������
  for (int startVertex = 0; startVertex < numVertices; ++startVertex) {
    if (visited[startVertex]) {
      continue;
    }

    bfsQueue.push(startVertex);
    visited[startVertex] = true;

    while (!bfsQueue.empty()) {
      int vertex = bfsQueue.front();
      bfsQueue.pop();

      partition[vertex] = currentPartition;
      currentSize++;

      if (currentSize >= targetSize) {
        currentSize = 0;
        currentPartition++;
      }

      for (int neighbor = 0; neighbor < numVertices; ++neighbor) {
        if (adjacencyMatrix[vertex][neighbor] == 1 && !visited[neighbor]) {
          bfsQueue.push(neighbor);
          visited[neighbor] = true;
        }
      }
    }
  }

  return partition;
}

vector<int> romanKDomSet(vvi adjMatrix, int k) {

  int n = adjMatrix.size();

  vector<int> domSet;
  pair<int, int> mid = calculateGraphRadius(adjMatrix);
  int graphRadius = mid.first;
  int graphCenter = mid.second;

  if (graphRadius <= k) {

    domSet.push_back(graphCenter);

  } else {

    vector<int> partition = splitGraphNew(adjMatrix);
    vvi subAdjMatrix1 = buildAdjacencyMatrix(adjMatrix, partition, 0);
    vvi subAdjMatrix2 = buildAdjacencyMatrix(adjMatrix, partition, 1);
    pair<int, int> mid1 = calculateGraphRadius(subAdjMatrix1);
    pair<int, int> mid2 = calculateGraphRadius(subAdjMatrix2);
    int graphRadius1 = mid1.first;
    int graphCenter1 = mid1.second;
    int graphRadius2 = mid2.first;
    int graphCenter2 = mid2.second;
    if (graphRadius1 <= k) {
      domSet.push_back(graphCenter1);
    }
    if (graphRadius2 <= k) {
      domSet.push_back(graphCenter2);
    }

  }

  return domSet;

}

std::vector<std::vector<int>> buildAdjacencyMatrix(
    const std::vector<std::vector<int>>& adjacencyMatrix,
    const std::vector<int>& partition, int part) {

  int numVertices = adjacencyMatrix.size();
  std::vector<std::vector<int>> subMatrix(numVertices,
                                          std::vector<int>(numVertices, 0));

  // ��������� ������� ��������� ��� �������� �������� �����
  for (int i = 0; i < numVertices; ++i) {
    if (partition[i] == part) {
      for (int j = 0; j < numVertices; ++j) {
        if (partition[j] == part) {
          subMatrix[i][j] = adjacencyMatrix[i][j];
        }
      }
    }
  }

  return subMatrix;

}

void multilevelGraphPartitioning(
    const std::vector<std::vector<int>>& adjacencyMatrix,
    std::vector<int>& partition) {
  std::default_random_engine generator(time(0));
  std::uniform_int_distribution<int> distribution(0, 1);
  int numVertices = adjacencyMatrix.size();
  partition.resize(numVertices);

  // ������������� ���������� ����������
  for (int i = 0; i < numVertices; ++i) {
    partition[i] = distribution(generator);
  }

  // ������������ ��������� ���������
  bool improvement = true;
  while (improvement) {
    improvement = false;

    // ���������� ������� ���������
    int numPartitions = 2;
    std::vector<int> partitionSize(numPartitions, 0);
    for (int i = 0; i < numVertices; ++i) {
      partitionSize[partition[i]]++;
    }
    int targetSize = numVertices / numPartitions;

    // ����� ������� ��� ������������ ����� �����������
    for (int i = 0; i < numVertices; ++i) {
      int currentPartition = partition[i];

      // ������� ���� ������ � ������� ���������
      int currentWeight = 0;
      for (int j = 0; j < numVertices; ++j) {
        if (j != i && partition[j] == currentPartition) {
          currentWeight += adjacencyMatrix[i][j];
        }
      }

      // ������� ���� ������ � �������� ���������
      int neighborPartition = 1 - currentPartition;
      int neighborWeight = 0;
      for (int j = 0; j < numVertices; ++j) {
        if (j != i && partition[j] == neighborPartition) {
          neighborWeight += adjacencyMatrix[i][j];
        }
      }

      // ���� ������������ �������� ������, ��������� ������������
      if (currentWeight - adjacencyMatrix[i][i] > targetSize &&
          neighborWeight + adjacencyMatrix[i][i] < targetSize) {
        partition[i] = neighborPartition;
        improvement = true;
      }
    }
  }
}

int computeCutSize(const std::vector<std::vector<int>>& adjacencyMatrix,
                   const std::vector<int>& partition) {
  int cutSize = 0;
  int numVertices = partition.size();

  for (int i = 0; i < numVertices; ++i) {
    for (int j = i + 1; j < numVertices; ++j) {
      if (partition[i] != partition[j]) {
        cutSize += adjacencyMatrix[i][j];
      }
    }
  }

  return cutSize;
}

void graphCut(const std::vector<std::vector<int>>& adjacencyMatrix,
              std::vector<int>& partition) {
  int numVertices = adjacencyMatrix.size();
  partition.resize(numVertices, 0);

  // ������������� ���������� ���������
  for (int i = 0; i < numVertices; ++i) {
    partition[i] = (i < numVertices / 2) ? 0 : 1;
  }

  int bestCutSize = computeCutSize(adjacencyMatrix, partition);

  // ����� ������� ������� ����� ������������ ������ ����� �����������
  for (int i = 0; i < numVertices; ++i) {
    for (int j = i + 1; j < numVertices; ++j) {
      if (partition[i] != partition[j]) {
        // ������������ ������ i � j ����� �����������
        partition[i] = 1 - partition[i];
        partition[j] = 1 - partition[j];

        // ���������� ����� ����� ����� ����� ������������
        int cutSize = computeCutSize(adjacencyMatrix, partition);

        // ���� ����� ����� ����� �����������, �������� ������ ������
        if (cutSize < bestCutSize) {
          bestCutSize = cutSize;
        } else {
          // � ��������� ������, �������� ������������ ������
          partition[i] = 1 - partition[i];
          partition[j] = 1 - partition[j];
        }
      }
    }
  }
}


