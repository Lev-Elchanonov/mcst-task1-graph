#pragma once
#include <iostream>

#include "controller.hpp"

// Класс-интерфейс для работы с программой
// Принимает команды от пользователя и передает их в контроллер
// Использовался паттерн MVC
class View {
    private:
        Controller controller_;
    public:
        explicit View(Graph* graph) : controller_(graph) {}
        void chat(std::istream& istr = std::cin);           // функция диалога пользователя с программой

};
