#pragma once
#include <map>
#include <string>
#include <utility>

#include "edge.hpp"


class vertex {
private:
    std::string id_;                                // идентификатор вершины
    std::map<std::string, edge> outgoing_edges_;    // выходящие из вершины ребра
public:
    explicit vertex(std::string id) : id_(std::move(id)) {}
    vertex() = default;

    [[nodiscard]] const std::string& get_id() const noexcept { return id_; }
    const edge& get_outgoing_edge(const std::string& id) const;

    void add_outgoing_edge(vertex* other_vertex, size_t weight) noexcept;

    void delete_outgoing_edge(const std::string& id) noexcept;

    [[nodiscard]] const std::map<std::string, edge>& get_outgoing_edges() const noexcept { return outgoing_edges_; }
};
