//	235. Lowest Common Ancestor of a Binary Search Tree
//------------------------------------------------------------------------------//
//	Given a binary search tree (BST), find the lowest common ancestor (LCA) of	//
//	two given nodes in the BST.													//
//	According to the definition of LCA on Wikipedia : “The lowest common		//
//	ancestor is defined between two nodes v and w as the lowest node in T		//
//	that has both v and w as descendants(where we allow a node to be a			//
//	descendant of itself).”													//
//				_______6______													//
//			  /				   \												//
//		   ___2__            ___8__												//
//		  /		 \		   /		\											//
//		 0      _4        7          9											//
//			   /   \															//
//			  3     5															//
//	For example, the lowest common ancestor(LCA) of nodes 2 and 8 is 6. Another //
//	example is LCA of nodes 2 and 4 is 2, since a node can be a descendant of	//
//	itself according to the LCA definition.										//
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
//从根节点往下，遇到刚好能囊括这两个节点的时候停止，并返回，迭代的方法
class Solution {
public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		while (true) {
			if (p->val < root->val && q->val < root->val)
				root = root->left;
			else if (p->val > root->val && q->val > root->val)
				root = root->right;
			else
				return root;
		}
		return root;
	}
};
//递归的方法
class Solution2 {
public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		if (p->val < root->val &&q->val < root->val)
			return lowestCommonAncestor(root->left, p, q);
		if (p->val > root->val && q->val > root->val)
			return lowestCommonAncestor(root->right, p, q);
		return root;
	}
};
//另外的实现形式
class Solution3 {
public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		return (root->val - p->val) * (root->val - q->val) < 1 ? root :
			lowestCommonAncestor(p->val < root->val ? root->left : root->right, p, q);
	}
};
//另外的实现形式
class Solution4 {
public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		while ((root->val - p->val) * (root->val - q->val) > 0)
			root = (p->val < root->val) ? root->left : root->right;
		return root;
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
//	TreeNode *root = new TreeNode(5);
//	root->left = new TreeNode(3);
//	root->left->left = new TreeNode(1);
//	root->left->right = new TreeNode(2);
//	root->right = new TreeNode(7);
//	root->right->left = new TreeNode(4);
//	root->right->right = new TreeNode(8);
//	TreeNode *res = test.lowestCommonAncestor(root, root->left->left, root->left);
//	manageTree.showTree(res, 0);
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