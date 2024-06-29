#include "../../s21_graph.h"

namespace s21 {

bool Graph::IsGraphDirected() const noexcept {
  for (int i = 0; i < size_; ++i) {
    for (int j = 0; j < size_; ++j) {
      if (graph_[i][j] != graph_[j][i]) {
        return true;
      }
    }
  }
  return false;
}

}  // namespace s21