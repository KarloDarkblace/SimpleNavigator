#include "../../s21_graph_algorithms.h"

// http://e-maxx.ru/algo/floyd_warshall_algorithm
// https://silvertests.ru/GuideView.aspx?id=29791

namespace s21 {

Matrix GraphAlgorithms::GetShortestPathsBetweenAllVertices(Graph& graph) {
  Matrix adjacency_matrix = graph.GetMatrix();
  Matrix dist = adjacency_matrix;

  int size = adjacency_matrix.size();
  if (size < 1) {
    throw std::runtime_error(
        graph.GetDictionary().GetMessage("error_empty_graph"));
  }

  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      if (i != j && dist[i][j] == 0) {
        dist[i][j] = std::numeric_limits<int>::max() / 2;
      }
    }
  }

  for (int k = 0; k < size; ++k) {  // промежуточная вершина
    for (int i = 0; i < size; ++i) {    // начальная вершина
      for (int j = 0; j < size; ++j) {  // конечная вершина
        if (dist[i][k] + dist[k][j] < dist[i][j]) {
          dist[i][j] = dist[i][k] + dist[k][j];
        }
      }
    }
  }

  return dist;
}

}  // namespace s21
