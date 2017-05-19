//	106. Construct Binary Tree from Inorder and Postorder Traversal
//------------------------------------------------------------------------------//
//	Given inorder and postorder traversal of a tree, construct the binary tree.	//
//	Note:																		//
//	You may assume that duplicates do not exist in the tree.					//
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
//递归
//利用后序遍历的最后一个元素找到根节点，中序遍历可以得到根节点的左右子树的中序遍历
//在根节点左右两边，迭代的生成树
class Solution {
public:
	TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
		return buildTree(inorder.begin(), inorder.end(), postorder.begin(), postorder.end());
	}
private:
	template<class RandomAcessIterator>
	TreeNode* buildTree(RandomAcessIterator inbegin, RandomAcessIterator inend,
		RandomAcessIterator postbegin, RandomAcessIterator postend) {
		if (inbegin == inend) return nullptr;
		if (postbegin == postend) return nullptr;
		TreeNode *root = new TreeNode(*prev(postend));
		auto pos = find(inbegin, inend, *prev(postend));
		int rightlength = distance(pos, inend);
		root->left = buildTree(inbegin, pos, postbegin, postend - rightlength);
		root->right = buildTree(pos + 1, inend, postend - rightlength, prev(postend));
		return root;
	}
};
//递归：不用迭代器
class Solution2 {

public:
	/* from Preorder and Inorder Traversal */
	TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
		return helper(inorder, 0, inorder.size(), postorder, 0, postorder.size());
	}

	TreeNode* helper(vector<int>& inorder, int i, int j, vector<int>& postorder, int ii, int jj)
	{
		// tree        1 2 3 4 5 6 7   
		// inorder     [4 2 5] 1 [6 3 7]
		// postorder   [4 5 2] [6 7 3] 1
		// 每次从 postorder 尾部取一个值 mid，作为树的根节点
		// 检查 mid 在 inorder 中 的位置，则 mid 前面部分将作为 树的左子树，右部分作为树的右子树

		if (i >= j || ii >= j)
			return nullptr;

		int mid = postorder[jj - 1];
		auto f = find(inorder.begin() + i, inorder.begin() + j, mid);

		int dis = inorder.begin() + j - f;

		TreeNode* root = new TreeNode(mid);
		root->left = helper(inorder, i, j - dis, postorder, ii, jj - dis);
		root->right = helper(inorder, j - dis + 1, j, postorder, jj - dis, jj - 1);
		return root;
	}
};
//迭代的方法
class Solution3 {
public:
	TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
		if (inorder.size() == 0)return NULL;
		TreeNode *p;
		TreeNode *root;
		stack<TreeNode *> stn;

		root = new TreeNode(postorder.back());
		stn.push(root);
		postorder.pop_back();

		while (true)
		{
			if (inorder.back() == stn.top()->val)
			{
				p = stn.top();
				stn.pop();
				inorder.pop_back();
				if (inorder.size() == 0) break;
				if (stn.size() && inorder.back() == stn.top()->val)
					continue;
				p->left = new TreeNode(postorder.back());
				postorder.pop_back();
				stn.push(p->left);
			}
			else
			{
				p = new TreeNode(postorder.back());
				postorder.pop_back();
				stn.top()->right = p;
				stn.push(p);
			}
		}
		return root;
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
//	Solution3 test;
//	ManageTree manageTree;
//	
//	vector<int> inOrder{ 1,2,3,4 };
//	vector<int> PostOrder{ 1,4,3,2 };
//	TreeNode *root = test.buildTree(inOrder, PostOrder);
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