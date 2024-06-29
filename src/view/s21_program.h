#ifndef A2_SIMPLENAVIGATOR_SRC_VIEW_S21_VIEW_H_
#define A2_SIMPLENAVIGATOR_SRC_VIEW_S21_VIEW_H_

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>

#include "../s21_dictionary.h"
#include "../s21_graph.h"
#include "../s21_graph_algorithms.h"

#define COLOR_RED_BEGIN "\033[1;31m"
#define COLOR_RED_END "\033[0m"

namespace s21 {

class Program {
 public:
  void Run();

 private:
  void PrintListCommands() noexcept;
  void PrintListCommandsRu() noexcept;
  void PrintListCommandsEn() noexcept;
  void PrintError(const std::string& message) noexcept;
  void ClearConsole() noexcept;
  void SetLanguage() noexcept;
  char GetCommand() noexcept;
  bool IsCorrectCommand(const char& command) noexcept;

  void HandleUploadGraph() noexcept;
  void HandleDepthFirstSearch() noexcept;
  void HandleBreadthFirstSearch() noexcept;
  void HandleShortestPathBetweenVertices() noexcept;
  void HandleShortestPathsBetweenAllVertices() noexcept;
  void HandleLeastSpanningTree() noexcept;
  void HandleSolveTravelingSalesmanProblem() noexcept;

 private:
  std::shared_ptr<Graph> graph_ = nullptr;
  GraphAlgorithms graph_alg_;
  std::string language_ = "ru";
  Dictionary dictionary_{language_};
};

}  // namespace s21

#endif  // A2_SIMPLENAVIGATOR_SRC_VIEW_S21_VIEW_H_
