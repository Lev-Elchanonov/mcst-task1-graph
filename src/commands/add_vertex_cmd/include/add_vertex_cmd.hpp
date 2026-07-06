#pragma once
#include "i_command.hpp"

class add_vertex_cmd : public i_command {
    public:
        std::string execute(Graph &graph, const std::vector<std::string>& args) override {
            if (!validate_args(args)) {
                return "Failure: Incorrect args";
            }
            graph.add_vertex(args.front());
            return "";
        }


        bool validate_args(const std::vector<std::string> &args) override {
            bool broken_arguments = args.size() != 1 || std::isdigit(args[0].front());
            return !broken_arguments;
        }
};
