#include "edge.hpp"

#include <stdexcept>

edge::edge(size_t weight, vertex* source, vertex* dest) : weight_(weight), source_(source), dest_(dest) {
    if (!source || !dest) {
        throw std::invalid_argument("Error: source or dest cannot be nullptr");
    }
}

void edge::set_weight(size_t new_weight) noexcept {
    weight_ = new_weight;
}

size_t edge::get_weight() const noexcept {
    return weight_;
}

const vertex& edge::get_source() const noexcept {
    return *source_;
}

const vertex& edge::get_dest() const noexcept {
    return *dest_;
}


