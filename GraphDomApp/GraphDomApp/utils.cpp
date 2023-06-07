#include "utils.h"

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

  vvi adjMatrix(n, vi(n, 0));  // создаем пустую матрицу смежности
  queue<int> q;
  q.push(0);  // начинаем обход графа с вершины 0
  vi visited(n, false);  // массив для отслеживания посещенных вершин
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
        if (--m == 0) break;  // если добавили все ребра, выходим из цикла
      }
    }
  }
  return adjMatrix;
}

vector<vector<int>> removeIsolatedVertices(
    vector<vector<int>> adjacencyMatrix) {
  vector<int> isolatedVertices;
  int n = adjacencyMatrix.size();

  // Поиск изолированных вершин
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

  // Удаление изолированных вершин
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

  // Заголовок графа
  ofile << "graph " << graphName << " {\n";

  // Вывод вершин
  for (int i = 0; i < n; i++) {
    ofile << "\t" << i+1 << ";\n";
  }

  // Вывод ребер
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

  // Закрытие файла
  ofile << "}\n";
  ofile.close();

  // Команды для генерации изображения графа
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

    return degreeA > degreeB;  // Сортировка по убыванию степени
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

int calculateGraphRadius(const std::vector<std::vector<int>>& adjacencyMatrix) {
  int n = adjacencyMatrix.size();

  // Инициализация матрицы расстояний
  std::vector<std::vector<int>> distance(n, std::vector<int>(n, INF));

  // Вычисление кратчайших расстояний между всеми парами вершин с помощью
  // алгоритма Флойда-Уоршелла
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

  // Находим максимальное расстояние в каждой строке матрицы расстояний
  std::vector<int> maxDistances(n, 0);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (distance[i][j] > maxDistances[i]) {
        maxDistances[i] = distance[i][j];
      }
    }
  }

  // Находим минимальное из максимальных расстояний
  int graphRadius = INF;
  for (int i = 0; i < n; ++i) {
    if (maxDistances[i] < graphRadius) {
      graphRadius = maxDistances[i];
    }
  }

  return graphRadius;
}
