#include <iostream>
#include <memory>

struct Data {
    int num {-1};
    std::string description {"uninitialized"};
};

std::ostream& operator<<(std::ostream& os, const Data& d) {
    os << "num = " << d.num << ", desc = " << d.description;
    return os;
}

class Stack {
    struct Node {
        Data data;
        std::unique_ptr<Node> next {nullptr};
    };

    std::unique_ptr<Node> _top {nullptr};

public:
    void push(const Data& d) {
        auto node = std::make_unique<Node>(d);
        node->next = std::move(_top);
        _top = std::move(node);
    }

    [[nodiscard]] std::optional<Data> top() const {
        if (_top == nullptr) return std::nullopt;
        return std::make_optional(_top->data);
    }

    void pop() {
        _top = std::move(_top->next);
    }

    friend std::ostream& operator<<(std::ostream& os, const Stack& s);
};

std::ostream& operator<<(std::ostream& os, const Stack& s) {
    auto node = s._top.get();

    while (node != nullptr) {
        os << node->data << std::endl;
        node = node->next.get();
    }

    return os;
}

int main() {
    Stack stack;
    // test 1 - add items to the stack
    std::cout << "Test 1 - add items to the stack" << std::endl;
    std::cout << "-------------------------------" << std::endl;

    stack.push({1, "One"});
    stack.push({2, "Two"});
    stack.push({3, "Three"});
    stack.push({4, "Four"});
    stack.push({5, "Five"});

    std::cout << stack << std::endl;

    // test 2 - remove items from the stack
    std::cout << "Test 2 - remove items from the stack" << std::endl;
    std::cout << "------------------------------------" << std::endl;

    std::cout << "top: " << stack.top().value_or(Data {-1, "There's no data"}) << std::endl;
    stack.pop();
    std::cout << stack << std::endl;

    // test 3 - remove all items from the stack
    std::cout << "Test 3 - remove all items from the stack" << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    while (stack.top() != std::nullopt) {
        std::cout << stack << std::endl;
        stack.pop();
    }

    return 0;
}
