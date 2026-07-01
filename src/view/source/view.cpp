#include "view.hpp"
#include "output_msg.hpp"


void View::chat(std::istream& istr) {
    std::string input;
    std::string message;
    while (std::getline(istr, input)) {
        if (input == "exit") { break; }
        Output_msg operation_result = controller_.process_command(input);
        if (operation_result.get_result() == true && operation_result.get_msg() != "Success") {
            std::cout << operation_result.get_msg() << std::endl;
        } else if (operation_result.get_result() == false) {
            std::cout << "\tError: Unknown command" << std::endl;
        }
    }
}