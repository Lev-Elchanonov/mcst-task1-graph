#pragma once
#include <limits.h>

#include "i_command.hpp"
#include "maxflow_struct.hpp"

class maxflow_cmd : public i_command {
public:
    bool validate_args(const std::vector<std::string> &args) override {
        if (args.size() != 2              ||
            std::isdigit(args[0].front()) ||
            std::isdigit(args[1].front())) { return false; }

        return true;
    }


    std::string execute(Graph& graph, const std::vector<std::string>& args) override {
        if (!validate_args(args)) {
            return "Failure: Incorrect args";
        }
        auto maxflow_class = Maxflow(graph, args[1]);
        return std::to_string(maxflow_class.find_maxflow(args.front()));
    }

};
