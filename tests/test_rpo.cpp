#include <gtest/gtest.h>

#include "graph.hpp"
#include "rpo_cmd.hpp"

class Rpo_test : public ::testing::Test {
protected:
    Graph graph_;
    rpo_cmd rpo_;
};

TEST_F(Rpo_test, Simple_no_loops) {
    graph_.add_vertex("A");
    graph_.add_vertex("B");
    graph_.add_vertex("C");
    graph_.add_edge(1, "A", "B");
    graph_.add_edge(1, "B", "C");
    auto res = rpo_.execute(graph_, {"A"});
    EXPECT_EQ(res, "A B C");
}


TEST_F(Rpo_test, Medium_no_loops) {
    graph_.add_vertex("A");
    graph_.add_vertex("B");
    graph_.add_vertex("C");
    graph_.add_vertex("D");
    graph_.add_edge(1, "A", "B");
    graph_.add_edge(1, "A", "C");
    graph_.add_edge(1, "B", "D");
    graph_.add_edge(1, "C", "D");
    auto res = rpo_.execute(graph_, {"A"});
    EXPECT_TRUE(res == "A B C D" || res == "A C B D");
}

TEST_F(Rpo_test, Simple_loop) {
    graph_.add_vertex("A");
    graph_.add_vertex("B");
    graph_.add_vertex("C");
    graph_.add_edge(1, "A", "B");
    graph_.add_edge(1, "B", "C");
    graph_.add_edge(1, "C", "A");
    auto res = rpo_.execute(graph_, {"A"});
    EXPECT_EQ(res, "Found loop C->A\nA B C");
}


TEST_F(Rpo_test, Multiple_loops) {
    graph_.add_vertex("A");
    graph_.add_vertex("B");
    graph_.add_vertex("C");
    graph_.add_vertex("D");
    graph_.add_edge(1, "A", "B");
    graph_.add_edge(1, "B", "C");
    graph_.add_edge(1, "C", "A");
    graph_.add_edge(1, "C", "D");
    graph_.add_edge(1, "D", "B");
    auto res = rpo_.execute(graph_, {"A"});
    EXPECT_TRUE(res == "Found loop C->A\nFound loop D->B\nA B C D" || res == "Found loop D->B\nFound loop C->A\nA B C D");
}

TEST_F(Rpo_test, Alone_start_vertex) {
    graph_.add_vertex("A");
    graph_.add_vertex("B");
    graph_.add_vertex("C");
    graph_.add_edge(1, "B", "C");
    auto res = rpo_.execute(graph_, {"A"});
    EXPECT_EQ(res, "A");
}
TEST_F(Rpo_test, Unknown_start) {
    graph_.add_vertex("A");
    auto res = rpo_.execute(graph_, {"NONE"});
    EXPECT_EQ(res, "Unknown node NONE");
}