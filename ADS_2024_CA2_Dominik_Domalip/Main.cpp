#include <iostream>
#include <cassert>
#include "BinaryTree.h"
#include "KeyValuePair.h"
#include <set>
#include "ReadFromFile.h"
#include "CarData.h"

using namespace std;
/*Functors for populating the tree https://www.programiz.com/cpp-programming/functors */
class PopulateTreeByIntIndexFunctor {
public:
	void operator()(BinaryTree<KeyValuePair<int, set<CarData>>>& tree, string& index, string& filename, ReadFromFile<int, set<CarData>>& reader) {
		reader.populateBasedOnIntIndex(tree, index);
	}
};

class PopulateTreeByStringIndexFunctor {
public:
	void operator()(BinaryTree<KeyValuePair<string, set<CarData>>>& tree, string& index, string& filename, ReadFromFile<string, set<CarData>>& reader) {
		reader.populateBasedOnStringIndex(tree, index);
	}
};

/*PART2 Populate tree with Characters by reading a text file and create a set of words releated to that character*/
void PopulateByCharacters(BinaryTree<KeyValuePair<char, set<string>>>& tree, string& filename, ReadFromFile<char, set<string>>& reader) {
	
	reader.populateTreeCharacters(tree);

	tree.printInOrder();
	tree.clear(); //manage memory and clear 
}

/*PART4 Function that will print out index and how many each has rows, this is done by using the toArray function from binaryTree which traverses in orrder*/
template<typename K, typename V>
void DisplayIndex(BinaryTree<KeyValuePair<K, V>>& tree) {
	int size = tree.size(); //get size to stop for loop
	auto* array = tree.toArray(); //getr array, auto gets the type itself for the array
	//go through the array
	for (int i = 0; i < size; i++) {
		cout << array[i].first << ": " << array[i].second.size() << " rows" << endl;
	}
	cout << endl;
	delete[] array; //delete the array to free memory, not deleting tree yet because will be used for subset
}

/*PART4 Function that will go through values and display them based on specified index*/
template<typename K, typename V>
void DisplaySubset(BinaryTree<KeyValuePair<K, V>>& tree, K& key) {
	if (tree.containsKey(key)) { //check if we have key in tree
		auto value = tree[key]; //using the [] operator that already gets the value of the key 
		cout << "** SUBSET: " << key << " **" << endl;
		for (auto& item : value) { //go through the set of values
			cout << item << endl;
		}
	}
	else {
		cout << "NO KEY IN TREE." << endl;
	}
	tree.clear(); //after we display the subset we can get rid of the tree so there are no duplicates or left overs
	//if we still needed to manipulate the tree i would not clear but since after viewing we do not need anymore we can manage memory here 
}


int main() {
	/*File names*/
	string filenameCSV = "supercars.csv";
	string filenameTXT = "words.txt";

	/*Reader objects from ReaderFromFile.h used to read data from files, we need one for each type*/
	ReadFromFile<char, set<string>> wordReader(filenameTXT);
	ReadFromFile<int, set<CarData>> intReader(filenameCSV);
	ReadFromFile<string, set<CarData>> stringReader(filenameCSV);

	int input = 0;
	
	/*Using Interface with do while loop that I used in my last year project as well : https://github.com/Smartisek/oop-ca3-dominik-domalip/blob/master/src/CA3_Question7.java */
	do {
		cout << "---------------------------------------------------" << endl;
		cout << "CONSOLE COMMANDS" << endl;
		cout << "1. View All Unique Words From words.txt " << endl;
		cout << "2. Index supercars.csv and View Data" << endl;
		cout << "3. EXIT" << endl;
		cout << "---------------------------------------------------" << endl;
		cout << "Enter Command: ";
		cin >> input;
		if (input == 1) {
			BinaryTree<KeyValuePair<char, set<string>>> wordTree;
			PopulateByCharacters(wordTree, filenameTXT, wordReader);
		}
		else if (input == 2) {
			string index;
			cout << "---------------------------------------------------" << endl;
			cout << "This database contains information about supercars." << endl;
			cout << "You can choose to index the database by 'manufacturer', 'year', 'horsepower', 'startingPrice' or 'color'." << endl;
			cout << "---------------------------------------------------" << endl;
			cout << "INDEX by: ";
			cin >> index;
			if (index == "manufacturer" || index == "color" || index == "model") {	
				BinaryTree<KeyValuePair<string, set<CarData>>> treeString;
				PopulateTreeByStringIndexFunctor populateTreeByStringIndex; //creating functor instance to populate tree
				populateTreeByStringIndex(treeString, index, filenameCSV, stringReader); //using functor to populate tree
				cout << endl;
				DisplayIndex(treeString);
				cout << "---------------------------------------------------" << endl;
				cout << "Enter key subset you want to view: ";
				string key;
				cin >> key;
				DisplaySubset(treeString, key);
			}
			else if (index == "horsepower" || index == "year" || index == "startingPrice") {
				BinaryTree<KeyValuePair<int, set<CarData>>> treeInt;
				PopulateTreeByIntIndexFunctor populateTreeByIntIndex; //create functor
				populateTreeByIntIndex(treeInt, index, filenameCSV, intReader); //use functor
				cout << endl;
				DisplayIndex(treeInt);
				cout << "---------------------------------------------------" << endl;
				cout << "Enter key subset you want to view: ";
				int key;
				cin >> key;
				DisplaySubset(treeInt, key);
			}
		}

	} while (input != 3);

    return 0;
}