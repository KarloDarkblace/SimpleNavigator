#include "s21_program.h"
#include <ostream>

namespace s21 {

void Program::Run() {
  ClearConsole();
  SetLanguage();

  char choice;
  while (true) {
    PrintListCommands();

    choice = GetCommand();

    if (choice == 'q') {
      std::cout << dictionary_.GetMessage("bye_message") << std::endl;
      break;
    }

    ClearConsole();
    switch (choice) {
      case '1':
        HandleUploadGraph();
        break;
      case '2':
        HandleBreadthFirstSearch();
        break;
      case '3':
        HandleDepthFirstSearch();
        break;
      case '4':
        HandleShortestPathBetweenVertices();
        break;
      case '5':
        HandleShortestPathsBetweenAllVertices();
        break;
      case '6':
        HandleLeastSpanningTree();
        break;
      case '7':
        HandleSolveTravelingSalesmanProblem();
        break;
    }
  }
}

void Program::SetLanguage() noexcept {
  std::cout << dictionary_.GetMessage("select_language");
  std::string lang;
  std::getline(std::cin, lang);

  if (lang == "ru" || lang == "en") {
    language_ = lang;
    dictionary_.LoadLanguage(language_);
  } else {
    PrintError(dictionary_.GetMessage("unknown_language"));
    dictionary_.LoadLanguage("ru");
  }
}

void Program::PrintListCommands() noexcept {
  if (language_ == "ru") {
    PrintListCommandsRu();
  } else {
    PrintListCommandsEn();
  }
}

void Program::PrintListCommandsRu() noexcept {
  std::cout << "---------------------------------------------\n";
  std::cout << "| (1) - Загрузка исходного графа из файла   |\n";
  if (graph_ != nullptr) {
    std::cout << "| (2) - Обход графа в ширину                |\n";
    std::cout << "| (3) - Обход графа в глубину               |\n";
    std::cout << "| (4) - Поиск кратчайшего пути между        |\n";
    std::cout << "|      произвольными двумя вершинами        |\n";
    std::cout << "| (5) - Поиск кратчайших путей между        |\n";
    std::cout << "|      всеми парами вершин в графе          |\n";
    std::cout << "| (6) - Поиск минимального остовного дерева |\n";
    std::cout << "| (7) - Решение задачи комивояжера          |\n";
  }
  std::cout << "|                                           |\n";
  std::cout << "| (q) - Выйти из программы                  |\n";
  std::cout << "---------------------------------------------\n";
}

void Program::PrintListCommandsEn() noexcept {
  std::cout << "-----------------------------------------------\n";
  std::cout << "| (1) - Load initial graph from file          |\n";
  if (graph_ != nullptr) {
    std::cout << "| (2) - Breadth First Search                  |\n";
    std::cout << "| (3) - Depth First Search                    |\n";
    std::cout << "| (4) - Find shortest path between            |\n";
    std::cout << "|      two vertices                           |\n";
    std::cout << "| (5) - Find shortest paths between           |\n";
    std::cout << "|      all pairs of vertices in the graph     |\n";
    std::cout << "| (6) - Find the minimum spanning tree        |\n";
    std::cout << "| (7) - Solve the traveling salesman problem  |\n";
  }
  std::cout << "|                                             |\n";
  std::cout << "| (q) - Exit the program                      |\n";
  std::cout << "-----------------------------------------------\n";
}

char Program::GetCommand() noexcept {
  std::string input;
  char ch = '\0';

  while (true) {
    std::cout << std::endl << "-> ";
    std::getline(std::cin, input);

    if (input.empty()) {
      continue;
    }

    ch = input[0];

    if (IsCorrectCommand(ch)) {
      break;
    } else {
      if (graph_ == nullptr && ch != '1') {
        PrintError(dictionary_.GetMessage("unknown_command_or_load_graph"));
      } else {
        PrintError(dictionary_.GetMessage("unknown_command"));
      }
    }
  }

  return ch;
}

bool Program::IsCorrectCommand(const char& command) noexcept {
  if (graph_ == nullptr) {
    return command == '1' || command == 'q';
  }
  return command == 'q' || (command >= '1' && command <= '7');
}

void Program::PrintError(const std::string& message) noexcept {
  std::cout << COLOR_RED_BEGIN << message << COLOR_RED_END << std::endl
            << std::endl;
}

void Program::ClearConsole() noexcept {
  system("clear");
}

void Program::HandleUploadGraph() noexcept {
  ClearConsole();
  std::cout << dictionary_.GetMessage("enter_filename") << std::endl;
  std::cout << "---> graphs/graph_1.txt\n";
  std::cout << std::endl << "-> ";

  std::string input;
  std::getline(std::cin, input);

  if (graph_ == nullptr) {
    graph_ = std::make_shared<Graph>();
    graph_->SetLanguage(language_);
  }

  try {
    graph_->LoadGraphFromFile(input);
  } catch (const std::runtime_error& e) {
    PrintError(e.what());
    graph_.reset();
  }
}

void Program::HandleDepthFirstSearch() noexcept {
  ClearConsole();
  std::cout << dictionary_.GetMessage("enter_vertex") << std::endl;
  std::cout << "---> 2" << std::endl;
  std::cout << std::endl << "-> ";

  int vertex;
  std::string input;
  std::getline(std::cin, input);

  try {
    vertex = std::stoi(input);
  } catch (const std::invalid_argument&) {
    PrintError(dictionary_.GetMessage("enter_correct_integer"));
    return;
  }

  try {
    auto result = graph_alg_.DepthFirstSearch(*graph_, vertex);
    std::cout << std::endl << dictionary_.GetMessage("result_dfs") << std::endl;

    for (const auto& v : result) {
      std::cout << v + 1 << " ";
    }
    std::cout << std::endl << std::endl;

  } catch (const std::exception& e) {
    PrintError(e.what());
  }
}

void Program::HandleBreadthFirstSearch() noexcept {
  ClearConsole();
  std::cout << dictionary_.GetMessage("enter_vertex") << std::endl;
  std::cout << "---> 4" << std::endl;
  std::cout << std::endl << "-> ";

  int vertex;
  std::string input;
  std::getline(std::cin, input);

  try {
    vertex = std::stoi(input);
  } catch (const std::invalid_argument&) {
    PrintError(dictionary_.GetMessage("enter_correct_integer"));
    return;
  }

  try {
    auto result = graph_alg_.BreadthFirstSearch(*graph_, vertex);
    std::cout << std::endl << dictionary_.GetMessage("result_bfs") << std::endl;

    for (const auto& v : result) {
      std::cout << v << " ";
    }
    std::cout << std::endl << std::endl;

  } catch (const std::exception& e) {
    PrintError(e.what());
  }
}

void Program::HandleShortestPathBetweenVertices() noexcept {
  ClearConsole();
  std::cout << dictionary_.GetMessage("enter_vertices") << std::endl;
  std::cout << "---> 4" << std::endl;
  std::cout << "---> 5" << std::endl;
  std::cout << std::endl << "-> ";

  int start_vertex, finish_vertex;
  std::string input;

  std::getline(std::cin, input);
  try {
    start_vertex = std::stoi(input);
  } catch (const std::invalid_argument&) {
    PrintError(dictionary_.GetMessage("enter_correct_integer"));
    return;
  }

  std::cout << "-> ";
  std::getline(std::cin, input);
  try {
    finish_vertex = std::stoi(input);
  } catch (const std::invalid_argument&) {
    PrintError(dictionary_.GetMessage("enter_correct_integer"));
    return;
  }

  try {
    auto result = graph_alg_.GetShortestPathBetweenVertices(
        *graph_, start_vertex, finish_vertex);
    if (result == -1) {
      PrintError(dictionary_.GetMessage("error_get_path"));
      return;
    }

    std::cout << std::endl
              << dictionary_.GetMessage("result_shortest_path") << std::endl;
    std::cout << result << std::endl;
  } catch (const std::exception& e) {
    PrintError(e.what());
  }
}

void Program::HandleShortestPathsBetweenAllVertices() noexcept {
  ClearConsole();
  std::cout << dictionary_.GetMessage("result_shortest_paths") << std::endl;

  auto result = graph_alg_.GetShortestPathsBetweenAllVertices(*graph_);

  std::cout << "Результат:\n";
  for (size_t i = 0; i < result.size(); ++i) {
    for (size_t j = 0; j < result[i].size(); ++j) {
      std::cout << result[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

void Program::HandleLeastSpanningTree() noexcept {
  ClearConsole();
  std::cout << dictionary_.GetMessage("result_mst") << std::endl;

  auto result = graph_alg_.GetLeastSpanningTree(*graph_);

  std::cout << "Результат:\n";
  for (size_t i = 0; i < result.size(); ++i) {
    for (size_t j = 0; j < result[i].size(); ++j) {
      std::cout << result[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

void Program::HandleSolveTravelingSalesmanProblem() noexcept {
  ClearConsole();
  std::cout << dictionary_.GetMessage("result_voyager_problem") << std::endl;

  auto res = graph_alg_.SolveTravelingSalesmanProblem(*graph_);

  std::cout << dictionary_.GetMessage("total_distance") << std::endl
            << res.distance << std::endl;

  for (int i = 0; i < int(res.vertices.size()); i++) {
    std::cout << res.vertices[i];
    if (i < int(res.vertices.size()) - 1) {
      std::cout << " -> ";
    }
  }
  std::cout << std::endl;
}

}  // namespace s21
