#include <iostream>
#include <iomanip>

class BST {
    struct Node {
        int data {-1};
        Node* left {nullptr};
        Node* right {nullptr};
    };

    Node* _root {nullptr};

public:
    void insert(const int& data) {
        insert(data, _root);
    }

    void remove(const int& data) {
        auto node = _root;
        auto parent = static_cast<Node*>(nullptr);

        // find the node to delete
        while (node != nullptr) {
            if (data < node->data) {
                // go left
                parent = node;
                node = node->left;
            } else if (data > node->data) {
                // go right
                parent = node;
                node = node->right;
            } else {
                // found it!
                // "node" will be deleted
                // "parent" will be modified to disconnect the node
                break;
            }
        }

        // did I find the node to delete?
        if (node == nullptr) {
            // nope...
            return;
        }
        // assume the node has a left child
        Node* subtree = node->left;

        // if no left child (subtree is NULL), assume a right child
        if (subtree == nullptr) {
            subtree = node->right;
        }

        // is the node to delete on the left-side or right-side of the parent?
        if (parent == nullptr) {
            // the node has no parent...
        } else if (node == parent->left) {
            // on the left! connect child to parent's left side
            parent->left = subtree;
        } else if (node == parent->right) {
            // on the right! connect child to parent's right side
            parent->right = subtree;
        }

        // node should be disconnected now, so delete it!
        delete node;
    }

private:
    void insert(const int& data, Node*& node) {
        if (node == nullptr) {
            // I hit the bottom of the tree
            node = new Node {data};
        } else if (data < node->data) {
            // search left
            insert(data, node->left);
        } else if (data > node->data) {
            // search right
            insert(data, node->right);
        }
    }

    void print_tree(std::ostream& os, Node*& node, int indent) {
        if (node != nullptr) {
            print_tree(os, node->right, indent + 8);
            os << std::setw(indent) << node->data << std::endl;
            print_tree(os, node->left, indent + 8);
        }
    }

    friend std::ostream& operator<<(std::ostream& os, BST& bst);
};

std::ostream& operator<<(std::ostream& os, BST& bst) {
    bst.print_tree(os, bst._root, 0);
    return os;
}

int main() {
    BST bst;

    // test 1 - add nodes to the tree
    std::cout << "Test 1 : add nodes to tree" << std::endl;
    std::cout << "--------------------------" << std::endl;

    bst.insert(5);
    bst.insert(3);
    bst.insert(7);
    bst.insert(2);
    bst.insert(4);
    bst.insert(6);
    bst.insert(8);

    std::cout << bst << std::endl;

    // test 2 - delete node with no children
    std::cout << "Test 2 : delete node with no children" << std::endl;
    std::cout << "-------------------------------------" << std::endl;

    bst.remove(2);

    std::cout << bst << std::endl;

    // test 3 - delete node with one child
    std::cout << "Test 3 : delete node with one child" << std::endl;
    std::cout << "-----------------------------------" << std::endl;

    bst.remove(3);

    std::cout << bst << std::endl;

    return 0;
}
