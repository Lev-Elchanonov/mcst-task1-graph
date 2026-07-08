#include "view.hpp"


void view::chat(std::istream& istr) {
    std::string input;
    std::string message;
    while (std::getline(istr, input)) {
        if (input == "exit") { break; }
        std::string res_msg = controller_.process_command(input);
        if (!res_msg.empty()) {
            std::cout << res_msg << std::endl;
        }
    }
}