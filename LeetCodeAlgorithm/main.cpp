//	94. Binary Tree Inorder Traversal
//------------------------------------------------------------------------------//
//	Given a binary tree, return the inorder traversal of its nodes' values.		//
//	For example :																//
//	Given binary tree[1, null, 2, 3],											//
//	1																			//
//	 \																			//
//	  2																			//
//	 /																			//
//	3																			//
//	return[1, 3, 2].															//
//	Note: Recursive solution is trivial, could you do it iteratively?			//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<stack>
#include<unordered_map>
// constants
// function prototype
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
//递归的方法，占用O(n)的栈空间
class Solution 
{
public:
	vector<int> inorderTraversal(TreeNode* root) 
	{
		vector<int> result;
		inorderTranversal(root, result);
		return result;
	}
private:
	void inorderTranversal(TreeNode *root, vector<int> &result)
	{
		if (root == nullptr)
			return;
		inorderTranversal(root->left, result);
		result.push_back(root->val);
		inorderTranversal(root->right, result);
	}
};
//迭代的方法，利用一个stack，但会破坏树的结构，不实用
class Solution2
{
public:
	vector<int> inorderTraversal(TreeNode* root)
	{
		vector<int> result;
		if (root == nullptr)
			return result;
		stack<TreeNode *> stack;
		stack.push(root);
		while (!stack.empty())
		{
			TreeNode *cur = stack.top();
			if (cur->left)
			{
				stack.push(cur->left);
				cur->left = nullptr;
			}
			else
			{
				result.push_back(cur->val);
				stack.pop();
				if (cur->right)
					stack.push(cur->right);
			}
		}
		return result;
	}
};
//利用一个stack和一个hashtable，不会破坏树结构
class Solution3
{
public:
	vector<int> inorderTraversal(TreeNode* root)
	{
		vector<int> vector;
		if (!root)
			return vector;
		unordered_map<TreeNode *, bool> map;//left child has been visited:true.
		stack<TreeNode *> stack;
		stack.push(root);
		while (!stack.empty())
		{
			TreeNode *pNode = stack.top();
			if (pNode->left && !map[pNode])
			{
				stack.push(pNode->left);
				map[pNode] = true;
			}
			else
			{
				vector.push_back(pNode->val);
				stack.pop();
				if (pNode->right)
					stack.push(pNode->right);
			}
		}
		return vector;
	}
};
//只用stack，不会破坏树结构，对使用栈来说是最佳的
class Solution4
{
public:
	vector<int> inorderTraversal(TreeNode* root)
	{
		vector<int> result;
		stack<TreeNode*> stack;
		TreeNode *cur = root;
		while (!stack.empty() || cur != nullptr)
		{
			if (cur != nullptr)
			{
				stack.push(cur);
				cur = cur->left;
			}
			else
			{
				cur = stack.top();
				result.push_back(cur->val);
				stack.pop();
				cur = cur->right;
			}
		}
		return result;
	}
};
//Morris中序遍历，空间复杂度O(1)
//步骤：
//1. 如果当前节点的左孩子为空，则输出当前节点并将其右孩子作为当前节点。
//2. 如果当前节点的左孩子不为空，在当前节点的左子树中找到当前节点在中序遍历下的前驱节点。
//	a) 如果前驱节点的右孩子为空，将它的右孩子设置为当前节点。当前节点更新为当前节点的左孩子。
//	b) 如果前驱节点的右孩子为当前节点，将它的右孩子重新设为空（恢复树的形状）。输出当前节点。当前节点更新为当前节点的右孩子。
//3. 重复以上1、2直到当前节点为空。
class Solution5
{
public:
	vector<int> inorderTraversal(TreeNode* root)
	{
		vector<int> result;
		TreeNode *cur = root, *prev = nullptr;	//当前节点和前驱节点
		while (cur)
		{
			if (cur->left == nullptr)
			{
				result.push_back(cur->val);
				cur = cur->right;
				prev = cur;
			}
			else
			{
				TreeNode *node = cur->left;
				while (node->right != nullptr && node->right != cur)
					node = node->right;
				if (node->right == nullptr) { 
					node->right = cur;
					cur = cur->left;
				}
				else {
					result.push_back(cur->val);
					node->right = nullptr;
					prev = cur;
					cur = cur->right;
				}
			}
		}
	}
};
void destroy(TreeNode *root)
{
	if (root == nullptr)
		return;
	destroy(root->left);
	destroy(root->right);
	delete root;
}
int main(void)
{
	Solution5 test;
	TreeNode *root = new TreeNode(1);
	root->right = new TreeNode(2);
	root->right->left = new TreeNode(3);
	auto x = test.inorderTraversal(root);
	for_each(x.begin(), x.end(), [](int y) {
		cout << y << " ";
	});
	destroy(root);
	cout << endl;
	
	// code to keep window open for MSVC++
	cin.clear();
	while (cin.get() != '\n')
		continue;
	cin.get();

	return 0;
}