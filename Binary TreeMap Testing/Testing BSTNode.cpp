#include "pch.h"
#include "CppUnitTest.h"
#include "../ADS_2024_CA2_Dominik_Domalip/BinaryTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BinaryTreeMapTesting
{
	TEST_CLASS(BSTNodeTest) {
public:

	TEST_METHOD(ConstructorTest) {
		BSTNode<string, int> node("Number", 1);
		Assert::AreEqual(node.getKey().c_str(), "Number"); //c_str() is used to convert string to const char*
		Assert::AreEqual(node.getValue(), 1);
		Assert::IsNull(node.getLeft());
		Assert::IsNull(node.getRight());
		Assert::IsNull(node.getParent());
	}

	TEST_METHOD(AddLessThanTest) {
		BSTNode <string, int> node("N", 5);
		Assert::AreEqual(node.getKey().c_str(), "N");
		Assert::AreEqual(node.getValue(), 5);
		Assert::IsNull(node.getLeft());
		node.add("B", 3);
		Assert::IsNotNull(node.getLeft());
		Assert::AreEqual(node.getLeft()->getKey().c_str(), "B");
		Assert::AreEqual(node.getLeft()->getValue(), 3);
	}

	TEST_METHOD(AddMoreThanTest) {
		BSTNode <string, int> node("N", 5);
		Assert::AreEqual(node.getKey().c_str(), "N");
		Assert::AreEqual(node.getValue(), 5);
		Assert::IsNull(node.getRight());
		node.add("Z", 2);
		Assert::IsNotNull(node.getRight());
		Assert::AreEqual(node.getRight()->getKey().c_str(), "Z");
		Assert::AreEqual(node.getRight()->getValue(), 2);
	}

	TEST_METHOD(AddGreaterThanChildTest) {
		BSTNode<string, int> node("C", 5);
		node.add("F", 3);
		BSTNode<string, int>* right = node.getRight();
		node.add("E", 2);
		node.add("H", 1);
		Assert::IsNotNull(right->getLeft());	
		Assert::AreEqual(right->getLeft()->getKey().c_str(), "E");
		Assert::IsNotNull(right->getRight());
		Assert::AreEqual(right->getRight()->getKey().c_str(), "H");
	}

	TEST_METHOD(AddLessThanChildTest) {
		BSTNode<string, int> node("K", 5);
		node.add("F", 3);
		BSTNode<string, int>* left = node.getLeft();
		node.add("A", 2);
		node.add("I", 1);
		Assert::IsNotNull(left->getLeft());
		Assert::AreEqual(left->getLeft()->getKey().c_str(), "A");
		Assert::IsNotNull(left->getRight());
		Assert::AreEqual(left->getRight()->getKey().c_str(), "I");
	}


	};
}