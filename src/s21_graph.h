#ifndef A2_SIMPLENAVIGATOR_SRC_S21_GRAPH_H_
#define A2_SIMPLENAVIGATOR_SRC_S21_GRAPH_H_

#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "s21_dictionary.h"

namespace s21 {

using Matrix = std::vector<std::vector<int>>;

class Graph final {

 public:
  void LoadGraphFromFile(const std::string& filename);
  void ExportGraphToDot(const std::string& filename);

 public:
  Matrix GetMatrix() const noexcept { return graph_; }
  int GetSize() const noexcept { return size_; }
  const Dictionary& GetDictionary() const noexcept { return dictionary_; }
  void SetLanguage(const std::string& language) {
    dictionary_.LoadLanguage(language);
  }

 private:
  bool IsGraphDirected() const noexcept;
  bool IsGraphConnected() const noexcept;

 private:
  int size_ = 0;
  Matrix graph_;
  Dictionary dictionary_{"ru"};
};

}  // namespace s21

#endif  // A2_SIMPLENAVIGATOR_SRC_S21_GRAPH_H_
