#include <iostream>

class LinkedList {
    struct Node {
        int data {-1};
        Node* next {nullptr};
    };

    Node* _start {nullptr};

public:
    void add(int data) {
        auto node = new Node {data};

        // is this the first node in chain?
        if (_start == nullptr) {
            // yes! I must be dealing with the first node in the chain!
            _start = node;
        } else {
            // no, there must be at least one node in the chain

            // so I have to find the end of the chain
            auto curr = _start;
            auto prev = (Node*)nullptr;

            while (curr != nullptr) {
                prev = curr;
                curr = curr->next;
            }

            if (prev != nullptr) {
                // we found the end of the chain!
                // so, let's add the new node to the end!
                prev->next = node;
            }
        }
    }

    void remove(int data) {
        auto curr = _start;
        auto prev = (Node*)nullptr;

        // find the node to delete
        while (curr != nullptr) {
            // which node has the value I am looking for?
            if (curr->data == data) break;
            prev = curr;
            curr = curr->next;
        }

        // did we find the node to delete?
        if (curr != nullptr) {
            // is this the first node?
            if (prev == nullptr) {
                // yes it is!
                _start = curr->next;
            } else {
                // no, it's a different node
                // detach node from chain
                prev->next = curr->next;
            }

            delete curr;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, LinkedList& list);
};

std::ostream& operator<<(std::ostream& os, LinkedList& list) {
    auto node = list._start;

    while (node != nullptr) {
        os << node->data << " ";
        node = node->next;
    }
    return os;
}

int main() {
    LinkedList list;
    // test 1 - add some data to the list
    list.add(1);
    list.add(2);
    list.add(3);
    list.add(4);
    list.add(5);

    std::cout << "Test 1 - add some data" << std::endl;
    std::cout << "----------------------" << std::endl;
    std::cout << list << std::endl;

    // test 2 - can we delete a node from the chain
    // remove the node that contains the value 3
    list.remove(3);

    std::cout << "Test 2 - delete a node" << std::endl;
    std::cout << "----------------------" << std::endl;
    std::cout << list << std::endl;

    // test 3 - can we delete the first node from the chain
    // remove the node that contains the value 1
    list.remove(1);

    std::cout << "Test 3 - delete the first node" << std::endl;
    std::cout << "------------------------------" << std::endl;
    std::cout << list << std::endl;

    return 0;
}
