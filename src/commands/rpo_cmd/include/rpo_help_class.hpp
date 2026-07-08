#pragma once
#include <vector>

#include "graph.hpp"

class rpo {
private:
    enum class color {
        White,  // непосещенная верщина
        Gray,   // вершина в обработке
        Black   // посещена
    };
    graph& graph_;
    std::unordered_map<std::string, color> color_map_;
    std::vector<std::string> postorder_;
    std::vector<std::string> loops_;
public:
    explicit rpo(graph& graph) : graph_(graph) {}
    void dfs(const std::string& vert_id) {
        color_map_[vert_id] = color::Gray;      // при посещении вершины перекрашиваем в Gray
        const auto& vert = graph_.get_vertex(vert_id);
        for (const auto& [neigh_id, edge] : vert.get_outgoing_edges()) {
            auto color_it = color_map_.find(neigh_id);
            color neigh_color = color_it == color_map_.end() ? color::White : color_it->second;
            if (neigh_color == color::White) {  // если вершина не посещена - запускаем из нее dfs
                dfs(neigh_id);
            }
            else if (neigh_color == color::Gray) {  // если мы дошли до серой вершины - значит обнаружили цикл
                loops_.push_back("Found loop " + vert_id + "->" + neigh_id);
            }
        }
        color_map_[vert_id] = color::Black;     // красим посещенную вершину в черный
        postorder_.push_back(vert_id);          // добавляем в порядок обхода
    }
    std::vector<std::string>& get_postorder() { return postorder_; }
    std::vector<std::string>& get_loops() { return loops_; }
};
