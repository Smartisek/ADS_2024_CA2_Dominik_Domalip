#pragma once
#include <iostream>

using namespace std;

template <class K, class V>
class BSTNode
{
	/*Pointers*/
	BSTNode<K, V>* parent;
	BSTNode<K, V>* left;
	BSTNode<K, V>* right;
	/*Data inside node*/
	K key;
	V value;

public:
	/*Constructors*/
	BSTNode();
	BSTNode(const BSTNode<K, V>& other); //copy constructor
	BSTNode<K, V>* operator=(const BSTNode<K, V>& other);
	BSTNode(K key, V value);
	/*Setters*/
	void setKey(K key);
	void setValue(V value);
	void setLeft(BSTNode<K, V>* l);
	void setRight(BSTNode<K, V>* r);
	/*Getters*/
	BSTNode<K, V>* getParent();
	BSTNode<K, V>* getLeft();
	BSTNode<K, V>* getRight();
	K& getKey();
	V& getValue();
	/*Functions*/ 
	int count();
	void add(K key, V value);
	void clear();
	/*Destructor*/
	~BSTNode();

};

template <class K, class V>
BSTNode<K, V>::BSTNode(const BSTNode<K, V>& other) //copy constructor making a deeep copy copy with subtrees
{
	left = right = nullptr; //new node starts with null pointers 

	if (other.left != nullptr) //check if other have left child 
	//if yes then create a new node copying the left child, this will be done recursively until the are no left chidlren 
		this->left = new BSTNode<K,V>(*other.left); 
	if (other.right != nullptr) //check if there are any right chidlren 
		//if yes then create a new node copying the right child, this will be done recursively until there are no right children
		this->right = new BSTNode<K,V>(*other.right);

}

template <class K, class V>
BSTNode<K, V>* BSTNode<K, V>::operator=(const BSTNode<K, V>& other)
{
	if (this == &other) //check if the current object is the same as the one trying to be assigned 
		return *this; //return the current object if it is 

	//delete pointers left and right so the current node does not hold any reference to the old subtrees
	delete left;
	delete right;

	//get the key and value from other node to be current node KV
	this->key = other.key;
	this->value = other.value;

	//discard any existing children 
	left = right = nullptr;

	//if the left side has a child create a new node and copy the left child by copy constructor which will recursively copy the entire left side
	if (other.left != nullptr)
		this->left = new BSTNode<K, V>(*other.left);
	//if the right side has a child create a new node and copy the right child by copy constructor which will recursively copy the entire right side
	if (other.right != nullptr)
		this->right = new BSTNode<K, V>(*other.right);

}

template <class K, class V>
BSTNode<K, V>::~BSTNode()
{
	////checks if both sides and if they are not null it will recursively delete the left and right side and set the sides pointers to null
	//if (left != nullptr)
	//{
	//	delete left;
	//	left = nullptr;
	//}
	//if (right != nullptr)
	//{
	//	delete right;
	//	right = nullptr;
	//}
	clear(); //clear function is called to delete the entire tree

}

template <class K, class V>
K& BSTNode<K, V>::getKey()
{
	return this->key;
}

template <class K, class V>
V& BSTNode<K, V>::getValue() {
	return this->value;
}

template <class K, class V>
BSTNode<K, V>* BSTNode<K, V>::getLeft()
{
	return this->left;
}

template <class K, class V>
BSTNode<K, V>* BSTNode<K, V>::getRight()
{
	return this->right;
}

template <class K, class V>
BSTNode<K, V>* BSTNode<K, V>::getParent()
{
	return this->parent;
}

template <class K, class V>
void BSTNode<K,V>::setLeft(BSTNode<K,V>* l)
{
	this->left = l;
}

template <class K, class V>
void BSTNode<K, V>::setRight(BSTNode<K, V>* r)
{
	this->right = r;
}


template <class K, class V>
BSTNode<K, V>::BSTNode()
{
	parent = nullptr;
	left = nullptr;
	right = nullptr;
}


template <class K, class V>
BSTNode<K, V>::BSTNode(K key, V value) //constructor for creating new node with pass in key and value 
{
	//left, right and parrent are nullptr as initial state when initiated
	//they are then set inside the function as add
	parent = nullptr;
	left = nullptr;
	right = nullptr;
	this->key = key;
	this->value = value;
}

template <class K, class V>
int BSTNode<K, V>::count()
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

template <class K, class V>
void BSTNode<K, V>::add(K key, V value)
{
	// base case for when the key that we want to add is same as the current node's key, just update the value and return stoppin the recursion
	if (key == this->key)
	{
		this->value = value;
		return;
	}
	else if (key < this->key) // left side, if the key trying to add is less than the current key go to left side
	{
		if (left == nullptr) 
		{
			//when left is null (empty) create a new node and set it's parent to be the current node we are on
			left = new BSTNode<K, V>(key, value);
			left->parent = this;
		}
		else // if it is not null then recursively call add funtion on the left child, this will go until it finds a null node
		{
			left->add(key, value);
		}
	}
	else //right subtree check meaing key > this->key
	{
		if (right == nullptr) // same logic, if right is empty just create a new node there and set the parent of it to be the current node
		{
			right = new BSTNode<K, V>(key, value);
			right->parent = this;
		}
		else //if the current right node is occupied then recursively call add on the right child which will go until it finds empty space for new node
		{
			right->add(key, value);
		}
	}
}

template<class K, class V>
void BSTNode<K, V>::clear()
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

template <class K, class V>
void BSTNode<K,V>::setKey(K key)
{
	this->key = key;
}

template <class K, class V>
void BSTNode<K, V>::setValue(V value)
{
	this->value = value;
}

