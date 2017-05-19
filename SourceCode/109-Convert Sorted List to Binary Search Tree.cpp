//	109. Convert Sorted List to Binary Search Tree
//------------------------------------------------------------------------------//
//	Given a singly linked list where elements are sorted in ascending order,	//
//	convert it to a height balanced BST.										//
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
//将链表的数据放入一个数组，然后调用数组生成平衡二叉树的方法，比较取巧
class Solution {
public:
	TreeNode* sortedListToBST(ListNode* head) {
		vector<int> sortArray;
		while (head) {
			sortArray.push_back(head->val);
			head = head->next;
		}
		return sortedArrayToBST(sortArray, 0, sortArray.size());
	}
private:
	TreeNode* sortedArrayToBST(vector<int>& nums, int start, int end) {
		if (start >= end)
			return nullptr;
		int mid = start + (end - start) / 2;
		TreeNode* root = new TreeNode(nums[mid]);
		root->left = sortedArrayToBST(nums, start, mid);
		root->right = sortedArrayToBST(nums, mid + 1, end);
		return root;
	}
};
//自底向上，利用双指针法寻找，一个指针一次走一步，一个指针一次走两步
//当快指针走到尾部时，慢指针即为中间的节点
class Solution2 {
public:
	TreeNode *sortedListToBST(ListNode *head)
	{
		return sortedListToBST(head, NULL);
	}

private:
	TreeNode *sortedListToBST(ListNode *head, ListNode *tail)
	{
		if (head == tail)
			return NULL;
		if (head->next == tail)    //
		{
			TreeNode *root = new TreeNode(head->val);
			return root;
		}
		ListNode *mid = head, *temp = head;
		while (temp != tail && temp->next != tail)    // 寻找中间节点
		{
			mid = mid->next;
			temp = temp->next->next;
		}
		TreeNode *root = new TreeNode(mid->val);
		root->left = sortedListToBST(head, mid);
		root->right = sortedListToBST(mid->next, tail);
		return root;
	}
};
//自底向上，记录链表的长度，深度优先搜索
//时间复杂度O(n)，空间复杂度O(nlogn)
class Solution3 {
public:
	TreeNode *sortedListToBST(ListNode *head)
	{
		int len = 0;
		ListNode *p = head;
		while (p) {
			len++;
			p = p->next;
		}
		return sortedListToBST(head, 0, len - 1);
	}
private:
	TreeNode *sortedListToBST(ListNode *&head, int start, int end)
	{
		if (start > end)
			return nullptr;
		int mid = start + (end - start) / 2;
		TreeNode *leftChild = sortedListToBST(head, start, mid - 1);
		TreeNode *parent = new TreeNode(head->val);
		parent->left = leftChild;
		head = head->next;
		parent->right = sortedListToBST(head, mid + 1, end);
		return parent;
	}
};
//分治法，自顶向下，时间复杂度O(n^2)，空间复杂度O(nlogn)
class Solution4 {
public:
	TreeNode* sortedListToBST(ListNode* head) {
		return sortedListToBST(head, listLength(head));
	}
	TreeNode* sortedListToBST(ListNode* head, int len) {
		if (len == 0) return nullptr;
		if (len == 1) return new TreeNode(head->val);
		TreeNode* root = new TreeNode(nth_node(head, len / 2 + 1)->val);
		root->left = sortedListToBST(head, len / 2);
		root->right = sortedListToBST(nth_node(head, len / 2 + 2),
			(len - 1) / 2);
		return root;
	}
	int listLength(ListNode* node) {
		int n = 0;
		while (node) {
			++n;
			node = node->next;
		}
		return n;
	}
	ListNode* nth_node(ListNode* node, int n) {
		while (--n)
			node = node->next;
		return node;
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
//	ListNode* head = new ListNode(1);
//	head->next = new ListNode(2);
//	head->next->next = new ListNode(3);
//	head->next->next->next = new ListNode(4);
//	head->next->next->next->next = new ListNode(5);
//	TreeNode* root = test.sortedListToBST(head);
//	manageTree.showTree(root,0);
//	manageTree.destroy(root);
//	while (head) {
//		ListNode* temp = head;
//		head = head->next;
//		delete temp;
//	}
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