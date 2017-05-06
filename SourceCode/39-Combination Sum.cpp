//	39. Combination Sum
//------------------------------------------------------------------------------//
//	Given a set of candidate numbers (C) (without duplicates) and a target		//
//	number (T), find all unique combinations in C where the candidate numbers	//
//	sums to T.																	//
//	The same repeated number may be chosen from C unlimited number of times.	//
//	Note:																		//
//	All numbers(including target) will be positive integers.					//
//	The solution set must not contain duplicate combinations.					//
//	For example, given candidate set[2, 3, 6, 7] and target 7,					//
//	A solution set is :															//
//	[																			//
//		[7],																	//
//		[2, 2, 3]																//
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
	vector<vector<int>> combinationSum(vector<int>& candidates, int target)
	{
		vector<vector<int>> result;
		vector<int> record;
		int n = candidates.size();
		if (n == 0)
			return result;
		sort(candidates.begin(), candidates.end());
		findCombine(candidates, target, target, record, result);
		return result;
	}
private:
	void findCombine(vector<int>& candidates, int target, int remain, vector<int> &record, vector<vector<int>> &result)
	{
		for (int i = 0; i < candidates.size(); i++)
		{
			if (!record.empty()&&candidates[i] < record.back())
				continue;
			if (candidates[i] < remain)
			{
				record.push_back(candidates[i]);
				findCombine(candidates, target, remain - candidates[i], record, result);
				record.pop_back();
			}
			else if (candidates[i] == remain)
			{
				record.push_back(candidates[i]);
				result.push_back(record);
				record.pop_back();
				return;
			}
			else
				return;
		}
		return;
	}
};
//另一种形式
class Solution2
{
public:
	vector<vector<int>> combinationSum(vector<int>& candidates, int target)
	{
		sort(candidates.begin(), candidates.end());
		vector<vector<int>> result;		//最终结果
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
		for (size_t i = start; i < candicates.size(); i++)
		{
			if (gap < candicates[i])	//剪枝
				return;
			else
			{
				record.push_back(candicates[i]);
				dfs(candicates, result, record, gap - candicates[i], i);
				record.pop_back();
			}
		}
		return;
	}
};
//int main(void)
//{
//	Solution2 test;
//	vector<int> a = { 2,3,5,7 };
//	auto x = test.combinationSum(a, 7);
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}
