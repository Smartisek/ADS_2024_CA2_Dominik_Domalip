#pragma once
#include "BSTNode.h"
#include <vector>
#include <set>
using namespace std;

template <class T>
class BinaryTree
{
	void addItemToArray(BSTNode<T>* node, int& pos,pair<typename T::key_type, typename T::value_type>* arr);
public:
	// Constructors
	BSTNode<T>* root;
	BinaryTree();
	BinaryTree(const BinaryTree<T>& other);
	BinaryTree<T> operator=(const BinaryTree<T>& other);

	// Functions
	void add(T& item);
	bool remove(T& item);
	void clear();
	int count();
	T& get(T& item);
	bool containsKey(typename T::key_type key);
	typename T::value_type& get(typename T::key_type key);
	set<typename T::key_type> keySet();
	

	// Prints 
	void printInOrder();
	void printInOrder(BSTNode<T>* node);
	void printPreOrder();
	void printPreOrder(BSTNode<T>* node);
	void printPostOrder();
	void printPostOrder(BSTNode<T>* node);
	pair<typename T::key_type, typename T::value_type>* toArray();
	~BinaryTree();
};

template <class T>
BinaryTree<T>::BinaryTree() //default constructor
{
	root = nullptr;
}

template <class T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>& other) //copy constructor
{
	root = nullptr; //initialize the root to null
	if (other.root != nullptr) //if other tree root is not null  
		root = new BSTNode<T>(*other.root); //create a new node copying the root of the other tree
}

template <class T>
BinaryTree<T> BinaryTree<T>::operator=(const BinaryTree<T>& other) //assign one binary tree to another
{
	if (this == &other) { //check if the current object is the same as the one trying to be assigned (check by memory address)
		return *this; //return the current object if it is
	}

	clear(); //clear the current tree to make space for the new one

	if (other.root != nullptr) { // if the other tree root is not null
		root = new BSTNode<T>(*other.root); // create a new node copying others tree rot node by copy constructor
	}
	else { //if the other tree root is null
		root = nullptr; //set the root to null
	}
	return *this; //return the current object
}

template <class T>
void BinaryTree<T>::add(T& item)
{
	if (root == nullptr) //if root is empty just create a new node
	{
		root = new BSTNode<T>(item);
	}
	else //if root is not empty
	{
		root->add(item); //call BSTNode add function onto the root which will correctly set new node in the tree
	}
}

template <class T>
int BinaryTree<T>::count()
{
	if (root == nullptr) //if root is empty return 0
		return 0;
	return root->count(); //call count from BSTNode 
}

template <class T>
bool BinaryTree<T>::containsKey(typename T::key_type key) {
	BSTNode<T>* current = root; //pointer for the start of the tree that will traverse through tree untill finds key 

	while (current != nullptr) {
	if (current->getKey() == key) {
		return true; //if the root is the key return true
	}
	else if (current->getKey() > key) {
		current = current->getLeft(); //if current pointer is more than what looking for then go search left
	}
	else {
		current = current->getRight(); //if current pointer is less than what looking for then go search right
	 }
  }
	return false; // will return false if we dont find it 
	
}

template <class T>
typename T::value_type& BinaryTree<T>::get(typename T::key_type key) {
	BSTNode<T>* current = root; //make a pointer to strat at the root 

	while (current != nullptr) { //same as for containsKey we go until we find the key but instead get a value of that key
		if (current->getKey() == key) {
			return current->getItem().getValue();
		}
		else if (current->getKey() > key) {
			current = current->getLeft();
		}
		else {
			current = current->getRight();
		}
	}
	throw logic_error("Item was not found!"); //if we dont find the key throw an error
}

template <class T>
void collectKeys(BSTNode<T>* node, set<typename T::key_type>& keySet) { //helper function not available for user
	if (node != nullptr) { //base case to stop
		/*IN-ORDER TRAVERS*/
		collectKeys(node->getLeft(), keySet); //recursively go left
		keySet.insert(node->getItem().getKey()); //insert key into the set
		collectKeys(node->getRight(), keySet); //go recursively right
	}
}

