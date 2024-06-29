#include <gtest/gtest.h>

#include "../s21_graph.h"
#include "../s21_graph_algorithms.h"

/*

BREADTH FIRST SEARCH

*/

TEST(AlgorithmsTest, BreadthFirstSearch1) {
  s21::Graph graph;
  graph.LoadGraphFromFile("graphs/graph_1.txt");
  s21::GraphAlgorithms algorithms;

  std::vector<int> result = algorithms.BreadthFirstSearch(graph, 1);
  std::vector<int> expected_result = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

  ASSERT_EQ(result, expected_result);
}

TEST(AlgorithmsTest, BreadthFirstSearchGraph2) {
  s21::Graph graph;
  graph.LoadGraphFromFile("graphs/graph_2.txt");
  s21::GraphAlgorithms algorithms;

  std::vector<int> result = algorithms.BreadthFirstSearch(graph, 1);
  std::vector<int> expected_result = {1, 2, 3};

  ASSERT_EQ(result, expected_result);
}

TEST(AlgorithmsTest, BreadthFirstSearchGraphError1) {
  s21::Graph graph;
  s21::GraphAlgorithms algorithms;

  ASSERT_ANY_THROW(algorithms.BreadthFirstSearch(graph, 1));
}

TEST(AlgorithmsTest, BreadthFirstSearchGraphError2) {
  s21::Graph graph;
  graph.LoadGraphFromFile("graphs/graph_2.txt");
  s21::GraphAlgorithms algorithms;

  ASSERT_ANY_THROW(algorithms.BreadthFirstSearch(graph, 5));
}

TEST(AlgorithmsTest, BreadthFirstSearchGraphError3) {
  s21::Graph graph;
  graph.LoadGraphFromFile("graphs/graph_2.txt");
  s21::GraphAlgorithms algorithms;

  ASSERT_ANY_THROW(algorithms.BreadthFirstSearch(graph, -205));
}

/*

DEPTH FIRST SEARCH

*/

TEST(AlgorithmsTest, DepthFirstSearch1) {
  s21::Graph graph;
  graph.LoadGraphFromFile("graphs/graph_5.txt");
  s21::GraphAlgorithms algorithms;

  std::vector<int> result = algorithms.DepthFirstSearch(graph, 1);
  std::vector<int> expected_result = {0, 1, 2, 3};

  ASSERT_EQ(result, expected_result);
}

TEST(AlgorithmsTest, DepthFirstSearch2) {
  s21::Graph graph;
  graph.LoadGraphFromFile("graphs/graph_2.txt");
  s21::GraphAlgorithms algorithms;

  std::vector<int> result = algorithms.DepthFirstSearch(graph, 2);
  std::vector<int> expected_result = {1, 0, 2};

  ASSERT_EQ(result, expected_result);
}

TEST(AlgorithmsTest, DepthFirstSearchGraphError1) {
  s21::Graph graph;
  s21::GraphAlgorithms algorithms;

  ASSERT_ANY_THROW(algorithms.BreadthFirstSearch(graph, 1));
}

TEST(AlgorithmsTest, DepthFirstSearchGraphError2) {
  s21::Graph graph;
  graph.LoadGraphFromFile("graphs/graph_5.txt");
  s21::GraphAlgorithms algorithms;

  ASSERT_ANY_THROW(algorithms.BreadthFirstSearch(graph, 10));
}

TEST(AlgorithmsTest, DepthFirstSearchGraphError3) {
  s21::Graph graph;
  graph.LoadGraphFromFile("graphs/graph_2.txt");
  s21::GraphAlgorithms algorithms;

  ASSERT_ANY_THROW(algorithms.BreadthFirstSearch(graph, -205));
}

/*

GET SHORTEST PATHS BETWEEN VERTICES

*/

TEST(AlgorithmsTest, GetShortestPathBetweenVertices1) {
  s21::Graph graph;
  graph.LoadGraphFromFile("graphs/graph_2.txt");
  s21::GraphAlgorithms algorithms;

  int result = algorithms.GetShortestPathBetweenVertices(graph, 3, 1);
  int expected_result = 5;

  ASSERT_EQ(result, expected_result);
}

TEST(AlgorithmsTest, GetShortestPathBetweenVertices2) {
  s21::Graph graph;
  graph.LoadGraphFromFile("graphs/graph_5.txt");
  s21::GraphAlgorithms algorithms;

  int result = algorithms.GetShortestPathBetweenVertices(graph, 1, 2);
  int expected_result = 2;

  ASSERT_EQ(result, expected_result);
}

TEST(AlgorithmsTest, GetShortestPathBetweenVertices3) {
  s21::Graph graph;
  graph.LoadGraphFromFile("graphs/graph_4.txt");
  s21::GraphAlgorithms algorithms;

  int result = algorithms.GetShortestPathBetweenVertices(graph, 1, 4);
  int expected_result = 4;

  ASSERT_EQ(result, expected_result);
}

TEST(AlgorithmsTest, GetShortestPathBetweenVerticesError1) {
  s21::Graph graph;
  graph.LoadGraphFromFile("graphs/graph_2.txt");
  s21::GraphAlgorithms algorithms;

  ASSERT_ANY_THROW(algorithms.GetShortestPathBetweenVertices(graph, 100, -1));
}

TEST(AlgorithmsTest, GetShortestPathBetweenVerticesError2) {
  s21::Graph graph;
  s21::GraphAlgorithms algorithms;

  ASSERT_ANY_THROW(algorithms.GetShortestPathBetweenVertices(graph, 0, 0));
}

