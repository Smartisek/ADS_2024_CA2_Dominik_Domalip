#pragma once
#include "BSTNode.h"
#include <vector>
using namespace std;

template <class K, class V>
class BinaryTree
{
	void addItemToArray(BSTNode<K, V>* node, int& pos,pair<K,V>* arr);
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
	BSTNode<T>* toBeRemoved = root;
	BSTNode<T>* parent = nullptr;
	bool found = false;

	while (!found && toBeRemoved != nullptr)
	{

		if (toBeRemoved->getKey() == key)
		{

			found = true;
		}
		else
		{
			parent = toBeRemoved;
			if (toBeRemoved->getKey() > key)
			{
				toBeRemoved = toBeRemoved->getLeft();
			}
			else
			{
				toBeRemoved = toBeRemoved->getRight();
			}
		}
	}
	if (!found)
		return false;

	if (toBeRemoved->getLeft() == nullptr || toBeRemoved->getRight() == nullptr)
	{
		BSTNode<K, V>* newChild;
		if (toBeRemoved->getLeft() == nullptr)
		{
			newChild = toBeRemoved->getRight();
		}
		else
		{
			newChild = toBeRemoved->getLeft();
		}
		if (parent == nullptr)
		{
			root = newChild;
		}
		else if (parent->getLeft() == toBeRemoved)
		{
			parent->setLeft(newChild);
		}
		else
		{
			parent->setRight(newChild);
		}
		return true;
	}

	BSTNode<K, V>* smallestParent = toBeRemoved;
	BSTNode<K, V>* smallest = toBeRemoved->getRight();
	while (smallest->getLeft() != nullptr)
	{
		smallestParent = smallest;
		smallest = smallest->getLeft();
	}
	toBeRemoved->setKey(smallest->getKey());
	toBeRemoved->setValue(smallest->getValue());

	if (smallestParent == toBeRemoved)
	{
		smallestParent->setRight(smallest->getRight());
	}
	else
	{
		smallestParent->setLeft(smallest->getRight());
	}

	delete smallest;

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
void BinaryTree<K, V>::clear()
{
	delete root;
	root = nullptr;
}
template <class K, class V>
BinaryTree<K, V>::~BinaryTree()
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