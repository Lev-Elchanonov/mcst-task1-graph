#pragma once
#include <ctime>
#include <fstream>

#include "i_command.hpp"

class visualize_cmd : public i_command {
public:
    std::string execute(Graph &graph, const std::vector<std::string>& args) override {
        if (!validate_args(args)) {
            return "Failure: Incorrect args";
        }
        std::string dot_format = graph.export_to_dot();

        std::string dot_filename = "/tmp/graph_" + std::to_string(std::time(nullptr)) + ".dot";
        std::string png_filename = "/tmp/graph_" + std::to_string(std::time(nullptr)) + ".png";

        std::ofstream dot_file(dot_filename);
        if (!dot_file) {
            return "Failure: Cannot create temporary DOT file";
        }
        dot_file << dot_format;
        dot_file.close();

        std::string command = "dot -Tpng " + dot_filename + " -o " + png_filename;
        int result = std::system(command.c_str());

        if (result != 0) {
            return "Failure: Graphviz conversion failed";
        }

        command = "xdg-open " + png_filename + " 2>/dev/null";

        result = std::system(command.c_str());

        if (result != 0) {
            return "Graph exported but cannot open viewer";
        }
        std::remove(dot_filename.c_str());
        return "";
    }

    bool validate_args(const std::vector<std::string> &args) override {
        return args.empty();
    }
};
