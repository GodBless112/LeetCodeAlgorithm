//	101. Symmetric Tree
//------------------------------------------------------------------------------//
//	Given a binary tree, check whether it is a mirror of itself (ie, symmetric	//
//	around its center).															//
//	For example, this binary tree[1, 2, 2, 3, 4, 4, 3] is symmetric :			//
//		1																		//
//	   / \																		//
//	  2   2																		//
//	 / \ / \																	//
//	3  4 4  3																	//
//	But the following[1, 2, 2, null, 3, null, 3] is not:						//
//		1																		//
//	   / \																		//
//	  2   2																		//
//	   \   \																	//
//		3    3																	//
//	Note:																		//
//	Bonus points if you could solve it both recursively and iteratively.		//
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

struct TreeNode {
    int val;
    TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
//递归的方法，比较左子树的节点翻转到右子树对应结点是否一致
class Solution 
{
public:
	bool isSymmetric(TreeNode* root) 
	{
		if (root == nullptr)
			return true;
		return isSymmetric(root->left, root->right);
	}
private:
	bool isSymmetric(TreeNode* p, TreeNode* q)
	{
		if (p == nullptr && q == nullptr)
			return true;
		if (p == nullptr || q == nullptr)
			return false;
		return p->val == q->val && isSymmetric(p->left, q->right) 
			&& isSymmetric(p->right, q->left);
	}
};
//迭代版本
class Solution2
{
public:
	bool isSymmetric(TreeNode* root)
	{
		if (root == nullptr)
			return true;
		stack<TreeNode*> mystack;
		mystack.push(root->left);
		mystack.push(root->right);
		while (!mystack.empty())
		{
			TreeNode* p = mystack.top(); mystack.pop();
			TreeNode* q = mystack.top(); mystack.pop();
			if (!p && !q)
				continue;
			if (!p || !q)
				return false;
			if (p->val != q->val)
				return false;
			mystack.push(p->left);
			mystack.push(q->right);
			mystack.push(p->right);
			mystack.push(q->left);
		}
		return true;
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
//	root->right = new TreeNode(2);
//	root->left->left = new TreeNode(3);
//	root->left->right = new TreeNode(4);
//	root->right->left = new TreeNode(4);
//	root->right->right = new TreeNode(3);
//	cout << boolalpha << test.isSymmetric(root) << endl;
//	manageTree.destroy(root);
//	root = new TreeNode(1);
//	root->left = new TreeNode(2);
//	root->right = new TreeNode(3);
//	cout << boolalpha << test.isSymmetric(root);
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