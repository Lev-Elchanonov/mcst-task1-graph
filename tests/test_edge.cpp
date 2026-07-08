#include <gtest/gtest.h>

#include "graph.hpp"

class edge_test : public ::testing::Test {
protected:
    graph graph_;
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


TEST_F(edge_test, Add_edge) {
    graph_.add_vertex("T1");
    graph_.add_vertex("T2");
    EXPECT_THROW(graph_.get_edge("T1", "T2"), std::out_of_range);
    EXPECT_NO_THROW(graph_.get_edge("A", "B"));
    EXPECT_THROW(graph_.get_edge("A", "T1"), std::out_of_range);

    graph_.add_edge(111, "T1", "T2");
    EXPECT_NO_THROW(graph_.get_edge("T1", "T2"));
    auto current_edge = graph_.get_edge("T1", "T2");
    EXPECT_EQ(current_edge.get_dest().get_id(), "T2");
    EXPECT_EQ(current_edge.get_source().get_id(), "T1");
    EXPECT_EQ(current_edge.get_weight(), 111);

    graph_.add_edge(999, "T2", "T1");
    EXPECT_THROW(graph_.get_edge("T2", "T1"), std::out_of_range);

    EXPECT_NO_THROW(graph_.add_edge(-1, "A", "E"));
    EXPECT_NO_THROW(graph_.add_edge(0, "A", "D"));

    auto error_msg = graph_.add_edge(100, "A", "NON_EXIST");
    EXPECT_EQ(error_msg, "Unknown node NON_EXIST");

    error_msg = graph_.add_edge(100, "NON_EXIST_1", "NON_EXIST_2");
    EXPECT_EQ(error_msg, "Unknown nodes NON_EXIST_1 NON_EXIST_2");
}

TEST_F(edge_test, Remove_edge) {
    EXPECT_NO_THROW(graph_.get_edge("A", "B"));
    graph_.delete_edge("A", "B");
    EXPECT_THROW(graph_.get_edge("A", "B"), std::out_of_range);

    graph_.add_edge(1000, "A", "A");
    EXPECT_NO_THROW(graph_.get_edge("A", "A"));
    graph_.delete_edge("A", "A");
    EXPECT_THROW(graph_.get_edge("A", "A"), std::out_of_range);

    EXPECT_NO_THROW(graph_.delete_edge("NON_EXIST_1", "NON_EXIST_2"));
}