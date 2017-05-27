//	145. Binary Tree Postorder Traversal
//------------------------------------------------------------------------------//
//	Given a binary tree, return the postorder traversal of its nodes' values.	//
//	For example :																//
//	Given binary tree{ 1,#,2,3 },												//
//		1																		//
//		 \																		//
//		  2																		//
//		 /																		//
//		3																		//
//	return[3, 2, 1].															//
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
	vector<int> postorderTraversal(TreeNode* root)
	{
		vector<int> result;
		postorderTraversal(root, result);
		return result;
	}
private:
	void postorderTraversal(TreeNode *root, vector<int> &result)
	{
		if (root == nullptr)
			return;
		postorderTraversal(root->left, result);
		postorderTraversal(root->right, result);
		result.push_back(root->val);
	}
};
//迭代的方法，利用栈，类似于中序遍历的处理，但需加入一个节点记录上一个访问过的值
class Solution2 {
public:
	vector<int> postorderTraversal(TreeNode* root) {
		vector<int> result;
		stack<TreeNode*> stack;
		TreeNode *cur = root, *last = nullptr;
		while (!stack.empty() || cur != nullptr) {
			if (cur != nullptr) {
				stack.push(cur);
				cur = cur->left;
			}
			else {
				TreeNode* topNode = stack.top();
				if (topNode->right && last != topNode->right)
					cur = topNode->right;
				else {
					result.push_back(topNode->val);
					last = topNode;
					stack.pop();
				}
			}
		}
		return result;
	}
};
//迭代的方法，利用栈，最后反向一下
class Solution3 {
public:
	vector<int> postorderTraversal(TreeNode *root) {
		stack<TreeNode*> nodeStack;
		vector<int> result;
		//base case
		if (root == nullptr)
			return result;
		nodeStack.push(root);
		while (!nodeStack.empty())
		{
			TreeNode* node = nodeStack.top();
			result.push_back(node->val);
			nodeStack.pop();
			if (node->left)
				nodeStack.push(node->left);
			if (node->right)
				nodeStack.push(node->right);
		}
		reverse(result.begin(), result.end());
		return result;

	}
};
//Morris后序遍历
//步骤：
//当前节点设置为临时节点dump。
//1. 如果当前节点的左孩子为空，则将其右孩子作为当前节点。
//2. 如果当前节点的左孩子不为空，在当前节点的左子树中找到当前节点在中序遍历下的前驱节点。
//	a) 如果前驱节点的右孩子为空，将它的右孩子设置为当前节点。当前节点更新为当前节点的左孩子。
//	b) 如果前驱节点的右孩子为当前节点，将它的右孩子重新设为空。倒序输出从当前节点的左孩子到该
//	前驱节点这条路径上的所有节点。当前节点更新为当前节点的右孩子。
//3. 重复以上1、2直到当前节点为空。
class Solution4 {
public:
	vector<int> postorderTraversal(TreeNode* root) {
		vector<int> nodes;
		TreeNode* dump = new TreeNode(0);
		dump->left = root;
		TreeNode* curNode = dump;
		while (curNode) {
			if (curNode->left) {
				TreeNode* predecessor = curNode->left;
				while (predecessor->right && predecessor->right != curNode)
					predecessor = predecessor->right;
				if (!(predecessor->right)) {
					predecessor->right = curNode;
					curNode = curNode->left;
				}
				else {
					reverseAddNodes(curNode->left, predecessor, nodes);
					predecessor->right = NULL;
					curNode = curNode->right;
				}
			}
			else curNode = curNode->right;
		}
		return nodes;
	}
private:
	void reverseNodes(TreeNode* start, TreeNode* end) {
		if (start == end) return;
		TreeNode* x = start;
		TreeNode* y = start->right;
		TreeNode* z;
		while (x != end) {
			z = y->right;
			y->right = x;
			x = y;
			y = z;
		}
	}
	void reverseAddNodes(TreeNode* start, TreeNode* end, vector<int>& nodes) {
		reverseNodes(start, end);
		TreeNode* node = end;
		while (true) {
			nodes.push_back(node->val);
			if (node == start) break;
			node = node->right;
		}
		reverseNodes(end, start);
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
//	Solution4 test;
//	TreeNode *root = new TreeNode(1);
//	root->left = new TreeNode(2);
//	root->left->left = new TreeNode(3);
//	auto x = test.postorderTraversal(root);
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