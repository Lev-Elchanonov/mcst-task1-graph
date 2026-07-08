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
#include "tarjan_cmd.hpp"
#include "clear_cmd.hpp"
#include "rpo_cmd.hpp"

std::vector<std::string> controller::split_tokens(std::string str) {
    std::regex reg(R"(\s+)");
    std::sregex_token_iterator iter(str.begin(), str.end(), reg, -1);
    std::sregex_token_iterator end;

    std::vector<std::string> tokens(iter, end);
    return tokens;
}

void controller::register_default_commands() {
    commands_.emplace("NODE", std::make_unique<add_vertex_cmd>());
    commands_.emplace("EDGE", std::make_unique<add_edge_cmd>());
    commands_.emplace("REMOVE NODE", std::make_unique<remove_vertex_cmd>());
    commands_.emplace("REMOVE EDGE", std::make_unique<remove_edge_cmd>());
    commands_.emplace("LOOK", std::make_unique<visualize_cmd>());
    commands_.emplace("DIJKSTRA", std::make_unique<dijkstra_cmd>());
    commands_.emplace("MAXFLOW", std::make_unique<maxflow_cmd>());
    commands_.emplace("TARJAN", std::make_unique<tarjan_cmd>());
    commands_.emplace("CLEAR", std::make_unique<clear_cmd>());
    commands_.emplace("RPO_NUMBERING", std::make_unique<rpo_cmd>());
}


controller::controller(graph* graph) {
    if (!graph) {
        throw std::invalid_argument("Graph cannot be nullptr\n");
    }
    graph_ = graph;
    register_default_commands();
}

void controller::add_command(const std::string& command, std::unique_ptr<i_command> command_ptr) {
    commands_.emplace(command, std::move(command_ptr));
}
void controller::delete_command(const std::string& command) {
    commands_.erase(command);
}



std::string controller::process_command(const std::string& command) {
    std::vector<std::string> tokens = split_tokens(command);        // первый полученный токен - название команды, остальные - ее аргументы
    std::string command_name = tokens.front();
    tokens.erase(tokens.begin());
    if (command_name == "REMOVE") { // для REMOVE в имя команды входят первые 2 токена (REMOVE NODE, REMOVE EDGE)
        command_name += " " + tokens.front();
        tokens.erase(tokens.begin());
    }
    auto cmd = commands_.find(command_name); // поиск команды в хеш-мапе
    if (cmd == commands_.end()) {
        return  "";
    }
    return cmd->second->execute(*graph_, tokens); // вызов override метода в наследнике, реализующем конкретную команду
}

