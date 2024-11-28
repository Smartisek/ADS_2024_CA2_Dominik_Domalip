#pragma once
#include "BinaryTree.h"
#include "KeyValuePair.h"
#include "CarData.h"
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
	void populateBasedOnStringIndex(BinaryTree<KeyValuePair<K, V>>& tree, string& index);
	void populateBasedOnIntIndex(BinaryTree<KeyValuePair<K, V>>& tree, string& index);
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


/*For part 4 I have two functions for populating the tree with data from my supercars.csv (generated with chatgpt)
The reason for having two functions is because I did not find a way to do it with only one
I tried with template for K key however I was getting convert errors whenever the index was an int
Unfortunately I did not find a way to get it working with template but this is still fully functional for part 4 in main*/
template <typename K, typename V>
void ReadFromFile<K, V>::populateBasedOnStringIndex(BinaryTree<KeyValuePair<K, V>>& tree, string& index) {
	ifstream file(filename); //same as above open the file check
	if (!file.is_open()) { 
		throw invalid_argument("File not found"); //exception for not found 
		return; //stop
	}

	string line;
	while (getline(file, line)) {
		stringstream ss(line); //string stream for the line 
		/*Variables for storing the data based on cardata*/
		string model, manufacturer, color;
		int year, horsepower, startingPrice;
		//temporary store for integers 
		string yearTemp, horsepowerTemp, startingPriceTemp;
		//read in words by splitting with ,
		getline(ss, model, ',');
		getline(ss, manufacturer, ',');
		getline(ss, yearTemp, ',');
		getline(ss, horsepowerTemp, ',');
		getline(ss, color, ',');
		getline(ss, startingPriceTemp, ',');

		//convert strings to int with stoi and double  with stod 
		try {
			year = stoi(yearTemp);
			horsepower = stoi(horsepowerTemp);
			startingPrice = stoi(startingPriceTemp);
		}
		catch (const exception& e) {
			cerr << "Error parsing line: " << line << endl;
			cerr << "Exception: " << e.what() << endl;
			continue; // Skip this line and continue with the next
		}
		

		CarData car(model, manufacturer, year, horsepower, color, startingPrice); //create the entity 

		//determine the index passed in from user 
		K key;
		if (index == "model") {
			key = car.getModel();
		}
		else if (index == "manufacturer") {
			key = car.getManufacturer();
		}
		else if (index == "color") {
			key = car.getColor();
		}
		else {
			cerr << "Invalid index for string key" << endl;
			continue; // Skip this line and continue with the next
		}
		//make a set with car data and use put function that will handle alredy present key and not present
		set<CarData> carSet = { car };
		tree.put(key, carSet);
	}
	file.close(); // When finished, close the file 
}

template <typename K, typename V>
void ReadFromFile<K, V>::populateBasedOnIntIndex(BinaryTree<KeyValuePair<K, V>>& tree, string& index) {
	ifstream file(filename); //same as above open the file check
	if (!file.is_open()) {
		throw invalid_argument("File not found"); //exception for not found 
		return; //stop
	}

	string line;
	while (getline(file, line)) {
		stringstream ss(line); //string stream for the line 
		/*Variables for storing the data based on CarData*/
		string model, manufacturer, color;
		int year, horsepower, startingPrice;
		//temporary store for integers 
		string yearTemp, horsepowerTemp, startingPriceTemp;
		//read in words by splitting with ,
		getline(ss, model, ',');
		getline(ss, manufacturer, ',');
		getline(ss, yearTemp, ',');
		getline(ss, horsepowerTemp, ',');
		getline(ss, color, ',');
		getline(ss, startingPriceTemp, ',');

		//convert strings to int with stoi and double  with stod 
		try {
			year = stoi(yearTemp);
			horsepower = stoi(horsepowerTemp);
			startingPrice = stoi(startingPriceTemp);
		}
		catch (const exception& e) {
			cerr << "Error parsing line: " << line << endl;
			cerr << "Exception: " << e.what() << endl;
			continue; // Skip this line and continue with the next
		}

		CarData car(model, manufacturer, year, horsepower, color, startingPrice); //create the entity 

		//determine the index passed in from user 
		int key;
		if (index == "year") {
			key = car.getYear(); // use int for year
		}
		else if (index == "horsepower") {
			key = car.getHorsepower(); // use int for horsepower
		}
		else if (index == "startingPrice") {
			key = car.getStartingPrice(); // use int for startingPrice
		}
		else {
			cerr << "Invalid index for integer key" << endl;
			continue; // Skip this line and continue with the next
		}
		//make a set with car data and use put function that will handle alredy present key and not present
		set<CarData> carSet = { car };
		tree.put(key, carSet);
	}
	file.close(); // When finished, close the file 
}