template <class T>
set<typename T::key_type> BinaryTree<T>::keySet() {
	set<typename T::key_type> keySet; //make set where to store 
	collectKeys(root, keySet); //call helper function to collect keys
	return keySet; //return the set with keys 
}


template <class T>
bool BinaryTree<T>::remove(T& item)
{
	/******Visualisation for this alghorithm: https://www.youtube.com/watch?v=DkOswl0k7s4 ******/
	/*Help Variables*/
	BSTNode<T>* toBeRemoved = root; //points to the node needed to remove
	BSTNode<T>* parent = nullptr; //will point to the parent of toBeRemoved, keeps track when traversing tree
	bool found = false; //check if we found needed node

	while (!found && toBeRemoved != nullptr) //when node is not yet found and root is not empty
	{

		if (toBeRemoved->getItem().getKey() == item.getKey()) //check for when the key is actually the first node which is root 
		{

			found = true; //was found
		}
		else
		{
			parent = toBeRemoved; //set the parent to the current node
			if (toBeRemoved->getItem().getKey() > item.getKey()) //check if the current node's key is more than what we are looking for
			{
				toBeRemoved = toBeRemoved->getLeft(); //when yes, move to the left child and parent is the previous node
			}
			else
			{
				toBeRemoved = toBeRemoved->getRight(); //when key is less than the current node, move to the right child
			}
		}
	} //exits while loop when we found node we are loking for

	//node is not present in this tree
	if (!found)
		return false;

	/***Remove when node has max one child***/
	if (toBeRemoved->getLeft() == nullptr || toBeRemoved->getRight() == nullptr) //check if node has max one child
	{
		/*Deciding on newChild*/
		BSTNode<T>* newChild; //new pointer will point to the child of the node to be removed
		if (toBeRemoved->getLeft() == nullptr) //if the node to be removed does not have left kid
		{
			newChild = toBeRemoved->getRight(); //set the new child to right child
		}
		else //node to be removed does not have right child
		{
			newChild = toBeRemoved->getLeft(); //set the new child to left child
		}

		/*Giving a newChild to a parent instead of toBeRemoved node*/
		if (parent == nullptr) //when node to be removed is the root 
		{
			root = newChild; //update the root to be the new child 
		}
		else if (parent->getLeft() == toBeRemoved) //when parents left child is what we are looking for
		{
			parent->setLeft(newChild); //change the left child from toBeRemoved to newChild 
		}
		else //parents right child is the node needed to be removed 
		{
			parent->setRight(newChild); //set the right child to be the new child
		}
		return true; //return true when node was removed
	}

	/*Logic for removing node with TWO CHILDREN*/
	/*Another way could be to find the biggest node in left subtree*/
	BSTNode<T>* smallestParent = toBeRemoved; //will keep track of the parent of the smallest node
	BSTNode<T>* smallest = toBeRemoved->getRight(); //starts as right child of node to be removed
	//find the smallest node in the right subtree
	while (smallest->getLeft() != nullptr)
	{
		smallestParent = smallest; //set the parent of the smallest node to be the current smallest node
		smallest = smallest->getLeft();//found the smallest node in the right subtree
	}
	toBeRemoved->getItem().setKey(smallest->getItem().getKey()); //change toBeRemoved node key to be the smallest one in right subtree
	toBeRemoved->getItem().setValue(smallest->getItem().getValue());  //change toBeRemoved node value to be the smallest one in right subtree

	if (smallestParent == toBeRemoved) //when smallestParent is same node as to be removed
	{
		smallestParent->setRight(smallest->getRight()); //right child of smallest parent is now the right child of smallest
	}
	else //when smallestParent is not the same as toBeRemoved
	{
		smallestParent->setLeft(smallest->getRight()); //left child of smallest parent is now the right child of smallest
	}

	delete smallest; //delete the smallest node
	return true; //return true when node was removed

}

