#include "controller.hpp"

#include <iostream>
#include <regex>
#include <stdexcept>
#include <vector>

#include "add_edge_cmd.hpp"
#include "add_vertex_cmd.hpp"
#include "remove_edge_cmd.hpp"
#include "remove_vertex_cmd.hpp"
#include "visualize_cmd.hpp"
#include "dijkstra_cmd.hpp"
#include "maxflow_cmd.hpp"
#include "src/commands/tarjan_cmd/include/tarjan_cmd.hpp"

std::vector<std::string> Controller::split_tokens(std::string str) {
    std::regex reg(R"(\s+)");
    std::sregex_token_iterator iter(str.begin(), str.end(), reg, -1);
    std::sregex_token_iterator end;

    std::vector<std::string> tokens(iter, end);
    return tokens;
}

void Controller::register_default_commands() {
    commands_.emplace("NODE", std::make_unique<add_vertex_cmd>());
    commands_.emplace("EDGE", std::make_unique<add_edge_cmd>());
    commands_.emplace("REMOVE NODE", std::make_unique<remove_vertex_cmd>());
    commands_.emplace("REMOVE EDGE", std::make_unique<remove_edge_cmd>());
    commands_.emplace("LOOK", std::make_unique<visualize_cmd>());
    commands_.emplace("DIJKSTRA", std::make_unique<dijkstra_cmd>());
    commands_.emplace("MAXFLOW", std::make_unique<maxflow_cmd>());
    commands_.emplace("TARJAN", std::make_unique<tarjan_cmd>());
}


Controller::Controller(Graph* graph) {
    if (!graph) {
        throw std::invalid_argument("Graph cannot be nullptr\n");
    }
    graph_ = graph;
    register_default_commands();
}

void Controller::add_command(const std::string& command, std::unique_ptr<i_command> command_ptr) {
    commands_.emplace(command, std::move(command_ptr));
}
void Controller::delete_command(const std::string& command) {
    commands_.erase(command);
}



std::string Controller::process_command(const std::string &command) {
    std::vector<std::string> tokens = split_tokens(command);
    std::string command_name = tokens.front();
    tokens.erase(tokens.begin());
    if (command_name == "REMOVE") {
        command_name += " " + tokens.front();
        tokens.erase(tokens.begin());
    }
    auto cmd = commands_.find(command_name);
    if (cmd == commands_.end()) {
        return  "";
    }
    return cmd->second->execute(*graph_, tokens);
}

