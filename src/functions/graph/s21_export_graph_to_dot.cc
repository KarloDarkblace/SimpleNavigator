#include "../../s21_graph.h"

namespace s21 {

void Graph::ExportGraphToDot(const std::string& filename) {
  if (size_ == 0 || graph_.empty()) {
    throw std::runtime_error(dictionary_.GetMessage("error_empty_graph"));
  }

  std::ofstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error(dictionary_.GetMessage("error_open_file"));
  }

  auto is_directed = IsGraphDirected();

  file << (is_directed ? "digraph" : "graph") << " S21 {\n";

  for (int i = 0; i < size_; ++i) {
    file << "    " << i + 1 << ";\n";
  }

  for (int i = 0; i < size_; ++i) {
    for (int j = 0; j < size_; ++j) {
      if (graph_[i][j] != 0) {
        if (is_directed) {
          file << "    " << i + 1 << " -> " << j + 1 << ";\n";
        } else if (j > i) {
          file << "    " << i + 1 << " -- " << j + 1 << ";\n";
        }
      }
    }
  }

  file << "}\n";
  file.close();
}

}  // namespace s21
