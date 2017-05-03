//	46. Permutations
//------------------------------------------------------------------------------//
//	Given a collection of distinct numbers, return all possible permutations.	//
//	For example,																//
//	[1, 2, 3] have the following permutations :									//
//	[																			//
//		[1, 2, 3],																//
//		[1, 3, 2],																//
//		[2, 1, 3],																//
//		[2, 3, 1],																//
//		[3, 1, 2],																//
//		[3, 2, 1]																//
//	]																			//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<functional>
#include<iterator>
#include<iomanip>
#include<sstream>
// constants
// function prototype
using namespace std;
class Solution 
{
public:
	vector<vector<int>> permute(vector<int>& nums) 
	{
		vector<vector<int>> result;
		permuteDFS(nums, result, 0);
		return result;
	}
private:
	void permuteDFS(vector<int> &nums, vector<vector<int>> &result, int k)
	{
		if (k == nums.size() - 1)
		{
			result.push_back(nums);
			return;
		}
		for (int i = k; i < nums.size(); i++)
		{
			swap(nums[i], nums[k]);
			permuteDFS(nums, result, k + 1);
			swap(nums[i], nums[k]);
		}
	}
};
//利用STL的next_permutation
class Solution2
{
public:
	vector<vector<int>> permute(vector<int>& nums)
	{
		vector<vector<int>> result;
		sort(nums.begin(), nums.end());
		do
			result.push_back(nums);
		 while (next_permutation(nums.begin(), nums.end()));
		 return result;
	}
};
//利用自己实现的next_permutation
class Solution3
{
public:
	vector<vector<int>> permute(vector<int>& nums)
	{
		vector<vector<int>> result;
		sort(nums.begin(), nums.end());
		do
			result.push_back(nums);
		while (next_permutation(nums));
		return result;
	}
private:
	bool next_permutation(vector<int>& nums)
	{
		int size = nums.size();
		if (size < 2)
			return false;
		auto i = nums.rbegin();
		for (; i != (nums.rend() - 1); i++)
			if (*i > *(i + 1))
				break;
		if (i == nums.rend() - 1)
		{
			reverse(nums.begin(), nums.end());
			return false;
		}
		auto j = nums.rbegin();
		while (j != (i + 1) && *j <= *(i + 1))
			j++;
		swap(*(i + 1), *j);
		reverse(nums.rbegin(), i + 1);
		return true;
	}
};
//int main(void)
//{
//	Solution3 test;
//	vector<int> a({ 1,2,3 });
//	auto x = test.permute(a);
//	for (auto y1 : x)
//	{
//		for (auto y2 : y1)
//			cout << y2 << " ";
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
