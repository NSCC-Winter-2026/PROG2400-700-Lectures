#include <iostream>

// factorial
// 5! = 5 x 4 x 3 x 2 x 1 = 120

int factorial(int num) {
    int answer = num;
    while (num > 1) {
        num--;
        answer *= num;
    }
    return answer;
}

int factorial_recursive(int num) {
    // easiest: 1! = 1
    // end condition
    if (num == 1) return 1;

    return num * factorial_recursive(num - 1);
}


int main() {
    // without recursion
    std::cout << "5! = " << factorial(5) << std::endl;
    std::cout << "5! = " << factorial_recursive(5) << std::endl;

    return 0;
}
