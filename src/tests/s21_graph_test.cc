#include <gtest/gtest.h>

#include "../s21_graph.h"

std::string ReadFileToString(const std::string& filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    throw std::runtime_error("Could not open file");
  }
  std::stringstream buffer;
  buffer << file.rdbuf();
  file.close();
  return buffer.str();
}

TEST(GraphTest, LoadGraphFromFile1) {
  s21::Graph graph;
  graph.LoadGraphFromFile("graphs/graph_2.txt");

  s21::Matrix expected_result = {{0, 8, 5}, {3, 0, 594}, {594, 2, 0}};

  ASSERT_EQ(graph.GetSize(), 3);
  ASSERT_EQ(graph.GetMatrix(), expected_result);
}

TEST(GraphTest, LoadGraphFromFile2) {
  s21::Graph graph;
  graph.LoadGraphFromFile("graphs/graph_3.txt");

  s21::Matrix expected_result = {{0, 1, 0}, {2, 0, 0}, {0, 5, 0}};

  ASSERT_EQ(graph.GetSize(), 3);
  ASSERT_EQ(graph.GetMatrix(), expected_result);
}

TEST(GraphTest, LoadGraphFromFile3) {
  s21::Graph graph;
  graph.LoadGraphFromFile("graphs/graph_4.txt");

  s21::Matrix expected_result = {{0, 2, 3, 4, 5},
                                 {1, 0, 3, 4, 5},
                                 {1, 2, 0, 4, 5},
                                 {1, 2, 3, 0, 5},
                                 {1, 2, 3, 4, 0}};

  ASSERT_EQ(graph.GetSize(), 5);
  ASSERT_EQ(graph.GetMatrix(), expected_result);
}

TEST(GraphTest, LoadGraphFromFileError1) {
  s21::Graph graph;
  ASSERT_ANY_THROW(graph.LoadGraphFromFile("graphs/errors/graph_1.txt"));
}

TEST(GraphTest, LoadGraphFromFileError2) {
  s21::Graph graph;
  ASSERT_ANY_THROW(graph.LoadGraphFromFile("graphs/errors/graph_2.txt"));
}

TEST(GraphTest, LoadGraphFromFileError3) {
  s21::Graph graph;
  ASSERT_ANY_THROW(graph.LoadGraphFromFile("graphs/errors/graph_3.txt"));
}

TEST(GraphTest, LoadGraphFromFileError4) {
  s21::Graph graph;
  ASSERT_ANY_THROW(graph.LoadGraphFromFile("graphs/errors/graph_4.txt"));
}

TEST(GraphTest, LoadGraphFromFileError5) {
  s21::Graph graph;
  ASSERT_ANY_THROW(
      graph.LoadGraphFromFile("graphs/errors/graph_not_connected.txt"));
}

TEST(GraphTest, ExportGraphToDot1) {
  s21::Graph graph;
  graph.LoadGraphFromFile("graphs/graph_1.txt");

  std::string dot_file = "test_graph_1.dot";
  graph.ExportGraphToDot(dot_file);

  std::string expected_content =
      "graph S21 {\n"
      "    1;\n"
      "    2;\n"
      "    3;\n"
      "    4;\n"
      "    5;\n"
      "    6;\n"
      "    7;\n"
      "    8;\n"
      "    9;\n"
      "    10;\n"
      "    11;\n"
      "    1 -- 2;\n"
      "    1 -- 3;\n"
      "    1 -- 4;\n"
      "    1 -- 5;\n"
      "    1 -- 6;\n"
      "    1 -- 7;\n"
      "    1 -- 8;\n"
      "    1 -- 9;\n"
      "    1 -- 10;\n"
      "    1 -- 11;\n"
      "    2 -- 3;\n"
      "    2 -- 4;\n"
      "    2 -- 5;\n"
      "    2 -- 6;\n"
      "    2 -- 7;\n"
      "    2 -- 8;\n"
      "    2 -- 9;\n"
      "    2 -- 10;\n"
      "    2 -- 11;\n"
      "    3 -- 4;\n"
      "    3 -- 5;\n"
      "    3 -- 6;\n"
      "    3 -- 7;\n"
      "    3 -- 8;\n"
      "    3 -- 9;\n"
      "    3 -- 10;\n"
      "    3 -- 11;\n"
      "    4 -- 5;\n"
      "    4 -- 6;\n"
      "    4 -- 7;\n"
      "    4 -- 8;\n"
      "    4 -- 9;\n"
      "    4 -- 10;\n"
      "    4 -- 11;\n"
      "    5 -- 6;\n"
      "    5 -- 7;\n"
      "    5 -- 8;\n"
      "    5 -- 9;\n"
      "    5 -- 10;\n"
      "    5 -- 11;\n"
      "    6 -- 7;\n"
      "    6 -- 8;\n"
      "    6 -- 9;\n"
      "    6 -- 10;\n"
      "    6 -- 11;\n"
      "    7 -- 8;\n"
      "    7 -- 9;\n"
      "    7 -- 10;\n"
      "    7 -- 11;\n"
      "    8 -- 9;\n"
      "    8 -- 10;\n"
      "    8 -- 11;\n"
      "    9 -- 10;\n"
      "    9 -- 11;\n"
      "    10 -- 11;\n"
      "}\n";

  std::string actual_content = ReadFileToString(dot_file);
  ASSERT_EQ(actual_content, expected_content);
}

TEST(GraphTest, ExportGraphToDot2) {
  s21::Graph graph;
  graph.LoadGraphFromFile("graphs/graph_2.txt");

  std::string dot_file = "test_graph_2.dot";
  graph.ExportGraphToDot(dot_file);

  std::string expected_content =
      "digraph S21 {\n"
      "    1;\n"
      "    2;\n"
      "    3;\n"
      "    1 -> 2;\n"
      "    1 -> 3;\n"
      "    2 -> 1;\n"
      "    2 -> 3;\n"
      "    3 -> 1;\n"
      "    3 -> 2;\n"
      "}\n";

  std::string actual_content = ReadFileToString(dot_file);
  ASSERT_EQ(actual_content, expected_content);
}

TEST(GraphTest, ExportGraphToDot3) {
  s21::Graph graph;
  graph.LoadGraphFromFile("graphs/graph_3.txt");

  std::string dot_file = "test_graph_3.dot";
  graph.ExportGraphToDot(dot_file);

  std::string expected_content =
      "digraph S21 {\n"
      "    1;\n"
      "    2;\n"
      "    3;\n"
      "    1 -> 2;\n"
      "    2 -> 1;\n"
      "    3 -> 2;\n"
      "}\n";

  std::string actual_content = ReadFileToString(dot_file);
  ASSERT_EQ(actual_content, expected_content);
}

TEST(GraphTest, ExportGraphToDotError1) {
  s21::Graph graph;
  ASSERT_ANY_THROW(graph.ExportGraphToDot("fhj;DFKL;HASDFHKL;ADSFJKL"));
}