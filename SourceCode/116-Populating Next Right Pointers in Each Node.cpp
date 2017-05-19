//	116. Populating Next Right Pointers in Each Node
//------------------------------------------------------------------------------//
//	Given a binary tree															//
//	struct TreeLinkNode {														//
//		TreeLinkNode *left;														//
//		TreeLinkNode *right;													//
//		TreeLinkNode *next;														//
//	}																			//
//	Populate each next pointer to point to its next right node.If there is no	//
//	next right node, the next pointer should be set to NULL.					//
//	Initially, all next pointers are set to NULL.								//
//	Note:																		//
//	You may only use constant extra space.										//
//	You may assume that it is a perfect binary tree(ie, all leaves are at the	//
//	same level, and every parent has two children).								//
//	For example,																//
//	Given the following perfect binary tree,									//
//			1																	//
//		   / \																	//
//		  2   3																	//
//		 / \ / \																//
//		4  5 6  7																//
//	After calling your function, the tree should look like :					//
//			 1->NULL															//
//		   /  \																	//
//		  2 -> 3->NULL															//
//		 / \  / \																//
//		4->5->6->7->NULL														//
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


struct TreeLinkNode {
	int val;
	TreeLinkNode *left, *right, *next;
	TreeLinkNode(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};
//常数空间的方法，只能迭代！！
//一层一层的进行，每次用一个节点指向一层的最前面的节点
class Solution {
public:
	void connect(TreeLinkNode *root) {
		TreeLinkNode* head = root;
		TreeLinkNode*p = nullptr;
		while (head) {
			p = head;
			while (p && p->left) {
				p->left->next = p->right;
				if (p->next)
					p->right->next = p->next->left;
				p = p->next;
			}
			head = head->left;
		}
	}
};
//迭代的方法，利用一个queue，但这样不是常数空间
class Solution2 {
public:
	void connect(TreeLinkNode *root) {
		if (nullptr == root) return;
		queue<TreeLinkNode*> cur, next;
		cur.push(root);
		while (!cur.empty()) {
			while (!cur.empty()) {
				TreeLinkNode* node = cur.front();
				cur.pop();
				if (!cur.empty())
					node->next = cur.front();
				if (node->left)
					next.push(node->left);
				if (node->right)
					next.push(node->right);
			}
			swap(cur, next);
		}
	}
};
//递归的方法，利用一个节点记录它的右兄弟，但是这样也不是常数空间
class Solution3 {
public:
	void connect(TreeLinkNode *root) {
		connect(root, nullptr);
	}
private:
	void connect(TreeLinkNode *root, TreeLinkNode* rightBro) {
		if (nullptr == root) return;
		root->next = rightBro;
		if (rightBro && rightBro->left)
			rightBro = rightBro->left;
		connect(root->left, root->right);
		connect(root->right, rightBro);
	}
};
//递归的方法2，一样的问题，空间复杂度不是常数
class Solution4 {
public:
	void connect(TreeLinkNode *root) {
		if (!root) return;
		if (root->left) {
			root->left->next = root->right;
			if (root->next)
				root->right->next = root->next->left;
		}
		connect(root->left);
		connect(root->right);
	}
};

class ManageTree
{
public:
	void destroy(TreeLinkNode *root)
	{
		if (root == nullptr)
			return;
		destroy(root->left);
		destroy(root->right);
		delete root;
	}
	void showTree(TreeLinkNode *root, int distance)
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
//	Solution test;
//	ManageTree manageTree;
//	TreeLinkNode* root = new TreeLinkNode(1);
//	root->left = new TreeLinkNode(2);
//	root->right = new TreeLinkNode(3);
//	root->left->left = new TreeLinkNode(4);
//	root->left->right = new TreeLinkNode(5);
//	root->right->left = new TreeLinkNode(6);
//	root->right->right = new TreeLinkNode(7);
//	test.connect(root);
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