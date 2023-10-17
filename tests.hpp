#include "graph_infector.hpp"
#include <random>
#include <cassert>

std::vector<std::pair<int, int>> generate_graph(int vertices_num, int edges_num) {
  std::mt19937_64 mersenne(time(nullptr));
  std::vector<std::pair<int, int>> edges(edges_num);
  for (int i = 0; i < edges_num; ++i) {
    edges[i].first = mersenne() % vertices_num;
    edges[i].second = mersenne() % vertices_num;
  }
  return edges;
}

void test(int vertices_num, int edges_num, int iterations) {
  for (int i = 0; i < iterations; ++i) {
    auto graph = Graph(generate_graph(vertices_num, edges_num));
    auto g = graph.get_adjacency_list();
    auto v = GraphInfector(graph.get_adjacency_list()).infect_all();
    assert(graph.check_infection(v));
  }
}

void make_some_tests() {
  test(10, 20, 100000);
  std::cout << "small graphs passed\n";
  test(100, 200, 10000);
  std::cout << "sparse graphs passed\n";
  test(100, 2000, 1000);
  std::cout << "dense graphs passed\n";
  test(1000, 100000, 100);
  std::cout << "big graphs passed\n";
}