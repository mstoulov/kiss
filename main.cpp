#include "tests.hpp"
#include <cstring>


int main(int argc, char* argv[]) {
  if (argc > 1 && strcmp(argv[1], "test") == 0){
    make_some_tests();
    std::cout << "tests passed!!!!";
    return 0;
  }

  auto graph = Graph(Graph::read_edges_list());
  auto preinfected = GraphInfector(graph.get_adjacency_list()).infect_all();
  auto selected_vertices = graph.to_original_numeration(preinfected);

  std::cout << selected_vertices.size() << "\n";
  for (auto el: selected_vertices) {
    std::cout << el << " ";
  }
  return 0;
}