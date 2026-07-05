#include "graph.hpp"

#include <stdexcept>

void Graph::add_vertex(const std::string& vert_name) noexcept {
    Vertex new_vertex(vert_name);
    vertices_[vert_name] = new_vertex;
}

std::string Graph::add_edge(size_t weight, const std::string& source_id, const std::string& dest_id) noexcept {
    if (!vertices_.contains(source_id) && !vertices_.contains(dest_id)) {
        return "Unknown nodes " + source_id + " " + dest_id;
    }
    if (!vertices_.contains(source_id)) {
        return "Unknown node " + source_id;
    }
    if (!vertices_.contains(dest_id)) {
        return "Unknown node " + dest_id;
    }
    auto source_iter = vertices_.find(source_id);
    auto dest_iter = vertices_.find(dest_id);
    source_iter->second.add_outgoing_edge(&dest_iter->second, weight); // добавление ребра source_id -> dest_id
    return "";
}

const Vertex& Graph::get_vertex(const std::string& vert_name) const {
    if (!vertices_.contains(vert_name)) {
        throw std::invalid_argument("Vertex not found");
    }
    return vertices_.find(vert_name)->second;
}

const Edge& Graph::get_edge(const std::string& source_id, const std::string& dest_id) const {
    if (!vertices_.contains(source_id)) {
        throw std::invalid_argument("Source vertex not found");
    }
    auto iter = vertices_.find(source_id);
    return iter->second.get_outgoing_edge(dest_id);
}

std::string Graph::delete_edge(const std::string& source_id, const std::string& dest_id) {
    if (!vertices_.contains(source_id) && !vertices_.contains(dest_id)) {
        return "Unknown nodes " + source_id + " " + dest_id;
    }
    if (!vertices_.contains(source_id)) {
        return "Unknown node " + source_id;
    }
    if (!vertices_.contains(dest_id)) {
        return "Unknown node " + dest_id;
    }
    auto source_iter = vertices_.find(source_id);
    source_iter->second.delete_outgoing_edge(dest_id);
    return "";
}


std::string Graph::delete_vertex(const std::string& vert_name) {
    if (!vertices_.contains(vert_name)) {
        return "Unknown node " + vert_name;
    }
    for (auto& element : vertices_) {
        element.second.delete_outgoing_edge(vert_name);
    }
    vertices_.erase(vert_name);
    return "";
}


std::string Graph::export_to_dot() const {
    std::string result = "digraph G {\n";
    result += "    rankdir=LR;\n";
    result += "    node [shape=circle];\n";

    for (const auto& [id, vertex] : vertices_) {
        result += "    \"" + id + "\";\n";
    }

    for (const auto& [id, vertex] : vertices_) {
        for (const auto& [dest_id, edge] : vertex.get_outgoing_edges()) {
            result += "    \"" + id + "\" -> \"" + dest_id + "\"";
            if (edge.get_weight() > 0) {
                result += " [label=\"" + std::to_string(edge.get_weight()) + "\"]";
            }
            result += ";\n";
        }
    }

    result += "}\n";
    return result;
}
