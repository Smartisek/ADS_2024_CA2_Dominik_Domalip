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
BinaryTree<K, V>::BinaryTree(const BinaryTree<K, V>& other)
{
	root = nullptr;
	if (other.root != nullptr)
		root = new BSTNode<K, V>(*other.root);
}

template <class K, class V>
BinaryTree<K, V> BinaryTree<K, V>::operator=(const BinaryTree<K, V>& other)
{
	if (this == &other)
		return *this;
	if (other.root != nullptr)
		root = new BSTNode<K, V>(*other.root);
	else
		root = nullptr;
	return *this;

}

template <class K, class V>
void BinaryTree<K, V>::add(K key, V value)
{
	if (root == nullptr)
	{
		root = new BSTNode<K, V>(key, value);
	}
	else
	{
		root->add(key, value);
	}
}

template <class K, class V>
int BinaryTree<K, V>::count()
{
	if (root == nullptr)
		return 0;
	return root->count();
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
	bool found = false;
	BSTNode<K, V>* current = root;
	while (!found)
	{
		if (current == nullptr)
			break;
		if (current->getKey() == key)
			return current->getValue();
		else if (current->getKey() > key)
			current = current->getLeft();
		else
			current = current->getRight();
	}
	throw logic_error("Item was not found!");
}
template <class K, class V>
void BinaryTree<K, V>::addItemToArray(BSTNode<K, V>* node, int& pos, pair<K, V>* arr)
{
	if (node != nullptr)
	{
		addItemToArray(node->getLeft(), pos, arr);
		arr[pos] = make_pair(node->getKey(), node->getValue());
		pos++;
		addItemToArray(node->getRight(), pos, arr);
	}

}

template <class K, class V>
pair<K, V>* BinaryTree<K, V>::toArray()
{
	pair<K, V>* arr = new pair<K, V>[root->count()];
	int pos = 0;
	addItemToArray(root, pos, arr);
	return arr;
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
	clear(); //call the clear function to delete all nodes and set root to null
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