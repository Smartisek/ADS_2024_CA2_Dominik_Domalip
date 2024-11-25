#pragma once
#include "BinaryTree.h"
#include "KeyValuePair.h"
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

template <typename K, typename V>
class ReadFromFile {
public:
	ReadFromFile(string& filename);
	void populateTree(BinaryTree<KeyValuePair<K,V>>& tree);
private:
	string filename;
};

template <typename K, typename V>
ReadFromFile<K, V>::ReadFromFile(string& filename) : filename(filename) {} //constructor

/*Similar function for reading data from file into the program as the one from my CA from last year: https://github.com/Smartisek/CA_Bugs_life/blob/main/Board.cpp*/
/*Logic is just read file line by line, split them into words and check if first letter already exist and put new word in the set else just put new entryt*/
template <typename K, typename V>
void ReadFromFile<K, V>::populateTree(BinaryTree<KeyValuePair<K, V>>& tree) {
	ifstream file(filename); //ifstream is used to open the specifed file inside the brackets
	if (!file.is_open()) { //when file does not open correctly throw an exception
		throw invalid_argument("File not found");
		return; //return to stop the function
	}

	string line; //string which will hold each line from the file
	while (getline(file, line)) { //will read line by line until there are no more lines
		stringstream ss(line); //create a string stream from the line 
		string word; //hold each word from line
		while (ss >> word) { //take words from the string stream one by one 
			char firstLetter = word[0]; //we get a character of the word
			if (tree.containsKey(firstLetter)) { //check if tree alrady has this key
				auto& wordsSet = tree.get(firstLetter); //retrieve the set of words linked to this letter
				wordsSet.insert(word); //insert new word into the set 
			}
			else { //key does not yet exist 
				set<string> wordsSet = { word }; //create a new set for words with this letter
				tree.put(firstLetter, wordsSet); //put the new key and value into the tree
			}
		}
	}
	file.close(); //when finished just close the file 
}