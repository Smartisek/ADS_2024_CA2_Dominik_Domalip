#include <iostream>
#include <cassert>
#include "BinaryTree.h"
#include "KeyValuePair.h"
#include <set>
#include "ReadFromFile.h"
#include "CarData.h"

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

	string filename = "supercars.csv";
	
	ReadFromFile<int, set<CarData>> reader(filename);
	BinaryTree<KeyValuePair<int, set<CarData>>> tree;
	string index = "horsepower";

	reader.populateBasedOnIntIndex(tree, index);
	cout << tree.size() << endl;

	tree.printInOrder();

	ReadFromFile<string, set<CarData>> reader2(filename);
	BinaryTree<KeyValuePair<string, set<CarData>>> tree2;
	string index2 = "model";

	reader2.populateBasedOnStringIndex(tree2, index2);
	cout << tree2.size() << endl;

	tree2.printInOrder();

    return 0;
}