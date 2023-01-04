/**
 * @file TaskManager.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2023-01-04
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#include "Utility/AVLTree.hpp"
#include "Utility/FileManager.hpp"

#include <fstream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace Task {

using std::cin;
using std::cout;
using std::endl;
using std::fstream;
using std::shared_ptr;
using std::string;
using std::vector;
using Utility::AVLTree;

static const shared_ptr<AVLTree<int>> tree = std::make_shared<AVLTree<int>>();

inline void init() {
    FileManager::init_all();
}

inline void build_by_vec(const vector<int>& vec) {
    for (auto val : vec) {
        tree->insert(val);
    }
}

inline void first_write_into_file(const vector<int>& vec) {
    if (vec.empty()) {
        return;
    }
    static constexpr int MAX_IN_LINE = 5;
    fstream              file;
    file.open(FileManager::Filename::Data, fstream::out);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open 'data.txt'!");
    }
    int idx = 0;
    for (auto val : vec) {
        if (idx && idx % MAX_IN_LINE == 0) {
            file << endl;
        }
        file << val << " ";
    }
    file << endl;
    file.close();
}

inline bool try_loading_from_file() {
    vector<int> vec;

    // import from file
    fstream file;
    file.open(FileManager::Filename::Data, fstream::in);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open 'data.txt'!");
    }
    int curr = 0;
    while (file >> curr) {
        vec.push_back(curr);
    }
    file.close();

    // build
    if (vec.empty()) {
        return false;
    }
    build_by_vec(vec);
    cout << "Successfully build the tree from `data.txt`!" << endl;
    cout << endl;
    cout << "You can change the file, whose path is => " << endl;
    cout << FileManager::fs::absolute(FileManager::Filename::Data) << endl;
    cout << endl;
    return true;
}

inline void input_by_iostream() {
    string      temp;
    vector<int> vec;
    cout << "Please input integers (separated by space, end with `#`)" << endl;
    cout << ">>> ";
    while (cin >> temp) {
        if (temp == "#") {
            break;
        }
        vec.push_back(std::stoi(temp));
    }
    cout << endl;
    first_write_into_file(vec);
    build_by_vec(vec);
    cout << "Successfully build the tree from `iostream` input!" << endl;
    cout << endl;
}

inline void build() {
    if (!try_loading_from_file()) {
        input_by_iostream();
    }
}

inline void show() {
    cout << "Here are the elements: " << endl;
    tree->print();
    cout << endl;

    cout << "It's size is => " << tree->size() << endl;
    cout << endl;

    cout << "It's height(start from 0) is => " << tree->height() << endl;
    cout << endl;

    cout << "Here's how it looks like while printing in layer: " << endl;
    tree->print_in_layer();

    cout << "Now, we'll assert it's order:" << endl;
    tree->assert_if_in_order();
}

inline void run_all_tasks() {
    init();
    build();
    show();
}

} // namespace Task