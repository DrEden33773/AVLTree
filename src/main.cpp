/**
 * @file main.cpp
 * @author Eden (edwardwang33773@gmail.com)
 * @brief
 * @version 0.1
 * @date 2022-12-26
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "TaskManager.hpp"
#include "Test/AVLTreeTest.hpp"

int main(int argc, char** argv) {
    // Test::AVLTreeTest();
    Task::run_all_tasks();
    return 0;
}
