#pragma once
#include <cstddef>

class vertex;

class edge {
private:
    size_t weight_;     // вес ребра
    vertex* source_;    // исток
    vertex* dest_;      // сток
public:
    explicit edge(size_t weight, vertex* source, vertex* dest);
    [[nodiscard]] size_t get_weight() const noexcept;
    [[nodiscard]] const vertex& get_source() const noexcept;
    [[nodiscard]] const vertex& get_dest() const noexcept;

    void set_weight(size_t new_weight) noexcept;
};
