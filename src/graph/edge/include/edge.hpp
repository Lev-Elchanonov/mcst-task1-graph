#pragma once
#include <cstddef>

class Vertex;

class Edge {
    private:
        size_t weight_;     // вес ребра
        Vertex* source_;    // исток
        Vertex* dest_;      // сток
    public:
        explicit Edge(size_t weight, Vertex* source, Vertex* dest);
        [[nodiscard]] size_t get_weight() const noexcept;
        [[nodiscard]] const Vertex& get_source() const noexcept;
        [[nodiscard]] const Vertex& get_dest() const noexcept;

        void set_weight(size_t new_weight) noexcept;

};
