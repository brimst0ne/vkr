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

pair<int, int> calculateGraphRadius(const std::vector<std::vector<int>>& adjacencyMatrix) {
  int n = adjacencyMatrix.size();
  vector<bool> hasNeighbors(adjacencyMatrix.size(), false);

  pair<int, int> res(INF, INF);

  // Инициализация матрицы расстояний
  std::vector<std::vector<int>> distance(n, std::vector<int>(n, INF));

  // Вычисление кратчайших расстояний между всеми парами вершин с помощью
  // алгоритма Флойда-Уоршелла
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (adjacencyMatrix[i][j] != 0) {
        hasNeighbors[i] = true;
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
      if (distance[i][j] > maxDistances[i] && hasNeighbors[i] && hasNeighbors[j] && i != j) {
        maxDistances[i] = distance[i][j];
      }
    }
  }

  // Находим минимальное из максимальных расстояний
  //int graphRadius = INF;
  //int center = INF;

  for (int i = 0; i < n; ++i) {
    if (maxDistances[i] < res.first && hasNeighbors[i]) {
      res.first = maxDistances[i];
      res.second = i;
    }
  }

  //return graphRadius;
  return res;
}

vector<int> romanKDomSetHEU1(vvi adjMatrix, int k, vector<int>& weights) {
  vector<int> domSet;
  vector<int> sortedVertices = sortVerticesByDegree(adjMatrix);
  //vector<int> weights(adjMatrix.size(), 0);
  int currentK = k;

  for (int i = 0; i < sortedVertices.size(); i++) {
    cout << sortedVertices[i] << " ";
  }
  cout << endl;

  vector<bool> isCovered(adjMatrix.size(), false);

  pair<int, int> mid = calculateGraphRadius(adjMatrix);
  int radius = mid.first;
  int center = mid.second;
  cout << "radius = " << radius << endl;

  if (radius <= k) {
    domSet.push_back(center);
    weights[center] = radius;
    isCovered[center] = true;
    vector<int> neighbors =
        getVerticesAtDistanceKOrLess(adjMatrix, center, radius);
    for (int i = 0; i < neighbors.size(); i++) {
      isCovered[neighbors[i]] = true;
    }
  } else {
    for (int i = 0; i < sortedVertices.size(); i++) {
      if (!isCovered[sortedVertices[i]]) {
        domSet.push_back(sortedVertices[i]);
        isCovered[sortedVertices[i]] = true;
        weights[sortedVertices[i]] = k;
        vector<int> currentNeighbors =
            getVerticesAtDistanceKOrLess(adjMatrix, sortedVertices[i], k);
        for (int j = 0; j < currentNeighbors.size(); j++) {
          isCovered[currentNeighbors[j]] = true;
        }
      }
    }
  }

  cout << "weights: " << endl;
  for (int i = 0; i < weights.size(); i++) {
    cout << weights[i] << ", ";
  }
  cout << endl;

  for (int i = 0; i < domSet.size(); i++) {
    vector<int> neighbors =
        getVerticesAtDistanceKOrLess(adjMatrix, domSet[i], currentK);
    cout << "neighbors: ";
    for (int j = 0; j < neighbors.size(); j++) {
      cout << neighbors[j] << " ";
    }
    cout << endl;
    int dominated = 0;
    for (int j = 0; j < neighbors.size(); j++) {
      cout << isCovered[neighbors[j]];
      if (isCovered[neighbors[j]]) {
        dominated++;
      }
    }
    cout << endl;
    vector<int> neighborsLess =
        getVerticesAtDistanceKOrLess(adjMatrix, domSet[i], currentK - 1);
    cout << "neighborsLess: ";
    for (int j = 0; j < neighborsLess.size(); j++) {
      cout << neighborsLess[j] << " ";
    }
    cout << endl;
    int dominatedLess = 0;
    for (int j = 0; j < neighborsLess.size(); j++) {
      cout << isCovered[neighborsLess[j]];
      if (isCovered[neighborsLess[j]]) {
        dominatedLess++;
      }
    }
    cout << endl;

    cout << "vertex " << domSet[i] << endl;
    cout << "dominated = " << dominated << endl;
    cout << "dominatedLess = " << dominatedLess << endl;
    cout << "currentK = " << currentK << endl;

    while (dominated == dominatedLess && dominated != 0) {
      currentK--;
      neighbors = getVerticesAtDistanceKOrLess(adjMatrix, domSet[i], currentK);
      dominated = 0;
      for (int j = 0; j < neighbors.size(); j++) {
        if (isCovered[neighbors[j]]) {
          dominated++;
        }
      }
      neighborsLess =
          getVerticesAtDistanceKOrLess(adjMatrix, domSet[i], currentK - 1);
      dominatedLess = 0;
      for (int j = 0; j < neighborsLess.size(); j++) {
        if (isCovered[neighborsLess[j]]) {
          dominatedLess++;
        }
      }

      weights[domSet[i]] = currentK;
    }
    currentK = k;
  }

  cout << "weights: " << endl;
  for (int i = 0; i < weights.size(); i++) {
    if (i > 0) cout << ", ";
    cout << weights[i];
  }
  cout << endl;
  cout << k << "-dominating set by heuristic 1: ";
  for (int i = 0; i < domSet.size(); i++) {
    if (i > 0) cout << ", ";
    cout << domSet[i];
  }
  cout << endl;

  return domSet;
}

