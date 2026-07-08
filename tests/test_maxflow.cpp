#include <gtest/gtest.h>

#include "graph.hpp"
#include "maxflow_cmd.hpp"

class maxflow_test : public ::testing::Test {
protected:
    graph graph_;
    maxflow_cmd maxflow_;
};

TEST_F(maxflow_test, Simple_graph_1) {
    graph_.add_vertex("A");
    graph_.add_vertex("B");
    graph_.add_vertex("C");
    graph_.add_vertex("D");
    graph_.add_vertex("E");
    graph_.add_vertex("F");

    graph_.add_edge(7, "A", "B");
    graph_.add_edge(4, "A", "C");
    graph_.add_edge(4, "B", "C");
    graph_.add_edge(2, "B", "E");
    graph_.add_edge(8, "C", "E");
    graph_.add_edge(4, "C", "D");
    graph_.add_edge(4, "E", "D");
    graph_.add_edge(5, "E", "F");
    graph_.add_edge(12, "D", "F");

    auto res = maxflow_.execute(graph_, {"A", "F"});
    EXPECT_EQ(res, "10");
}


TEST_F(maxflow_test, Simple_graph_2) {
    graph_.add_vertex("A");
    graph_.add_vertex("B");
    graph_.add_vertex("C");
    graph_.add_vertex("D");
    graph_.add_vertex("E");

    graph_.add_edge(30, "A", "B");
    graph_.add_edge(40, "A", "C");
    graph_.add_edge(20, "A", "D");
    graph_.add_edge(50, "B", "C");
    graph_.add_edge(40, "B", "E");
    graph_.add_edge(20, "C", "D");
    graph_.add_edge(30, "C", "E");
    graph_.add_edge(30, "D", "E");
    auto res = maxflow_.execute(graph_, {"A", "E"});
    EXPECT_EQ(res, "90");
}

TEST_F(maxflow_test, Large_graph_1) {
    graph_.add_vertex("A1");
    graph_.add_vertex("A2");
    graph_.add_vertex("A3");
    graph_.add_vertex("A4");
    graph_.add_vertex("A5");
    graph_.add_vertex("A6");
    graph_.add_vertex("A7");
    graph_.add_vertex("A8");

    graph_.add_edge(95, "A1", "A3");
    graph_.add_edge(32, "A1", "A2");
    graph_.add_edge(75, "A1", "A4");
    graph_.add_edge(57, "A1", "A5");
    graph_.add_edge(23, "A2", "A5");
    graph_.add_edge(16, "A2", "A8");
    graph_.add_edge(5, "A2", "A3");
    graph_.add_edge(18, "A3", "A4");
    graph_.add_edge(6, "A3", "A6");
    graph_.add_edge(9, "A4", "A6");
    graph_.add_edge(24, "A4", "A5");
    graph_.add_edge(20, "A5", "A7");
    graph_.add_edge(94, "A5", "A8");
    graph_.add_edge(11, "A6", "A5");
    graph_.add_edge(7, "A6", "A7");
    graph_.add_edge(81, "A7", "A8");
    auto res = maxflow_.execute(graph_, {"A1", "A8"});
    EXPECT_EQ(res, "128");
}



TEST_F(maxflow_test, Large_graph_2) {
    graph_.add_vertex("A1");
    graph_.add_vertex("A2");
    graph_.add_vertex("A3");
    graph_.add_vertex("A4");
    graph_.add_vertex("A5");
    graph_.add_vertex("A6");
    graph_.add_vertex("A7");
    graph_.add_vertex("A8");

    graph_.add_edge(5, "A1", "A2");
    graph_.add_edge(40, "A1", "A3");
    graph_.add_edge(5, "A1", "A4");
    graph_.add_edge(5, "A2", "A5");
    graph_.add_edge(30, "A3", "A2");
    graph_.add_edge(30, "A3", "A4");
    graph_.add_edge(20, "A3", "A6");
    graph_.add_edge(5, "A4", "A7");
    graph_.add_edge(15, "A5", "A8");
    graph_.add_edge(5, "A6", "A5");
    graph_.add_edge(5, "A6", "A7");
    graph_.add_edge(5, "A6", "A8");
    graph_.add_edge(15, "A7", "A8");
    auto res = maxflow_.execute(graph_, {"A1", "A8"});
    EXPECT_EQ(res, "25");
}

