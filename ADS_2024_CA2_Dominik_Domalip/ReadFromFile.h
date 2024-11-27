#pragma once
#include "BinaryTree.h"
#include "KeyValuePair.h"
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>

using namespace std;

template <typename K, typename V>
class ReadFromFile {
public:
	ReadFromFile(string& filename);
	void populateTreeCharacters(BinaryTree<KeyValuePair<K,V>>& tree);
private:
	string filename;
};

template <typename K, typename V>
ReadFromFile<K, V>::ReadFromFile(string& filename) : filename(filename) {} //constructor

/*Help function to remove special characters inspiration from: https://www.youtube.com/watch?v=pQka0CyFa7o */
string RemoveSpecialCharacters(const string& roughWord) {
	string cleanWord; //what we will return
	for (char ch : roughWord) { //go through each character 
		if (isalnum(ch)) { //funbction from cctype library that will check if character is "alphanumeric" meaning only letters and numbers 
			ch = tolower(ch); //make character lowercase 
			cleanWord += ch; //if character is alnum then we can add to the clean word string
		}
	}
	return cleanWord; //return finished word 
	//in the set we still will have , after the word but that is what we want and is handled in KeyValuePair overload operator for < <
}

/*For reading text file for Part 2: Characters and all the words asssociated*/
/*Similar function for reading data from file into the program as the one from my CA from last year: https://github.com/Smartisek/CA_Bugs_life/blob/main/Board.cpp*/
/*Logic is just read file line by line, split them into words and check if first letter already exist and put new word in the set else just put new entryt*/
template <typename K, typename V>
void ReadFromFile<K, V>::populateTreeCharacters(BinaryTree<KeyValuePair<K, V>>& tree) {
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
			word = RemoveSpecialCharacters(word); //remove special characters from the word
			if (!word.empty()) {
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
			
}
	file.close(); //when finished just close the file 
}
