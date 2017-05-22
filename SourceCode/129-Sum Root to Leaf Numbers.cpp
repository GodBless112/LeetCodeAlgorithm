//	129. Sum Root to Leaf Numbers
//------------------------------------------------------------------------------//
//	Given a binary tree containing digits from 0-9 only, each root-to-leaf path //
//	could represent a number.													//
//	An example is the root - to - leaf path 1->2->3 which represents the number //
//	123.																		//
//	Find the total sum of all root - to - leaf numbers.							//
//	For example,																//
//		1																		//
//	   / \																		//
//	  2   3																		//
//	The root - to - leaf path 1->2 represents the number 12.					//
//	The root - to - leaf path 1->3 represents the number 13.					//
//	Return the sum = 12 + 13 = 25.												//
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
//DFS,递归
class Solution {
public:
	int sumNumbers(TreeNode* root) {
		int result = 0;
		sumNumbers(root, 0, result);
		return result;
	}
private:
	void sumNumbers(TreeNode* root, int Path, int &result) {
		if (root == nullptr) return;
		if (root->left == nullptr && root->right == nullptr)
			result += Path * 10 + root->val;
		sumNumbers(root->left, Path * 10 + root->val, result);
		sumNumbers(root->right, Path * 10 + root->val, result);
	}
};
//另一种递归
class Solution2 {
public:
	int sumNumbers(TreeNode *root) {
		return dfs(root, 0);
	}
private:
	int dfs(TreeNode *root, int sum) {
		if (root == nullptr) return 0;
		if (root->left == nullptr && root->right == nullptr)
			return sum * 10 + root->val;
		return dfs(root->left, sum * 10 + root->val) +
			dfs(root->right, sum * 10 + root->val);
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
//	TreeNode *root = new TreeNode(1);
//	root->left = new TreeNode(2);
//	root->right = new TreeNode(3);
//	cout << test.sumNumbers(root);
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