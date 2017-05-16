//	104. Maximum Depth of Binary Tree
//------------------------------------------------------------------------------//
//	Given a binary tree, find its maximum depth.								//
//	The maximum depth is the number of nodes along the longest path from the	//
//	root node down to the farthest leaf node.		 							//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<deque>
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
//递归的方法
class Solution 
{
public:
	int maxDepth(TreeNode* root) 
	{
		int result = -1;
		if (root == nullptr)
			return 0;
		maxDepth(root, 1, result);
		return result;
	}
private:
	void maxDepth(TreeNode* root, int cur, int &max)
	{
		if (root == nullptr)
			return;
		if (cur >= max)
			max = cur;
		maxDepth(root->left, cur + 1, max);
		maxDepth(root->right, cur + 1, max);
	}
};
//更简洁的递归方法
class Solution2
{
public:
	int maxDepth(TreeNode* root)
	{
		if (root == nullptr) return 0;
		return max(maxDepth(root->left), maxDepth(root->right)) + 1;
	}
};
//迭代的方法
class Solution3
{
public:
	int maxDepth(TreeNode* root)
	{
		queue<TreeNode*> current, next;
		int result = 0;
		if (root == nullptr)
			return 0;
		else
			current.push(root);
		while (!current.empty()) {
			while (!current.empty()) {
				TreeNode* node = current.front();
				current.pop();
				if (node->left != nullptr) next.push(node->left);
				if (node->right != nullptr) next.push(node->right);
			}
			result++;
			swap(next, current);
		}
		return result;
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
//	Solution3 test;
//	ManageTree manageTree;
//	TreeNode *root = new TreeNode(3);
//	root->left = new TreeNode(9);
//	root->right = new TreeNode(20);
//	root->left->left = new TreeNode(15);
//	root->left->right = new TreeNode(7);
//
//	cout << test.maxDepth(root) << endl;
//	manageTree.destroy(root);
//	root = new TreeNode(1);
//	root->left = new TreeNode(2);
//	root->right = new TreeNode(3);
//	root->left->left = new TreeNode(4);
//	root->right->right = new TreeNode(5);
//	cout << test.maxDepth(root);
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