#pragma once
#include "BSTNode.h"
#include <vector>
using namespace std;

template <class K, class V>
class BinaryTree
{
	void addItemToArray(BSTNode<K, V>* node, int& pos,pair<K,V>* arr);
	void clear(BSTNode<K, V>* node); //private helper function that will do the logic and will be caller by clear below
public:
	BSTNode<K, V>* root;
	BinaryTree();
	BinaryTree(const BinaryTree<K, V>& other);
	BinaryTree<K, V> operator=(const BinaryTree<K, V>& other);
	void add(K key, V value);
	bool remove(K& key);
	void clear();
	int count();
	V& get(K& key);

	void printInOrder();
	void printInOrder(BSTNode<K, V>* node);
	void printPreOrder();
	void printPreOrder(BSTNode<K, V>* node);
	void printPostOrder();
	void printPostOrder(BSTNode<K, V>* node);
	pair<K, V>* toArray();
	~BinaryTree();
};

template <class K, class V>
BinaryTree<K, V>::BinaryTree()
{
	root = nullptr;
}

template <class K, class V>
BinaryTree<K, V>::BinaryTree(const BinaryTree<K, V>& other) //copy constructor
{
	root = nullptr; //initialize the root to null
	if (other.root != nullptr) //if other tree root is not null  
		root = new BSTNode<K, V>(*other.root); //create a new node copying the root of the other tree
}

template <class K, class V>
BinaryTree<K, V> BinaryTree<K, V>::operator=(const BinaryTree<K, V>& other) //assign one binary tree to another
{
	if (this == &other) //check if the current object is the same as the one trying to be assigned (check by memory address)
		return *this; //return the current object if it is

	if (other.root != nullptr) // if the other tree root is not null
		root = new BSTNode<K, V>(*other.root); // create a new node copying others tree rot node by copy constructor
	else //if the other tree root is null
		root = nullptr; //set the root to null
	return *this; //return the current object

}

template <class K, class V>
void BinaryTree<K, V>::add(K key, V value)
{
	if (root == nullptr) //if root is empty just create a new node
	{
		root = new BSTNode<K, V>(key, value);
	}
	else //if root is not empty
	{
		root->add(key, value); //call BSTNode add function onto the root which will correctly set new node in the tree
	}
}

template <class K, class V>
int BinaryTree<K, V>::count()
{
	if (root == nullptr) //if root is empty return 0
		return 0;
	return root->count(); //call count from BSTNode 
}

