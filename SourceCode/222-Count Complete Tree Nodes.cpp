//	222. Count Complete Tree Nodes
//------------------------------------------------------------------------------//
//	Given a complete binary tree, count the number of nodes.					//
//	Definition of a complete binary tree from Wikipedia :						//
//	In a complete binary tree every level, except possibly the last, is			//
//	completely filled, and all nodes in the last level are as far left as		//
//	possible.It can have between 1 and 2^h nodes inclusive at the last level h.	//
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
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
//利用队列,会超时
class Solution {
public:
	int countNodes(TreeNode* root) {
		if (nullptr == root) return 0;
		queue<TreeNode*> q;
		q.push(root);
		int levelnum = 1;
		int treenum = 0;
		while (!q.empty()) {
			queue<TreeNode*> next;
			treenum += q.size();
			if (q.size() != levelnum)
				return treenum;
			while (!q.empty()) {
				TreeNode *cur = q.front();
				q.pop();
				if (cur->left)
					next.push(cur->left);
				if (cur->right)
					next.push(cur->right);
			}
			q = next;
			levelnum *= 2;
		}
		return treenum;
	}
};
//递归的方法，每次比较左右子树高度，一致则为满树，否则向下递归
class Solution2 {
public:
	int countNodes(TreeNode* root) {
		if (nullptr == root) return 0;
		int hl = 0, hr = 0;
		TreeNode *left = root;
		TreeNode *right = root;
		while (left) {
			hl++;
			left = left->left;
		}
		while (right) {
			hr++;
			right = right->right;
		}
		if (hl == hr) return pow(2, hl) - 1;
		return 1 + countNodes(root->left) + countNodes(root->right);
	}
};
//第二种递归，计算左右子树高度以划分
class Solution3 {
public:
	int countNodes(TreeNode* root) {
		if (!root) return 0;
		int lh = height(root->left);
		int rh = height(root->right);
		if (lh == rh)
			return (1 << lh) + countNodes(root->right);  /*1(根节点) + (1<<lh)-1(完全左子树) + # of rightNode */
		else
			return (1 << rh) + countNodes(root->left);  /*1(根节点) + (1<<rh)-1(完全右子树) + # of leftNode*/
	}
private:
	int height(TreeNode *root) { //get the height of a complete binary tree.
		if (!root) return 0;
		return 1 + height(root->left);
	}
};
//迭代的做法，树的二分搜索
class Solution4 {
public:
	int countNodes(TreeNode* root) {
		if (!root) return 0;
		TreeNode *temp = root;
		int height = 0, count = 0, level;
		while (temp) {
			temp = temp->left;
			height++;
		}
		temp = root;
		level = height - 2;
		while (level >= 0) {
			TreeNode *left = temp->left;
			for (int i = 0; i < level; i++) {
				left = left->right;
			}
			if (left) {
				temp = temp->right;
				count += (1 << level);
			}
			else temp = temp->left;
			level--;
		}
		if (temp) count++;
		return (1 << (height - 1)) + count - 1;
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
//	TreeNode *root = new TreeNode(1);
//	root->left = new TreeNode(2);
//	root->right = new TreeNode(3);
//	cout << test.countNodes(root);
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