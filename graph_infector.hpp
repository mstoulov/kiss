#include "graph.hpp"
#include <set>

class GraphInfector {
public:
  explicit GraphInfector(const std::vector<std::vector<int>> &g) {
    vertices_num = g.size();
    adjacency_list = g;
    infected_neighbours_num.assign(vertices_num, 0);
    benefit.assign(vertices_num, 0);
    for (int i = 0; i < vertices_num; ++i) {
      benefit[i] = adjacency_list[i].size() * no_infected_neighbours_benefit;
    }
    for (int i = 0; i < vertices_num; ++i) {
      sorted_benefits.insert({benefit[i], i});
    }
  }

private:
  void infect_vertex(int v) {
    vertices_to_process.push(v);
    ++infected_vertices_num;
  }

  void select_vertex(int v) {
    selected_vertices.push_back(v);
    infect_vertex(v);
    infected_neighbours_num[v] = 2;
  }

  void process_infected_vertex(int v) {
    sorted_benefits.erase({benefit[v], v});
    for (int to: adjacency_list[v]) {
      add_infected_neighbour(to);
    }
  }

  void add_infected_neighbour(int v) {
    if (infected_neighbours_num[v] >= 2) {
      return;
    }

    infected_neighbours_num[v]++;
    if (infected_neighbours_num[v] == 2) {
      infect_vertex(v);
    }

    int benefit_delta;
    if (infected_neighbours_num[v] == 2) {
      benefit_delta = -one_infected_neighbours_benefit;
    } else {
      benefit_delta = one_infected_neighbours_benefit - no_infected_neighbours_benefit;
    }
    for (auto to: adjacency_list[v]) {
      if (infected_neighbours_num[to] >= 2) {
        continue;
      }
      sorted_benefits.erase({benefit[to], to});
      benefit[to] += benefit_delta;
      sorted_benefits.insert({benefit[to], to});
    }
  }

  void infect_most_benefit_vertex() {
    int vertex = sorted_benefits.begin()->second;
    sorted_benefits.erase(sorted_benefits.begin());
    select_vertex(vertex);
  }

public:
  std::vector<int> infect_all() {
    for (int i = 0; i < vertices_num; ++i) {
      if (adjacency_list[i].size() <= 1) {
        select_vertex(i);
      }
    }

    while (infected_vertices_num < vertices_num) {
      if (vertices_to_process.empty()) {
        infect_most_benefit_vertex();
      } else {
        process_infected_vertex(vertices_to_process.front());
        vertices_to_process.pop();
      }
    }

    return selected_vertices;
  }

private:
  int vertices_num;
  int infected_vertices_num = 0;
  std::vector<std::vector<int>> adjacency_list;
  std::vector<int> infected_neighbours_num;
  std::vector<int> benefit;
  std::set<std::pair<int, int>, std::greater<>> sorted_benefits;
  std::queue<int> vertices_to_process;
  std::vector<int> selected_vertices;

  static const int no_infected_neighbours_benefit = 1;
  static const int one_infected_neighbours_benefit = 2;
};
