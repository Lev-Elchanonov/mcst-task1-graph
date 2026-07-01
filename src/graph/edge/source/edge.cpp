#include "edge.hpp"

#include <stdexcept>

Edge::Edge(size_t weight, Vertex* source, Vertex* dest) : weight_(weight), source_(source), dest_(dest) {
    if (!source || !dest) {
        throw std::invalid_argument("Error: source or dest cannot be nullptr");
    }
}

void Edge::set_weight(size_t new_weight) noexcept {
    weight_ = new_weight;
}

size_t Edge::get_weight() const noexcept {
    return weight_;
}

const Vertex& Edge::get_source() const noexcept {
    return *source_;
}

const Vertex& Edge::get_dest() const noexcept {
    return *dest_;
}

