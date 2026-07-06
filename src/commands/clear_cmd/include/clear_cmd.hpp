#pragma once
#include "i_command.hpp"

class clear_cmd final : public i_command {
    public:
        std::string execute(Graph &graph, const std::vector<std::string>& args) override {
            if (!validate_args(args)) {
                return "Failure: Incorrect args";
            }
            graph.clear();
            return "";
        }


        bool validate_args(const std::vector<std::string> &args) override {
            return args.empty();
        }
};
