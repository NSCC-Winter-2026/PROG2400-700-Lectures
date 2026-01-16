#include <iostream>

int main() {
    auto a = 0xFF;
    auto b = 0x1234'5678UL;
    auto c = 0x1122'3344'5566'7788ull;

    std::cout << std::hex << std::showbase;
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    std::cout << c << std::endl;

    auto a_ptr = (void*)0xFF;
    auto b_ptr = (void*)0x1234'5678UL;
    auto c_ptr = (void*)0x1122'3344'5566'7788ull;

    std::cout << std::hex << std::showbase;
    std::cout << a_ptr << std::endl;
    std::cout << b_ptr << std::endl;
    std::cout << c_ptr << std::endl;

    // pointer usage
    auto num = 0x1234;
    auto ptr = &num;

    std::cout << "*ptr = " << *ptr << std::endl;

    return 0;
}
