#include "../../s21_graph_algorithms.h"

namespace s21 {

std::vector<int> GraphAlgorithms::DepthFirstSearch(Graph& graph,
                                                   const int& start_vertex) {
  int size = graph.GetSize();
  if (start_vertex < 1 || start_vertex > size) {
    throw std::runtime_error(
        graph.GetDictionary().GetMessage("invalid_start_vertex") +
        std::to_string(size));
  }

  std::vector<int> result;
  s21::stack<int> stack;
  std::vector<bool> visited(size, false);

  stack.push(start_vertex - 1);

  while (!stack.empty()) {
    int vertex = stack.top();
    stack.pop();

    if (!visited[vertex]) {
      visited[vertex] = true;
      result.push_back(vertex);

      const auto& adjacency_matrix = graph.GetMatrix();
      for (int i = adjacency_matrix[vertex].size() - 1; i >= 0; --i) {
        if (adjacency_matrix[vertex][i] != 0 && !visited[i]) {
          stack.push(i);
        }
      }
    }
  }

  return result;
}

}  // namespace s21
