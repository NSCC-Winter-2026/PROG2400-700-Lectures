#include <iostream>
#include <memory>

struct Student {
    std::string name;
    std::string id;
};

std::ostream& operator<<(std::ostream& os, const Student& student) {
    os << "Name: " << student.name << ", ID: " << student.id;
    return os;
}

class Queue {
    struct Node {
        Student data {"uninitialized", "W0000000"};
        std::unique_ptr<Node> next {nullptr};
    };

    std::unique_ptr<Node> _front {nullptr};
    Node* _back {nullptr}; // not a smart pointer since it will not have ownership

public:
    void push_back(const Student& data) {
        auto node = std::make_unique<Node>(data);

        // is there a back node already?
        if (_back == nullptr) {
            // no, there isn't.
            _front = std::move(node);
            _back = _front.get();
        } else {
            // yes! there is.
            _back->next = std::move(node);
            _back = _back->next.get();
        }
    }

    [[nodiscard]] Student front() const {
        return _front != nullptr ? _front->data : Student();
    }

    void pop_front() {
        const auto node = std::move(_front);

        // detach node from front of queue
        _front = std::move(node->next);

        // if removing the last node, reset the back pointer
        if (_front == nullptr) {
            _back = nullptr;
        }
    }

    [[nodiscard]] bool empty() const {
        return _front == nullptr;
    }

    friend std::ostream& operator<<(std::ostream& os, const Queue& queue);
};

std::ostream& operator<<(std::ostream& os, const Queue& queue) {
    auto node = queue._front.get();
    while (node != nullptr) {
        os << node->data << std::endl;
        node = node->next.get();
    }
    return os;
}

int main() {
    Queue queue;

    // test 1 - add data to the queue
    std::cout << "Test 1: add data to the end of the queue" << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    queue.push_back({"John Smith", "W111111"});
    queue.push_back({"Jane Doe", "W222222"});
    queue.push_back({"Jill Hill", "W333333"});
    queue.push_back({"Jack Sprat", "W444444"});
    queue.push_back({"Bill Hill", "W555555"});

    std::cout << queue << std::endl;

    // test 2 - view data at the front of the queue
    std::cout << "Test 2: view data at the front of the queue" << std::endl;
    std::cout << "-------------------------------------------" << std::endl;

    std::cout << queue.front() << std::endl;

    // test 3 - remove node from front of the queue
    std::cout << "Test 3: remove node from the front of the queue" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    queue.pop_front();
    std::cout << queue << std::endl;

    // test 4 - remove all nodes from the queue
    std::cout << "Test 4: remove all nodes from the queue" << std::endl;
    std::cout << "---------------------------------------" << std::endl;

    while (!queue.empty()) {
        queue.pop_front();
        std::cout << queue << std::endl;
    }

    return 0;
}
