#pragma once
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "graph.hpp"

class Tarjan {
    private:
        std::unordered_map<std::string, size_t> indexes_;
        std::unordered_map<std::string, size_t> lowlinks_;
        std::unordered_map<std::string, bool> in_stack_;
        std::stack<std::string> vertex_stack_;
        Graph& graph_;

        std::vector<std::vector<std::string>> scc_;         //компоненты сильной связности
    public:
        explicit Tarjan(Graph& graph) : graph_(graph) {}

        void strong_connect(const std::string& vertex_id) {
            indexes_[vertex_id] = indexes_.size();
            lowlinks_[vertex_id] = indexes_.size();

            vertex_stack_.push(vertex_id);
            in_stack_[vertex_id] = true;

            auto vertex = graph_.get_vertex(vertex_id);
            for (auto& [neighbour, _] : vertex.get_outgoing_edges()) {
                if (indexes_[neighbour] == 0) {
                    strong_connect(neighbour);
                    lowlinks_[vertex_id] = std::min(lowlinks_[vertex_id], lowlinks_[neighbour]);
                }
                else if (in_stack_[neighbour]) {
                    lowlinks_[vertex_id] = std::min(lowlinks_[vertex_id], indexes_[neighbour]);
                }
            }
            if (lowlinks_[vertex_id] == indexes_[vertex_id]) {
                std::vector<std::string> new_scc;
                std::string other_neighbour;
                while (vertex_id != other_neighbour) {
                    other_neighbour = vertex_stack_.top();
                    vertex_stack_.pop();
                    new_scc.push_back(other_neighbour);
                    in_stack_[other_neighbour] = false;
                }
                if (new_scc.size() > 1)
                    scc_.push_back(new_scc);
            }
        }
        std::vector<std::vector<std::string>> get_scc() const noexcept { return scc_; }
};
