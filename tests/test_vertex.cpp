#include <gtest/gtest.h>

#include "graph.hpp"

class Vertex_test : public ::testing::Test {
    protected:
        Graph graph_;
        void SetUp() override {
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
        }
};


TEST_F(Vertex_test, Add_vertex) {
    graph_.add_vertex("PP");
    EXPECT_NO_THROW(graph_.get_vertex("PP"));
    EXPECT_EQ(graph_.get_vertex("PP").get_id(), "PP");
    EXPECT_EQ(graph_.get_vertex("PP").get_outgoing_edges().size(), 0);
}

TEST_F(Vertex_test, Remove_vertex) {
    EXPECT_NO_THROW(graph_.get_vertex("D"));
    EXPECT_NO_THROW(graph_.get_vertex("B").get_outgoing_edge("D"));
    EXPECT_NO_THROW(graph_.get_vertex("C").get_outgoing_edge("D"));
    EXPECT_EQ(graph_.delete_vertex("NONE"), "Unknown node NONE");
    graph_.delete_vertex("D");

    EXPECT_THROW(graph_.get_vertex("B").get_outgoing_edge("D"),std::out_of_range);
    EXPECT_THROW(graph_.get_vertex("C").get_outgoing_edge("D"),std::out_of_range);
    EXPECT_THROW(graph_.get_vertex("D"), std::invalid_argument);

    auto error_msg = graph_.delete_vertex("NON_EXIST");
    EXPECT_EQ(error_msg, "Unknown node NON_EXIST");
}
