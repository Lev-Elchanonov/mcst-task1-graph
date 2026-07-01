#pragma once
#include <cstddef>

class Vertex;

class Edge {
    private:
        std::size_t weight_;
        Vertex* source_;
        Vertex* dest_;
    public:
        explicit Edge(size_t weight, Vertex* source, Vertex* dest);
        [[nodiscard]] size_t get_weight() const noexcept;
        [[nodiscard]] const Vertex& get_source() const noexcept;
        [[nodiscard]] const Vertex& get_dest() const noexcept;

        void set_weight(size_t new_weight) noexcept;
};
