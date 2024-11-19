#include "pch.h"
#include "CppUnitTest.h"
#include "../ADS_2024_CA2_Dominik_Domalip/BinaryTree.h"
#include "../ADS_2024_CA2_Dominik_Domalip/KeyValuePair.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework; 

namespace BinaryTreeMapTesting
{
	TEST_CLASS(TreeMapTest) {
public:
	TEST_METHOD(ConstructorTest) {
		BinaryTree<KeyValuePair<string,int>> tree;
		Assert::IsNull(tree.root);
	}

	TEST_METHOD(AddToEmptyTree) {
		BinaryTree<KeyValuePair<string, int>> tree;
		Assert::IsNull(tree.root);
		KeyValuePair<string, int> Aone("A", 1);
		tree.add(Aone);
		Assert::IsNotNull(tree.root);
		Assert::AreEqual(tree.root->getItem().getKey().c_str(), "A");
	}

	TEST_METHOD(AddToRootLeft) {
		BinaryTree<KeyValuePair<string, int>> tree;
		KeyValuePair<string, int> Btwo("B", 2);
		KeyValuePair<string, int> Aone("A", 1);
		tree.add(Btwo);
		tree.add(Aone);
		Assert::IsNotNull(tree.root);
		Assert::AreEqual(tree.root->getItem().getKey().c_str(), "B");
		BSTNode<KeyValuePair<string, int>>* left = tree.root->getLeft();
		Assert::IsNotNull(left);
		Assert::AreEqual(left->getItem().getKey().c_str(), "A");
	}

	TEST_METHOD(AddToRootRight) {
		BinaryTree<KeyValuePair<string, int>> tree;
		KeyValuePair<string, int> Gtwo("G", 2);
		KeyValuePair<string, int> Jone("J", 1);
		tree.add(Gtwo);
		tree.add(Jone);
		Assert::IsNotNull(tree.root);
		Assert::AreEqual(tree.root->getItem().getKey().c_str(), "G");
		BSTNode<KeyValuePair<string, int>>* right = tree.root->getRight();
		Assert::IsNotNull(right);
		Assert::AreEqual(right->getItem().getKey().c_str(), "J");
	}

	TEST_METHOD(CountOnEmptyTreeTest) {
		BinaryTree<KeyValuePair<string, int>> tree;
		Assert::AreEqual(tree.count(), 0);
	}

	TEST_METHOD(RegularCountTest) {
		BinaryTree<KeyValuePair<string, int>> tree;
		KeyValuePair<string, int> Aone("A", 1);
		KeyValuePair<string, int> Btwo("B", 2);
		KeyValuePair<string, int> Cthree("C", 3);
		tree.add(Aone);
		tree.add(Btwo);
		tree.add(Cthree);
		Assert::AreEqual(tree.count(), 3);
	}

	TEST_METHOD(GetAValueOfKeyTest) {
		BinaryTree<KeyValuePair<string, int>> tree;
		KeyValuePair<string, int> Aone("A", 1);
		KeyValuePair<string, int> Btwo("B", 2);
		KeyValuePair<string, int> Cthree("C", 3);
		tree.add(Aone);
		tree.add(Btwo);
		tree.add(Cthree);
		KeyValuePair<string, int> key("A", 0);
		Assert::AreEqual(tree.get(key).getValue(), 1);
	}

	TEST_METHOD(ClearTreeTest) {
		BinaryTree<KeyValuePair<string, int>> tree;
		KeyValuePair<string, int> Aone("A", 1);
		KeyValuePair<string, int> Btwo("B", 2);
		KeyValuePair<string, int> Cthree("C", 3);
		tree.add(Aone);
		tree.add(Btwo);
		tree.add(Cthree);
		tree.clear();
		Assert::IsNull(tree.root);
		Assert::AreEqual(tree.count(), 0);
		
		//Can be reused? 
		tree.add(Aone);
		Assert::IsNotNull(tree.root);
		Assert::AreEqual(tree.count(), 1);
		Assert::AreEqual(tree.root->getItem().getKey().c_str(), "A");
	}

	TEST_METHOD(RemoveLeafNodeTest) {
		BinaryTree<KeyValuePair<string, int>> tree;
		KeyValuePair<string, int> Dfour("D", 4);
		KeyValuePair<string, int> Btwo("B", 2);
		KeyValuePair<string, int> Fsix("F", 6);
		KeyValuePair<string, int> Cthree("C", 3);
		KeyValuePair<string, int> Aone("A", 1);
		KeyValuePair<string, int> Efive("E", 5);
		KeyValuePair<string, int> Gseven("G", 7);

		tree.add(Dfour);
		tree.add(Btwo);
		tree.add(Fsix);
		tree.add(Aone);
		tree.add(Cthree);
		tree.add(Efive);
		tree.add(Gseven);

		Assert::AreEqual(tree.count(), 7);
		KeyValuePair<string, int> keyRemove("E", 0);
		tree.remove(keyRemove);
		Assert::AreEqual(tree.count(), 6);

		Assert::AreEqual(tree.root->getItem().getKey().c_str(), "D"); //root
		Assert::AreEqual(tree.root->getLeft()->getItem().getKey().c_str(), "B"); //left chidl
		Assert::AreEqual(tree.root->getRight()->getItem().getKey().c_str(), "F"); //right child

		BSTNode<KeyValuePair<string, int>>* right = tree.root->getRight();
		BSTNode<KeyValuePair<string, int>>* left = tree.root->getLeft();

		Assert::AreEqual(left->getLeft()->getItem().getKey().c_str(), "A");
		Assert::AreEqual(left->getRight()->getItem().getKey().c_str(), "C");

		Assert::IsNull(right->getLeft());
		Assert::AreEqual(right->getRight()->getItem().getKey().c_str(), "G");

    /*  D    Before removing
	   / \
	  B   F
	 / \ / \
	A  C E  G

	After removing E
		D
	   / \
	  B   F
	 / \   \
	A  C    G

	*/
	}
	TEST_METHOD(RemoveKeyNotPresentTest) {
		BinaryTree<KeyValuePair<string, int>> tree;
		KeyValuePair<string, int> Dfour("D", 4);
		KeyValuePair<string, int> Btwo("B", 2);
		KeyValuePair<string, int> Fsix("F", 6);
		KeyValuePair<string, int> Cthree("C", 3);
		KeyValuePair<string, int> Aone("A", 1);
		KeyValuePair<string, int> Efive("E", 5);
		KeyValuePair<string, int> Gseven("G", 7);

		tree.add(Dfour);
		tree.add(Btwo);
		tree.add(Fsix);
		tree.add(Aone);
		tree.add(Cthree);
		tree.add(Efive);
		tree.add(Gseven);

		Assert::AreEqual(tree.count(), 7);
		KeyValuePair<string, int> keyRemove("H", 0);
		tree.remove(keyRemove);
		Assert::AreEqual(tree.count(), 7);
		Assert::AreEqual(tree.root->getItem().getKey().c_str(), "D"); //root
		Assert::AreEqual(tree.root->getLeft()->getItem().getKey().c_str(), "B"); //left chidl
		Assert::AreEqual(tree.root->getRight()->getItem().getKey().c_str(), "F"); //right child
		//pointers to left and right from roots kids
		BSTNode<KeyValuePair<string, int>>* right = tree.root->getRight();
		BSTNode<KeyValuePair<string, int>>* left = tree.root->getLeft();

		Assert::AreEqual(left->getLeft()->getItem().getKey().c_str(), "A");
		Assert::AreEqual(left->getRight()->getItem().getKey().c_str(), "C");
		Assert::AreEqual(right->getLeft()->getItem().getKey().c_str(), "E");
		Assert::AreEqual(right->getRight()->getItem().getKey().c_str(), "G");
	}

	TEST_METHOD(RemoveNodeWithOneChildTest) {
		BinaryTree<KeyValuePair<string, int>> tree;
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

		Assert::AreEqual(tree.count(), 7);

		//remove node
		KeyValuePair<string, int> keyRemove("G", 0);
		tree.remove(keyRemove);
		Assert::AreEqual(tree.count(), 6);
		Assert::IsNotNull(tree.root); //root should not be null
		Assert::AreEqual(tree.root->getItem().getKey().c_str(), "D"); //get key of root
		Assert::AreEqual(tree.root->getLeft()->getItem().getKey().c_str(), "B"); //get key of left
		Assert::AreEqual(tree.root->getRight()->getItem().getKey().c_str(), "F"); //get key of right

		BSTNode<KeyValuePair<string, int>>* right = tree.root->getRight();
		BSTNode<KeyValuePair<string, int>>* left = tree.root->getLeft();

		Assert::AreEqual(left->getLeft()->getItem().getKey().c_str(), "A");
		Assert::AreEqual(right->getLeft()->getItem().getKey().c_str(), "E");
		Assert::AreEqual(right->getRight()->getItem().getKey().c_str(), "H");

	/*  D   Before removing
	   / \
	  B   F
	 / \   \
	A   C   G
			 \
			  H


		D    After removung
	   / \
	  B   F
	 / \   \
	A   C   H

*/
	}

	TEST_METHOD(RemoveNodeWithTwoChildrenTest) {
		BinaryTree<KeyValuePair<string, int>> tree;
		KeyValuePair<string, int> Dfour("D", 4);
		KeyValuePair<string, int> Btwo("B", 2);
		KeyValuePair<string, int> Fsix("F", 6);
		KeyValuePair<string, int> Cthree("C", 3);
		KeyValuePair<string, int> Aone("A", 1);
		KeyValuePair<string, int> Efive("E", 5);
		KeyValuePair<string, int> Gseven("G", 7);

		tree.add(Dfour);
		tree.add(Btwo);
		tree.add(Fsix);
		tree.add(Aone);
		tree.add(Cthree);
		tree.add(Efive);
		tree.add(Gseven);

		Assert::AreEqual(tree.count(), 7);
		KeyValuePair<string, int> keyRemove("B", 0);
		tree.remove(keyRemove);
		Assert::AreEqual(tree.count(), 6);

		Assert::AreEqual(tree.root->getItem().getKey().c_str(), "D"); //root
		//after deleting B, C should be promoted as it is bigger than A and smaller than D
		Assert::AreEqual(tree.root->getLeft()->getItem().getKey().c_str(), "C"); 
		Assert::AreEqual(tree.root->getRight()->getItem().getKey().c_str(), "F");

		BSTNode<KeyValuePair<string, int>>* right = tree.root->getRight();
		BSTNode<KeyValuePair<string, int>>* left = tree.root->getLeft();

		Assert::AreEqual(left->getLeft()->getItem().getKey().c_str(), "A");
		Assert::IsNull(left->getRight()); //this spot is now empty from C moving up
		Assert::AreEqual(right->getLeft()->getItem().getKey().c_str(), "E");
		Assert::AreEqual(right->getRight()->getItem().getKey().c_str(), "G");

	/*  D   Before removing
	   / \
	  B   F
	 / \ / \
	A  C E  G


		D    After removing B
	   / \
	  C   F
	 /   / \
	A   E   G

	*/
	}

	TEST_METHOD(RemoveNodeWithMultipleChildrenTest) {
          
		BinaryTree<KeyValuePair<string, int>> tree;
		KeyValuePair<string, int> Height("H", 8);
		KeyValuePair<string, int> Dfour("D", 4);
		KeyValuePair<string, int> Ltwelve("L", 12);
		KeyValuePair<string, int> Btwo("B", 2);
		KeyValuePair<string, int> Fsix("F", 6);
		KeyValuePair<string, int> Aone("A", 1);
		KeyValuePair<string, int> Cthree("C", 3);
		KeyValuePair<string, int> Efive("E", 5);
		KeyValuePair<string, int> Gseven("G", 7);
		KeyValuePair<string, int> Jten("J", 10);
		KeyValuePair<string, int> Nfourteen("N", 14);
		KeyValuePair<string, int> Inine("I", 9);
		KeyValuePair<string, int> Keleven("K", 11);
		KeyValuePair<string, int> Mthirteen("M", 13);
		KeyValuePair<string, int> Ofifteen("O", 15);

		tree.add(Height);
		tree.add(Dfour);
		tree.add(Ltwelve);
		tree.add(Btwo);
		tree.add(Fsix);
		tree.add(Aone);
		tree.add(Cthree);
		tree.add(Efive);
		tree.add(Gseven);
		tree.add(Jten);
		tree.add(Nfourteen);
		tree.add(Inine);
		tree.add(Keleven);
		tree.add(Mthirteen);
		tree.add(Ofifteen);

		Assert::AreEqual(tree.count(), 15);

		BSTNode<KeyValuePair<string, int>>* right = tree.root->getRight();
		Assert::IsNotNull(right->getRight()->getLeft());
		Assert::AreEqual(right->getRight()->getLeft()->getItem().getKey().c_str(), "M");
		KeyValuePair<string, int> keyRemove("L", 0);

		tree.remove(keyRemove);
		Assert::AreEqual(tree.count(), 14);
		Assert::AreEqual("M", tree.root->getRight()->getItem().getKey().c_str());
		Assert::IsNull(right->getRight()->getLeft());

		/*
		           H    Before removing 
			    /     \
			   /       \
			  /         \ 
			 D           L
			/ \        /   \
		   B   F      J     N
		  / \ / \    / \   / \
		 A  C E  G  I   K  M  O                    (Using graphics from inclass lecture code)
		
		 
			       H    Before removing 
			    /     \
			   /       \
			  /         \ 
			 D           M
			/ \        /   \
		   B   F      J     N
		  / \ / \    / \     \
		 A  C E  G  I   K     O

		*/
	}

	};
}
