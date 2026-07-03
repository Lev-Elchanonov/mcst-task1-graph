#include "graph.hpp"

#include <stdexcept>

void Graph::add_vertex(const std::string& vert_name) noexcept {
    Vertex new_vertex(vert_name);
    vertices_[vert_name] = new_vertex;
}

std::string Graph::add_edge(size_t weight, const std::string& source_id, const std::string& dest_id) noexcept {
    auto source_iter = vertices_.find(source_id);
    auto dest_iter = vertices_.find(dest_id);
    if (dest_iter == vertices_.end() && source_iter == vertices_.end()) {
        return "Unknown nodes " + source_id + " " + dest_id;
    }
    if (source_iter == vertices_.end()) {
        return "Unknown node " + source_id;
    }
    if (dest_iter == vertices_.end()) {
        return "Unknown node " + dest_id;
    }
    source_iter->second.add_outgoing_edge(&dest_iter->second, weight);
    dest_iter->second.add_incoming_edge(&source_iter->second, weight);
    return "";
}

const Vertex& Graph::get_vertex(const std::string& vert_name) const {
    auto iter = vertices_.find(vert_name);
    if (iter == vertices_.end()) {
        throw std::invalid_argument("Vertex not found");
    }
    return iter->second;
}

const Edge& Graph::get_edge(const std::string& source_id, const std::string& dest_id) const {
    auto iter = vertices_.find(source_id);
    if (iter == vertices_.end()) {
        throw std::invalid_argument("Source vertex not found");
    }
    return iter->second.get_outgoing_edge(dest_id);
}

std::string Graph::delete_edge(const std::string& source_id, const std::string& dest_id) {
    auto source_iter = vertices_.find(source_id);
    auto dest_iter = vertices_.find(dest_id);
    if (dest_iter == vertices_.end() && source_iter == vertices_.end()) {
        return "Unknown nodes " + source_id + " " + dest_id;
    }
    if (source_iter == vertices_.end()) {
        return "Unknown node " + source_id;
    }
    if (dest_iter == vertices_.end()) {
        return "Unknown node " + dest_id;
    }

    source_iter->second.delete_outgoing_edge(dest_id);
    dest_iter->second.delete_incoming_edge(source_id);
    return "";
}


std::string Graph::delete_vertex(const std::string& vert_name) {
    auto iter = vertices_.find(vert_name);
    if (iter == vertices_.end()) {
        return "Unknown node " + vert_name;
    }
    for (auto& element : vertices_) {
        element.second.delete_outgoing_edge(vert_name);
        element.second.delete_incoming_edge(vert_name);
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
