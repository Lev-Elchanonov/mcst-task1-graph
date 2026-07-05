#include <gtest/gtest.h>

#include "dijkstra_cmd.hpp"
#include "graph.hpp"

class Graph_test : public ::testing::Test {
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

TEST_F(Graph_test, Add_vertex) {
    graph_.add_vertex("PP");
    EXPECT_NO_THROW(graph_.get_vertex("PP"));
    EXPECT_EQ(graph_.get_vertex("PP").get_id(), "PP");
    EXPECT_EQ(graph_.get_vertex("PP").get_outgoing_edges().size(), 0);



}

TEST_F(Graph_test, Remove_vertex) {
    EXPECT_NO_THROW(graph_.get_vertex("D"));
    EXPECT_NO_THROW(graph_.get_vertex("B").get_outgoing_edge("D"));
    EXPECT_NO_THROW(graph_.get_vertex("C").get_outgoing_edge("D"));

    graph_.delete_vertex("D");

    EXPECT_THROW(graph_.get_vertex("B").get_outgoing_edge("D"),std::out_of_range);
    EXPECT_THROW(graph_.get_vertex("C").get_outgoing_edge("D"),std::out_of_range);
    EXPECT_THROW(graph_.get_vertex("D"), std::invalid_argument);

    auto error_msg = graph_.delete_vertex("NON_EXIST");
    EXPECT_EQ(error_msg, "Unknown node NON_EXIST");
}

TEST_F(Graph_test, Clear) {
    EXPECT_NE(graph_.get_vertices().size(), 0);
    graph_.clear();
    EXPECT_EQ(graph_.get_vertices().size(), 0);
}

TEST_F(Graph_test, Add_edge) {
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

TEST_F(Graph_test, Remove_edge) {
    EXPECT_NO_THROW(graph_.get_edge("A", "B"));
    graph_.delete_edge("A", "B");
    EXPECT_THROW(graph_.get_edge("A", "B"), std::out_of_range);

    graph_.add_edge(1000, "A", "A");
    EXPECT_NO_THROW(graph_.get_edge("A", "A"));
    graph_.delete_edge("A", "A");
    EXPECT_THROW(graph_.get_edge("A", "A"), std::out_of_range);

    EXPECT_NO_THROW(graph_.delete_edge("NON_EXIST_1", "NON_EXIST_2"));
}

TEST_F(Graph_test, Dijkstra) {
    graph_.add_vertex("F");
    graph_.add_edge(100, "A", "F");
    graph_.add_edge(13, "B", "E");
    graph_.add_edge(4, "E", "F");

    std::unique_ptr<dijkstra_cmd> dijkstra = std::make_unique<dijkstra_cmd>();
    auto res = dijkstra->execute(graph_, {"A"});
    EXPECT_EQ(res, "C 3\nD 4\nB 5\nE 7\nF 11");

    graph_.delete_edge("E", "F");
    res = dijkstra->execute(graph_, {"A"});
    EXPECT_EQ(res, "C 3\nD 4\nB 5\nE 7\nF 100");

    graph_.delete_vertex("E");
    res = dijkstra->execute(graph_, {"A"});
    EXPECT_EQ(res, "C 3\nD 4\nB 5\nF 100");


    graph_.clear();
    graph_.add_vertex("A");
    graph_.add_vertex("B");
    graph_.add_vertex("C");
    graph_.add_vertex("D");
    graph_.add_edge(10, "A", "B");
    graph_.add_edge(10, "B", "C");
    graph_.add_edge(10, "C", "D");

    graph_.add_vertex("ALONE");
    res = dijkstra->execute(graph_, {"A"});
    EXPECT_EQ(res, "B 10\nC 20\nD 30");

    res = dijkstra->execute(graph_, {"ALONE"});
    EXPECT_TRUE(res.empty());
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}