//	16. 3Sum Closest
//------------------------------------------------------------------------------//
//	Given an array S of n integers, find three integers in S such that the		//	 
//	sum is closest to a given number, target. Return the sum of the three i		//
//	ntegers. You may assume that each input would have exactly one solution.	//
//------------------------------------------------------------------------------//
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
//左右夹逼法，时间O(n2),空间O(1)
class Solution 
{
public:
	int threeSumClosest(vector<int>& nums, int target) 
	{
		sort(nums.begin(), nums.end());
		int result = 0;
		int diff = INT_MAX;
		for (int i = 0; i < nums.size(); i++)
		{
			int j = i + 1;
			int k = nums.size() - 1;
			while (j < k)
			{
				int sum = nums[i] + nums[j] + nums[k];
				if (sum == target)
				{
					return target;
				}
				int gap = abs(sum - target);
				if (gap < diff)
				{
					diff = abs(nums[i] + nums[j] + nums[k] - target);
					result = nums[i] + nums[j] + nums[k];
				}
				else if (sum < target)
				{						
					j++;
					while (j < k&&nums[j] == nums[j - 1])
						j++;
				}
				else if (sum > target)
				{
					k--;
					while (j < k&&nums[k] == nums[k + 1])
						k--;
				}
			}
			while (i + 1 < nums.size() && nums[i] == nums[i + 1])
				i++;
		}
		return result;
	}
};
//STL iterator形式
class Solution2
{
public:
	int threeSumClosest(vector<int>& nums, int target)
	{
		sort(nums.begin(), nums.end());
		int result = 0;
		int diff = INT_MAX;
		for (auto i = nums.begin(); i != nums.end() - 2; i++)
		{
			auto j = next(i);
			auto k = prev(nums.end());
			while (j < k)
			{
				const int sum = *i + *j + *k;
				if (sum == target)
					return target;
				const int gap = abs(sum - target);
				if (gap < diff)
				{
					diff = gap;
					result = sum;
				}
				if (sum < target)
					j++;
				else
					k--;
			}
		}
	}
};
//int main(void)
//{
//	Solution test;
//	vector<int> a({ 1,2,4,8,16,32,64,128 });
//	cout << test.threeSumClosest(a, 82) << endl;
//	
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}
