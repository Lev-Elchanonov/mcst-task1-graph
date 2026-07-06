#pragma once
#include <string>
#include <unordered_map>

#include "vertex.hpp"

class Graph {
    private:
        std::unordered_map<std::string, Vertex> vertices_;      // хеш-мапа вершин
    public:
        void add_vertex(const std::string& vert_name) noexcept;
        std::string add_edge(size_t weight, const std::string& source_id, const std::string& dest_id) noexcept;

        const Vertex& get_vertex(const std::string& vert_name) const;
        const Edge& get_edge(const std::string& source_id, const std::string& dest_id) const;

        std::string delete_vertex(const std::string& vert_name) noexcept;
        std::string delete_edge(const std::string& source_id, const std::string& dest_id) noexcept;

        std::unordered_map<std::string, Vertex> get_vertices() const noexcept { return vertices_; }
        std::string export_to_dot() const noexcept; // для визуализации графа

        void clear() noexcept { vertices_.clear(); } // полная очистка графа

        bool has_vertex(const std::string& vert_name) const noexcept { return vertices_.contains(vert_name); }
};
