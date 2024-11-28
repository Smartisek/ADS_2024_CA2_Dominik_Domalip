#include <iostream>
#include <cassert>
#include "BinaryTree.h"
#include "KeyValuePair.h"
#include <set>
#include "ReadFromFile.h"
#include "CarData.h"

using namespace std;

/*PART2 Populate tree with Characters by reading a text file and create a set of words releated to that character*/
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

/*Function that will print out index and how many each has rows, this is done by using the toArray function from binaryTree which traverses in orrder*/
template<typename K, typename V>
void DisplayIndex(BinaryTree<KeyValuePair<K, V>>& tree) {
	int size = tree.size(); //get size to stop for loop
	auto* array = tree.toArray(); //getr array, auto gets the type itself for the array
	//go through the array
	for (int i = 0; i < size; i++) {
		cout << array[i].first << ": " << array[i].second.size() << " rows" << endl;
	}

	delete[] array; //delete the array to free memory
}


void PopulateTreeByIntIndex(BinaryTree<KeyValuePair<int, set<CarData>>>& tree, string& index, string& filename) {
	ReadFromFile<int, set<CarData>> reader(filename);
	reader.populateBasedOnIntIndex(tree, index);
}

void PopulateTreeByStringIndex(BinaryTree<KeyValuePair<string, set<CarData>>>& tree, string& index, string& filename) {
	ReadFromFile<string, set<CarData>> reader(filename);
	reader.populateBasedOnStringIndex(tree, index);
}

int main() {

	string filename = "supercars.csv";
	

	string index;

	cout << "This database contains information about supercars." << endl;
	cout << "You can choose to index the database by 'manufacturer', 'year', 'horsepower', 'startingPrice or 'color'." << endl;
	cout << "INDEX by: ";
	cin >> index;

	if (index == "manufacturer" || index == "color" || index == "model") {
		BinaryTree<KeyValuePair<string, set<CarData>>> tree;
		PopulateTreeByStringIndex(tree, index, filename);
		DisplayIndex(tree);
	}
	else if (index == "horsepower" || index == "year" || index == "strartingPrice") {
		BinaryTree<KeyValuePair<int, set<CarData>>> tree;
		PopulateTreeByIntIndex(tree, index, filename);
		DisplayIndex(tree);
	}
	else {
		cout << "INVALID INDEX" << endl;
	}









	//ReadFromFile<int, set<CarData>> reader(filename);
	//BinaryTree<KeyValuePair<int, set<CarData>>> tree;
	//string index = "horsepower";

	//reader.populateBasedOnIntIndex(tree, index);
	//cout << tree.size() << endl;
	////displayIndex(tree);
	////tree.printInOrder();

	//ReadFromFile<string, set<CarData>> reader2(filename);
	//BinaryTree<KeyValuePair<string, set<CarData>>> tree2;
	//string index2 = "manufacturer";

	//reader2.populateBasedOnStringIndex(tree2, index2);
	//cout << tree2.size() << endl;
	//displayIndex(tree2);
	////tree2.printInOrder();

    return 0;
}