#pragma once
#include <iostream>

#include "controller.hpp"

// Класс-интерфейс для работы с программой
// Принимает команды от пользователя и передает их в контроллер
// Использовался паттерн MVC
class view {
private:
    controller controller_;
public:
    explicit view(graph* graph) : controller_(graph) {}
    void chat(std::istream& istr = std::cin);           // функция диалога пользователя с программой

};
