//	111. Minimum Depth of Binary Tree
//------------------------------------------------------------------------------//
//	Given a binary tree, find its minimum depth.								//
//	The minimum depth is the number of nodes along the shortest path from the	//
//	root node down to the nearest leaf node.		 							//
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
//深度优先搜索，搜到一个叶子节点，记录其深度，并比较
class Solution 
{
public:
	int minDepth(TreeNode* root) 
	{
		int result = INT_MAX;
		if (root == nullptr)
			return 0;
		minDepth(root, 1, result);
		return result;
	}
private:
	void minDepth(TreeNode* root, int cur, int &min)
	{
		if (root == nullptr) return;
		if (cur > min) return;
		if (root->left == nullptr && root->right == nullptr)
			if (cur < min)
				min = cur;
		minDepth(root->left, cur + 1, min);
		minDepth(root->right, cur + 1, min);
	}
};
//递归的方法，用一个bool变量记录节点是否有兄弟
class Solution2
{
public:
	int minDepth(const TreeNode *root) {
		return minDepth(root, false);
	}
private:
	static int minDepth(const TreeNode *root, bool hasbrother) {
		if (!root) return hasbrother ? INT_MAX : 0;
		return 1 + min(minDepth(root->left, root->right != NULL),
			minDepth(root->right, root->left != NULL));
	}
};
//迭代的方法，一层一层的自顶向下推进，遇到第一个叶子节点停止，比递归的好
//上述递归方法需要遍历所有节点，而迭代不用
class Solution3
{
public:
	int minDepth(TreeNode* root)
	{
		queue<TreeNode*> current, next;
		int result = 0;
		if (root == nullptr)
			return 0;
		else
			current.push(root);
		while (!current.empty()) {
			while (!current.empty()) {
				TreeNode* node = current.front();
				current.pop();
				if (node->left == nullptr&&node->right == nullptr)
					return result + 1;
				if (node->left != nullptr) next.push(node->left);
				if (node->right != nullptr) next.push(node->right);
			}
			result++;
			swap(next, current);
		}
		return result;
	}
};
//用stack实现的迭代方法
class Solution4
{
public:
	int minDepth(TreeNode* root) {
		if (root == nullptr)
			return 0;
		int result = INT_MAX;
		stack<pair<TreeNode*, int>> s;
		s.push(make_pair(root, 1));
		while (!s.empty()) {
			auto node = s.top().first;
			auto depth = s.top().second;
			s.pop();
			if (node->left == nullptr && node->right == nullptr)
				result = min(result, depth);
			if (node->left && result > depth) //剪枝
				s.push(make_pair(node->left, depth + 1));
			if (node->right && result > depth) //剪枝
				s.push(make_pair(node->right, depth + 1));
		}
		return result;
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
//	Solution test;
//	ManageTree manageTree;
//	TreeNode *root = new TreeNode(3);
//	root->left = new TreeNode(9);
//	root->right = new TreeNode(20);
//	root->left->left = new TreeNode(15);
//	root->left->left->left = new TreeNode(7);
//	
//	cout << test.minDepth(root) << endl;
//	manageTree.destroy(root);
//	root = new TreeNode(1);
//	root->left = new TreeNode(2);
//	root->right = new TreeNode(3);
//	root->left->left = new TreeNode(4);
//	root->right->right = new TreeNode(5);
//	cout << test.minDepth(root) << endl;
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