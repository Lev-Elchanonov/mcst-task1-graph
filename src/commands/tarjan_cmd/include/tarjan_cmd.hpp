#pragma once
#include <algorithm>
#include <stack>

#include "i_command.hpp"
#include "tarjan_help_class.hpp"

class tarjan_cmd final : public i_command {
public:
    std::string execute(graph& graph, const std::vector<std::string>& args) override {
        if (!validate_args(args)) {
            return "Failure: Incorrect args";
        }
        auto tarjan_class = tarjan(graph);
        const auto& start_vertex = args.front();
        tarjan_class.strong_connect(start_vertex);
        auto all_scc = tarjan_class.get_scc();
        for (auto& scc : all_scc) {
            std::ranges::sort(scc);
        }
        std::string res;
        for (auto& scc : all_scc) {
            for (auto& vertex : scc) {
                res += vertex + " ";
            }
            res.pop_back();
            res += "\n";
        }
        if (!res.empty()) {
            res.pop_back();
        }
        return res;
    }

    bool validate_args(const std::vector<std::string> &args) override {
        bool broken_arguments = args.size() != 1 || std::isdigit(args[0].front());
        return !broken_arguments;
    }
};
