//	117. Populating Next Right Pointers in Each Node II
//------------------------------------------------------------------------------//
//	Follow up for problem "Populating Next Right Pointers in Each Node".		//
//	What if the given tree could be any binary tree ? Would your previous		//
//	solution still work ?														//
//	Note:																		//
//	You may only use constant extra space.										//
//	For example,																//
//	Given the following perfect binary tree,									//
//			1																	//
//		   / \																	//
//		  2   3																	//
//		 / \   \																//
//		4  5    7																//
//	After calling your function, the tree should look like :					//
//			 1->NULL															//
//		   /  \																	//
//		  2 -> 3->NULL															//
//		 / \    \																//
//		4 -> 5 -> 7->NULL														//
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
		while (root) {
			TreeLinkNode* next = nullptr;	//下一层的第一个节点
			TreeLinkNode* prev = nullptr;	//当前层的前一个节点
			for (; root; root = root->next) {
				if (nullptr == next) next = root->left ? root->left : root->right;
				if (root->left) {
					if (prev) prev->next = root->left;
					prev = root->left;
				}
				if (root->right) {
					if (prev) prev->next = root->right;
					prev = root->right;
				}
			}
			root = next;		//更新到下一层
		}
	}
};
//迭代的方法，利用一个中间变量节点，放在每一层的头部
class Solution2 {
public:
	void connect(TreeLinkNode* root) {
		while (root != nullptr) {
			TreeLinkNode* tempChild = new TreeLinkNode(0);
			TreeLinkNode* currentChild = tempChild;
			while (root != nullptr) {
				if (root->left != nullptr) { currentChild->next = root->left; currentChild = currentChild->next; }
				if (root->right != nullptr) { currentChild->next = root->right; currentChild = currentChild->next; }
				root = root->next;
			}
			root = tempChild->next;
		}
	}
};
//迭代的方法，利用一个queue，但这样不是常数空间
class Solution3 {
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

//递归的方法，尾递归
class Solution4 {
public:
	void connect(TreeLinkNode *root) {
		if (root == nullptr) return;
		TreeLinkNode dummy(-1);
		for (TreeLinkNode *curr = root, *prev = &dummy;
			curr; curr = curr->next) {
			if (curr->left != nullptr) {
				prev->next = curr->left;
				prev = prev->next;
			}
			if (curr->right != nullptr) {
				prev->next = curr->right;
				prev = prev->next;
			}
		}
		connect(dummy.next);
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
//	Solution2 test;
//	ManageTree manageTree;
//	TreeLinkNode* root = new TreeLinkNode(1);
//	root->left = new TreeLinkNode(2);
//	root->right = new TreeLinkNode(3);
//	root->left->left = new TreeLinkNode(4);
//	root->left->right = new TreeLinkNode(5);
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