#include "pch.h"
#include "CppUnitTest.h"
#include <fstream>
#include "../ADS_2024_CA2_Dominik_Domalip/ReadFromFile.h"
#include "../ADS_2024_CA2_Dominik_Domalip/BinaryTree.h"
#include "../ADS_2024_CA2_Dominik_Domalip/KeyValuePair.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework; 

/*I know I should also test the reading from file method however I did not find a way how to do that because every time my test cannot find the file
	even when it is specified correctly like "../ADS_2024_CA2_Dominik_Domalip/words.txt" . It works inside my main program so I decided to skip these tests
	*/

namespace BinaryTreeMapTesting
{
	TEST_CLASS(TreeMapTest) {
public:
	TEST_METHOD(ConstructorTest) {
		BinaryTree<KeyValuePair<string, int>> tree;
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

	TEST_METHOD(ContainsKeyTest) {
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
		Assert::IsTrue(tree.containsKey("D"));
		Assert::IsTrue(tree.containsKey("B"));
		Assert::IsFalse(tree.containsKey("T"));

		KeyValuePair<string, int> keyRemove("D", 0);
		tree.remove(keyRemove);
		Assert::AreEqual(tree.count(), 6);
		Assert::IsFalse(tree.containsKey("D"));
	}

	TEST_METHOD(GetValueContainsKeyTest) {
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
		Assert::AreEqual(tree.get("D"), 4);
		Assert::AreEqual(tree.get("B"), 2);
	}

	TEST_METHOD(GetValueNoKeyTest) {
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

		try {
			tree.get("T");
			Assert::Fail();
		}
		catch (const std::exception& e) {
			Assert::AreEqual("Item was not found!", e.what());
		}
	}

	TEST_METHOD(GetSetOfKeysTest) {
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

		set<string> expected = { "A", "B", "C", "D", "E", "F", "G" };
		set<string> actual = tree.keySet();

		Assert::AreEqual(expected.size(), actual.size());

		//Check the order of keys, should be in order
		auto it1 = expected.begin();
		auto it2 = actual.begin();

		while (it1 != expected.end() && it2 != actual.end()) { //go through both sets and compare them if htey are the same 
			Assert::AreEqual(*it1, *it2);
			it1++;
			it2++;
		}
	}

	TEST_METHOD(SizeOfKeyValueTest) {
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

		Assert::AreEqual(tree.size(), 7);
		Assert::AreEqual(tree.count(), 7);
	}

	TEST_METHOD(PutAValueIntoAlreadyExistKey) {
		BinaryTree<KeyValuePair<string, set<string>>> tree; //create a tree of class KeyValuePair with value being a set of strings 
		KeyValuePair<string, set<string>> Awords("A", { "Apple" , "Apostole"});
		KeyValuePair<string, set<string>> Bwords("B", { "Banana", "Bread"});

		tree.add(Awords);
		tree.add(Bwords);

		Assert::AreEqual(tree.size(), 2);
		Assert::IsTrue(tree.containsKey("A"));
		Assert::IsTrue(tree.containsKey("B"));
		//check if the size of the set is 2
		//static_cast is used for comparing the 2 to the size_t type which is the return type of the size() function in set
		Assert::AreEqual(tree.get("A").size(), static_cast<size_t>(2));
		Assert::AreEqual(tree.get("B").size(), static_cast<size_t>(2));
#
		//try to put value 
		set<string> newAWord = { "Ankle" };
		tree.put("A", newAWord);

		set<string> newBWord = { "Boil" , "Botanic", "Bee"};
		tree.put("B", newBWord);

		Assert::AreEqual(tree.get("A").size(), static_cast<size_t>(3));
		Assert::AreEqual(tree.get("B").size(), static_cast<size_t>(5));
	}

	TEST_METHOD(PutAValueKeyNotInTreeTest) {
		BinaryTree<KeyValuePair<string, set<string>>> tree; //create a tree of class KeyValuePair with value being a set of strings 
		KeyValuePair<string, set<string>> Awords("A", { "Apple" , "Apostole"});
		KeyValuePair<string, set<string>> Bwords("B", { "Banana", "Bread"});

		tree.add(Awords);
		tree.add(Bwords);

		Assert::AreEqual(tree.size(), 2);
		Assert::IsTrue(tree.containsKey("A"));
		Assert::IsTrue(tree.containsKey("B"));

		//try to put value
		set<string> newCWord = { "Candy" , "Cane" };
		tree.put("C", newCWord);

		Assert::AreEqual(tree.size(), 3);
		Assert::IsTrue(tree.containsKey("C"));
		Assert::AreEqual(tree.get("C").size(), static_cast<size_t>(2));

		set<string> moreCwords = { "Cup", "Cupcake" };
		tree.put("C", moreCwords);	
		Assert::AreEqual(tree.get("C").size(), static_cast<size_t>(4));
	}

	//Testing remove by key so just reusing my previous remove tests 
	TEST_METHOD(RemoveByKeyLeafNodeTest) {
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
		
		tree.remove("E");
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
	}

	TEST_METHOD(RemoveByKeyOneChildTest) {
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

		
		tree.remove("G");
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
	}

	TEST_METHOD(RemoveByKeyTwoChildrenTest) {
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
		tree.remove("B");
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
	}

	TEST_METHOD(RemoveByKeyRemoveMultipleChildrenTest) {
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
		

		tree.remove("L");
		Assert::AreEqual(tree.count(), 14);
		Assert::AreEqual("M", tree.root->getRight()->getItem().getKey().c_str());
		Assert::IsNull(right->getRight()->getLeft());
	}

	TEST_METHOD(GetValueWithOperatorBracketTest) {
		BinaryTree<KeyValuePair<string, int>> tree;
		KeyValuePair<string, int> Dfour("A", 4);
		tree.add(Dfour);

		Assert::AreEqual(tree.size(), 1); // Gets the value of the node with key "A"
		Assert::IsTrue(tree.containsKey("A"));
		Assert::AreEqual(tree["A"], 4);

		KeyValuePair<string, int> Btwo("B", 2);
		tree.add(Btwo);
		int value = tree["B"];
		Assert::AreEqual(value, 2);

		try {
			tree["C"];
			Assert::Fail();
		}
		catch (const std::exception& e) {
			Assert::AreEqual("Key not found!", e.what());
		}

		

		/*--------------------------------------------------------------*/

		BinaryTree<KeyValuePair<string, set<string>>> tree2; //test with value of sets 
		KeyValuePair<string, set<string>> Awords("A", { "Apple" , "Apostole" });

		tree2.add(Awords);

		Assert::AreEqual(tree2.size(), 1);
		Assert::IsTrue(tree2.containsKey("A"));
		set<string> wordsA = tree2["A"];
		Assert::AreEqual(wordsA.size(), static_cast<size_t>(2));
	}
};
};
