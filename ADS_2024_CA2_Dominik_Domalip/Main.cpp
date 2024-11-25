#include <iostream>
#include <cassert>
#include "BinaryTree.h"
#include "KeyValuePair.h"
#include <set>


int main() {
	BinaryTree<KeyValuePair<string, set<string>>> tree; //create a tree of class KeyValuePair with value being a set of strings 
	KeyValuePair<string, set<string>> Awords("A", { "Apple" , "Apostole" });
	KeyValuePair<string, set<string>> Bwords("B", { "Banana", "Bread" });

	tree.add(Awords);
	tree.add(Bwords);

	tree.printInOrder();

	cout << "--------------------------" << endl;

	tree.printPostOrder();

	cout << "--------------------------" << endl;

	tree.printPreOrder();

	/*BinaryTree<KeyValuePair<string, int>> tree;
	KeyValuePair<string, int> Dfour("D", 4);
	KeyValuePair<string, int> Btwo("B", 2);
	KeyValuePair<string, int> Fsix("F", 6);
	KeyValuePair<string, int> Aone("A", 1);
	KeyValuePair<string, int> Efive("E", 5);
	KeyValuePair<string, int> Gseven("G", 7);
	KeyValuePair<string, int> Height("H", 8);

	tree.add(Dfour);
	tree.add(Btwo);
	tree.add(Fsix);
	tree.add(Aone);
	tree.add(Efive);
	tree.add(Gseven);
	tree.add(Height);

	tree.printInOrder();*/

    return 0;
}