TEST(AlgorithmsTest, GetShortestPathBetweenVerticesError3) {
  s21::Graph graph;
  s21::GraphAlgorithms algorithms;

  ASSERT_ANY_THROW(algorithms.GetShortestPathBetweenVertices(graph, 2, 1));
}

/*

GET SHORTEST PATHS BETWEEN ALL VERTICES

*/

TEST(AlgorithmsTest, GetShortestPathsBetweenAllVertices1) {
  s21::Graph graph;
  graph.LoadGraphFromFile("graphs/graph_2.txt");
  s21::GraphAlgorithms algorithms;

  s21::Matrix result = algorithms.GetShortestPathsBetweenAllVertices(graph);
  s21::Matrix expected_result = {{0, 7, 5}, {3, 0, 8}, {5, 2, 0}};

  ASSERT_EQ(result, expected_result);
}

TEST(AlgorithmsTest, GetShortestPathsBetweenAllVerticesGraph2) {
  s21::Graph graph;
  graph.LoadGraphFromFile("graphs/graph_1.txt");
  s21::GraphAlgorithms algorithms;

  s21::Matrix result = algorithms.GetShortestPathsBetweenAllVertices(graph);
  s21::Matrix expected_result = {{0, 29, 20, 20, 16, 31, 100, 12, 4, 31, 18},
                                 {29, 0, 15, 29, 28, 40, 72, 21, 29, 41, 12},
                                 {20, 15, 0, 15, 14, 25, 81, 9, 23, 27, 13},
                                 {20, 29, 15, 0, 4, 12, 92, 12, 24, 13, 25},
                                 {16, 28, 14, 4, 0, 16, 94, 9, 20, 16, 22},
                                 {31, 40, 25, 12, 16, 0, 95, 24, 35, 3, 37},
                                 {100, 72, 81, 92, 94, 95, 0, 90, 101, 98, 84},
                                 {12, 21, 9, 12, 9, 24, 90, 0, 15, 25, 13},
                                 {4, 29, 23, 24, 20, 35, 101, 15, 0, 35, 18},
                                 {31, 41, 27, 13, 16, 3, 98, 25, 35, 0, 38},
                                 {18, 12, 13, 25, 22, 37, 84, 13, 18, 38, 0}};

  ASSERT_EQ(result, expected_result);
}

TEST(AlgorithmsTest, GetShortestPathsBetweenAllVerticesGraphError1) {
  s21::Graph graph;
  s21::GraphAlgorithms algorithms;

  ASSERT_ANY_THROW(algorithms.GetShortestPathsBetweenAllVertices(graph));
}

/*

GET LEAST SPANNING TREE

*/

TEST(AlgorithmsTest, GetLeastSpanningTreeGraph1) {
  s21::Graph graph;
  graph.LoadGraphFromFile("graphs/graph_5.txt");
  s21::GraphAlgorithms algorithms;

  s21::Matrix result = algorithms.GetLeastSpanningTree(graph);
  s21::Matrix expected_result = {
      {0, 2, 0, 5}, {2, 0, 0, 0}, {0, 0, 0, 7}, {5, 0, 7, 0}};

  ASSERT_EQ(result, expected_result);
}

TEST(AlgorithmsTest, GetLeastSpanningTreeGraph2) {
  s21::Graph graph;
  graph.LoadGraphFromFile("graphs/graph_3.txt");
  s21::GraphAlgorithms algorithms;

  s21::Matrix result = algorithms.GetLeastSpanningTree(graph);
  s21::Matrix expected_result = {{0, 1, 0}, {1, 0, 5}, {0, 5, 0}};

  ASSERT_EQ(result, expected_result);
}

TEST(AlgorithmsTest, GetLeastSpanningTreeGraphError1) {
  s21::Graph graph;
  s21::GraphAlgorithms algorithms;

  ASSERT_ANY_THROW(algorithms.GetLeastSpanningTree(graph));
}

/*

SOLVE TRAVELING SALESMAN PROBLEM

*/

TEST(AlgorithmsTest, SolveTravelingSalesmanProblem1) {
  s21::Graph graph;
  graph.LoadGraphFromFile("graphs/graph_7.txt");
  s21::GraphAlgorithms algorithms;

  auto result = algorithms.SolveTravelingSalesmanProblem(graph);
  std::vector<int> vertices_result = {1, 5, 2, 4, 3, 1};
  int distance_result = 15;

  ASSERT_EQ(result.vertices, vertices_result);
  ASSERT_EQ(result.distance, distance_result);
}

TEST(AlgorithmsTest, SolveTravelingSalesmanProblem2) {
  s21::Graph graph;
  graph.LoadGraphFromFile("graphs/graph_6.txt");
  s21::GraphAlgorithms algorithms;

  auto result = algorithms.SolveTravelingSalesmanProblem(graph);
  std::vector<int> vertices_result = {1, 3, 2, 4, 5, 1};
  int distance_result = 14;

  ASSERT_EQ(result.vertices, vertices_result);
  ASSERT_EQ(result.distance, distance_result);
}

TEST(AlgorithmsTest, SolveTravelingSalesmanProblemError1) {
  s21::Graph graph;
  s21::GraphAlgorithms algorithms;

  ASSERT_ANY_THROW(algorithms.SolveTravelingSalesmanProblem(graph));
}