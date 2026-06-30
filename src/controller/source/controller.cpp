#include "controller.hpp"

#include <regex>
#include <stdexcept>
#include <vector>


std::vector<std::string> Controller::split_tokens(std::string str) {
    std::regex reg(R"(\s+)");
    std::sregex_token_iterator iter(str.begin(), str.end(), reg);
    std::sregex_token_iterator end;

    std::vector<std::string> tokens(iter, end);
    return tokens;
}

Controller::Controller(Graph *graph) {
    if (!graph) {
        throw std::invalid_argument("Graph cannot be nullptr\n");
    }
    graph_ = graph;
}

Output_msg Controller::process_command(const std::string &command) {
    std::vector<std::string> tokens = split_tokens(command);
    // тут надо выбирать функцию по первому токену
}

