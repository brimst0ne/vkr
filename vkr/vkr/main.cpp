#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
#include <random>
#include <fstream>
#include <unordered_set>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

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

//-------------------------------------------------------------------

vvi generateGraph(int n, int m) {    //Эвристическая функция генерации случайного графа
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

//-------------------------------------------------------------------

vector<vector<int>> removeIsolatedVertices(    //Функция удаления изолированных вершин в графе
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

//-------------------------------------------------------------------

int countEdges(vvi adjMatrix) {     //Функция подсчета количества ребер в графе
  
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

//-------------------------------------------------------------------

vector<int> getVerticesAtDistanceK(vector<vector<int>> adjacencyMatrix,    //Функция для нахождения всех вершин на расстоянии ровно k от данной
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

//-------------------------------------------------------------------

vector<int> getVerticesAtDistanceKOrLess(vector<vector<int>> adjacencyMatrix,    //Функция для нахождения k-окрестности вершины 
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

//-------------------------------------------------------------------

void generateGraphvizFile(vector<vector<int>> adjacencyMatrix,    //Функция для создания изображения графа при помощи Graphviz
                          string graphName, vector<int> domSet) {
  int n = adjacencyMatrix.size();

  ofstream ofile;
  ofile.open(graphName + ".gv");

  // Заголовок графа
  ofile << "graph " << graphName << " {\n";

  // Вывод вершин
  for (int i = 0; i < n; i++) {
    ofile << "\t" << i << ";\n";
  }

  // Вывод ребер
  for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) {
      if (adjacencyMatrix[i][j] == 1) {
        ofile << "\t" << i << " -- " << j << ";\n";
      }
    }
  }

  for (int vertex : domSet) {
    ofile << "    " << vertex << " [style=filled, fillcolor=red];" << std::endl;
  }

  // Закрытие файла
  ofile << "}\n";
  ofile.close();

  // Команды для генерации изображения графа
  system(("fdp -Tpng " + graphName + ".gv -o " + graphName + ".png").c_str());
  system((graphName + ".png").c_str());
}

//-------------------------------------------------------------------

vector<int> findMinDomSet(vvi adjMatrix, int n, int k) {
  vector<int> domSet;  // для хранения k-доминирующего множества

  vector<bool> unmarked(n, true);  // для хранения маркированных вершин

  // пока все вершины не пройдены
  while (true) {
    

    // выбираем вершину с максимальной близостью к неотмеченным вершинам
    int maxDegree = -1;
    int maxDegreeVertex = -1;
    for (int i = 0; i < n; i++) {
      if (!unmarked[i]) continue;

      int degree = 0;
      for (int j = 0; j < n; j++) {
        if (adjMatrix[i][j] && unmarked[j]) degree++;
      }

      if (degree > maxDegree) {
        maxDegree = degree;
        maxDegreeVertex = i;
      }
    }

    cout << "maxDegree: " << maxDegree << endl;
    cout << "maxDegreeVertex: " << maxDegreeVertex << endl;

    if (maxDegreeVertex == -1) break;  // маркировка вершин завершена

    domSet.push_back(maxDegreeVertex);  // добавляем выбранную вершину в
                                        // к-доминирующее множество
    unmarked[maxDegreeVertex] = false;  // помечаем выбранную вершину

    // помечаем всех соседей выбранной вершины как пройденных
    for (int i = 0; i < n; i++) {
      if (adjMatrix[maxDegreeVertex][i]) unmarked[i] = false;
    }

    //if (domSet.size() >= k)
      //break;  // выбрано достаточное количество вершин для к-доминирующего
              // множества
  }

  // Вывод множества на экран
  cout << "Minimal " << k << "-dominating set: ";
  for (int i = 0; i < domSet.size(); i++) {
    if (i > 0) cout << ", ";
    cout << domSet[i];  // +1 - для вывода вершин начиная с 1
  }
  return domSet;
}

//-------------------------------------------------------------------

vector<int> findKDomSet1(vvi adjMatrix, int n, int k) {

  vector<int> domSet;
  vector<bool> unmarked(n, true);

  while (true) {
    // выбираем вершину с максимальной близостью к неотмеченным вершинам
    int maxDegree = -1;
    int maxDegreeVertex = -1;
    for (int i = 0; i < n; i++) {
      cout << unmarked[i] << endl;
      if (!unmarked[i]) continue;

      int degree = 0;
      for (int j = 0; j < n; j++) {
        if (adjMatrix[i][j] && unmarked[j]) degree++;
      }

      if (degree > maxDegree) {
        maxDegree = degree;
        maxDegreeVertex = i;
      }
    }

    cout << "maxDegree: " << maxDegree << endl;
    cout << "maxDegreeVertex: " << maxDegreeVertex << endl;

    if (maxDegreeVertex == -1) break;  // маркировка вершин завершена

    domSet.push_back(maxDegreeVertex);  // добавляем выбранную вершину в
                                        // к-доминирующее множество
    unmarked[maxDegreeVertex] = false;  // помечаем выбранную вершину

    vector<int> kNeighbors =
        getVerticesAtDistanceKOrLess(adjMatrix, maxDegreeVertex, k);

    for (int i = 0; i < kNeighbors.size(); i++) {
      unmarked[kNeighbors[i]] = false;
    }

    // if (domSet.size() >= k)
    // break;  // выбрано достаточное количество вершин для к-доминирующего
    // множества
  }

  // Вывод множества на экран
  cout << k << "-dominating set by heuristic 1: ";
  for (int i = 0; i < domSet.size(); i++) {
    if (i > 0) cout << ", ";
    cout << domSet[i];  // +1 - для вывода вершин начиная с 1
  }
  return domSet;

}

//-------------------------------------------------------------------

vector<int> findKDomSet2(vvi adjMatrix, int n, int k, int alpha, double loopTime) {

  vector<int> domSet;
  vector<bool> unmarked(n, true);
  double workTime = 0;

  while (true) {
    if (workTime >= loopTime ||
        find(unmarked.begin(), unmarked.end(), 1) == unmarked.end()) {
      break;
    }

    double start = clock();
    int maxDegree = -1;
    int maxDegreeVertex = -1;
    for (int i = 0; i < n; i++) {
      cout << unmarked[i] << endl;
      if (!unmarked[i]) continue;

      int degree = 0;
      for (int j = 0; j < n; j++) {
        if (adjMatrix[i][j] && unmarked[j]) degree++;
      }

      if (degree > maxDegree) {             //TODO: Дописать эту функцию!!!
        maxDegree = degree;
        maxDegreeVertex = i;
      }
    }

    cout << "maxDegree: " << maxDegree << endl;
    cout << "maxDegreeVertex: " << maxDegreeVertex << endl;

    vector<int> kNeighbors =
        getVerticesAtDistanceKOrLess(adjMatrix, maxDegreeVertex, k);
    vector<int> notDominatedKNeighbors;
    for (int i = 0; i < kNeighbors.size(); i++) {
      if (unmarked[kNeighbors[i]]) {
        notDominatedKNeighbors.push_back(kNeighbors[i]);
      }
    }

    if (notDominatedKNeighbors.size() >= alpha) {
      
    }

    double finish = clock();
    workTime = finish - start;
  }

  // Вывод множества на экран
  cout << k << "-dominating set by heuristic 2: ";
  for (int i = 0; i < domSet.size(); i++) {
    if (i > 0) cout << ", ";
    cout << domSet[i];  // +1 - для вывода вершин начиная с 1
  }

  return domSet;

}

//-------------------------------------------------------------------

vector<int> sortVerticesByDegree(
    const vector<vector<int>>& adjacencyMatrix) {
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

//-------------------------------------------------------------------

vector<int> sortVerticesByKNeighbors(const vvi& adjMatrix, vector<int> domSet, int k) {

  vector<int> vertices;
  for (int i = 0; i < domSet.size(); ++i) {
    vertices.push_back(domSet[i]);
  }

  for (int i = 0; i < vertices.size(); i++) {
    cout << vertices[i] << " ";
  }
  cout << endl;

  sort(vertices.begin(), vertices.end(), [&adjMatrix, &domSet, &k, &vertices](int a, int b) {

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

//-------------------------------------------------------------------

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

//-------------------------------------------------------------------

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

    vector<int> kNeighbors = getVerticesAtDistanceKOrLess(adjMatrix, sortedVertices[i], k);
    vector<int> notDominatedNeighbors;

    for (int k = 0; k < kNeighbors.size(); k++) {
      if (!isCovered[kNeighbors[k]]) {
        notDominatedNeighbors.push_back(kNeighbors[k]);
      }
    }

    if (!isCovered[sortedVertices[i]] || notDominatedNeighbors.size() >= alpha) {
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

//-------------------------------------------------------------------

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

//-------------------------------------------------------------------

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

//-------------------------------------------------------------------

vector<int> romanKDomSet(vvi adjMatrix, vi devices) {

  vector<int> domSet;



  return domSet;

}

//-------------------------------------------------------------------
//-------------------------------------------------------------------


int main() {
  srand(time(NULL));  // используем текущее время в качестве зерна для
                      // генератора случайных чисел
  //int n = rand() % 10 + 2;  // генерируем число вершин в диапазоне от 1 до 500
  //int m = rand() % (n * (n - 1) / 2) + 1;  // генерируем число ребер в диапазоне от 1 до n * (n - 1) / 2
  int n = 10 + rand() % (20 - 10 + 1);
  int m = rand() % (n * (n - 1) / 2) + 1;
  vvi adjMatrix = generateGraph(n, m);
  //vvi adjMatrix = BA_graph(n, 2);
  // выводим граф в виде матрицы смежности
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

  //vector<int> kDomSet = findKDomSet1(newAdjMatrix, nn, 2);
  unsigned int start = clock();
  vector<int> kDomSet1 = HEU1(newAdjMatrix, nn, 1);
  unsigned int time = clock() - start;
  cout << "HEU1 work time = " << time / 1000.0 << endl;

  start = clock();
  vector<int> kDomSet2 = HEU2(newAdjMatrix, nn, 1, 2, 0.005);
  time = clock() - start;
  cout << "HEU2 work time = " << time / 1000.0 << endl;

  vector<int> reducedDomSet = redundantRemoval(newAdjMatrix, kDomSet2, 1);
  //vector<int> kDomSet = findMinDomSet(newAdjMatrix, nn, 2);

  generateGraphvizFile(newAdjMatrix, "HEU1", kDomSet1);
  generateGraphvizFile(newAdjMatrix, "HEU2", kDomSet2);
  generateGraphvizFile(newAdjMatrix, "ReducedDomSet", reducedDomSet);
  //generateGraphvizFile(treeAdjMatrix, treeName);

  

  return 0;
}