template <class K, class V>
bool BinaryTree<K, V>::remove(K& key)
{
	/******Visualisation for this alghorithm: https://www.youtube.com/watch?v=DkOswl0k7s4 ******/
	/*Help Variables*/
	BSTNode<K, V>* toBeRemoved = root; //points to the node needed to remove
	BSTNode<K, V>* parent = nullptr; //will point to the parent of toBeRemoved, keeps track when traversing tree
	bool found = false; //check if we found needed node

	while (!found && toBeRemoved != nullptr) //when node is not yet found and root is not empty
	{

		if (toBeRemoved->getKey() == key) //check for when the key is actually the first node which is root 
		{

			found = true; //was found
		}
		else
		{
			parent = toBeRemoved; //set the parent to the current node
			if (toBeRemoved->getKey() > key) //check if the current node's key is more than what we are looking for
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
		BSTNode<K, V>* newChild; //new pointer will point to the child of the node to be removed
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
		delete toBeRemoved; //free the memory when not needed anymore
		return true; //return true when node was removed
	}

	/*Logic for removing node with TWO CHILDREN*/
	/*Another way could be to find the biggest node in left subtree*/
	BSTNode<K, V>* smallestParent = toBeRemoved; //will keep track of the parent of the smallest node
	BSTNode<K, V>* smallest = toBeRemoved->getRight(); //starts as right child of node to be removed
	//find the smallest node in the right subtree
	while (smallest->getLeft() != nullptr)
	{
		smallestParent = smallest; //set the parent of the smallest node to be the current smallest node
		smallest = smallest->getLeft();//found the smallest node in the right subtree
	}
	toBeRemoved->setKey(smallest->getKey()); //change toBeRemoved node key to be the smallest one in right subtree
	toBeRemoved->setValue(smallest->getValue());  //change toBeRemoved node value to be the smallest one in right subtree

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

template <class K, class V>
V& BinaryTree<K, V>::get(K& key)
{
	BSTNode<K, V>* current = root; //create a pointer node starting from the roor 

	while (current != nullptr) //until found do below 
	{
		if (current == nullptr) //stop the while, means tree is empty
			break;

		if (current->getKey() == key) //if root is the key looking for then return the value 
			return current->getValue();

		else if (current->getKey() > key) //if the root is more than the key 
			current = current->getLeft(); //go left and find the key
		else //if the root is less than the key
			current = current->getRight(); //go right and find the key
	}
	throw logic_error("Item was not found!");
}

template <class K, class V>
void BinaryTree<K, V>::addItemToArray(BSTNode<K, V>* node, int& pos, pair<K, V>* arr) //help function for toArray
{
	//This will add pair into array inorder traversal of the tree in sorted order
	if (node != nullptr) //base case for recurison 
	{
		addItemToArray(node->getLeft(), pos, arr); //recursively call itself on the left child of current node at position into arr
		arr[pos] = make_pair(node->getKey(), node->getValue()); //add both key and value to array at posiotin pos
		pos++; //go next position
		addItemToArray(node->getRight(), pos, arr); //recursively call itself on the right child of current node at position into arr
	}

}

template <class K, class V>
pair<K, V>* BinaryTree<K, V>::toArray()
{
	pair<K, V>* arr = new pair<K, V>[root->count()]; //create a new array of type pair<K, V> with size of count funcion
	int pos = 0; //start from 0
	addItemToArray(root, pos, arr); //call the helper function to add items to array
	return arr; //return the array
}

template <class K, class V>
void BinaryTree<K, V>::clear() //public clear function using private helper function
{
	clear(root); //call function with the clear logic
	root = nullptr; //set the root to null after clearing
}

template<class K, class V>
void BinaryTree<K, V>::clear(BSTNode<K, V>* node) //private helper function for logic delete
{
	if (node != nullptr) { //base case, when node is not empty
		clear(node->getLeft()); //call the recursive function for the left child of current node
		clear(node->getRight()); //call the recursive function for the right child of current node
		delete node; //finaly delete current node 
	}
}

template <class K, class V>
BinaryTree<K, V>::~BinaryTree() //Destructor Function for memory management
{
	if (root != nullptr)
	{
		delete root;
		root = nullptr;
	}
}

template <class K, class V>
void BinaryTree<K, V>::printInOrder()
{
	this->printInOrder(root);
	cout << endl;
}

template <class K, class V>
void BinaryTree<K,V>::printInOrder(BSTNode<K,V>* node)
{
	
	if (node != nullptr) { // base case for the recursive function
		printInOrder(node->getLeft()); //call the recursive funtion for the left child of current node 
		cout << node->getKey() << ": " << node->getValue() << " "; //print the value of the current node 
		printInOrder(node->getRight()); // call the recursive funtion for the right child of current node
	}
	// first visit left subtree, then print the current node and then visit right subtree
}

template <class K, class V>
void BinaryTree<K, V>::printPreOrder()
{
	this->printPreOrder(root);
	cout << endl;
}

template <class K, class V>
void BinaryTree<K, V>::printPreOrder(BSTNode<K, V>* node)
{
	if (node != nullptr) {
		cout << node->getKey() << ": " << node->getValue() << " "; //print the value of the current node
		printPreOrder(node->getLeft()); //call the recursive funtion for the left child of current node
		printPreOrder(node->getRight()); // call the recursive funtion for the right child of current node
	}
	// first print the current node , then visit left subtree and then right subtree
}

template <class K, class V>
void BinaryTree<K, V>::printPostOrder()
{
	this->printPostOrder(root);
	cout << endl;
}

template <class K, class V>
void BinaryTree<K, V>::printPostOrder(BSTNode<K, V>* node)
{
	if (node != nullptr) {
		printPostOrder(node->getLeft()); //call the recursive funtion for the left child of current node
		printPostOrder(node->getRight()); // call the recursive funtion for the right child of current node
		cout << node->getKey() << ": " << node->getValue() << " "; //print the value of the current node
	}
}