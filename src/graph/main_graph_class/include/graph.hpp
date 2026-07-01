#pragma once
#include <string>
#include <unordered_map>

#include "vertex.hpp"

class Graph {
    private:
        std::unordered_map<std::string, Vertex> vertices_;
    public:
        void add_vertex(const std::string& vert_name) noexcept;
        void add_edge(size_t weight, const std::string& source_id, const std::string& dest_id);

        const Vertex& get_vertex(const std::string& vert_name) const;
        const Edge& get_edge(const std::string& source_id, const std::string& dest_id) const;

        void delete_vertex(const std::string& vert_name);
        void delete_edge(const std::string& source_id, const std::string& dest_id);
};
