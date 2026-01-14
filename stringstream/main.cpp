#include <iostream>
#include <sstream>

int main() {
    // the user enters a command (e.g. L 100 200)
    std::string user_input;
    std::string command;
    auto start = -1;
    auto end = -1;

    std::cout << "Enter a command and two numbers: ";
    std::getline(std::cin, user_input);

    std::stringstream ss(user_input);
    ss >> command;

    if (command.length() > 1) {
        std::cout << "You typed text." << std::endl;
    } else {
        // is there anything left in the stringstream?
        if (ss.eof()) {
            std::cout << "I am pretty sure you typed a command." << std::endl;
        } else {
            // let's see if the next thing is a number
            ss >> start;

            if (ss.fail()) {
                std::cout << "You typed text, not a command." << std::endl;
            }
        }

        std::cout << "command: " << command;
        std::cout << ", start: " << start;
        std::cout << ", end: " << end << std::endl;
    }

    return 0;
}