vector<int> romanKDomSetHEU2(vvi adjMatrix, int k, vector<int>& weights, int alpha, double loopTime) {
  vector<int> domSet;
  vector<int> sortedVertices = sortVerticesByDegree(adjMatrix);
  //vector<int> weights(adjMatrix.size(), 0);
  int currentK = k;

  for (int i = 0; i < sortedVertices.size(); i++) {
    cout << sortedVertices[i] << " ";
  }
  cout << endl;

  vector<bool> isCovered(adjMatrix.size(), false);
  double workTime = 0;
  pair<int, int> mid = calculateGraphRadius(adjMatrix);
  int radius = mid.first;
  int center = mid.second;
  if (radius <= k) {
    domSet.push_back(center);
    weights[center] = radius;
    isCovered[center] = true;
    vector<int> neighbors =
        getVerticesAtDistanceKOrLess(adjMatrix, center, radius);
    for (int i = 0; i < neighbors.size(); i++) {
      isCovered[neighbors[i]] = true;
    }
  } else {
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
        weights[sortedVertices[i]] = k;
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
        weights[sortedVertices[i]] = k;
        vector<int> currentNeighbors =
            getVerticesAtDistanceKOrLess(adjMatrix, sortedVertices[i], k);
        for (int j = 0; j < currentNeighbors.size(); j++) {
          isCovered[currentNeighbors[j]] = true;
        }
      }
    }
  }

  for (int i = 0; i < domSet.size(); i++) {
    vector<int> neighbors =
        getVerticesAtDistanceKOrLess(adjMatrix, domSet[i], currentK);
    cout << "neighbors: ";
    for (int j = 0; j < neighbors.size(); j++) {
      cout << neighbors[j] << " ";
    }
    cout << endl;
    int dominated = 0;
    for (int j = 0; j < neighbors.size(); j++) {
      cout << isCovered[neighbors[j]];
      if (isCovered[neighbors[j]]) {
        dominated++;
      }
    }
    cout << endl;
    vector<int> neighborsLess =
        getVerticesAtDistanceKOrLess(adjMatrix, domSet[i], currentK - 1);
    cout << "neighborsLess: ";
    for (int j = 0; j < neighborsLess.size(); j++) {
      cout << neighborsLess[j] << " ";
    }
    cout << endl;
    int dominatedLess = 0;
    for (int j = 0; j < neighborsLess.size(); j++) {
      cout << isCovered[neighborsLess[j]];
      if (isCovered[neighborsLess[j]]) {
        dominatedLess++;
      }
    }
    cout << endl;

    cout << "vertex " << domSet[i] << endl;
    cout << "dominated = " << dominated << endl;
    cout << "dominatedLess = " << dominatedLess << endl;
    cout << "currentK = " << currentK << endl;

    while (dominated == dominatedLess && dominated != 0) {
      currentK--;
      neighbors = getVerticesAtDistanceKOrLess(adjMatrix, domSet[i], currentK);
      dominated = 0;
      for (int j = 0; j < neighbors.size(); j++) {
        if (isCovered[neighbors[j]]) {
          dominated++;
        }
      }
      neighborsLess =
          getVerticesAtDistanceKOrLess(adjMatrix, domSet[i], currentK - 1);
      dominatedLess = 0;
      for (int j = 0; j < neighborsLess.size(); j++) {
        if (isCovered[neighborsLess[j]]) {
          dominatedLess++;
        }
      }

      weights[domSet[i]] = currentK;
    }
    currentK = k;
  }

  cout << k << "-dominating set by roman heuristic 2: ";
  for (int i = 0; i < domSet.size(); i++) {
    if (i > 0) cout << ", ";
    cout << domSet[i];
  }
  cout << endl;

  return domSet;
}

void generateWeightsGraphvizFile(vector<vector<int>> adjacencyMatrix,
                                 string graphName, vector<int> domSet,
                                 vector<int>& weights) {
  int n = adjacencyMatrix.size();

  ofstream ofile;
  ofile.open(graphName + ".gv");

  // Заголовок графа
  ofile << "graph " << graphName << " {\n";

  // Вывод вершин
  for (int i = 0; i < n; i++) {
    ofile << "\t" << i + 1 << ";\n";
  }

  // Вывод ребер
  for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) {
      if (adjacencyMatrix[i][j] == 1) {
        ofile << "\t" << i + 1 << " -- " << j + 1 << ";\n";
      }
    }
  }

  for (int i = 0; i < n; i++) {
    ofile << "\t" << i + 1 << " [label=\"" << i + 1 << " (" << weights[i] << ")\"]"
          << ";\n";
  }

  for (int vertex : domSet) {
    ofile << "    " << vertex + 1 << " [style=filled, fillcolor=red];"
          << std::endl;
  }

  // Закрытие файла
  ofile << "}\n";
  ofile.close();

  // Команды для генерации изображения графа
  system(("fdp -Tpng " + graphName + ".gv -o " + graphName + ".png").c_str());
  // system((graphName + ".png").c_str());
}
