#include "../../s21_graph_algorithms.h"

#include <limits>

// https://www.youtube.com/watch?v=vPHUm874EoA
// https://ru.algorithmica.org/cs/spanning-trees/prim/
// http://e-maxx.ru/algo/mst_prim

namespace s21 {

Matrix GraphAlgorithms::GetLeastSpanningTree(Graph& graph) {
  Matrix adjacency_matrix = graph.GetMatrix();
  int n = adjacency_matrix.size();

  if (n < 1) {
    throw std::runtime_error(
        graph.GetDictionary().GetMessage("error_empty_graph"));
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (adjacency_matrix[i][j] != 0) {
        adjacency_matrix[j][i] = adjacency_matrix[i][j];
      }
    }
  }

  Matrix mst(n, std::vector<int>(n, 0));

  std::vector<bool> used(n, false);
  std::vector<int> min_e(n, std::numeric_limits<int>::max());
  std::vector<int> sel_e(n, -1);

  min_e[0] = 0;
  for (int i = 0; i < n; ++i) {
    int v = -1;
    for (int j = 0; j < n; ++j) {
      if (!used[j] && (v == -1 || min_e[j] < min_e[v])) {
        v = j;
      }
    }

    used[v] = true;
    if (sel_e[v] != -1) {
      mst[v][sel_e[v]] = mst[sel_e[v]][v] = adjacency_matrix[v][sel_e[v]];
    }

    for (int to = 0; to < n; ++to) {
      if (adjacency_matrix[v][to] && !used[to] &&
          adjacency_matrix[v][to] < min_e[to]) {
        min_e[to] = adjacency_matrix[v][to];
        sel_e[to] = v;
      }
    }
  }

  return mst;
}

}  // namespace s21