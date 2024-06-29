#include "../../s21_graph_algorithms.h"

namespace s21 {

GraphAlgorithms::TsmResult GraphAlgorithms::SolveTravelingSalesmanProblem(
    Graph& graph) {
  const int kNumAnts =
      20;  // количество муравьев, используемых в каждом цикле алгоритма
  const int kNumIterations = 1000;  // количество итераций алгоритма
  const double kAlpha =
      1.0;  // вес феромонов в формуле вероятности выбора следующей вершины
  const double kBeta =
      5.0;  // вес расстояния в формуле вероятности выбора следующей вершины.
  const double kEvaporation = 0.5;  // коэффициент испарения феромонов
  const double kQ = 100.0;  // количество феромонов, выделяемых каждым муравьем

  int num_vertices = graph.GetSize();

  if (num_vertices < 1) {
    throw std::runtime_error(
        graph.GetDictionary().GetMessage("error_empty_graph"));
  }

  Matrix distances = graph.GetMatrix();
  std::vector<std::vector<double>> pheromones(
      num_vertices, std::vector<double>(num_vertices, 1.0));

  std::vector<int> best_path;
  double best_distance = std::numeric_limits<double>::infinity();

  std::random_device rd;
  std::mt19937 gen(rd());

  for (int iteration = 0; iteration < kNumIterations; ++iteration) {
    std::vector<std::vector<int>> paths(kNumAnts);
    std::vector<double> distances_travelled(kNumAnts, 0.0);

    for (int ant = 0; ant < kNumAnts; ++ant) {
      paths[ant].push_back(0);

      std::vector<bool> visited(num_vertices, false);
      visited[0] = true;

      for (int step = 1; step < num_vertices; ++step) {
        int current_vertex = paths[ant].back();
        std::vector<double> probabilities(num_vertices, 0.0);
        double total_prob = 0.0;

        for (int next_vertex = 0; next_vertex < num_vertices; ++next_vertex) {
          if (!visited[next_vertex] &&
              distances[current_vertex][next_vertex] > 0) {
            probabilities[next_vertex] =
                std::pow(pheromones[current_vertex][next_vertex], kAlpha) *
                std::pow(1.0 / distances[current_vertex][next_vertex], kBeta);
            total_prob += probabilities[next_vertex];
          }
        }

        if (total_prob == 0) {
          distances_travelled[ant] = std::numeric_limits<double>::infinity();
          break;
        }

        std::discrete_distribution<> dist(probabilities.begin(),
                                          probabilities.end());
        int next_vertex = dist(gen);

        paths[ant].push_back(next_vertex);
        distances_travelled[ant] += distances[current_vertex][next_vertex];
        visited[next_vertex] = true;
      }

      if (distances_travelled[ant] != std::numeric_limits<double>::infinity()) {
        int last_vertex = paths[ant].back();
        if (distances[last_vertex][0] > 0) {
          distances_travelled[ant] += distances[last_vertex][0];
          paths[ant].push_back(0);
        } else {
          distances_travelled[ant] = std::numeric_limits<double>::infinity();
        }

        if (distances_travelled[ant] < best_distance) {
          best_distance = distances_travelled[ant];
          best_path = paths[ant];
        }
      }
    }

    for (int i = 0; i < num_vertices; ++i) {
      for (int j = 0; j < num_vertices; ++j) {
        pheromones[i][j] *= (1.0 - kEvaporation);
      }
    }

    for (int ant = 0; ant < kNumAnts; ++ant) {
      if (distances_travelled[ant] != std::numeric_limits<double>::infinity()) {
        for (size_t i = 0; i < paths[ant].size() - 1; ++i) {
          int u = paths[ant][i];
          int v = paths[ant][i + 1];
          pheromones[u][v] += kQ / distances_travelled[ant];
          pheromones[v][u] += kQ / distances_travelled[ant];
        }
      }
    }
  }

  TsmResult result;
  result.vertices = best_path;
  result.distance = best_distance;

  for (auto& vertex : result.vertices) {
    vertex += 1;
  }

  return result;
}

}  // namespace s21
