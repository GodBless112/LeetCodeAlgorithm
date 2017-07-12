//	257. Binary Tree Paths
//------------------------------------------------------------------------------//
//	Given a binary tree, return all root-to-leaf paths.							//
//	For example, given the following binary tree :								//
//			1																	//
//		   / \																	//
//		  2   3																	//
//		   \																	//
//			5																	//
//	All root - to - leaf paths are :											//
//	["1->2->5", "1->3"]															//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<sstream>
#include<unordered_map>
#include<stack>
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
//递归版本
class Solution {
public:
	vector<string> binaryTreePaths(TreeNode* root) {
		vector<string> result;
		string path;
		helper(root, path, result);
		return result;
	}
private:
	void helper(TreeNode *root, string path, vector<string> &result) {
		if (root == nullptr) return;
		if (root->left == nullptr&&root->right == nullptr) {
			path += to_string(root->val);
			result.push_back(path);
			return;
		}
		path += to_string(root->val) + "->";
		helper(root->left, path, result);
		helper(root->right, path, result);
	}
};
//迭代版，用栈
class Solution2 {
public:
	vector<string> binaryTreePaths(TreeNode* root) {
		vector<string> res;
		TreeNode *curNode;
		string curPath;
		stack<pair<TreeNode*, string>> liveNodes;
		if (root) liveNodes.push(make_pair(root, ""));
		while (!liveNodes.empty())
		{
			curNode = liveNodes.top().first;
			curPath = liveNodes.top().second;
			liveNodes.pop();
			if (!curNode->left && !curNode->right)
			{
				res.push_back(curPath + std::to_string(curNode->val));
			}
			else
			{
				if (curNode->left)  liveNodes.push(make_pair(curNode->left, curPath + std::to_string(curNode->val) + "->"));
				if (curNode->right) liveNodes.push(make_pair(curNode->right, curPath + std::to_string(curNode->val) + "->"));
			}
		}
		return res;
	}
};
//迭代版，利用队列
class Solution3 {
public:
	vector<string> binaryTreePaths(TreeNode* root) {
		queue<pair<TreeNode*, string>> liveNodes[2];
		int cur = 0, next = 1;
		TreeNode* curNode;
		string curPath;
		vector<string> res;

		if (root) liveNodes[cur].push(make_pair(root, ""));
		while (!liveNodes[cur].empty())
		{
			curNode = liveNodes[cur].front().first;
			curPath = liveNodes[cur].front().second;
			liveNodes[cur].pop();
			if (!curNode->left && !curNode->right) res.push_back(curPath + std::to_string(curNode->val));
			else {
				if (curNode->left)  liveNodes[next].push(make_pair(curNode->left, curPath + std::to_string(curNode->val) + "->"));
				if (curNode->right) liveNodes[next].push(make_pair(curNode->right, curPath + std::to_string(curNode->val) + "->"));
			}
			if (liveNodes[cur].empty()) swap(cur, next);
		}
		return res;
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
//	TreeNode *root = new TreeNode(5);
//	root->left = new TreeNode(3);
//	root->left->left = new TreeNode(1);
//	root->left->right = new TreeNode(2);
//	root->right = new TreeNode(7);
//	root->right->left = new TreeNode(4);
//	root->right->right = new TreeNode(8);
//	auto res = test.binaryTreePaths(root);
//	for (auto s : res)
//		cout << s << endl;
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