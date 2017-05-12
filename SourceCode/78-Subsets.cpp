//	78. Subsets
//------------------------------------------------------------------------------//
//	Given a set of distinct integers, nums, return all possible subsets.		//
//	Note: The solution set must not contain duplicate subsets.					//
//	For example,																//
//		If nums = [1, 2, 3], a solution is :									//
//		  [																		//
//			  [3],																//
//			  [1],																//
//			  [2],																//
//			  [1, 2, 3],														//
//			  [1, 3],															//
//			  [2, 3],															//
//			  [1, 2],															//
//			  []																//
//		  ]																		//
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
//DFS的方法，递归，回溯
class Solution 
{
public:
	vector<vector<int>> subsets(vector<int>& nums) 
	{
		const int size = nums.size();
		vector<vector<int>> result;
		vector<int> sub;
		result.push_back(sub);
		subsetsDFS(size, 0, 0, sub, nums, result);
		return result;
	}
private:
	void subsetsDFS(int n, int start, int cur, vector<int> &sub, vector<int> &nums, vector<vector<int>> &result)
	{
		if (cur == n)
			return;
		for (int i = start; i < n; i++)
		{
			sub.push_back(nums[i]);
			result.push_back(sub);
			subsetsDFS(n, i + 1, cur + 1, sub, nums, result);
			sub.pop_back();
		}
	}
};
//迭代的方法，每次将nums中剩余的一个元素添加到已有的各子集，形成一组新的子集，并加入结果
class Solution2
{
public:
	vector<vector<int>> subsets(vector<int>& nums) 
	{
		sort(nums.begin(), nums.end());
		vector<vector<int>> subs(1, vector<int>());
		for (int i = 0; i < nums.size(); i++) {
			int n = subs.size();
			for (int j = 0; j < n; j++) {
				subs.push_back(subs[j]);
				subs.back().push_back(nums[i]);
			}
		}
		return subs;
	}
};
//位向量法，开一个位向量，每个元素可以选或者不选
class Solution3
{
public:
	vector<vector<int> > subsets(vector<int> &S) 
	{
		sort(S.begin(), S.end()); 
		vector<vector<int> > result;
		vector<bool> selected(S.size(), false);
		subsets(S, selected, 0, result);
		return result;
	}
private:
	static void subsets(const vector<int> &S, vector<bool> &selected, int step,
		vector<vector<int> > &result) {
		if (step == S.size()) {
			vector<int> subset;
			for (int i = 0; i < S.size(); i++) {
				if (selected[i]) subset.push_back(S[i]);
			}
			result.push_back(subset);
			return;
		}
		//不选S[step]
		selected[step] = false;
		subsets(S, selected, step + 1, result);
		//选S[step]
		selected[step] = true;
		subsets(S, selected, step + 1, result);
	}
};
//二进制法，位操作法，利用一个整形来代表是否选择这个数，0代表不选，1代表选
class Solution4 {
public:
	vector<vector<int>> subsets(vector<int>& nums) {
		sort(nums.begin(), nums.end());
		int num_subset = pow(2, nums.size());
		vector<vector<int> > res(num_subset, vector<int>());
		for (int i = 0; i < nums.size(); i++)
			for (int j = 0; j < num_subset; j++)
				if ((j >> i) & 1)
					res[j].push_back(nums[i]);
		return res;
	}
};
//int main(void)
//{
//	Solution test;
//	vector<int> input = { 1,2,3 };
//	auto a = test.subsets(input);
//	for_each(a.begin(), a.end(), [](vector<int> &x) {
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
