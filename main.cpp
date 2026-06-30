#include <iostream>
#include <memory>
#include <ostream>

#include "view.hpp"


int main() {
    try {
        auto graph = std::make_unique<Graph>();
        auto dialogue = std::make_unique<View>((graph.get()));
        dialogue->chat();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
