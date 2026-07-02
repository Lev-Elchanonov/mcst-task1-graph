#include "vertex.hpp"

#include <stdexcept>

const Edge& Vertex::get_incoming_edge(const std::string &id) const{
    const auto iter = incoming_edges_.find(id);
    if (iter == incoming_edges_.end()) {
        throw std::out_of_range("Vertex with id " + id + " not found\n");
    }
    return iter->second;
}

const Edge& Vertex::get_outgoing_edge(const std::string &id) const{
    const auto iter = outgoing_edges_.find(id);
    if (iter == outgoing_edges_.end()) {
        throw std::out_of_range("Vertex with id " + id + " not found\n");
    }
    return iter->second;
}

void Vertex::add_incoming_edge(Vertex* other_vertex, size_t weight) noexcept {
    if (!other_vertex) { return; }
    if (outgoing_edges_.find(other_vertex->id_) != outgoing_edges_.end()) { return; } // уже существует ребро между вершинами

    const std::string& id = other_vertex->get_id();
    const auto iter = incoming_edges_.find(id);
    if (iter != incoming_edges_.end()) { return; }

    Edge new_edge(weight, other_vertex, this);
    incoming_edges_.insert({id, new_edge});
}

void Vertex::add_outgoing_edge(Vertex* other_vertex, size_t weight) noexcept {
    if (!other_vertex) { return; }
    if (incoming_edges_.find(other_vertex->id_) != incoming_edges_.end()) { return; }

    const std::string& id = other_vertex->get_id();
    const auto iter = outgoing_edges_.find(id);
    if (iter != outgoing_edges_.end()) { return; }

    Edge new_edge(weight, this, other_vertex);
    outgoing_edges_.insert({id, new_edge});
}

void Vertex::delete_incoming_edge(const std::string& id) noexcept {
    incoming_edges_.erase(id);
}

void Vertex::delete_outgoing_edge(const std::string& id) noexcept {
    outgoing_edges_.erase(id);
}

