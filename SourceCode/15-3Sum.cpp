//	15. 3Sum
#include <iostream>
#include<vector>
#include<string>
#include<cctype>
#include<algorithm>
#include<set>
#include<unordered_map>
// constants
// function prototype
using namespace std;
//左右夹逼法
class Solution 
{
public:
	vector<vector<int>> threeSum(vector<int>& nums) 
	{
		vector<vector<int>> result;
		if (nums.size() < 3)
			return result;
		sort(nums.begin(), nums.end());
		for (int i = 0; i < nums.size() - 2; i++)
		{
			int start = i + 1;
			int end = nums.size() - 1;
			int target = -nums[i];
			if (nums[i] > 0)
				break;
			while (start < end)
			{
				int gap = nums[start] + nums[end];
				if (gap == target)
				{
					vector<int> triple = { nums[i],nums[start],nums[end] };
					result.push_back(triple);
					while (start < end&&nums[start] == triple[1])
						start++;
					while (start < end&&nums[end] == triple[2])
						end--;
				}
				else if (gap > target)
					end--;
				else
					start++;
			}
			while (i + 1 < nums.size() && nums[i] == nums[i + 1])
				i++;
		}
		return result;
	}
};
//左右夹逼法，O(n2)，更通用的形式
class Solution2
{
public:
	vector<vector<int>> threeSum(vector<int>& nums)
	{
		vector<vector<int>> result;
		if (nums.size() < 3)
			return result;
		sort(nums.begin(), nums.end());
		const int target = 0;
		auto last = nums.end();
		for (auto i = nums.begin(); i != last - 2; i++)
		{
			auto j = i + 1;
			if (i != nums.begin() && *i == *(i - 1))
				continue;
			auto k = last - 1;
			while (j < k)
			{
				if ((*i + *j + *k) < target)
				{
					j++;
					while (*j == *(j - 1) && j < k) ++j;
				}
				else if ((*i + *j + *k) > target)
				{
					k--;
					while (*k == *(k + 1) && j < k) --k;
				}
				else
				{
					result.push_back({ *i,*j,*k });
					j++;
					k--;
					while (*j == *(j - 1) && j < k) ++j;
					while (*k == *(k + 1) && j < k) --k;
				}
			}
		}
		return result;
	}
};
//int main(void)
//{
//	Solution test;
//	vector<int> a({ -1,0,1,2,-1,-4 });
//	auto x=test.threeSum(a);
//	
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}
