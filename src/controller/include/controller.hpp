#pragma once
#include <vector>

#include "graph.hpp"
#include "output_msg.hpp"

class Controller {
    private:
        Graph* graph_;

        static std::vector<std::string> split_tokens(std::string s);
    public:
        explicit Controller(Graph* graph);
        Output_msg process_command(const std::string& command);
};
