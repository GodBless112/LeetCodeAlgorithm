//	114. Flatten Binary Tree to Linked List
//------------------------------------------------------------------------------//
//	Given a binary tree, flatten it to a linked list in-place.					//
//	For example,																//
//	Given																		//
//			1																	//
//		   / \																	//
//		  2   5																	//
//		 / \   \																//
//		3   4   6																//
//	The flattened tree should look like :										//
//	1																			//
//	 \																			//
//	  2																			//
//	   \																		//
// 	    3																		//
//		 \																		//
//		  4																		//
//		   \																	//
//			5																	//
//			 \																	//
//			  6																	//
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
//递归：自底向上的做法，利用深度优先搜索找到前序遍历中最后的节点
//然后将其最后的节点，然后层层逆推
class Solution {
public:
	void flatten(TreeNode* root) {
		if (root == nullptr)
			return;
		flatten(root->right);
		flatten(root->left);
		root->right = prev;
		root->left = nullptr;
		prev = root;
	}
private:
	TreeNode* prev = nullptr;	//C++11的特性，可以在声明时赋初值
};
//DFS，左右分别处理，左子树插入到根节点和右子树之间
class Solution2 {
public:
	void flatten(TreeNode* root) {
		if (root == nullptr) return;
		flatten(root->left);
		flatten(root->right);
		if (nullptr == root->left) return;
		//将左子树插入到root和root->right之间
		TreeNode* p = root->left;
		while (p->right) p = p->right;
		p->right = root->right;
		root->right = root->left;
		root->left = nullptr;
	}
};
//利用一个head记录头结点，一个tail记录尾节点
//本质的思想类似于方法一，自底向上，递归回溯
//时，tail指向的是上一次递归的结果，也就是当
//前节点应该连接的节点
class Solution3 {
public:
	void flatten(TreeNode* root) {
		flatten(root, nullptr);
	}
private:
	TreeNode* flatten(TreeNode *head, TreeNode *tail) {
		if (nullptr == head) return tail;
		head->right = flatten(head->left, flatten(head->right, tail));
		head->left = nullptr;
		return head;
	}
};
//迭代的方法，利用一个栈来实现前序遍历
//每次把栈顶的节点的右节点，左节点一次压入栈，当前节点左节点变为null，右节点变为栈顶节点
class Solution4 {
public:
	void flatten(TreeNode* root) {
		if (root == nullptr) return;
		stack<TreeNode*> s;
		s.push(root);
		while (!s.empty()) {
			auto p = s.top();
			s.pop();
			if (p->right)
				s.push(p->right);
			if (p->left)
				s.push(p->left);
			p->left = nullptr;
			if (!s.empty())
				p->right = s.top();
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
//	TreeNode* root = new TreeNode(1);
//	root->left = new TreeNode(2);
//	root->right = new TreeNode(5);
//	root->left->left = new TreeNode(3);
//	root->left->right = new TreeNode(4);
//	root->right->right = new TreeNode(6);
//	test.flatten(root);
//	manageTree.showTree(root, 0);
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