#include <iostream>
#include <memory>
#include <ostream>

#include "view.hpp"


int main() {
    try {
        auto graph_ = std::make_unique<graph>();
        auto dialogue = std::make_unique<view>((graph_.get()));
        dialogue->chat();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
