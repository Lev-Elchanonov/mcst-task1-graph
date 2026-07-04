#pragma once
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "graph.hpp"

class Tarjan {
    private:
        std::unordered_map<std::string, size_t> indexes_;   // для отметки на каком шаге dfs были пройдены вершины
        std::unordered_map<std::string, size_t> lowlinks_;  // для определения минимального index до которого можно добраться из вершины v
        std::unordered_map<std::string, bool> in_stack_;    // для определения есть ли вершина в стеке или нет
        std::stack<std::string> vertex_stack_;              // стек вершин
        Graph& graph_;
        size_t count_ = 0;

        std::vector<std::vector<std::string>> scc_;         // компоненты сильной связности
    public:
        explicit Tarjan(Graph& graph) : graph_(graph) {}

        void strong_connect(const std::string& vertex_id) {
            indexes_[vertex_id] = count_;
            lowlinks_[vertex_id] = count_;
            count_++;

            vertex_stack_.push(vertex_id);
            in_stack_[vertex_id] = true;

            auto vertex = graph_.get_vertex(vertex_id);
            for (auto& [neighbour, _] : vertex.get_outgoing_edges()) {
                auto it = indexes_.find(neighbour);
                if (it == indexes_.end()) {
                    strong_connect(neighbour);
                    // если потомок может добраться до более меньшего индекса, то и мы можем
                    lowlinks_[vertex_id] = std::min(lowlinks_[vertex_id], lowlinks_[neighbour]);
                }
                // если дошли до вершины, которая уже есть в стеке - то найден цикл
                else if (in_stack_[neighbour]) {
                    // значит vertex_id может гарантировано добраться до neighbour, либо до вершины с меньшим индексом
                    lowlinks_[vertex_id] = std::min(lowlinks_[vertex_id], indexes_[neighbour]);
                }
            }
            // если встретили корень компоненты связности, то извлекаем все из стека и заносим в одну ксс
            if (lowlinks_[vertex_id] == indexes_[vertex_id]) {
                std::vector<std::string> new_scc;
                std::string other_neighbour;
                // раскрутка стека пока не дойдем до корня копмоненты связности
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
