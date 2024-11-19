#pragma once
#include <iostream>
#include "KeyValuePair.h"

using namespace std;

template <class T>
class BSTNode
{
	/*Pointers*/
	BSTNode<T>* parent;
	BSTNode<T>* left;
	BSTNode<T>* right;
	/*Data inside node*/
	T data;

public:
	/*Constructors*/
	BSTNode();
	BSTNode(const BSTNode<T>& other); //copy constructor
	BSTNode<T>& operator=(const BSTNode<T>& other);
	BSTNode(T data);
	/*Setters*/
	void setItem(T item);
	void setLeft(BSTNode<T>* l);
	void setRight(BSTNode<T>* r);
	/*Getters*/
	BSTNode<T>* getParent();
	BSTNode<T>* getLeft();
	BSTNode<T>* getRight();

	T& getItem();
	/*Functions*/ 
	int count();
	void add(const T& item);
	void clear();
	/*Destructor*/
	~BSTNode();
	
	//getters for key and value
	auto getKey() const -> decltype(data.getKey()) {
		return data.getKey();
	}

	auto getValue() const -> decltype(data.getValue()) {
		return data.getValue();
	}
};

template <class T>
BSTNode<T>::BSTNode(const BSTNode<T>& other) //copy constructor making a deeep copy copy with subtrees
{
	parent = nullptr; //parent is set to null as the new node is not connected to any tree yet
	left = right = nullptr; //new node starts with null pointers 

	//copy the data from the other node to the new node
	data = other.data; 

	if (other.left != nullptr) { //check if other have left child 
		//if yes then create a new node copying the left child, this will be done recursively until the are no left chidlren 
		this->left = new BSTNode<T>(*other.left);
		this->left->parent = this; //set parent of the new node to be current node 
	}

	if (other.right != nullptr){ //check if there are any right chidlren 
		//if yes then create a new node copying the right child, this will be done recursively until there are no right children
		this->right = new BSTNode<T>(*other.right);
		this->right->parent = this; //set parent of the new node to be current node
		}
}

template <class T>
BSTNode<T>& BSTNode<T>::operator=(const BSTNode<T>& other)
{
	if (this == &other) //check if the current object is the same as the one trying to be assigned 
		return *this; //return the current object if it is 

	//delete the current tree to make space for the new one
	clear();
	//copy the data from the other node to the new node
	data = other.data;

	//discard any existing children 
	left = right = nullptr;

	//if the left side has a child create a new node and copy the left child by copy constructor which will recursively copy the entire left side
	if (other.left != nullptr) {
		this->left = new BSTNode<T>(*other.left);
		this->left->parent = this;
	}
		
	//if the right side has a child create a new node and copy the right child by copy constructor which will recursively copy the entire right side
	if (other.right != nullptr) {
		this->right = new BSTNode<T>(*other.right);
		this->right->parent = this;
	}
		

	return *this; //return the current object
}

template <class T>
BSTNode<T>::~BSTNode()
{
	
	clear(); //clear function is called to delete the entire tree

}

template <class T>
T& BSTNode<T>::getItem() {
	return this->data;
}

template <class T>
BSTNode<T>* BSTNode<T>::getLeft()
{
	return this->left;
}

template <class T>
BSTNode<T>* BSTNode<T>::getRight()
{
	return this->right;
}

template <class T>
BSTNode<T>* BSTNode<T>::getParent()
{
	return this->parent;
}

template <class T>
void BSTNode<T>::setLeft(BSTNode<T>* l)
{
	this->left = l;
}

template <class T>
void BSTNode<T>::setRight(BSTNode<T>* r)
{
	this->right = r;
}


template <class T>
BSTNode<T>::BSTNode() //default constructor 
{
	parent = nullptr;
	left = nullptr;
	right = nullptr;
}


template <class T>
BSTNode<T>::BSTNode(T data) //constructor for creating new node with pass in key and value 
{
	//left, right and parrent are nullptr as initial state when initiated
	//they are then set inside the function as add
	parent = nullptr;
	left = nullptr;
	right = nullptr;
	this->data = data; //set the data to be the data passed in
}

template <class T>
int BSTNode<T>::count()
{
	int c = 1; // 1 for the first node 
	if (left != nullptr) //base case to stop the recursion
	{
		c += left->count(); //add to c and go all the way left possible 
	}
	if (right != nullptr)
	{
		c += right->count(); //go as right as possible 
	}
	return c;
}

template <class T>
void BSTNode<T>::add(const T& item)
{
	// base case for when the key that we want to add is same as the current node's key, just update the value and return stoppin the recursion
	if (item.getKey() == this->data.getKey())
	{
		this->data.setValue(item.getValue());
		return;
	}
	else if (item.getKey() < this->data.getKey()) // left side, if the key trying to add is less than the current key go to left side
	{
		if (left == nullptr) 
		{
			//when left is null (empty) create a new node and set it's parent to be the current node we are on
			left = new BSTNode<T>(item);
			left->parent = this;
		}
		else // if it is not null then recursively call add funtion on the left child, this will go until it finds a null node
		{
			left->add(item);
		}
	}
	else //right subtree check meaing key > this->key
	{
		if (right == nullptr) // same logic, if right is empty just create a new node there and set the parent of it to be the current node
		{
			right = new BSTNode<T>(item);
			right->parent = this;
		}
		else //if the current right node is occupied then recursively call add on the right child which will go until it finds empty space for new node
		{
			right->add(item);
		}
	}
}

template<class T>
void BSTNode<T>::clear()
{
	if (left != nullptr) { //if left is not null then recursively call clear on the left child and delete the left child
		left->clear();
		delete left;
		left = nullptr;
	}
	if (right != nullptr) { //if right is not null then recursively call clear on the right child and delete the right child
		right->clear();
		delete right;
		right = nullptr;
	}
}

template <class T>
void BSTNode<T>::setItem(T item)
{
	this->data = item;
}


