#pragma once

#include "i_command.hpp"
#include "maxflow_struct.hpp"

class maxflow_cmd final : public i_command {
    public:
        bool validate_args(const std::vector<std::string> &args) override {
            bool broken_arguments = args.size() != 2 || std::isdigit(args[0].front()) || std::isdigit(args[1].front());
            return !broken_arguments;
        }


        std::string execute(Graph& graph, const std::vector<std::string>& args) override {
            if (!validate_args(args)) {
                return "Failure: Incorrect args";
            }
            auto maxflow_class = Maxflow(graph, args[1]);
            return std::to_string(maxflow_class.find_maxflow(args.front()));
        }

};
