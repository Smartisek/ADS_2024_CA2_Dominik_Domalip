#include "pch.h"
#include "CppUnitTest.h"
#include "../ADS_2024_CA2_Dominik_Domalip/BinaryTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BinaryTreeMapTesting
{
	TEST_CLASS(BinaryTreeMapTesting)
	{
	public:
		
		TEST_METHOD(TestAddToEmptyTree)
		{
			BinaryTree<int> tree;
			tree.add(1);
			Assert::IsNotNull(tree.root);
			Assert::AreEqual(1, tree.root->getItem());
		}
	};
}
