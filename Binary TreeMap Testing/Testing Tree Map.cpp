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

	TEST_METHOD(RemoveKeyTest) {
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
	}

	};
}
