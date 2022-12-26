/**
 * @file AVLTreeTest.hpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-26
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#include "../Utility/AVLTree.hpp"

#include <iostream>
#include <vector>

namespace Test {

using std::cout, std::endl;

void AVLTreeTest() {
    Utility::AVLTree<int> tree { 1, 3, 7, 4, 5, 9, 2 };
    tree.print();
    cout << "size: " << tree.get_size() << endl;
    cout << endl;

    // test insert `existing` element
    for (auto toInsert : { 3, 4, 5, 9 }) {
        tree.insert(toInsert);
        tree.print();
        cout << "size: " << tree.get_size() << endl;
        cout << endl;
    }

    // test insert `non-existing` element
    for (auto toInsert : { 0, 6, 8, 10 }) {
        tree.insert(toInsert);
        tree.print();
        cout << "size: " << tree.get_size() << endl;
        cout << endl;
    }

    // test remove `existing` element
    for (auto toRemove : { 3, 4, 5, 9 }) {
        tree.remove(toRemove);
        tree.print();
        cout << "size: " << tree.get_size() << endl;
        cout << endl;
    }

    // test remove `non-existing` element
    for (auto toRemove : { 3, 4, 5, 9 }) {
        tree.remove(toRemove);
        tree.print();
        cout << "size: " << tree.get_size() << endl;
        cout << endl;
    }

    // test copy construct/assignment
    Utility::AVLTree<int> copied = tree;
    copied.print();
    cout << "size: " << copied.get_size() << endl;
    cout << endl;

    // test move construct/assignment
    Utility::AVLTree<int> moved = std::move(copied);
    moved.print();
    cout << "size: " << moved.get_size() << endl;
    cout << endl;
    copied.print();
    cout << "size: " << copied.get_size() << endl;
    cout << endl;
}

} // namespace Test