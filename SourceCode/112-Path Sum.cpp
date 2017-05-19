//	112. Path Sum
//------------------------------------------------------------------------------//
//	Given a binary tree and a sum, determine if the tree has a root-to-leaf		//
//	path such that adding up all the values along the path equals the given sum.//
//	For example :																//
//	Given the below binary tree and sum = 22,									//
//			5																	//
//		   / \																	//
//		  4   8																	//
//		 /	 / \																//
//		11  13  4																//
//	   / \		 \																//
//	  7   2       1																//
//	return true, as there exist a root - to - leaf path 5->4->11->2 which sum	//
//	is 22.		 																//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<queue>
#include<stack>
// constants
// function prototype
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
//利用一个bool变量记录该节点是否有兄弟节点
class Solution 
{
public:
	bool hasPathSum(TreeNode* root, int sum)
	{
		if (root == nullptr) return false;
		return DFS(root, sum, false);
	}
	bool DFS(TreeNode* root, int sum, bool hasBrother)
	{
		if (root == nullptr) 
			return !hasBrother && sum == 0;
		return DFS(root->left, sum - root->val, root->right)
			|| DFS(root->right, sum - root->val, root->left);
	}
};
//更直接的方式
class Solution2
{
public:
	bool hasPathSum(TreeNode *root, int sum) {
		if (root == nullptr) return false;
		if (root->left == nullptr && root->right == nullptr) // leaf
			return sum == root->val;
		return hasPathSum(root->left, sum - root->val)
			|| hasPathSum(root->right, sum - root->val);
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
//	cout << boolalpha << test.hasPathSum(root, 27) << endl;
//	manageTree.destroy(root);
//	root = new TreeNode(1);
//	root->left = new TreeNode(2);
//	root->right = new TreeNode(3);
//	root->left->left = new TreeNode(4);
//	root->right->right = new TreeNode(5);
//	cout << boolalpha << test.hasPathSum(root, 7) << endl;
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