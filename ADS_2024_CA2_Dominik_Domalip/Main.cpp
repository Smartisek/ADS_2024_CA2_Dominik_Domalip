#include <iostream>
#include <cassert>
#include "BinaryTree.h"
#include "KeyValuePair.h"
#include <set>
#include "ReadFromFile.h"


int main() {
	string filename = "words.txt";
    BinaryTree<KeyValuePair<char, set<string>>> tree;

	ReadFromFile<char, set<string>> reader(filename);
	reader.populateTree(tree);

	cout << tree.size() << endl;

	tree.printInOrder();

    return 0;
}