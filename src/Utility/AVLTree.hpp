/**
 * @file AVLTree.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-26
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include <compare>
#include <concepts>
#include <initializer_list>
#include <iostream>
#include <queue>
#include <stack>
#include <stdexcept>

namespace Utility {

using std::cout;
using std::endl;

template <class T>
requires std::three_way_comparable<T>
class AVLTree {
    struct Node {
        T     data {};
        Node* left   = nullptr;
        Node* right  = nullptr;
        int   height = 0;
    };

    Node* root = nullptr;

    int _size = 0;

    /**
     * @brief return height of `node`
     *
     * @param node
     * @return int
     */
    int height(Node* node) {
        if (node == nullptr) {
            return -1;
        }
        return node->height;
    }

    /**
     * @brief return max of two inputs
     *
     * @param a
     * @param b
     * @return int
     */
    int max(int a, int b) {
        return a > b ? a : b;
    }

    /**
     * @brief `LL` rotation
     *
     * @param node
     * @return Node*
     */
    Node* rotateWithLeftChild(Node* node) {
        Node* leftChild   = node->left;
        node->left        = leftChild->right;
        leftChild->right  = node;
        node->height      = max(height(node->left), height(node->right)) + 1;
        leftChild->height = max(height(leftChild->left), node->height) + 1;
        return leftChild;
    }

    /**
     * @brief `RR` rotation
     *
     * @param node
     * @return Node*
     */
    Node* rotateWithRightChild(Node* node) {
        Node* rightChild   = node->right;
        node->right        = rightChild->left;
        rightChild->left   = node;
        node->height       = max(height(node->left), height(node->right)) + 1;
        rightChild->height = max(height(rightChild->right), node->height) + 1;
        return rightChild;
    }

    /**
     * @brief `LR` rotation => first `RR` then `LL`
     *
     * @param node
     * @return Node*
     */
    Node* doubleWithLeftChild(Node* node) {
        node->left = rotateWithRightChild(node->left);
        return rotateWithLeftChild(node);
    }

    /**
     * @brief `RL` rotation => first `LL` then `RR`
     *
     * @param node
     * @return Node*
     */
    Node* doubleWithRightChild(Node* node) {
        node->right = rotateWithLeftChild(node->right);
        return rotateWithRightChild(node);
    }

    /**
     * @brief insert `data` into `node`
     *
     * @param data
     * @param node
     * @return Node*
     */
    Node* insert(const T& data, Node* node) {
        if (node == nullptr) {
            // create a new node
            node       = new Node();
            node->data = data;
            ++_size;
        } else if (data < node->data) {
            // insert to left
            node->left = insert(data, node->left);
            // check balance
            if (height(node->left) - height(node->right) == 2) {
                if (data < node->left->data) {
                    node = rotateWithLeftChild(node);
                } else {
                    node = doubleWithLeftChild(node);
                }
            }
        } else if (data > node->data) {
            // insert to right
            node->right = insert(data, node->right);
            // check balance
            if (height(node->right) - height(node->left) == 2) {
                if (data > node->right->data) {
                    node = rotateWithRightChild(node);
                } else {
                    node = doubleWithRightChild(node);
                }
            }
        }
        node->height = max(height(node->left), height(node->right)) + 1;
        return node;
    }

    /**
     * @brief find min(leftest) node on the tree rooted at `node`
     *
     * @param node
     * @return Node*
     */
    Node* findMin(Node* node) {
        if (node == nullptr) {
            return nullptr;
        } else if (node->left == nullptr) {
            return node;
        } else {
            return findMin(node->left);
        }
    }

    /**
     * @brief find max(rightest) node on the tree rooted at `node`
     *
     * @param node
     * @return Node*
     */
    Node* findMax(Node* node) {
        if (node == nullptr) {
            return nullptr;
        } else if (node->right == nullptr) {
            return node;
        } else {
            return findMax(node->right);
        }
    }

    /**
     * @brief remove `data` from `node`
     *
     * @param data
     * @param node
     * @return Node*
     */
    Node* remove(const T& data, Node* node) {
        Node* temp = nullptr;
        if (node == nullptr) {
            // not found

            return nullptr;
        } else if (data < node->data) {
            // find from left

            node->left = remove(data, node->left);
        } else if (data > node->data) {
            // find from right

            node->right = remove(data, node->right);
        } else if (node->left && node->right) {
            // found the correct node, have two children
            // replace the correct node with `the min node on the right subtree`
            // then remove `the min node on the right subtree`

            temp        = findMin(node->right);
            node->data  = temp->data;
            node->right = remove(node->data, node->right);
        } else {
            // found the correct node, have one/no child
            // then, replace correct node with it's child
            // or, simply delete it

            temp = node;
            if (node->left == nullptr) {
                node = node->right;
            } else if (node->right == nullptr) {
                node = node->left;
            }
            delete temp;
            --_size;
        }

        // now, the correct node has been removed

        // check balance of `node`
        if (node == nullptr) {
            return node;
        }
        auto leftChild  = node->left;
        auto rightChild = node->right;
        node->height    = max(height(leftChild), height(rightChild)) + 1;
        if (height(leftChild) - height(rightChild) == 2) {
            if (height(leftChild->left) - height(leftChild->right) == 1) {
                return rotateWithLeftChild(node);
            } else {
                return doubleWithLeftChild(node);
            }
        } else if (height(rightChild) - height(leftChild) == 2) {
            if (height(rightChild->right) - height(rightChild->left) == 1) {
                return rotateWithRightChild(node);
            } else {
                return doubleWithRightChild(node);
            }
        }
        return node;
    }

    /**
     * @brief print tree in `inorder` traversal
     *
     * @param node
     */
    void print(Node* node) {
        if (node == nullptr) {
            return;
        }
        print(node->left);
        cout << node->data << " ";
        print(node->right);
    }

    /**
     * @brief clear tree rooted at `node`
     *
     * @param node
     */
    void clear(Node* node) {
        if (node == nullptr) {
            return;
        }
        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    /**
     * @brief Default constructor
     *
     */
    AVLTree() = default;

    /**
     * @brief Constructor, with initializer_list
     *
     * @param init
     */
    AVLTree(const std::initializer_list<T> init) {
        for (auto& input : init) {
            insert(input);
        }
    }

    /**
     * @brief Copt constructor
     *
     * @param other
     */
    AVLTree(const AVLTree& other) {
        // `inOrder` traversal copy
        std::stack<Node*> stack;
        Node*             node = other.root;
        while (node || !stack.empty()) {
            while (node) {
                stack.push(node);
                node = node->left;
            }
            node = stack.top();
            stack.pop();
            insert(node->data);
            node = node->right;
        }
    }

    /**
     * @brief copy assignment
     *
     * @param other
     * @return AVLTree&
     */
    AVLTree& operator=(const AVLTree& other) {
        if (this == &other) {
            return *this;
        }
        // clear current tree
        clear(root);
        // `inOrder` traversal copy
        std::stack<Node*> stack;
        Node*             node = other.root;
        while (node || !stack.empty()) {
            while (node) {
                stack.push(node);
                node = node->left;
            }
            node = stack.top();
            stack.pop();
            insert(node->data);
            node = node->right;
        }
        return *this;
    }

    /**
     * @brief Move constructor
     *
     * @param other
     */
    AVLTree(AVLTree&& other) noexcept
        : _size(other._size)
        , root(other.root) {
        other.root  = nullptr;
        other._size = 0;
    }

    /**
     * @brief Move assignment
     *
     * @param other
     * @return AVLTree&
     */
    AVLTree& operator=(AVLTree&& other) noexcept {
        _size       = other._size;
        root        = other.root;
        other.root  = nullptr;
        other._size = 0;
    }

    /**
     * @brief Destructor
     *
     */
    ~AVLTree() {
        clear(root);
    }

    void insert(const T& data) {
        root = insert(data, root);
    }
    void remove(const T& data) {
        root = remove(data, root);
    }

    void print() {
        if (root == nullptr) {
            cout << "empty tree!" << endl;
            return;
        }
        print(root);
        cout << endl;
    }
    void print_in_layer() {
        if (root == nullptr) {
            cout << "empty tree!" << endl;
            cout << endl;
            return;
        }
        std::queue<Node*> queue;
        queue.push(root);
        while (!queue.empty()) {
            size_t curr_layer_size = queue.size();
            while (curr_layer_size > 0) {
                auto node = queue.front();
                cout << node->data << " ";
                if (node->left) {
                    queue.push(node->left);
                }
                if (node->right) {
                    queue.push(node->right);
                }
                queue.pop();
                --curr_layer_size;
            }
            cout << endl;
        }
        cout << endl;
    }
    void assert_if_in_order() {
        std::stack<Node*> stack;
        std::vector<T>    expand;
        Node*             node = root;
        while (node || !stack.empty()) {
            while (node) {
                stack.push(node);
                node = node->left;
            }
            node = stack.top();
            expand.push_back(node->data);
            stack.pop();
            node = node->right;
        }
        for (size_t i = 1; i < expand.size(); ++i) {
            if (expand.at(i - 1) >= expand.at(i)) {
                throw std::runtime_error("not in order!");
            }
        }
        cout << "in order!" << endl;
        cout << endl;
    }

    T findMin() {
        return findMin(root)->data;
    }
    T findMax() {
        return findMax(root)->data;
    }

    bool contains(const T& data) {
        Node* node = root;
        while (node != nullptr) {
            if (data < node->data) {
                node = node->left;
            } else if (data > node->data) {
                node = node->right;
            } else {
                return true;
            }
        }
        return false;
    }
    bool isEmpty() {
        return root == nullptr;
    }

    // height starts from 0, should >= 0
    int height() {
        return height(root);
    }
    // size starts from 0, should >= 0
    int size() {
        return _size;
    }
};

} // namespace Utility