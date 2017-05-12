//	77. Combinations
//------------------------------------------------------------------------------//
//	Given two integers n and k, return all possible combinations of k numbers	//
//	out of 1 ... n.																//
//	For example,																//
//	If n = 4 and k = 2, a solution is :											//
//	[																			//
//		[2, 4],																	//
//		[3, 4],																	//
//		[2, 3],																	//
//		[1, 2],																	//
//		[1, 3],																	//
//		[1, 4],																	//
//	]																			//
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
//DFS，深度优先搜索，递归，时间复杂度O(n!)
class Solution 
{
public:
	vector<vector<int>> combine(int n, int k) 
	{
		vector<vector<int>> result;
		vector<int> combine;
		combineDFS(n, k, 1, 0, combine, result);
		return result;
	}
private:
	//start,开始的数，cur当前搜索的数量
	void combineDFS(int n, int k, int start, int cur, vector<int> &combine, vector<vector<int>> &result)
	{
		if (cur == k)
		{
			result.push_back(combine);
			return;
		}
		for (int i = start; i <= n; ++i) 
		{
			combine.push_back(i);
			combineDFS(n, k, i + 1, cur + 1, combine, result);
			combine.pop_back();
		}
	}
};
//迭代，利用STL::prev_permutation
class Solution2 
{
public:
	vector<vector<int> > combine(int n, int k) 
	{
		vector<int> values(n);
		iota(values.begin(), values.end(), 1);
		vector<bool> select(n, false);
		fill_n(select.begin(), k, true);
		vector<vector<int> > result;
		do {
			vector<int> one(k);
			for (int i = 0, index = 0; i < n; ++i)
				if (select[i])
					one[index++] = values[i];
			result.push_back(one);
		} while (prev_permutation(select.begin(), select.end()));
		return result;
	}
};
//int main(void)
//{
//	Solution test;
//	auto a = test.combine(5, 3);
//	for_each(a.begin(), a.end(), [](vector<int> & x) {
//		for (auto y : x)
//			cout << y << " ";
//		cout << endl;
//	});
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
