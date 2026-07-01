#pragma once
#include "i_command.hpp"

class add_vertex_cmd : public i_command {
    public:
        std::string execute(Graph &graph, const std::vector<std::string>& args) override {
            if (!validate_args(args)) {
                return "Failure: Incorrect args\n";
            }
            graph.add_vertex(args.front());
            return "Success";
        }


        bool validate_args(const std::vector<std::string> &args) override {
            return true;
        }
};
