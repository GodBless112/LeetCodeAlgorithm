//	96. Unique Binary Search Trees
//------------------------------------------------------------------------------//
//	Given n, how many structurally unique BST's (binary search trees) that		//
//	store values 1...n?															//
//	For example,																//
//	Given n = 3, there are a total of 5 unique BST's.							//
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

//对于一个二叉搜索树集合，以i为根节点的话，则左子树由1~i-1构成，右子树由i+1~n构成
//数量为左子树个数乘以右子树个数，那么，可以用动态规划来考虑，另f[i]为以i为根节点
//的BST数量，f[i]=f[i-1]*f[n-i]，令F[n]为n个数的所有BST组合，F[n]=∑f[i]
class Solution 
{
public:
	int numTrees(int n) 
	{
		if (n < 2)
			return 1;
		vector<int> F(n + 1, 0);
		F[0] = F[1] = 1;
		for (int i = 2; i <= n; i++)
			for (int j = 1; j <= i; j++)
				F[i] += F[j - 1] * F[i - j];
		return F[n];
	}
};
//int main(void)
//{
//	Solution test;
//	cout << test.numTrees(3);
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