//	107. Binary Tree Level Order Traversal II
//------------------------------------------------------------------------------//
//	Given a binary tree, return the bottom-up level order traversal of its		//
//	nodes' values. (ie, from left to right, level by level from leaf to root).	//
//	For example :																//
//	Given binary tree[3, 9, 20, null, null, 15, 7],								//
//		3																		//
//	   / \																		//
//	  9  20																		//
//		/ \																		//
//	   15   7																	//
//	return its bottom - up level order traversal as :							//
//	[																			//
//		[15, 7],																//
//		[9, 20],																//
//		[3]																		//
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
//迭代的方法，利用队列实现层序遍历，最后反向。
//或者采用插入的方式，插入到begin前，但不建议这样
class Solution
{
public:
	vector<vector<int>> levelOrderBottom(TreeNode* root)
	{
		vector<vector<int>> result;
		if (root == nullptr)
			return result;
		queue<TreeNode*> cur, next;
		cur.push(root);
		while (!cur.empty())
		{
			vector<int> level;
			while (!cur.empty())
			{
				TreeNode* node = cur.front(); cur.pop();
				level.push_back(node->val);
				if (node->left)
					next.push(node->left);
				if (node->right)
					next.push(node->right);
			}
			result.push_back(level);
			swap(cur, next);
		}
		reverse(result.begin(), result.end());
		return result;
	}
};
//递归的方法，insert的方法比reverse要慢，这是因为vector插入不是常数时间
class Solution2
{
public:
	vector<vector<int>> levelOrderBottom(TreeNode* root)
	{
		vector<vector<int>> result;
		tranverse(root, 1, result);
		return result;
	}
private:
	void tranverse(TreeNode* root, size_t level, vector<vector<int>>& result)
	{
		if (root == nullptr)
			return;
		if (level > result.size())
			result.insert(result.begin(), vector<int>());
		result[result.size() - level].push_back(root->val);
		tranverse(root->left, level + 1, result);
		tranverse(root->right, level + 1, result);
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
//	auto levelOrder = test.levelOrderBottom(root);
//	for_each(levelOrder.begin(), levelOrder.end(), [](vector<int> &x) {
//		for (auto y : x)
//			cout << y << " ";
//		cout << endl;
//	});
//	manageTree.destroy(root);
//	root = new TreeNode(1);
//	root->left = new TreeNode(2);
//	root->right = new TreeNode(3);
//	root->left->left = new TreeNode(4);
//	root->right->right = new TreeNode(5);
//	levelOrder = test.levelOrderBottom(root);
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