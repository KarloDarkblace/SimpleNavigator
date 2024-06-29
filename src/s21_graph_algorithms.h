#ifndef A2_SIMPLENAVIGATOR_SRC_S21_GRAPH_ALGORITHMS_H_
#define A2_SIMPLENAVIGATOR_SRC_S21_GRAPH_ALGORITHMS_H_

#include <cmath>
#include <limits>
#include <random>
#include <vector>

#include "structures/s21_queue.h"
#include "structures/s21_stack.h"

#include "s21_graph.h"

namespace s21 {

class GraphAlgorithms final {

 public:
  struct TsmResult {
    std::vector<int> vertices;
    double distance;
  };

 public:
  std::vector<int> DepthFirstSearch(Graph& graph, const int& start_vertex);
  std::vector<int> BreadthFirstSearch(Graph& graph, const int& start_vertex);

  int GetShortestPathBetweenVertices(Graph& graph, const int& vertex1,
                                     const int& vertex2);
  Matrix GetShortestPathsBetweenAllVertices(Graph& graph);

  Matrix GetLeastSpanningTree(Graph& graph);

  TsmResult SolveTravelingSalesmanProblem(Graph& graph);

 private:
  std::vector<int> short_path_;
};

}  // namespace s21

#endif  // A2_SIMPLENAVIGATOR_SRC_S21_GRAPH_ALGORITHMS_H_