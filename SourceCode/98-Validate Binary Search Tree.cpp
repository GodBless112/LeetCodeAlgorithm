//	98. Validate Binary Search Tree
//------------------------------------------------------------------------------//
//	Given a binary tree, determine if it is a valid binary search tree (BST).	//
//	Assume a BST is defined as follows :										//
//	The left subtree of a node contains only nodes with keys less than the		//
//	node's key.																	//
//	The right subtree of a node contains only nodes with keys greater than the	//
//	node's key.																	//
//	Both the left and right subtrees must also be binary search trees.			//
//	Example 1 :																	//
//		 2																		//
//		/ \																		//
//	   1   3																	//
//	Binary tree[2, 1, 3], return true.											//
//	Example 2:																	//
//		 1																		//
//		/ \																		//
//	   2   3																	//
//	Binary tree[1, 2, 3], return false.											//
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
//二叉查找树的性质：对于节点X，它的左子树的所有元素都比X的元素小，右子树的所有元素都比X的元素大
//可以利用定界来检查是否合法
class Solution 
{
public:
	bool isValidBST(TreeNode* root) 
	{
		return isValidBST(root, nullptr, nullptr);
	}
private:
	bool isValidBST(TreeNode *root, TreeNode* minNode, TreeNode* maxNode)
	{
		if (root == nullptr)
			return true;
		if (minNode && root->val <= minNode->val || maxNode && root->val >= maxNode->val)
			return false;
		return isValidBST(root->left, minNode, root) && isValidBST(root->right, root, maxNode);
	}
};
//利用中序遍历来检查是否合法
class Solution2 {
public:
	bool isValidBST(TreeNode* root) {
		TreeNode* prev = nullptr;
		return validate(root, prev);
	}
	bool validate(TreeNode* node, TreeNode* &prev) {
		if (node == nullptr) return true;
		if (!validate(node->left, prev)) return false;
		if (prev != nullptr && prev->val >= node->val) return false;
		prev = node;
		return validate(node->right, prev);
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
//	TreeNode *root = new TreeNode(2);
//	root->left = new TreeNode(1);
//	root->right = new TreeNode(3);
//	cout << boolalpha << test.isValidBST(root) << endl;
//	manageTree.destroy(root);
//	root = new TreeNode(1);
//	root->left = new TreeNode(2);
//	root->right = new TreeNode(3);
//	cout << boolalpha << test.isValidBST(root);
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