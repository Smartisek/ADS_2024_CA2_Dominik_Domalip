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

void testOperator() {
 {
        BSTNode<std::string, int> node1("A", 1);
        node1.add("B", 2);
        node1.add("C", 3);

        BSTNode<std::string, int> node2;
        node2 = node1;

        assert(node2.getKey() == "A");
        assert(node2.getValue() == 1);
        assert(node2.getLeft()->getKey() == "B");
        assert(node2.getLeft()->getValue() == 2);
        assert(node2.getRight()->getKey() == "C");
        assert(node2.getRight()->getValue() == 3);
    }
}

int main() {
    testOperator();
    cout << "tests passed" << endl;
    return 0;
}