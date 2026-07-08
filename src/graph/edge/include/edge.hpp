#pragma once
#include <cstddef>

class vertex;

class edge {
private:
    long long weight_;     // вес ребра
    vertex* source_;    // исток
    vertex* dest_;      // сток
public:
    explicit edge(long long weight, vertex* source, vertex* dest);
    [[nodiscard]] long long get_weight() const noexcept;
    [[nodiscard]] const vertex& get_source() const noexcept;
    [[nodiscard]] const vertex& get_dest() const noexcept;

    void set_weight(long long new_weight) noexcept;
};
