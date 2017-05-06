//	40. Combination Sum II
//------------------------------------------------------------------------------//
//	Given a collection of candidate numbers (C) and a target number (T), find	//
//	all unique combinations in C where the candidate numbers sums to T.			//
//	Each number in C may only be used once in the combination.					//
//	Note:																		//
//	All numbers(including target) will be positive integers.					//
//	The solution set must not contain duplicate combinations.					//
//	For example, given candidate set[10, 1, 2, 7, 6, 1, 5] and target 8,		//
//	A solution set is :															//
//	[																			//
//		[1, 7],																	//
//		[1, 2, 5],																//
//		[2, 6],																	//
//		[1, 1, 6]																//
//	]																			//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<functional>
#include<sstream>
// constants
// function prototype
using namespace std;
//深度优先递归，回溯加剪枝
class Solution
{
public:
	vector<vector<int>> combinationSum2(vector<int>& candidates, int target)
	{
		vector<vector<int>> result;		//最终结果
		if (candidates.empty())
			return result;
		sort(candidates.begin(), candidates.end());
		vector<int> record;				//中间结果
		dfs(candidates, result, record, target, 0);
		return result;
	}
private:
	void dfs(vector<int> &candicates, vector<vector<int>> &result, vector<int> &record, int gap, size_t start)
	{
		if (gap == 0)
		{
			result.push_back(record);
			return;
		}
		int previous = -1;
		for (size_t i = start; i < candicates.size(); i++)
		{
			if (previous == candicates[i])
				continue;
			if (gap < candicates[i])	//剪枝
				return;
			else
			{
				previous = candicates[i];
				record.push_back(candicates[i]);
				dfs(candicates, result, record, gap - candicates[i], i + 1);
				record.pop_back();
			}
		}
		return;
	}
};
//int main(void)
//{
//	Solution test;
//	vector<int> a = { 10, 1, 2, 7, 6, 1, 5 };
//	auto x = test.combinationSum2(a, 8);
//	for (auto y1 : x)
//	{
//		for (auto y2 : y1)
//		{
//			cout << y2 << " ";
//		}
//		cout << endl;
//	}
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}
