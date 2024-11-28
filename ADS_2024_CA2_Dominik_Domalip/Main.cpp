#include <iostream>
#include <cassert>
#include "BinaryTree.h"
#include "KeyValuePair.h"
#include <set>
#include "ReadFromFile.h"

using namespace std;

void PopulateByCharacters() {
	string filename = "words.txt";
	BinaryTree<KeyValuePair<char, set<string>>> tree;

	ReadFromFile<char, set<string>> reader(filename);
	reader.populateTreeCharacters(tree);

	cout << tree.size() << endl;

	tree.printInOrder();

	tree.clear();

	cout << tree.size() << endl;
}

int main() {
	PopulateByCharacters();
    return 0;
}