template <class T>
T& BinaryTree<T>::get(T& item)
{
	BSTNode<T>* current = root; //create a pointer node starting from the roor 

	while (current != nullptr) //until found do below 
	{
		if (current == nullptr) //stop the while, means tree is empty
			break;

		if (current->getItem().getKey() == item.getKey()) //if root is the key looking for then return the value 
			return current->getItem();

		else if (current->getItem().getKey() > item.getKey()) //if the root is more than the key 
			current = current->getLeft(); //go left and find the key
		else //if the root is less than the key
			current = current->getRight(); //go right and find the key
	}
	throw logic_error("Item was not found!");
}

template <class T>
void BinaryTree<T>::addItemToArray(BSTNode<T>* node, int& pos, pair<typename T::key_type, typename T::value_type>* arr) //help function for toArray
{
	//This will add pair into array inorder traversal of the tree in sorted order
	if (node != nullptr) //base case for recurison 
	{
		addItemToArray(node->getLeft(), pos, arr); //recursively call itself on the left child of current node at position into arr
		arr[pos] = make_pair(node->getItem().getKey(), node->getItem().getValue()); //add both key and value to array at posiotin pos
		pos++; //go next position
		addItemToArray(node->getRight(), pos, arr); //recursively call itself on the right child of current node at position into arr
	}

}

template <class T>
pair<typename T::key_type, typename T::value_type>* BinaryTree<T>::toArray()
{
	T* arr = new T[root->count()]; //new array of size of tree
	int pos = 0; //start at 0
	addItemToArray(root, pos, arr); //call function above 
	return arr;
}

template <class T>
void BinaryTree<T>::clear() //public clear function using private helper function
{
	if (root != nullptr) {
		root->clear(); //call the clear function from BSTNode
		delete root;
		root = nullptr;
	}
}



template <class T>
BinaryTree<T>::~BinaryTree() //Destructor Function for memory management
{
	clear(); //call the clear function to delete all nodes in the tree, clear handles all the memory alredy no need for redundancy
}

template <class T>
void BinaryTree<T>::printInOrder()
{
	this->printInOrder(root);
	cout << endl;
}

template <class T>
void BinaryTree<T>::printInOrder(BSTNode<T>* node)
{
	
	if (node != nullptr) { // base case for the recursive function
		printInOrder(node->getLeft()); //call the recursive funtion for the left child of current node 
		cout << node->getItem().getKey() << ": " << node->getItem().getValue() << " "; //print the value of the current node 
		printInOrder(node->getRight()); // call the recursive funtion for the right child of current node
	}
	// first visit left subtree, then print the current node and then visit right subtree
}

template <class T>
void BinaryTree<T>::printPreOrder()
{
	this->printPreOrder(root);
	cout << endl;
}

template <class T>
void BinaryTree<T>::printPreOrder(BSTNode<T>* node)
{
	if (node != nullptr) {
		cout << node->getItem().getKey() << ": " << node->getItem().getValue() << " "; //print the value of the current node
		printPreOrder(node->getLeft()); //call the recursive funtion for the left child of current node
		printPreOrder(node->getRight()); // call the recursive funtion for the right child of current node
	}
	// first print the current node , then visit left subtree and then right subtree
}

template <class T>
void BinaryTree<T>::printPostOrder()
{
	this->printPostOrder(root);
	cout << endl;
}

template <class T>
void BinaryTree<T>::printPostOrder(BSTNode<T>* node)
{
	if (node != nullptr) {
		printPostOrder(node->getLeft()); //call the recursive funtion for the left child of current node
		printPostOrder(node->getRight()); // call the recursive funtion for the right child of current node
		cout << node->getItem().getKey() << ": " << node->getItem().getValue() << " "; //print the value of the current node
	}
}