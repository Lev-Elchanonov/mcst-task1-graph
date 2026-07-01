#pragma once
#include <map>
#include <string>
#include <utility>

#include "edge.hpp"


class Vertex {
    private:
        std::string id_;
        std::map<std::string, Edge> incoming_edges_;
        std::map<std::string, Edge> outgoing_edges_;
    public:
        explicit Vertex(std::string id) : id_(std::move(id)) {}
        Vertex() = default;

        [[nodiscard]] const std::string& get_id() const noexcept { return id_; }
        [[nodiscard]] const Edge& get_incoming_edge(const std::string &id) const;
        [[nodiscard]] const Edge& get_outgoing_edge(const std::string& id) const;

        void add_incoming_edge(Vertex* other_vertex, size_t weight) noexcept;
        void add_outgoing_edge(Vertex* other_vertex, size_t weight) noexcept;

        void delete_incoming_edge(const std::string& id) noexcept;
        void delete_outgoing_edge(const std::string& id) noexcept;
};

