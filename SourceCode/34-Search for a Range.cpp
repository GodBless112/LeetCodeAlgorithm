//	34. Search for a Range
//------------------------------------------------------------------------------//
//	Given an array of integers sorted in ascending order, find the starting and //
//	ending position of a given target value.									//
//	Your algorithm's runtime complexity must be in the order of O(log n).		//
//	If the target is not found in the array, return[-1, -1].					//
//	For example,																//
//	Given[5, 7, 7, 8, 8, 10] and target value 8,								//
//	return[3, 4].																//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<cctype>
#include<algorithm>
#include<stack>
#include<list>
#include<functional>
// constants
// function prototype
using namespace std;
//STL方法，lower_bound返回第一个大于等于target的值的位置，upper_bound返回第一个大于target的位置
class Solution 
{
public:
	vector<int> searchRange(vector<int>& nums, int target) 
	{
		auto a = lower_bound(nums.begin(), nums.end(), target);
		if (a == nums.end() || *a > target)
			return{ -1,-1 };
		auto b = upper_bound(a, nums.end(), target);
		vector<int> result(2);
		result[0] = a - nums.begin();
		result[1] = b - nums.begin() - 1;
		return result;
	}
};
//二分查找
class Solution2
{
public:
	vector<int> searchRange(vector<int>& nums, int target)
	{
		if (nums.empty())
			return { -1,-1 };
		int low, high;
		int start = 0, end = nums.size() - 1;
		while (start <= end)
		{
			if (nums[start] == target)
			{
				low = start;
				end = nums.size();
				while (start < end)
				{
					int mid2 = (start + end) / 2;
					if (nums[mid2] > target)
						end = mid2;
					else
						start = mid2 + 1;
				}
				high = start - 1;
				return{ low,high };
			}
			int mid = (start + end) / 2;
			if (nums[mid] == target)
				end = mid;
			else if (nums[mid] > target)
				end = mid - 1;
			else
				start = mid + 1;
		}
		return{ -1,-1 };
	}
};
class Solution3 
{
public:
	vector<int> searchRange(vector<int> & nums, int target) 
	{
		int n = nums.size();
		if (n == 0)
			return{ -1,-1 };
		int i = 0, j = n - 1;
		vector<int> ret(2, -1);
		// Search for the left one
		while (i < j)
		{
			int mid = (i + j) / 2;
			if (nums[mid] < target) i = mid + 1;
			else j = mid;
		}
		if (nums[i] != target) return ret;
		else ret[0] = i;

		// Search for the right one
		j = n - 1;  // We don't have to set i to 0 the second time.
		while (i < j)
		{
			int mid = (i + j) / 2 + 1;	// Make mid biased to the right
			if (nums[mid] > target) j = mid - 1;
			else i = mid;				// So that this won't make the search range stuck.
		}
		ret[1] = j;
		return ret;
	}
};
//int main(void)
//{
//	Solution test;
//	vector<int> a({  });
//	auto x = test.searchRange(a, 3);
//	for (auto y : x)
//		cout << y << " ";
//
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}
