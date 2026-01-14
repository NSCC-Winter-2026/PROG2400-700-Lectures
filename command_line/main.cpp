#include <iostream>
#include <string_view>
#include <vector>

void print_args(const int argc, char** argv) {
    const std::vector<std::string_view> args(argv + 1, argv + argc);

    for (const auto& arg : args) {
        std::cout << arg << std::endl;
    }
}

int main(const int argc, char* argv[]) {
    print_args(argc, argv);

    return 0;
}

