#include "vertex.hpp"

#include <stdexcept>

const edge& vertex::get_outgoing_edge(const std::string &id) const{
    if (!outgoing_edges_.contains(id)) {
        throw std::out_of_range("Vertex with id " + id + " not found\n");
    }
    return outgoing_edges_.find(id)->second;
}

void vertex::add_outgoing_edge(vertex* other_vertex, size_t weight) noexcept {
    if (!other_vertex) { return; }
    auto from_other_vertex = other_vertex->get_outgoing_edges();
    if (from_other_vertex.contains(this->id_)) { // если существует ребро в обратном направлении
        return;
    }

    const std::string& other_id = other_vertex->get_id();
    edge new_edge(weight, this, other_vertex);
    outgoing_edges_.insert_or_assign(other_id, new_edge);
}

void vertex::delete_outgoing_edge(const std::string& id) noexcept {
    outgoing_edges_.erase(id);
}

