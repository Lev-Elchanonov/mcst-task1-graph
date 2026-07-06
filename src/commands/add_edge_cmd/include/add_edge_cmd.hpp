#pragma once

#include "i_command.hpp"

class add_edge_cmd final : public i_command {
    public:
        std::string execute(Graph &graph, const std::vector<std::string>& args) override {
            if (!validate_args(args)) {
                return "Failure: Incorrect args";
            }
            return graph.add_edge(std::stoi(args[2]), args[0], args[1]);
        }

        static bool is_number(const std::string& s) {
            if (s.empty())
                return false;
            for (char c : s) {
                if (!std::isdigit(c)) {
                    return false;
                }
            }
            return true;
        }
        bool validate_args(const std::vector<std::string> &args) override {
            bool broken_arguments = args.size() != 3 || !is_number(args[2]) || std::isdigit(args[0].front()) || std::isdigit(args[1].front());
            return !broken_arguments;
        }
};
