//	95. Unique Binary Search Trees II
//------------------------------------------------------------------------------//
//	Given an integer n, generate all structurally unique BST's					//
//	(binary search trees) that store values 1...n.								//
//	For example,																//
//	Given n = 3, your program should return all 5 unique BST's shown below.		//
//	1      3	 3      2      1												//
//	 \	  /		/	   / \      \												//
//	 3   2     1      1   3      2												//
//	/	/		\                 \												//
// 2   1         2                 3											//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
// constants
// function prototype
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
//分析同I，递归的做法
class Solution 
{
public:
	vector<TreeNode*> generateTrees(int n) 
	{
		if (n == 0) return generate(1, 0);
		return generate(1, n);
	}
private:
	vector<TreeNode *> generate(int start, int end) {
		vector<TreeNode*> subTree;
		if (start > end) {
			subTree.push_back(nullptr);
			return subTree;
		}
		for (int k = start; k <= end; k++) {
			vector<TreeNode*> leftSubs = generate(start, k - 1);
			vector<TreeNode*> rightSubs = generate(k + 1, end);
			for (auto i : leftSubs) {
				for (auto j : rightSubs) {
					TreeNode *node = new TreeNode(k);
					node->left = i;
					node->right = j;
					subTree.push_back(node);
				}
			}
		}
		return subTree;
	}
};
int main(void)
{
	Solution test;
	auto x = test.generateTrees(0);
	cout << endl;
	
	// code to keep window open for MSVC++
	cin.clear();
	while (cin.get() != '\n')
		continue;
	cin.get();

	return 0;
}