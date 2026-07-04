#include "vertex.hpp"

#include <stdexcept>

const Edge& Vertex::get_outgoing_edge(const std::string &id) const{
    const auto iter = outgoing_edges_.find(id);
    if (iter == outgoing_edges_.end()) {
        throw std::out_of_range("Vertex with id " + id + " not found\n");
    }
    return iter->second;
}

void Vertex::add_outgoing_edge(Vertex* other_vertex, size_t weight) noexcept {
    if (!other_vertex) { return; }
    auto from_other_vertex = other_vertex->get_outgoing_edges();
    if (from_other_vertex.contains(this->id_)) { return; }

    const std::string& other_id = other_vertex->get_id();
    if (outgoing_edges_.contains(other_id)) { return; }

    Edge new_edge(weight, this, other_vertex);
    outgoing_edges_.insert({other_id, new_edge});
}

void Vertex::delete_outgoing_edge(const std::string& id) noexcept {
    outgoing_edges_.erase(id);
}

