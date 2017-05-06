//	100. Same Tree
//------------------------------------------------------------------------------//
//	Given two binary trees, write a function to check if they are equal or not.	//
//	Two binary trees are considered equal if they are structurally identical	//
//	and the nodes have the same value.											//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<functional>
#include<stack>
// constants
// function prototype
using namespace std;

struct TreeNode 
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };
//递归的检查
class Solution 
{
public:
	bool isSameTree(TreeNode* p, TreeNode* q) 
	{
		if (p == nullptr&&q == nullptr)
			return true;
		else if (!p || !q)
			return false;
		return (p->val == q->val) && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
	}
};
//迭代
class Solution2
{
public:
	bool isSameTree(TreeNode *p, TreeNode *q) 
	{
		stack<TreeNode*> s;
		s.push(p);
		s.push(q);
		while (!s.empty()) 
		{
			p = s.top(); s.pop();
			q = s.top(); s.pop();
			if (!p && !q) continue;
			if (!p || !q) return false;
			if (p->val != q->val) return false;
			s.push(p->left);
			s.push(q->left);
			s.push(p->right);
			s.push(q->right);
		}
		return true;
	}
};
//int main(void)
//{
//	Solution test;
//	TreeNode *a, *b;
//	a = new TreeNode(1);
//	a->left = new TreeNode(2);
//	b = new TreeNode(1);
//	b->right = new TreeNode(2);
//	cout << boolalpha << test.isSameTree(a, b);
//	delete a->left; delete a;
//	delete b->right; delete b;
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
