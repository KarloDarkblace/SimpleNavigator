#include "../../s21_graph_algorithms.h"

#include <queue>

namespace s21 {

int GraphAlgorithms::GetShortestPathBetweenVertices(Graph& graph,
                                                    const int& vertex1,
                                                    const int& vertex2) {
  if (vertex1 < 1 || vertex1 > graph.GetSize()) {
    throw std::runtime_error(
        graph.GetDictionary().GetMessage("invalid_start_vertex"));
  }
  if (vertex2 < 1 || vertex2 > graph.GetSize()) {
    throw std::runtime_error(
        graph.GetDictionary().GetMessage("invalid_start_vertex"));
  }
  using pii = std::pair<int, int>;

  int size = graph.GetSize();
  std::priority_queue<pii, std::vector<pii>, std::greater<>> pq;
  std::vector<int> dist(size, std::numeric_limits<int>::max());
  std::vector<int> prev(size, -1);
  short_path_.clear();

  int start = vertex1 - 1;
  int end = vertex2 - 1;

  dist[start] = 0;
  pq.emplace(0, start);

  while (!pq.empty()) {
    int u = pq.top().second;
    int u_dist = pq.top().first;
    pq.pop();

    if (u == end) {
      break;
    }

    if (u_dist > dist[u])
      continue;

    for (int v = 0; v < size; ++v) {
      int weight = graph.GetMatrix()[u][v];
      if (weight > 0 && dist[u] + weight < dist[v]) {
        dist[v] = dist[u] + weight;
        pq.emplace(dist[v], v);
        prev[v] = u;
      }
    }
  }

  if (dist[end] == std::numeric_limits<int>::max()) {
    return -1;
  }
  for (int at = end; at != -1; at = prev[at]) {
    short_path_.push_back(at + 1);
  }
  std::reverse(short_path_.begin(), short_path_.end());

  return dist[end];
}

}  // namespace s21