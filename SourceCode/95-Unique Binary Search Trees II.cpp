//	95. Unique Binary Search Trees II
//------------------------------------------------------------------------------//
//	Given an integer n, generate all structurally unique BST's					//
//	(binary search trees) that store values 1...n.								//
//	For example,																//
//	Given n = 3, your program should return all 5 unique BST's shown below.		//
//	1      3	 3      2      1												//
//	 \	  /		/	   / \      \												//
//	 3   2     1      1   3      2												//
//	/	/		\                 \												//
// 2   1         2                 3											//
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
//分析同I，递归的做法
class Solution
{
public:
	vector<TreeNode*> generateTrees(int n)
	{
		if (n == 0) return vector<TreeNode*>();
		return generate(1, n);
	}
private:
	vector<TreeNode *> generate(int start, int end) {
		vector<TreeNode *> subTree;
		if (start > end)
		{
			subTree.push_back(nullptr);
			return subTree;
		}
		for (int k = start; k <= end; k++) {
			vector<TreeNode*> leftTree = generate(start, k - 1);
			vector<TreeNode*> rightTree = generate(k + 1, end);
			for (auto i : leftTree) {
				for (auto j : rightTree) {
					TreeNode *node = new TreeNode(k);
					node->left = i;
					node->right = j;
					subTree.push_back(node);
				}
			}
		}
		return subTree;
	}
};
//动态规划，迭代形式，n的树林由n-1的树林生成，分两种情况
//1.n为根节点，n不为根节点
class Solution2 {
public:
	TreeNode* clone(TreeNode* root) {
		if (root == nullptr)
			return nullptr;
		TreeNode* newroot = new TreeNode(root->val);
		newroot->left = clone(root->left);
		newroot->right = clone(root->right);
		return newroot;
	}
	vector<TreeNode *> generateTrees(int n) {
		if (n == 0)
			return vector<TreeNode *>();
		vector<TreeNode *> res(1, nullptr);
		for (int i = 1; i <= n; i++) {
			vector<TreeNode *> tmp;
			for (int j = 0; j<res.size(); j++) {
				TreeNode* oldroot = res[j];
				TreeNode* root = new TreeNode(i);
				TreeNode* target = clone(oldroot);
				root->left = target;
				tmp.push_back(root);

				if (oldroot != nullptr) {
					TreeNode* tmpold = oldroot;
					while (tmpold->right != nullptr) {
						TreeNode* nonroot = new TreeNode(i);
						TreeNode *tright = tmpold->right;
						tmpold->right = nonroot;
						nonroot->left = tright;
						TreeNode *target = clone(oldroot);
						tmp.push_back(target);
						tmpold->right = tright;
						tmpold = tmpold->right;
					}
					tmpold->right = new TreeNode(i);
					TreeNode *target = clone(oldroot);
					tmp.push_back(target);
					tmpold->right = nullptr;
				}
			}
			res = tmp;
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
//	Solution2 test;
//	int n = 0;
//	auto Trees = test.generateTrees(n);
//	ManageTree manageTree;
//	for (auto x : Trees)
//	{
//		manageTree.showTree(x, 0);
//		cout << "--------------------" << endl;
//		manageTree.destroy(x);
//	}
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