//	230. Kth Smallest Element in a BST
//------------------------------------------------------------------------------//
//	Given a binary search tree, write a function kthSmallest to find the kth	//
//	smallest element in it.														//
//	Note:																		//
//	You may assume k is always valid, 1 ? k ? BST's total elements.				//
//	Follow up :																	//
//	What if the BST is modified(insert / delete operations) often and you need	//
//	to find the kth smallest frequently ? How would you optimize the kthSmallest//
//	routine ?																	//
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
//利用栈,递归的做法，中序遍历
class Solution {
public:
	int kthSmallest(TreeNode* root, int k) {
		pushAll(root);
		for (int i = 0; i < k - 1; ++i) {
			TreeNode* cur = s.top();
			s.pop();
			pushAll(cur->right);
		}
		return s.top()->val;
	}
private:
	stack<TreeNode *> s;
	void pushAll(TreeNode *root) {
		while (root) {
			s.push(root);
			root = root->left;
		}
	}
};
//中序遍历，将k值变成了引用，如果输入时右值时，会出错，最好用方案3
class Solution2 {
public:
	int kthSmallest(TreeNode* root, int& k) {
		if (root) {
			int x = kthSmallest(root->left, k);
			return !k ? x : !--k ? root->val : kthSmallest(root->right, k);
		}
	}
};
//中序遍历，不改变原先函数形式，用一个helper
class Solution3 {
public:
	int kthSmallest(TreeNode* root, int k) {
		return find(root, k);
	}
	int find(TreeNode* root, int& k) {
		if (root) {
			int x = find(root->left, k);
			return !k ? x : !--k ? root->val : find(root->right, k);
		}
		return 0;
	}
};
//法1迭代形式
class Solution4 {
public:
	int kthSmallest(TreeNode* root, int k) {
		stack<TreeNode *> st;
		TreeNode *p = root;
		while (p || !st.empty())
		{
			while (p)
			{
				st.push(p);
				p = p->left;
			}
			p = st.top();
			if (--k == 0)
				return p->val;
			st.pop();
			p = p->right;
		}
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
};
//int main(void)
//{
//	Solution3 test;
//	ManageTree mt;
//	TreeNode *root = new TreeNode(1);
//	root->left = new TreeNode(3);
//	root->left->left = new TreeNode(1);
//	root->left->left->right = new TreeNode(2);
//	root->left->right = new TreeNode(4);
//	root->right = new TreeNode(7);
//	root->right->left = new TreeNode(6);
//	root->right->right = new TreeNode(9);
//	root->right->right->left = new TreeNode(8);
//	root->right->right->right = new TreeNode(10);
//	cout << test.kthSmallest(root, 1);
//	mt.destroy(root);
//	cout << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}