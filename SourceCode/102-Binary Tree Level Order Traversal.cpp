//	102. Binary Tree Level Order Traversal
//------------------------------------------------------------------------------//
//	Given a binary tree, return the level order traversal of its nodes' values. //
//	(ie, from left to right, level by level).									//
//	For example :																//
//	Given binary tree[3, 9, 20, null, null, 15, 7],								//
//		3																		//
//	   / \																		//
//	  9   20																	//
//	 / \																		//
//	15  7																		//
//	return its level order traversal as :										//
//	[																			//
//		[3],																	//
//		[9, 20],																//
//		[15, 7]																	//
//	]		 																	//
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
//层序遍历
//迭代的方法，利用两个队列，一个队列记录当前层的节点，一个队列记录下一层的
class Solution 
{
public:
	vector<vector<int>> levelOrder(TreeNode* root) 
	{
		vector<vector<int>> result;
		if (root == nullptr)
			return result;
		queue<TreeNode*> curStack;
		curStack.push(root);
		while (!curStack.empty())
		{
			vector<int> level;
			queue<TreeNode*> NextStack;
			while (!curStack.empty())
			{
				TreeNode *node = curStack.front(); curStack.pop();
				level.push_back(node->val);
				if (node->left)
					NextStack.push(node->left);
				if (node->right)
					NextStack.push(node->right);
			}
			result.push_back(level);
			curStack = NextStack;
		}
		return result;
	}
};
//递归的方法
class Solution2
{
public:
	vector<vector<int> > levelOrder(TreeNode *root) 
	{
		vector<vector<int>> result;
		traverse(root, 1, result);
		return result;
	}
	void traverse(TreeNode *root, size_t level, vector<vector<int>> &result) 
	{
		if (!root) return;
		if (level > result.size())
			result.push_back(vector<int>());
		result[level - 1].push_back(root->val);
		traverse(root->left, level + 1, result);
		traverse(root->right, level + 1, result);
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
//	root->left->right = new TreeNode(7);
//
//	auto levelOrder = test.levelOrder(root);
//	for_each(levelOrder.begin(), levelOrder.end(), [](vector<int> &x) {
//		for (auto y : x)
//			cout << y << " ";
//		cout << endl;
//	});
//	manageTree.destroy(root);
//	root = new TreeNode(1);
//	root->left = new TreeNode(2);
//	root->right = new TreeNode(3);
//	levelOrder = test.levelOrder(root);
//	for_each(levelOrder.begin(), levelOrder.end(), [](vector<int> &x) {
//		for (auto y : x)
//			cout << y << " ";
//		cout << endl;
//	});
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