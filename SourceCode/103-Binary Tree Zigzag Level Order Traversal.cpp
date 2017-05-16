//	103. Binary Tree Zigzag Level Order Traversal
//------------------------------------------------------------------------------//
//	Given a binary tree, return the zigzag level order traversal of its nodes'	//
//	values. (ie, from left to right, then right to left for the next level and	//
//	alternate between).															//
//	For example :																//
//	Given binary tree[3, 9, 20, null, null, 15, 7],								//
//		 3																		//
//		/ \																		//
//	   9  20																	//
//		 / \																	//
//		15  7																	//
//	return its zigzag level order traversal as :								//
//	[																			//
//		[3],																	//
//		[20, 9],																//
//		[15, 7]																	//
//	]		 																	//
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
//迭代的方法，利用两个双向队列
class Solution 
{
public:
	vector<vector<int>> zigzagLevelOrder(TreeNode* root) 
	{
		vector<vector<int>> result;
		if (root == nullptr)
			return result;
		deque<TreeNode*> cur;
		deque<TreeNode*> next;
		int type = 0;
		cur.push_back(root);
		while (!cur.empty())
		{
			vector<int> level;
			while (!cur.empty())
			{
				TreeNode *node;
				node = cur.back();
				cur.pop_back();
				level.push_back(node->val);
				if (type == 0)
				{
					if (node->left)
						next.push_back(node->left);
					if (node->right)
						next.push_back(node->right);
				}
				else
				{
					if (node->right)
						next.push_back(node->right);
					if (node->left)
						next.push_back(node->left);
				}
			}
			type = (type + 1) % 2;
			result.push_back(level);
			swap(cur, next);
		}
		return result;
	}
};
//递归的方法
class Solution2 
{
public:
	vector<vector<int>> zigzagLevelOrder(TreeNode* root)
	{
		vector<vector<int>> result;
		traverse(root, 1, result);
		return result;
	}
private:
	void traverse(TreeNode *root, size_t level, vector<vector<int>> &result)
	{
		if (root == nullptr)
			return;
		if (level > result.size())
			result.push_back(vector<int>());
		if (level & 0x01)
			result[level - 1].push_back(root->val);
		else
			result[level - 1].insert(result[level - 1].begin(), root->val);
		traverse(root->left, level + 1, result);
		traverse(root->right, level + 1, result);
	}
};
//迭代的方法2，利用单向队列，偶数层取反
class Solution3 {
public:
	vector<vector<int> > zigzagLevelOrder(TreeNode *root) {
		vector<vector<int> > result;
		queue<TreeNode*> current, next;
		bool left_to_right = true;
		if (root == nullptr) {
			return result;
		}
		else {
			current.push(root);
		}
		while (!current.empty()) {
			vector<int> level; // elments in one level
			while (!current.empty()) {
				TreeNode* node = current.front();
				current.pop();
				level.push_back(node->val);
				if (node->left != nullptr) next.push(node->left);
				if (node->right != nullptr) next.push(node->right);
			}
			if (!left_to_right) reverse(level.begin(), level.end());
			result.push_back(level);
			left_to_right = !left_to_right;
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
//	auto levelOrder = test.zigzagLevelOrder(root);
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
//	levelOrder = test.zigzagLevelOrder(root);
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