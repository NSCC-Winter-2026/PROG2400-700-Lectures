#include <iostream>
#include <filesystem>
#include <queue>

namespace fs = std::filesystem;

void list_folders_recursively(const fs::path& path, int indent = 0) {
    // list the folders in the current path
    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.is_directory()) {
            const auto& sub_folder = entry.path();
            std::cout << std::string(indent, ' ') << sub_folder << std::endl;
            list_folders_recursively(sub_folder, indent + 2);
        }
    }
}

void list_folders(const fs::path& path) {
    // use breadth-first searching
    std::queue<std::pair<fs::path, int>> paths;
    // add initial folders to the queue
    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.is_directory()) {
            paths.emplace(entry.path(), 0);
        }
    }

    while (!paths.empty()) {
        // take a path (folder) and go into that folder
        auto current = paths.front();
        std::cout << std::string(current.second, ' ') << current.first << std::endl;
        paths.pop();
        // push all folders on to the queue
        for (const auto& entry : fs::directory_iterator(current.first)) {
            if (entry.is_directory()) {
                paths.emplace(entry.path(), current.second + 2);
            }
        }
    }
}

int main() {
    // create a program to show folder names

    auto path = fs::path(".");

    std::cout << std::endl;
    std::cout << "Non-recursive..." << std::endl;
    std::cout << "----------------" << std::endl;
    std::cout << std::endl;
    list_folders(path);

    std::cout << std::endl;
    std::cout << "Recursive..." << std::endl;
    std::cout << "------------" << std::endl;
    std::cout << std::endl;
    list_folders_recursively(path);

    return 0;
}
