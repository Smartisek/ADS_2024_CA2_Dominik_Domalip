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
		Assert::AreEqual(node.getKey().c_str(), "Number");
		Assert::AreEqual(node.getValue(), 1);
		Assert::IsNull(node.getLeft());
		Assert::IsNull(node.getRight());
		Assert::IsNull(node.getParent());
	}

	};
}