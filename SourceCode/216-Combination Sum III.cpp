//	216. Combination Sum III
//------------------------------------------------------------------------------//
//	Find all possible combinations of k numbers that add up to a number n,		//
//	given that only numbers from 1 to 9 can be used and each combination should //
//	be a unique set of numbers.													//
//	Example 1:																	//
//	Input: k = 3, n = 7															//
//	Output :																	//
//	[[1, 2, 4]]																	//
//	Example 2 :																	//
//	Input : k = 3, n = 9														//
//	Output :																	//
//	[[1, 2, 6], [1, 3, 5], [2, 3, 4]]											//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<queue>
#include<set>
#include<ctime>
#include<stdlib.h>
// constants
// function prototype
using namespace std;
//深度优先搜索，加回溯
class Solution {
public:
	vector<vector<int>> combinationSum3(int k, int n) {
		vector<vector<int>> result;
		vector<int> record;
		DFS(result, record, k, n, 1);
		return result;
	}
private:
	void DFS(vector<vector<int>> &result, vector<int> &record, int k, int gap, int start) {
		if (record.size() > k)
			return;
		if (gap == 0) {
			if (record.size() != k) return;
			result.push_back(record);
			return;
		}
		for (int i = start; i <= 9; ++i) {
			if (gap < i) return;	//剪枝回溯
			else {
				record.push_back(i);
				DFS(result, record, k, gap - i, i + 1);
				record.pop_back();
			}
		}
	}
};
//另外几种版本的回溯，更简洁
class Solution2 {
public:
	vector<vector<int>> combinationSum3(int k, int n) {
		vector<vector<int>> result;
		vector<int> record;
		DFS(result, record, k, n, 1);
		return result;
	}
private:
	void DFS(vector<vector<int>> &result, vector<int> &record, int k, int gap, int start) {
		if (gap == 0 && k == 0) {
			result.push_back(record);
			return;
		}
		for (int i = start; i <= 10 - k&&i <= gap; ++i) {
			record.push_back(i);
			DFS(result, record, k - 1, gap - i, i + 1);
			record.pop_back();
		}
	}
};
class Solution3 {
public:
	vector<vector<int>> combinationSum3(int k, int n) {
		vector<vector<int>> result;
		vector<int> record;
		DFS(result, record, k, n);
		return result;
	}
private:
	void DFS(vector<vector<int>> &result, vector<int> &record, int k, int gap) {
		if (gap == 0 && record.size() == k) {
			result.push_back(record);
			return;
		}
		if (record.size() < k) {
			for (int i = record.empty() ? 1 : record.back() + 1; i<=9 && i <= gap; ++i) {
				record.push_back(i);
				DFS(result, record, k, gap - i);
				record.pop_back();
			}
		}
	}
};
//int main(void)
//{
//	Solution2 test;
//	auto res = test.combinationSum3(3, 27);
//	for_each(res.begin(), res.end(), [](vector<int> &nums) {
//		for (auto num : nums)
//			cout << num << " ";
//		cout << endl;
//	});
//	cout << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}