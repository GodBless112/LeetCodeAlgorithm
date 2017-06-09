//	173. Binary Search Tree Iterator
//------------------------------------------------------------------------------//
//	Implement an iterator over a binary search tree (BST). Your iterator will	//
//	be initialized with the root node of a BST.									//
//	Calling next() will return the next smallest number in the BST.				//
//	Note: next() and hasNext() should run in average O(1) time and uses O(h)	//
//	memory, where h is the height of the tree.									//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<queue>
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
//利用队列，中序遍历，但是用了O(n)的空间
class BSTIterator {
public:
	BSTIterator(TreeNode *root) {
		TreeNode *cur = root, *prev = nullptr;
		while (cur) {
			if (cur->left == nullptr) {
				q.push(cur->val);
				cur = cur->right;
			}
			else {
				prev = cur->left;
				while (prev->right && prev->right != cur) 
					prev = prev->right;
				if (prev->right == nullptr) {
					prev->right = cur;
					cur = cur->left;
				}
				else {
					q.push(cur->val);
					prev->right = nullptr;
					cur = cur->right;		
				}
			}
		}
	}

	/** @return whether we have a next smallest number */
	bool hasNext() {
		return !q.empty();
	}

	/** @return the next smallest number */
	int next() {
		int result = q.front();
		q.pop();
		return result;
	}
private:
	queue<int> q;
};
//利用栈，每次将所有左节点推入栈
class BSTIterator2 {
public:
	BSTIterator2(TreeNode *root) {
		pushAll(root);
	}

	/** @return whether we have a next smallest number */
	bool hasNext() {
		return !s.empty();
	}

	/** @return the next smallest number */
	int next() {
		TreeNode *tmp = s.top();
		s.pop();
		pushAll(tmp->right);
		return tmp->val;
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
//法二的变形，适用性可能不强，如果不调用hasnext的话，工作不正常
class BSTIterator3 {
private:
	TreeNode *current = NULL;
	stack<TreeNode*> s;
public:
	BSTIterator3(TreeNode *root) {
		// initialize the current pointer
		current = root;
	}

	/** @return whether we have a next smallest number */
	bool hasNext() {
		while (current) {
			s.push(current);
			current = current->left;
		}
		if (s.empty()) {
			return false;
		}
		return true;
	}

	/** @return the next smallest number */
	int next() {
		TreeNode* node = s.top();
		s.pop();
		current = node->right;
		return node->val;
	}
};
/**
* Your BSTIterator will be called like this:
* BSTIterator i = BSTIterator(root);
* while (i.hasNext()) cout << i.next();
*/
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
//	ManageTree manageTree;
//	TreeNode* root = new TreeNode(2);
//	root->left = new TreeNode(1);
//	root->right = new TreeNode(3);
//	BSTIterator2 i = BSTIterator2(root);
//	while (i.hasNext()) cout << i.next();
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