#pragma once
#include <algorithm>

#include "i_command.hpp"
#include "rpo_help_class.hpp"

class rpo_cmd final : public i_command {
private:
    enum class Color {
        White,
        Gray,
        Black
    };
public:
    std::string execute(graph &graph, const std::vector<std::string>& args) override {
        if (!validate_args(args)) {
            return "Failure: Incorrect args";
        }
        if (!graph.has_vertex(args.front())) {
            return "Unknown node " + args.front();
        }
        auto rpo_class = rpo(graph);
        rpo_class.dfs(args.front());
        auto& post_order = rpo_class.get_postorder();
        std::ranges::reverse(post_order);
        auto& loops = rpo_class.get_loops();
        std::string res;
        for (auto& loop : loops) {
            res += loop + "\n";
        }
        for (auto& vertex : post_order) {
            res += vertex + " ";
        }
        if (!res.empty()) {
            res.pop_back();
        }
        return res;
    }

    bool validate_args(const std::vector<std::string>& args) override {
        bool broken_arguments = args.size() != 1 || std::isdigit(args[0].front());
        return !broken_arguments;
    }
};
