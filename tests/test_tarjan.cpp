#include <gtest/gtest.h>

#include "graph.hpp"
#include "tarjan_cmd.hpp"

class tarjan_test : public ::testing::Test {
protected:
    graph graph_;
    tarjan_cmd tarjan_;
};

TEST_F(tarjan_test, Graph_1) {
    graph_.add_vertex("A");
    graph_.add_vertex("B");
    graph_.add_vertex("C");
    graph_.add_vertex("D");
    graph_.add_vertex("E");
    graph_.add_vertex("F");
    graph_.add_vertex("G");
    graph_.add_vertex("H");
    graph_.add_vertex("I");
    graph_.add_edge(1, "A", "B");
    graph_.add_edge(1, "B", "E");
    graph_.add_edge(1, "B", "C");
    graph_.add_edge(1, "C", "C");
    graph_.add_edge(1, "C", "F");
    graph_.add_edge(1, "D", "B");
    graph_.add_edge(1, "D", "G");
    graph_.add_edge(1, "E", "D");
    graph_.add_edge(1, "E", "A");
    graph_.add_edge(1, "F", "H");
    graph_.add_edge(1, "G", "E");
    graph_.add_edge(1, "H", "I");
    graph_.add_edge(1, "I", "F");
    auto res = tarjan_.execute(graph_, {"A"});
    EXPECT_TRUE(res == "F H I\nA B D E G" || res == "A B D E G\nF H I");
}


TEST_F(tarjan_test, Simple_graph_2) {
    graph_.add_vertex("A1");
    graph_.add_vertex("A2");
    graph_.add_vertex("A3");
    graph_.add_vertex("A4");
    graph_.add_vertex("B1");
    graph_.add_vertex("B2");
    graph_.add_vertex("C1");
    graph_.add_vertex("C2");
    graph_.add_vertex("C3");

    graph_.add_edge(1, "A1", "A2");
    graph_.add_edge(1, "A2", "A3");
    graph_.add_edge(1, "A3", "A4");
    graph_.add_edge(1, "A4", "A1");
    graph_.add_edge(1, "A2", "B1");
    graph_.add_edge(1, "B1", "B2");
    graph_.add_edge(1, "B2", "C2");
    graph_.add_edge(1, "C1", "C2");
    graph_.add_edge(1, "C2", "C3");
    graph_.add_edge(1, "C3", "C1");

    auto res = tarjan_.execute(graph_, {"A1"});
    EXPECT_TRUE(res == "C1 C2 C3\nA1 A2 A3 A4" || res == "A1 A2 A3 A4\nC1 C2 C3");
}
