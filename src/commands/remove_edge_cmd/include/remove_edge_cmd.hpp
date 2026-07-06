#pragma once
#include "i_command.hpp"

class remove_edge_cmd : public i_command {
    public:
        std::string execute(Graph &graph, const std::vector<std::string>& args) override {
            if (!validate_args(args)) {
                return "Failure: Incorrect args";
            }
            return graph.delete_edge(args[0], args[1]);
        }

        bool validate_args(const std::vector<std::string> &args) override {
            bool broken_arguments = args.size() != 2 || std::isdigit(args[0].front()) || std::isdigit(args[1].front());
            return !broken_arguments;
        }
};
