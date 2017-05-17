//	108. Convert Sorted Array to Binary Search Tree
//------------------------------------------------------------------------------//
//	Given an array where elements are sorted in ascending order, convert it to	//
//	a height balanced BST.		 												//
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
//平衡二叉查找树即AVL树，满足树的任意节点，左右子树的高度最多差1
//可以有很多种，取最简单的，递归的方法
class Solution
{
public:
	TreeNode* sortedArrayToBST(vector<int>& nums)
	{
		return sortedArrayToBST(nums.begin(), nums.end());
	}
private:
	template<typename RandomAccessIterator>
	TreeNode* sortedArrayToBST(RandomAccessIterator first, RandomAccessIterator last)
	{
		const auto length = distance(first, last);
		if (length <= 0) return nullptr;
		auto mid = first + length / 2;
		TreeNode *root = new TreeNode(*mid);
		root->left = sortedArrayToBST(first, mid);
		root->right = sortedArrayToBST(mid + 1, last);
		return root;
	}
};
//不用迭代器
class Solution2 {
	TreeNode* sortedArrayToBST(vector<int>& nums, int start, int end) {
		if (end <= start) return NULL;
		int midIdx = (end + start) / 2;
		TreeNode* root = new TreeNode(nums[midIdx]);
		root->left = sortedArrayToBST(nums, start, midIdx);
		root->right = sortedArrayToBST(nums, midIdx + 1, end);
		return root;
	}
public:
	TreeNode* sortedArrayToBST(vector<int>& nums) {
		return sortedArrayToBST(nums, 0, nums.size());
	}
};
//不用额外函数
class Solution3 {
public:
	TreeNode *sortedArrayToBST(vector<int> &num) {
		if (num.size() == 0) return NULL;
		if (num.size() == 1)
		{
			return new TreeNode(num[0]);
		}

		int middle = num.size() / 2;
		TreeNode* root = new TreeNode(num[middle]);

		vector<int> leftInts(num.begin(), num.begin() + middle);
		vector<int> rightInts(num.begin() + middle + 1, num.end());

		root->left = sortedArrayToBST(leftInts);
		root->right = sortedArrayToBST(rightInts);

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
//	Solution2 test;
//	ManageTree manageTree;
//	vector<int> input = { 1,2,3,4,5,6,7,8,9 };
//
//	auto BST = test.sortedArrayToBST(input);
//	manageTree.showTree(BST, 0);
//	manageTree.destroy(BST);
//
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