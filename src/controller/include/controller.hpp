#pragma once
#include <memory>
#include <vector>

#include "graph.hpp"
#include "i_command.hpp"

// Парсит команды, переданные от View, и выбирает одну из команд
class Controller {
    private:
        Graph* graph_;                                                          // граф
        std::unordered_map<std::string, std::unique_ptr<i_command>> commands_;  // хеш-мапа команд (паттерн Command)
        static std::vector<std::string> split_tokens(std::string s);            // приватная функция парсинга текста пользователя на токены

        void register_default_commands();                                       // для регистрации стандартных команд, прописанных в задании
    public:
        explicit Controller(Graph* graph);
        std::string process_command(const std::string& command);                // поиск и обработка команды

        void add_command(const std::string& command, std::unique_ptr<i_command> command_ptr);   // для добавления новой команды в хеш-мапу (для расширяемости)
        void delete_command(const std::string& command);                                        // удаление команды из хеш-мапы
};
