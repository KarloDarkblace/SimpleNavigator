#include "../../s21_graph.h"

namespace s21 {

void Graph::LoadGraphFromFile(const std::string& filename) {
  std::ifstream file(filename);
  unsigned int size;
  if (!file.is_open()) {
    throw std::runtime_error(dictionary_.GetMessage("error_open_file"));
  }
  std::string line;

  if (std::getline(file, line)) {
    std::istringstream iss(line);
    if (iss >> size && size != 0) {
      size_ = size;
      graph_.resize(size, std::vector<int>(size));
    } else {
      throw std::runtime_error(dictionary_.GetMessage("error_read_size"));
    }
  } else {
    throw std::runtime_error(dictionary_.GetMessage("error_read_line_size"));
  }

  for (int i = 0; i < size_; ++i) {
    if (std::getline(file, line)) {
      std::istringstream iss(line);
      std::string token;
      for (int j = 0; j < size_; ++j) {
        if (iss >> token) {
          try {
            graph_[i][j] = std::stoi(token);
          } catch (const std::invalid_argument&) {
            throw std::runtime_error(
                dictionary_.GetMessage("error_convert_distance") + token);
          } catch (const std::out_of_range&) {
            throw std::runtime_error(
                dictionary_.GetMessage("error_distance_out_of_range") + token);
          }
        } else {
          throw std::runtime_error(
              dictionary_.GetMessage("error_read_distance_matrix"));
        }
      }
    } else {
      throw std::runtime_error(
          dictionary_.GetMessage("error_read_line_distances"));
    }
  }

  file.close();

  if (!IsGraphConnected()) {
    size_ = 0;
    graph_.clear();
    throw std::runtime_error(
        dictionary_.GetMessage("error_graph_not_connected"));
  }
}

bool Graph::IsGraphConnected() const noexcept {
  if (size_ == 0)
    return false;

  auto BFS = [this](int start) -> int {
    std::vector<bool> visited(size_, false);
    std::queue<int> queue;
    int visited_count = 0;

    queue.push(start);
    visited[start] = true;
    visited_count++;

    while (!queue.empty()) {
      int vertex = queue.front();
      queue.pop();

      for (int i = 0; i < size_; ++i) {
        if (graph_[vertex][i] != 0 && !visited[i]) {
          queue.push(i);
          visited[i] = true;
          visited_count++;
        }
      }
    }

    return visited_count;
  };

  for (int i = 0; i < size_; ++i) {
    if (BFS(i) == size_) {
      return true;
    }
  }

  return false;
}

}  // namespace s21
