#pragma once
#include <vector>

#include "graph.hpp"

class Rpo {
    private:
        enum class Color {
            White,  // непосещенная верщина
            Gray,   // вершина в обработке
            Black   // посещена
        };
        Graph& graph_;
        std::unordered_map<std::string, Color> color_map_;
        std::vector<std::string> postorder_;
        std::vector<std::string> loops_;
    public:
        explicit Rpo(Graph& graph) : graph_(graph) {}
        void dfs(const std::string& vert_id) {
            color_map_[vert_id] = Color::Gray;      // при посещении вершины перекрашиваем в Gray
            const auto& vert = graph_.get_vertex(vert_id);
            for (const auto& [neigh_id, edge] : vert.get_outgoing_edges()) {
                auto color_it = color_map_.find(neigh_id);
                Color neigh_color = color_it == color_map_.end() ? Color::White : color_it->second;
                if (neigh_color == Color::White) {  // если вершина не посещена - запускаем из нее dfs
                    dfs(neigh_id);
                }
                else if (neigh_color == Color::Gray) {  // если мы дошли до серой вершины - значит обнаружили цикл
                    loops_.push_back("Found loop " + vert_id + "->" + neigh_id);
                }
            }
            color_map_[vert_id] = Color::Black;     // красим посещенную вершину в черный
            postorder_.push_back(vert_id);          // добавляем в порядок обхода
        }
        std::vector<std::string>& get_postorder() { return postorder_; }
        std::vector<std::string>& get_loops() { return loops_; }
};
