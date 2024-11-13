#include "pch.h"
#include "CppUnitTest.h"
#include "../ADS_2024_CA2_Dominik_Domalip/BinaryTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BinaryTreeMapTesting
{
	TEST_CLASS(TreeMapTest) {
public:
	TEST_METHOD(ConstructorTest) {
		BinaryTree<string, int> tree;
		Assert::IsNull(tree.root);
	}

	TEST_METHOD(AddToEmptyTree) {
		BinaryTree<string, int> tree;
		Assert::IsNull(tree.root);
		tree.add("A", 1);
		Assert::IsNotNull(tree.root);
		Assert::AreEqual(tree.root->getKey().c_str(), "A");
	}

	TEST_METHOD(AddToRootLeft) {
		BinaryTree<string, int> tree;
		tree.add("B", 2);
		tree.add("A", 1);
		Assert::IsNotNull(tree.root);
		Assert::AreEqual(tree.root->getKey().c_str(), "B");
		BSTNode<string, int>* left = tree.root->getLeft();
		Assert::IsNotNull(left);
		Assert::AreEqual(left->getKey().c_str(), "A");
	}

	TEST_METHOD(AddToRootRight) {
		BinaryTree<string, int> tree;
		tree.add("G", 2);
		tree.add("J", 1);
		Assert::IsNotNull(tree.root);
		Assert::AreEqual(tree.root->getKey().c_str(), "G");
		BSTNode<string, int>* right = tree.root->getRight();
		Assert::IsNotNull(right);
		Assert::AreEqual(right->getKey().c_str(), "J");
	}

	TEST_METHOD(CountOnEmptyTreeTest) {
		BinaryTree<string, int> tree;
		Assert::AreEqual(tree.count(), 0);
	}

	TEST_METHOD(RegularCountTest) {
		BinaryTree<string, int> tree;
		tree.add("A", 1);
		tree.add("B", 2);
		tree.add("C", 3);
		Assert::AreEqual(tree.count(), 3);
	}
	};
}
