//	236. Lowest Common Ancestor of a Binary Tree
//------------------------------------------------------------------------------//
//	Given a binary tree, find the lowest common ancestor (LCA) of two given		//
//	nodes in the tree.															//
//	According to the definition of LCA on Wikipedia : “The lowest common		//
//	ancestor is defined between two nodes v and w as the lowest node in T that	//
//	has both v and w as descendants(where we allow a node to be a descendant of //
//	itself).”																	//
//				_______3______													//
//			   /			  \													//
//		   ___5__           ___1__												//
//		  /      \		   /	  \												//
//		 6       _2       0        8											//
//				/   \															//
//			   7     4															//
//	For example, the lowest common ancestor(LCA) of nodes 5 and 1 is 3. Another //
//	example is LCA of nodes 5 and 4 is 5, since a node can be a descendant of	//
//	itself according to the LCA definition.										//
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
//递归版：分别寻找左右子树中包含p或q的最低子树，找到后进行比较，如果说pq都不为null
//则为pq的父节点，如果p为null则返回q，反之q为null，返回p
class Solution {
public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		if (nullptr == root || root == p || root == q)
			return root;
		TreeNode *left = lowestCommonAncestor(root->left, p, q);
		TreeNode *right = lowestCommonAncestor(root->right, p, q);
		return !left ? right : !right ? left : root;
	}
};
//迭代版
class Solution2 {
	struct Frame {
		TreeNode* node;
		Frame* parent;
		vector<TreeNode*> subs;
	};
public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		Frame answer;
		stack<Frame> stack;
		stack.push({ root, &answer });
		while (stack.size()) {
			Frame *top = &stack.top(), *parent = top->parent;
			TreeNode *node = top->node;
			if (!node || node == p || node == q) {
				parent->subs.push_back(node);
				stack.pop();
			}
			else if (top->subs.empty()) {
				stack.push({ node->right, top });
				stack.push({ node->left, top });
			}
			else {
				TreeNode *left = top->subs[0], *right = top->subs[1];
				parent->subs.push_back(!left ? right : !right ? left : node);
				stack.pop();
			}
		}
		return answer.subs[0];
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
//	Solution2 test;
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
//	auto common = test.lowestCommonAncestor(root, root->right->right, root->right);
//	cout << common->val << endl;
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