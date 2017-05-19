//	113. Path Sum II
//------------------------------------------------------------------------------//
//	Given a binary tree and a sum, find all root-to-leaf paths where each		//
//	path's sum equals the given sum.											//
//	For example :																//
//	Given the below binary tree and sum = 22,									//
//			5																	//
//		   / \																	//
//		  4   8																	//
//		 /   / \																//
//		11  13  4																//
//	   / \	   / \																//
//	  7   2	  5   1																//
//	return																		//
//	[																			//
//		[5, 4, 11, 2],															//
//		[5, 8, 4, 5]															//
//	]																			//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<stack>
// constants
// function prototype
using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
//深度优先搜索，找到叶子节点后，如果是一条合法路径，则记录到result
//采用Path记录路径，每次复制一份
class Solution {
public:
	vector<vector<int>> pathSum(TreeNode* root, int sum) {
		vector<vector<int>> result;
		vector<int> Path;
		pathSum(root, sum, Path, result);
		return result;
	}
private:
	void pathSum(TreeNode* root, int sum, 
		vector<int> Path, vector<vector<int>> &result) {
		if (root == nullptr) return;
		if (root->left == nullptr && root->right == nullptr) {
			if (root->val == sum) {
				Path.push_back(root->val);
				result.push_back(Path);
			}
			return;
		}
		Path.push_back(root->val);
		pathSum(root->left, sum - root->val, Path, result);
		pathSum(root->right, sum - root->val, Path, result);
	}
};
//公用一份Path记录路径，每次回溯弹出当前节点，这样效率更高
class Solution2 {
public:
	vector<vector<int>> pathSum(TreeNode* root, int sum) {
		vector<vector<int>> result;
		vector<int> Path;
		pathSum(root, sum, Path, result);
		return result;
	}
private:
	void pathSum(TreeNode* root, int sum,
		vector<int> &Path, vector<vector<int>> &result) {
		if (root == nullptr) return;
		Path.push_back(root->val);
		if (root->left == nullptr && root->right == nullptr && root->val == sum)
			result.push_back(Path);
		pathSum(root->left, sum - root->val, Path, result);
		pathSum(root->right, sum - root->val, Path, result);
		Path.pop_back();
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
//	TreeNode* root = new TreeNode(5);
//	root->left = new TreeNode(4);
//	root->right = new TreeNode(8);
//	root->left->left = new TreeNode(11);
//	root->left->left->left = new TreeNode(7);
//	root->left->left->right = new TreeNode(2);
//	root->right->left = new TreeNode(13);
//	root->right->right = new TreeNode(4);
//	root->right->right->left = new TreeNode(5);
//	root->right->right->right = new TreeNode(1);
//	auto res = test.pathSum(root, 22);
//	for_each(res.begin(), res.end(), [](vector<int> &x) {
//		for (auto y : x)
//			cout << y << " ";
//		cout << endl;
//	});
//	manageTree.destroy(root);
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