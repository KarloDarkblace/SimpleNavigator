#include <stdexcept>
#include "../../s21_graph_algorithms.h"

// https://ru.algorithmica.org/cs/shortest-paths/bfs/

namespace s21 {

std::vector<int> GraphAlgorithms::BreadthFirstSearch(Graph& graph,
                                                     const int& start_vertex) {
  int size = graph.GetSize();
  if (start_vertex < 1 || start_vertex > size) {
    throw std::runtime_error(
        graph.GetDictionary().GetMessage("invalid_start_vertex") +
        std::to_string(size));
  }

  std::vector<bool> visited(size, false);
  std::vector<int> order;
  s21::queue<int> queue;

  queue.push(start_vertex);
  visited[start_vertex - 1] = true;

  while (!queue.empty()) {
    int current_vertex = queue.front();
    queue.pop();
    order.push_back(current_vertex);

    for (int i = 0; i < size; ++i) {
      if (graph.GetMatrix()[current_vertex - 1][i] != 0 && !visited[i]) {
        queue.push(i + 1);
        visited[i] = true;
      }
    }
  }

  return order;
}

}  // namespace s21
