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
	}
	};
}
