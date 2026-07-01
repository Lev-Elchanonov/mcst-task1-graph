#pragma once

#include "i_command.hpp"

class add_edge_cmd : public i_command {
    public:
        std::string execute(Graph &graph, const std::vector<std::string>& args) override {
            if (!validate_args(args)) {
                return "Failure: Incorrect args\n";
            }
            return graph.add_edge(std::stoi(args[2]), args[0], args[1]);
        }

        bool validate_args(const std::vector<std::string> &args) override {
            return true;
        }
};
