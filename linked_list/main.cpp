#include <iostream>

class LinkedList {
    struct Node {
        int data {-1};
        Node* next {nullptr};
    };

    Node* _start {nullptr};

public:
    class iterator {
        Node* _node {nullptr};
        int _index {-1};

    public:
        explicit iterator(Node* node = nullptr) : _node(node) {
        }

        int operator*() const { return _node->data; }

        iterator& operator++() {
            _node = _node->next;
            return *this;
        }

        bool operator!=(const iterator it) const { return _node != it._node; }
    };

    [[nodiscard]] iterator begin() const { return iterator(_start); }
    [[nodiscard]] iterator end() const { return iterator(nullptr); }

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

    /// inserts a node in the middle of the linked list
    /// @param data the integer to insert
    /// @param before the value of the node to insert before
    void insert(const int data, const int before) {
        auto node = new Node {data};
        // find the node to insert before
        auto curr = _start;
        auto prev = static_cast<Node*>(nullptr);

        while (curr != nullptr) {
            // what node am I looking for?
            if (curr->data == before) break;
            prev = curr;
            curr = curr->next;
        }

        // am I inserting the node at the start?
        if (prev == nullptr) {
            // yes!
            node->next = _start;
            _start = node;
        } else {
            // no.

            // either insert or add to end of list
            node->next = prev->next;
            prev->next = node;
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

    // test 4 - can we insert a node a spot in the list
    // insert the value 6 before the node that contains the value 4
    list.insert(6, 4);

    std::cout << "Test 4 - insert a node" << std::endl;
    std::cout << "----------------------" << std::endl;
    std::cout << list << std::endl;

    // test 5 - what happens when we try to insert before a node that doesn't exist?
    // insert the value 7 before the node that contains the value 10
    list.insert(7, 10);

    std::cout << "Test 5 - insert a node before an invalid node" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << list << std::endl;

    // test 6 - insert before the first node
    // insert the value 12 before the node that contains the value 2
    list.insert(12, 2);

    std::cout << "Test 6 - insert a node before the first node" << std::endl;
    std::cout << "--------------------------------------------" << std::endl;
    std::cout << list << std::endl;

    // test 7 - using a for loop to output node values
    std::cout << "Test 7 - using a for loop to output node values" << std::endl;
    std::cout << "-----------------------------------------------" << std::endl;

    for (auto i = list.begin(); i != list.end(); ++i) {
        std::cout << *i << " ";
    }
    std::cout << std::endl;

    for (auto i : list) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}
