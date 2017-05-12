//	81. Search in Rotated Sorted Array II
//------------------------------------------------------------------------------//
//	Follow up for "Search in Rotated Sorted Array":								//
//	What if duplicates are allowed ?											//
//	Would this affect the run - time complexity ? How and why ?					//
//	Suppose an array sorted in ascending order is rotated at some pivot unknown //
//	to you beforehand.															//
//	(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).							//
//	Write a function to determine if a given target is in the array.			//
//	The array may contain duplicates.											//
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
//与无重复元素的情况不同，判断界限的方式不一样
//nums[start] <= nums[mid]无法分界，须分别对待
class Solution
{
public:
	bool search(vector<int>& nums, int target)
	{
		int start = 0, end = nums.size();
		//注意此处end是右开区间，每次end应该等于mid而不是mid-1
		while (start != end)
		{
			int mid = (start + end) / 2;
			if (nums[mid] == target)
				return true;
			if (nums[start] < nums[mid])
			{
				if (nums[start] <= target&&target < nums[mid])
					end = mid;
				else
					start = mid + 1;
			}
			else if (nums[start] > nums[mid])
			{
				if (nums[mid] < target&&target <= nums[end - 1])
					start = mid + 1;
				else
					end = mid;
			}
			else
				start++;
		}
		return false;
	}
};
//int main(void)
//{
//	Solution test;
//	vector<int> a({1,3 });
//	cout << test.search(a,1) << endl;
//	
//
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}
