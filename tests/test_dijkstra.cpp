#include <gtest/gtest.h>

#include "dijkstra_cmd.hpp"
#include "graph.hpp"

class Dijkstra_test : public ::testing::Test {
    protected:
        Graph graph_;
        dijkstra_cmd dijkstra_;
};

TEST_F(Dijkstra_test, Common_graph) {
    graph_.add_vertex("A");
    graph_.add_vertex("B");
    graph_.add_vertex("C");
    graph_.add_vertex("D");
    graph_.add_vertex("E");

    graph_.add_edge(5, "A", "B");
    graph_.add_edge(3, "A", "C");
    graph_.add_edge(2, "B", "C");
    graph_.add_edge(4, "B", "D");
    graph_.add_edge(1, "C", "D");
    graph_.add_edge(6, "C", "E");
    graph_.add_edge(3, "D", "E");
    graph_.add_vertex("F");
    graph_.add_edge(100, "A", "F");
    graph_.add_edge(13, "B", "E");
    graph_.add_edge(4, "E", "F");

    auto res = dijkstra_.execute(graph_, {"A"});
    EXPECT_EQ(res, "C 3\nD 4\nB 5\nE 7\nF 11");

    graph_.delete_edge("E", "F");
    res = dijkstra_.execute(graph_, {"A"});
    EXPECT_EQ(res, "C 3\nD 4\nB 5\nE 7\nF 100");

    graph_.delete_vertex("E");
    res = dijkstra_.execute(graph_, {"A"});
    EXPECT_EQ(res, "C 3\nD 4\nB 5\nF 100");
}

TEST_F(Dijkstra_test, Alone_vertex) {
    graph_.add_vertex("A");
    graph_.add_vertex("B");
    graph_.add_vertex("C");
    graph_.add_vertex("D");
    graph_.add_edge(10, "A", "B");
    graph_.add_edge(10, "B", "C");
    graph_.add_edge(10, "C", "D");

    graph_.add_vertex("ALONE");
    auto res = dijkstra_.execute(graph_, {"A"});
    EXPECT_EQ(res, "B 10\nC 20\nD 30");

    res = dijkstra_.execute(graph_, {"ALONE"});
    EXPECT_TRUE(res.empty());
}

