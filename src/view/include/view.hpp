#pragma once
#include <iostream>

#include "controller.hpp"

class View {
    private:
        Controller controller_;
    public:
        explicit View(Graph* graph) : controller_(graph) {}
        void chat(std::istream& istr = std::cin);

};
