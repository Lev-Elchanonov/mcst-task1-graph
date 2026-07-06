#pragma once
#include <vector>

#include "graph.hpp"

class i_command {
    public:
        virtual ~i_command() = default;
        virtual std::string execute(Graph& graph, const std::vector<std::string>& args) = 0;    // чисто виртуальная функция выполнения команды
        virtual bool validate_args(const std::vector<std::string>& args) = 0;                   // для проверки аргументов
};
