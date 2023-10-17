#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <queue>

class Graph {
public:
  static std::vector<std::pair<int, int>> read_edges_list() {
    int edges_num;
    std::cin >> edges_num;
    std::vector<std::pair<int, int>> edges(edges_num);
    for (auto &[u, v]: edges) {
      std::cin >> u >> v;
    }
    return edges;
  }

  explicit Graph(std::vector<std::pair<int, int>> edges) {
    for (auto &[u, v]: edges) {
      if (u > v) {
        std::swap(u, v);
      }
    }
    sort(edges.begin(), edges.end());
    edges.resize(unique(edges.begin(), edges.end()) - edges.begin());

    std::unordered_set<int> original_vertices;
    for (auto [u, v]: edges) {
      original_vertices.insert(u);
      original_vertices.insert(v);
    }

    int vertices_num = original_vertices.size();
    original_numeration.resize(vertices_num);
    adjacency_list.assign(vertices_num, std::vector<int>());
    int counter = 0;
    for (auto v: original_vertices) {
      original_numeration[counter] = v;
      compressed_numeration[v] = counter;
      ++counter;
    }

    for (auto [u, v]: edges) {
      if (u != v) {
        adjacency_list[compressed_numeration[u]].push_back(compressed_numeration[v]);
        adjacency_list[compressed_numeration[v]].push_back(compressed_numeration[u]);
      }
    }
  }

  std::vector<int> to_original_numeration(const std::vector<int> &vertices) {
    std::vector<int> ans;
    for (int v: vertices) {
      ans.push_back(original_numeration[v]);
    }
    return ans;
  }

  std::vector<std::vector<int>> get_adjacency_list() {
    return adjacency_list;
  }

  bool check_infection(const std::vector<int> &preinfected) {
    std::queue<int> infected;
    int vertices_num = adjacency_list.size();
    std::vector<int> infected_neighnours_num(vertices_num, 0);
    for (auto v: preinfected) {
      infected.push(v);
      infected_neighnours_num[v] = 2;
    }

    int infected_num = 0;
    while (!infected.empty()) {
      int v = infected.front();
      infected.pop();
      ++infected_num;
      for (int to: adjacency_list[v]) {
        if (++infected_neighnours_num[to] == 2) {
          infected.push(to);
        }
      }
    }
    return infected_num == vertices_num;
  }

private:
  std::vector<int> original_numeration;
  std::unordered_map<int, int> compressed_numeration;
  std::vector<std::vector<int>> adjacency_list;
};
