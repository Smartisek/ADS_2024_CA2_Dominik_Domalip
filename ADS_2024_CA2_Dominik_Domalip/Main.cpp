#include <iostream>
#include <cassert>
#include "BinaryTree.h"

void testAdd() {
    BinaryTree<int, std::string> tree;
    tree.add(10, "Root");
    tree.add(5, "Left");
    tree.add(15, "Right");
    tree.add(3, "Left Left");
    tree.add(7, "Left Right");

    // Print the tree structure
    tree.printInOrder();


    // Assertions (replace with your test framework's assertion methods)
    int key = 10;
    assert(tree.get(key) == "Root");
    key = 5;
    assert(tree.get(key) == "Left");
    key = 15;
    assert(tree.get(key) == "Right");
    key = 3;
    assert(tree.get(key) == "Left Left");
    key = 7;
    assert(tree.get(key) == "Left Right");

    std::cout << "All add tests passed!" << std::endl;
}

int main() {
    testAdd();
    return 0;
}