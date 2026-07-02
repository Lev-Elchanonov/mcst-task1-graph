#pragma once
#include <memory>
#include <vector>

#include "graph.hpp"
#include "i_command.hpp"
#include "output_msg.hpp"

class Controller {
    private:
        Graph* graph_;
        std::unordered_map<std::string, std::unique_ptr<i_command>> commands_;
        static std::vector<std::string> split_tokens(std::string s);

        void register_default_commands();
    public:
        explicit Controller(Graph* graph);
        std::string process_command(const std::string& command);

        void add_command(const std::string& command, std::unique_ptr<i_command> command_ptr);
        void delete_command(const std::string& command);
};
