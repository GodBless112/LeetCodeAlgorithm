//	199. Binary Tree Right Side View
//------------------------------------------------------------------------------//
//	Given a binary tree, imagine yourself standing on the right side of it,		//
//	return the values of the nodes you can see ordered from top to bottom.		//
//	For example :																//
//	Given the following binary tree,											//
//		 1           <-- -														//
//		/ \																		//
//		2  3         <-- -														//
//		 \	\																	//
//		  5  4       <-- -														//
//	You should return[1, 3, 4].													//
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
//DFS，用一个变量记录所在层数，有点类似于前序遍历
class Solution {
public:
	vector<int> rightSideView(TreeNode* root) {
		vector<int> result;
		rightSideView(root, 0, result);
		return result;
	}
private:
	void rightSideView(TreeNode* root, int level, vector<int> &result) {
		if (nullptr == root) return;
		if (level >= result.size())
			result.push_back(root->val);
		rightSideView(root->right, level + 1, result);
		rightSideView(root->left, level + 1, result);
	}
};
//BFS，利用两个队列实现（用栈也可以）
class Solution2 {
public:
	vector<int> rightSideView(TreeNode* root) {
		vector<int> result;
		if (nullptr == root) return result;
		queue<TreeNode*> q;
		queue<TreeNode*> cur;
		q.push(root);
		while (!q.empty()) {
			result.push_back(q.front()->val);
			while (!q.empty()) {
				TreeNode* node = q.front();
				q.pop();
				if (node->right)
					cur.push(node->right);
				if (node->left)
					cur.push(node->left);
			}
			swap(q, cur);
		}
		return result;
	}
};
//用一个队列实现
class Solution3 {
public:
	vector<int> rightSideView(TreeNode* root) {
		vector<int> result;
		if (nullptr == root) return result;
		queue<TreeNode*> q;
		q.push(root);
		while (!q.empty()) {
			result.push_back(q.front()->val);
			for (int i = q.size(); i > 0; --i) {
				TreeNode* node = q.front();
				q.pop();
				if (node->right)
					q.push(node->right);
				if (node->left)
					q.push(node->left);
			}
		}
		return result;
	}
};
//分治法，比较巧妙，分别获得左右子树的右视图，合成的时候
//右子树加上左子树多出的部分
class Solution4 {
public:
	vector<int> rightSideView(TreeNode* root) {
		vector<int> result;
		if (nullptr == root) return result;
		vector<int> left = rightSideView(root->left);
		vector<int> right = rightSideView(root->right);
		result.push_back(root->val);
		for (int i = 0; i < max(left.size(), right.size()); ++i) {
			if (i >= right.size())
				result.push_back(left[i]);
			else
				result.push_back(right[i]);
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
//	Solution4 test;
//	ManageTree manageTree;
//	TreeNode *root = new TreeNode(1);
//	root->left = new TreeNode(2);
//	root->right = new TreeNode(3);
//	root->left->left = new TreeNode(5);
//	root->right->right = new TreeNode(4);
//	auto res = test.rightSideView(root);
//	for_each(res.begin(), res.end(), [](int x) {cout << x << " "; });
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