#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
#include <limits>
#include <stack>
#include <list>

#include <stdlib.h> // srand, rand
#include <time.h> // time

using namespace std;

int N;
vector<vector<float>> dists; // distance matrix

template <typename T>
void print_matrix(const vector<vector<T>> &m) {
  for (unsigned int i = 0; i < m.size(); ++i) {
    cout << i << "| ";
    for (unsigned int j = 0; j < m[i].size(); ++j) {
      cout << m[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
}

template <typename T>
void print_adjacency_list(const vector<vector<T>> &m) {
  int i = 0;
  for (vector<T> u : m) {
    cout << i++ << "| ";
    for (T v : u) {
      cout << v << " ";
    }
    cout << endl;
  }
  cout << endl;
}

float tour_distance(const vector<int> &tour) {
  float sum = 0;
  for (int n = 1; n < N; ++n) {
    sum += dists[tour[n-1]][tour[n]];
  }
  return sum;
}

// prims algorithm
vector<vector<int>> prims() {
  vector<int> parent(N);
  vector<int> key(N, numeric_limits<int>::max());
  vector<bool> used(N, false);

  key[0] = 0;
  parent[0] = -1;

  for (int C = 0; C < N-1; ++C) {
    int u, min = numeric_limits<int>::max();
    // find current min element that is not used
    for (int v = 0; v < N; ++v) {
      if (used[v] == false && key[v] < min) {
        u = v, min = key[v];
      }
    }
    
    used[u] = true;
    for (int v = 0; v < N; v++) {
      if (dists[u][v] > 0 && used[v] == false && dists[u][v] < key[v]) {
        parent[v] = u;
        key[v] = dists[u][v];
      }
    }
  }

  // construct adjacency list
  vector<vector<int>> g(N);
  for (int i = 0; i < N; ++i) {
    int j = parent[i];
    if (j == -1)
      continue;

    g[i].push_back(j);
    g[j].push_back(i);
  }
  return g;
}

// greedy algorithm to find minimal matching
void perfect_matching(vector<vector<int>> &g) {
  list<int> odds;

  // find nodes with odd degree
  for (int u = 0; u < N; ++u) {
    if (g[u].size() % 2 != 0)
      odds.push_back(u);
  }
  
  // add edges to the matrix
  while (odds.size() > 0) {
    int v = odds.front();
    odds.pop_front();
    int closest = odds.front();
    float length = dists[closest][v];
    for (int u : odds) {
      if (dists[u][v] < length) {
        length = dists[u][v];
        closest = u;
      }
    }

    g[closest].push_back(v);
    g[v].push_back(closest);
    odds.remove(closest);
  }
}

vector<int> euler_path(vector<vector<int>> g, int start) {
  vector<int> path;
  stack<int> q;
  int cur = start;
  while (!q.empty() || g[cur].size() > 0) {
    if (g[cur].size() == 0) {
      path.push_back(cur);
      cur = q.top();
      q.pop();
    }
    else {
      q.push(cur);

      // grab any edge
      int neighbor = g[cur].back();
      g[cur].pop_back();

      // remove edge
      for (unsigned int i = 0; i < g[neighbor].size(); ++i) {
        if (g[neighbor][i] == cur) {
          g[neighbor].erase(g[neighbor].begin() + i);
          break;
        }
      }

      cur = neighbor;
    }
  }
  path.push_back(cur);
  return path;
}

vector<int> hamiltonian_path(vector<int> path) {
  vector<bool> visited(N, false);

  int start = path.front();
  visited[start] = true;
  auto cur = path.begin();
  auto next = cur+1;
  while (next != path.end()) {
    if (!visited[*next]) {
      cur = next;
      visited[*cur] = true;
      next = cur + 1;
    } else {
      next = path.erase(next);
    }
  }
  return path;
}

vector<int> christofides(int start) {
  auto g = prims();
  perfect_matching(g);
  vector<int> path = euler_path(g, start);
  path = hamiltonian_path(path);
  return path;
}

std::vector<int> tsp_2opt(std::vector<int> tour) {
  bool improved = true;
  while (improved) {
    improved = false;
    for (int i = 0; i < N; ++i) {
      for (int j = i + 3; j < N; ++j) {
        float cur = dists[tour[i]][tour[i+1]] + dists[tour[j]][tour[j-1]];
        float after = dists[tour[i]][tour[j-1]] + dists[tour[j]][tour[i+1]];

        if (after < cur) {
          reverse(tour.begin()+i+1, tour.begin()+j);
          improved = true;
        }
      }
    }
  }
  return tour;
}

int main() {
  cin >> N;

  float xv[N], yv[N];
  for (int i = 0; i < N; ++i) {
    float x, y;
    cin >> x >> y;
    xv[i] = x;
    yv[i] = y;
  }

  // initalize matrixes
  dists.resize(N);
  for (int i = 0; i < N; ++i) {
    dists[i].resize(N, 0);

    for (int j = 0; j < N; ++j) {
      dists[i][j] = sqrt(pow(xv[i] - xv[j],2) + pow(yv[i] - yv[j],2));
    }
  }


  // run christofides + 2opt K times and grab the best
  // one (+ ~1.0 on kattis) each time selecting a
  // new starting point for the euler path
  int K = 10; // K=100 gives time limit exceeded
  float best_dist = numeric_limits<float>::max();
  vector<int> best_tour;
  vector<int> tour;
  srand(time(NULL));
  for (int i = 0; i < K; ++i) {
    int start = rand() % N;
    tour = christofides(start);
    tour = tsp_2opt(tour);
    float dist = tour_distance(tour);
    if (dist < best_dist) {
      best_dist = dist;
      best_tour = tour;
    }

  }

  // rotate tour until we have the best one
  tour = best_tour;
  for (int i = 0; i < N-1; ++i) {
    rotate(tour.begin(), tour.begin()+1, tour.end());
    float dist = tour_distance(tour);
    if (dist < best_dist) {
      best_dist = dist;
      best_tour = tour;
    }
  }

  // print
  for (int n : best_tour) {
    cout << n << endl;
  }

  //cout << "distance: " << tour_distance(best_tour);
}
