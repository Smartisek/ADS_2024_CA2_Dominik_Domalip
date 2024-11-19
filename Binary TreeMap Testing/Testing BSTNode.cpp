#include "pch.h"
#include "CppUnitTest.h"
#include "../ADS_2024_CA2_Dominik_Domalip/BSTNode.h"
#include "../ADS_2024_CA2_Dominik_Domalip/KeyValuePair.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BinaryTreeMapTesting
{
	TEST_CLASS(BSTNodeTest) {
public:

	TEST_METHOD(ConstructorTest) {
		KeyValuePair<string, int> kv("Number", 1);
		BSTNode<KeyValuePair<string, int>> node(kv);
		Assert::AreEqual(node.getKey().c_str(), "Number"); //c_str() is used to convert string to const char*
		Assert::AreEqual(node.getValue(), 1);
		Assert::IsNull(node.getLeft());
		Assert::IsNull(node.getRight());
		Assert::IsNull(node.getParent());
	}

	TEST_METHOD(AddLessThanTest) {
		KeyValuePair<string, int> kv("N", 5);
		BSTNode<KeyValuePair<string, int>> node(kv);
		Assert::AreEqual(node.getKey().c_str(), "N");
		Assert::AreEqual(node.getValue(), 5);
		Assert::IsNull(node.getLeft());
		node.add(KeyValuePair<string, int>("B", 3));
		Assert::IsNotNull(node.getLeft());
		Assert::AreEqual(node.getLeft()->getKey().c_str(), "B");
		Assert::AreEqual(node.getLeft()->getValue(), 3);
	}

	TEST_METHOD(AddMoreThanTest) {
		KeyValuePair<string, int> kv("N", 5);
		BSTNode<KeyValuePair<string, int>> node(kv);
		Assert::AreEqual(node.getKey().c_str(), "N");
		Assert::AreEqual(node.getValue(), 5);
		Assert::IsNull(node.getRight());
		node.add(KeyValuePair<string, int>("Z", 2));
		Assert::IsNotNull(node.getRight());
		Assert::AreEqual(node.getRight()->getKey().c_str(), "Z");
		Assert::AreEqual(node.getRight()->getValue(), 2);
	}

	TEST_METHOD(AddGreaterThanChildTest) {
		KeyValuePair<string, int> kv("C", 5);
		BSTNode<KeyValuePair<string, int>> node(kv);
		node.add(KeyValuePair<string, int>("F", 3));
		BSTNode<KeyValuePair<string, int>>* right = node.getRight();
		node.add(KeyValuePair<string, int>("E", 2));
		node.add(KeyValuePair<string, int>("H", 1));
		Assert::IsNotNull(right->getLeft());	
		Assert::AreEqual(right->getLeft()->getKey().c_str(), "E");
		Assert::IsNotNull(right->getRight());
		Assert::AreEqual(right->getRight()->getKey().c_str(), "H");
	}

	TEST_METHOD(AddLessThanChildTest) {
		KeyValuePair<string, int> kv("K", 5);
		BSTNode<KeyValuePair<string, int>> node(kv);
		node.add(KeyValuePair<string, int>("F", 3));
		BSTNode<KeyValuePair<string, int>>* left = node.getLeft();
		node.add(KeyValuePair<string, int>("A", 2));
		node.add(KeyValuePair<string, int>("I", 1));
		Assert::IsNotNull(left->getLeft());
		Assert::AreEqual(left->getLeft()->getKey().c_str(), "A");
		Assert::IsNotNull(left->getRight());
		Assert::AreEqual(left->getRight()->getKey().c_str(), "I");
	}

	TEST_METHOD(CountFunctionTest) {
		KeyValuePair<string, int> kv("K", 5);
		BSTNode<KeyValuePair<string, int>> node(kv);
		node.add(KeyValuePair<string, int>("F", 3));
		node.add(KeyValuePair<string, int>("A", 2));
		node.add(KeyValuePair<string, int>("I", 1));
		Assert::AreEqual(node.count(), 4);
	}

	TEST_METHOD(AssignOperatorTest) {
			KeyValuePair<string, int> kv("K", 5);
			BSTNode<KeyValuePair<string, int>> node(kv);
			node.add(KeyValuePair<string, int>("H", 26));
			node.add(KeyValuePair<string, int>("N", 6));

			BSTNode<KeyValuePair<string, int>> assignToNode;
            assignToNode = node;

            //check root
            Assert::AreEqual(assignToNode.getKey().c_str(), "K");
            Assert::AreEqual(assignToNode.getValue(), 5);

            //check left
            Assert::AreEqual(assignToNode.getLeft()->getKey().c_str(), "H");
            Assert::AreEqual(assignToNode.getLeft()->getValue(), 26);

            //check right
            Assert::AreEqual(assignToNode.getRight()->getKey().c_str(), "N");
            Assert::AreEqual(assignToNode.getRight()->getValue(), 6);
        }

	TEST_METHOD(CopyConstructorTest) {
		KeyValuePair<string, int> kv("K", 5);
		BSTNode<KeyValuePair<string, int>> node(kv);
		node.add(KeyValuePair<string, int>("H", 26));
		node.add(KeyValuePair<string, int>("N", 6));

		BSTNode<KeyValuePair<string, int>> copyNode(node);

		//check root
		Assert::AreEqual(copyNode.getKey().c_str(), "K");
		Assert::AreEqual(copyNode.getValue(), 5);

		//check left
		Assert::AreEqual(copyNode.getLeft()->getKey().c_str(), "H");
		Assert::AreEqual(copyNode.getLeft()->getValue(), 26);

		//check right
		Assert::AreEqual(copyNode.getRight()->getKey().c_str(), "N");
		Assert::AreEqual(copyNode.getRight()->getValue(), 6);
	}
	};
}