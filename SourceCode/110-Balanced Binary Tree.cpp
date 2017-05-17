//	110. Balanced Binary Tree
//------------------------------------------------------------------------------//
//	Given a binary tree, determine if it is height-balanced.					//
//	For this problem, a height - balanced binary tree is defined as a binary	//
//	tree in which the depth of the two subtrees of every node never differ by	//
//	more than 1.		 														//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
// constants
// function prototype
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
//深度优先搜索得到子树的高度，判断是否平衡
//基于自底而上的方法
class Solution {
public:
	bool isBalanced(TreeNode* root) {
		return balancedHeight(root) >= 0;
	}
private:
	int balancedHeight(TreeNode* root)
	{
		if (root == nullptr)
			return 0;
		int left = balancedHeight(root->left);
		int right = balancedHeight(root->right);
		if (left < 0 || right < 0 || abs(left - right) > 1) return -1;
		return max(left, right) + 1;
	}
};
//基于自上而下的方法
class Solution2 {
public:
	bool isBalanced(TreeNode* root) {
		if (root == nullptr)
			return true;
		int left = depth(root->left);
		int right = depth(root->right);
		return abs(depth(root->left) - depth(root->right)) < 2 && isBalanced(root->left) && isBalanced(root->right);
	}
private:
	int depth(TreeNode* root)
	{
		if (root == nullptr)
			return 0;
		return max(depth(root->left), depth(root->right)) + 1;
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
//	Solution2 test;
//	ManageTree manageTree;
//	TreeNode *root = new TreeNode(3);
//	root->left = new TreeNode(9);
//	root->right = new TreeNode(20);
//	root->left->left = new TreeNode(15);
//	root->left->left->left = new TreeNode(7);
//	
//	cout << boolalpha << test.isBalanced(root) << endl;
//	manageTree.destroy(root);
//	root = new TreeNode(1);
//	root->left = new TreeNode(2);
//	root->right = new TreeNode(3);
//	root->left->left = new TreeNode(4);
//	root->right->right = new TreeNode(5);
//	cout << boolalpha << test.isBalanced(root) << endl;
//	cout << endl;
//	
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}