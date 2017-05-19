//	105. Construct Binary Tree from Preorder and Inorder Traversal
//------------------------------------------------------------------------------//
//	Given preorder and inorder traversal of a tree, construct the binary tree.	//
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
//利用前序遍历的第一个元素找到根节点，中序遍历可以得到根节点的左右子树的中序遍历
//在根节点左右两边，迭代的生成树
class Solution {
public:
	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
		return buildTree(preorder.begin(), preorder.end(), inorder.begin(), inorder.end());
	}
private:
	template<class RandomAcessIterator>
	TreeNode* buildTree(RandomAcessIterator prebegin, RandomAcessIterator preend,
		RandomAcessIterator inbegin, RandomAcessIterator inend) {
		if (prebegin == preend) return nullptr;
		if (inbegin == inend) return nullptr;
		TreeNode *root = new TreeNode(*prebegin);
		auto pos = find(inbegin, inend, *prebegin);
		int length = distance(inbegin, pos);
		root->left = buildTree(prebegin + 1, prebegin + 1 + length, inbegin, pos);
		root->right = buildTree(prebegin + 1 + length, preend, pos + 1, inend);
		return root;
	}
};
//递归：不用迭代器
class Solution2 {

public:
	/* from Preorder and Inorder Traversal */
	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {

		return helper(preorder, 0, preorder.size(), inorder, 0, inorder.size());

	}

	TreeNode* helper(vector<int>& preorder, int i, int j, vector<int>& inorder, int ii, int jj)
	{
		// tree        8 4 5 3 7 3
		// preorder    8 [4 3 3 7] [5]
		// inorder     [3 3 4 7] 8 [5]

		// 每次从 preorder 头部取一个值 mid，作为树的根节点
		// 检查 mid 在 inorder 中 的位置，则 mid 前面部分将作为 树的左子树，右部分作为树的右子树

		if (i >= j || ii >= j)
			return NULL;

		int mid = preorder[i];
		auto f = find(inorder.begin() + ii, inorder.begin() + jj, mid);

		int dis = f - inorder.begin() - ii;

		TreeNode* root = new TreeNode(mid);
		root->left = helper(preorder, i + 1, i + 1 + dis, inorder, ii, ii + dis);
		root->right = helper(preorder, i + 1 + dis, j, inorder, ii + dis + 1, jj);
		return root;
	}
};
//迭代的方法
class Solution3 {
public:
	TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {

		if (preorder.size() == 0)
			return NULL;
		stack<TreeNode *> st;
		TreeNode *t, *r, *root;
		int i, j, f;
		f = i = j = 0;
		root = new TreeNode(preorder[i]);
		st.push(root);
		t = root;
		i++;
		while (i<preorder.size())
		{
			if (!st.empty() && st.top()->val == inorder[j])
			{
				t = st.top();
				st.pop();

				f = 1;
				j++;
			}
			else
			{
				if (f == 0)
				{
					t->left = new TreeNode(preorder[i]);
					t = t->left;
					st.push(t);
					i++;
				}
				else
				{
					f = 0;
					t->right = new TreeNode(preorder[i]);
					t = t->right;
					st.push(t);
					i++;
				}
			}
		}
		return root;
	}
};
class Solution4 {
public:
	TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
		TreeNode *root = NULL; stack<TreeNode *> MyData;
		if (preorder.empty()) return root;
		root = new TreeNode(preorder[0]);
		MyData.push(root); int index = 0;
		for (int i = 1; i <= preorder.size(); i++) {
			TreeNode *cur = MyData.top();
			if ((MyData.top()->val) != inorder[index]) {
				cur->left = new TreeNode(preorder[i]);
				MyData.push(cur->left);
			}
			else {
				while (!MyData.empty() && ((MyData.top()->val) == inorder[index])) {
					cur = MyData.top(); MyData.pop(); index++;
				}
				if (index<inorder.size()) {
					cur->right = new TreeNode(preorder[i]);
					MyData.push(cur->right);
				}
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
//	vector<int> inOrder{ 4,2,5,1,6,3,7 };
//	vector<int> preOrder{ 1,2,4,5,3,6,7 };
//	TreeNode *root = test.buildTree(preOrder, inOrder);
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