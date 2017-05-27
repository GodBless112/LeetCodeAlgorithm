//	144. Binary Tree Preorder Traversal
//------------------------------------------------------------------------------//
//	Given a binary tree, return the preorder traversal of its nodes' values.	//
//	For example :																//
//	Given binary tree{ 1,#,2,3 },												//
//		1																		//
//		 \																		//
//		 2																		//
//		/																		//
//	   3																		//
//	return[1, 2, 3].															//
//	Note: Recursive solution is trivial, could you do it iteratively ?			//
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
//递归的方法，占用O(n)的栈空间
class Solution
{
public:
	vector<int> preorderTraversal(TreeNode* root)
	{
		vector<int> result;
		preorderTraversal(root, result);
		return result;
	}
private:
	void preorderTraversal(TreeNode *root, vector<int> &result)
	{
		if (root == nullptr)
			return;
		result.push_back(root->val);
		preorderTraversal(root->left, result);
		preorderTraversal(root->right, result);
	}
};
//迭代的方法，利用栈，将栈顶元素记录，并把它的右孩子和左孩子依次压入栈
class Solution2 {
public:
	vector<int> preorderTraversal(TreeNode* root) {
		vector<int> result;
		if (nullptr == root) return result;
		stack<TreeNode*> s;
		s.push(root);
		while (!s.empty()) {
			TreeNode* cur = s.top();
			s.pop();
			result.push_back(cur->val);
			if (cur->right) s.push(cur->right);
			if (cur->left) s.push(cur->left);
		}
		return result;
	}
};
//Morris前序遍历
//步骤：
//1. 如果当前节点的左孩子为空，则输出当前节点并将其右孩子作为当前节点。
//2. 如果当前节点的左孩子不为空，在当前节点的左子树中找到当前节点在中序遍历下的前驱节点。
//	a) 如果前驱节点的右孩子为空，将它的右孩子设置为当前节点。输出当前节点（在这里输出，这是与中
//	序遍历唯一一点不同）。当前节点更新为当前节点的左孩子。
//	b) 如果前驱节点的右孩子为当前节点，将它的右孩子重新设为空。当前节点更新为当前节点的右孩子。
//3. 重复以上1、2直到当前节点为空。
class Solution3 {
public:
	vector<int> preorderTraversal(TreeNode* root) {
		vector<int> result;
		TreeNode *cur = root, *prev = nullptr;	//当前节点和前驱节点
		while (cur) {
			if (cur->left == nullptr) {
				result.push_back(cur->val);
				cur = cur->right;
			}
			else {
				prev = cur->left;
				while (prev->right && prev->right != cur)
					prev = prev->right;
				if (prev->right == nullptr) {
					result.push_back(cur->val);
					prev->right = cur;
					cur = cur->left;
				}
				else {
					prev->right = nullptr;
					cur = cur->right;
				}
			}
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
};
//int main(void)
//{
//	Solution3 test;
//	TreeNode *root = new TreeNode(1);
//	root->left = new TreeNode(2);
//	root->left->left = new TreeNode(3);
//	auto x = test.preorderTraversal(root);
//	for_each(x.begin(), x.end(), [](int y) {
//		cout << y << " ";
//	});
//	ManageTree manageTree;
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