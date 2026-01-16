#include <iostream>
#include <vector>

std::ostream& operator<<(std::ostream& os, const std::vector<int>& v) {
    for (auto& n : v) {
        os << n << " ";
    }
    return os;
}

void operator<<(std::vector<int>& v, const std::vector<int>& in_vec) {
    for (auto& n : in_vec) {
        v.push_back(n);
    }
}

int main() {
    std::vector v1 = {1, 2, 3, 4, 5};

    std::cout << v1 << std::endl;
    std::cout << "capacity: " << v1.capacity() << std::endl;
    std::cout << "size: " << v1.size() << std::endl;

    v1.push_back(6);

    std::cout << v1 << std::endl;
    std::cout << "capacity: " << v1.capacity() << std::endl;
    std::cout << "size: " << v1.size() << std::endl;

    v1.push_back(7);

    std::cout << v1 << std::endl;
    std::cout << "capacity: " << v1.capacity() << std::endl;
    std::cout << "size: " << v1.size() << std::endl;

    v1.reserve(50);

    v1 << std::vector({8, 9, 10, 11, 12});

    std::cout << v1 << std::endl;
    std::cout << "capacity: " << v1.capacity() << std::endl;
    std::cout << "size: " << v1.size() << std::endl;

    v1 << std::vector({13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32});

    std::cout << v1 << std::endl;
    std::cout << "capacity: " << v1.capacity() << std::endl;
    std::cout << "size: " << v1.size() << std::endl;

    v1.shrink_to_fit();

    std::cout << v1 << std::endl;
    std::cout << "capacity: " << v1.capacity() << std::endl;
    std::cout << "size: " << v1.size() << std::endl;

    // display element 32
    std::cout << v1.at(32) << std::endl;

    return 0;
}
