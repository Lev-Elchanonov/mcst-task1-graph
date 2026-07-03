#pragma once
#include <string>
#include <unordered_map>
#include <vector>

#include "graph.hpp"

class Maxflow {
    private:
        struct M_edge {
            std::string to_;
            size_t capacity_;
            size_t flow_;
            size_t reverse_index_;
        };

        std::string dest_vertex_;
        std::unordered_map<std::string, std::vector<M_edge>> graph_;
        std::unordered_map<std::string, bool> visited_;

        void add_edge(const std::string& u, const std::string& v, size_t cap) {
            M_edge forward{v, cap, 0, graph_[v].size()};
            M_edge backward{u, 0, 0, graph_[u].size()};
            graph_[u].push_back(forward);
            graph_[v].push_back(backward);
        }

        int dfs_maxflow(const std::string& current_v, int min_capacity) {
            if (current_v == dest_vertex_) {
                return min_capacity;
            }
            visited_[current_v] = true;
            for (auto& edge : graph_[current_v]) {
                std::string to_vertex = edge.to_;
                int remaining = edge.capacity_ - edge.flow_;

                if (!visited_[to_vertex] && remaining > 0) {
                    int delta = dfs_maxflow(to_vertex, std::min(min_capacity, remaining));
                    if (delta > 0) {
                        edge.flow_ += delta;
                        graph_[to_vertex][edge.reverse_index_].flow_ -= delta;
                        return delta;
                    }
                }
            }
            return 0;
        }

    public:
        explicit Maxflow(Graph& graph, const std::string& dest_vertex) {
            dest_vertex_ = dest_vertex;
            auto vertices = graph.get_vertices();
            for (auto& [id, vertex] : vertices) {
                for (auto& [id, edge] : vertex.get_outgoing_edges()) {
                    add_edge(edge.get_source().get_id(), edge.get_dest().get_id(), edge.get_weight());
                }
            }
        }
        size_t find_maxflow(const std::string& start) {
            size_t total_flow = 0;

            while (true) {
                for (const auto& [id, _] : graph_) {
                    visited_[id] = false;
                }

                size_t delta = dfs_maxflow(start, INT_MAX);
                if (delta == 0) {
                    break;
                }
                total_flow += delta;
            }
            return total_flow;
        }
};
