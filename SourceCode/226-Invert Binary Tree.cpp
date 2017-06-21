//	226. Invert Binary Tree
//------------------------------------------------------------------------------//
//	Invert a binary tree.														//
//			4																	//
//		   / \																	//
//		  2   7																	//
//		 / \ / \																//
//		1  3 6  9																//
//	to																			//
//			4																	//
//		   / \																	//
//		  7   2																	//
//		 / \ / \																//
//		9  6 3  1																//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<queue>
// constants
// function prototype
using namespace std;
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
public:
	TreeNode* invertTree(TreeNode* root) {
		if (nullptr == root)
			return nullptr;
		TreeNode *left = invertTree(root->left);
		TreeNode *right = invertTree(root->right);
		root->right = left;
		root->left = right;
		return root;
	}
};
class ManageTree
{
public:
	void destroy(TreeNode *root)
	{
		if (root == nullptr)
			return;
		destroy(root->left);
		destroy(root->right);
		delete root;
	}
	void showTree(TreeNode *root, int distance)
	{
		if (root == nullptr)
			return;
		else
		{
			for (int i = 0; i < distance; i++)
				cout << "\t";
			cout << root->val << endl;
			showTree(root->left, distance + 1);
			showTree(root->right, distance + 1);
		}
	}
};
//int main(void)
//{
//	Solution test;
//	ManageTree manageTree;
//	TreeNode *root = new TreeNode(1);
//	root->left = new TreeNode(2);
//	root->right = new TreeNode(3);
//	manageTree.showTree(root, 0);
//	test.invertTree(root);
//	manageTree.showTree(root, 0);
//	manageTree.destroy(root);
//	cout << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}