//	33. Search in Rotated Sorted Array
//------------------------------------------------------------------------------//
//	Suppose an array sorted in ascending order is rotated at some pivot unknown //
//	to you beforehand.															//
//	(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).							//
//	You are given a target value to search.If found in the array return its		//
//	index, otherwise return -1.													//
//	You may assume no duplicate exists in the array.							//
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
//算法思想：先二分查找到旋转点，将旋转点作为偏移量再二分查找
class Solution 
{
public:
	int search(vector<int>& nums, int target) 
	{
		if (nums.empty())
			return -1;
		int offset = SearchReverse(nums);
		int size = nums.size();
		int start = 0, end = size - 1;
		if (target < nums[(start + offset) % size] || target > nums[(end + offset) % size])
			return -1;
		while (start <= end)
		{
			int min = nums[(start + offset) % size];
			int max = nums[(end + offset) % size];
			
			int mid = (end + start) / 2;
			int middle = nums[(mid + offset) % size];
			if (target == middle)
				return ((mid + offset) % size);
			else if (target < middle)
				end = mid - 1;
			else
				start = mid + 1;
		}
		return -1;
	}
	int SearchReverse(vector<int>& nums)
	{
		int result = 0;
		int start = 0, end = nums.size() - 1;
		while (start < end)
		{
			if (nums[start] <= nums[end])
				break;
			int mid = (end + start) / 2;
			if (nums[start] > nums[mid])
				end = mid - 1;
			else if (nums[mid] > nums[end])
				start = mid + 1;
		}
		if (nums[nums.size() - 1] < nums[start])
			return end + 1;
		return start;
	}
};
//算法思想，直接二分，确定分界,比方案一更优
class Solution2
{
public:
	int search(vector<int>& nums, int target)
	{
		int start = 0, end = nums.size();
		while (start != end)
		{
			int mid = (start + end) / 2;
			if (nums[mid] == target)
				return mid;
			if (nums[start] <= nums[mid])
			{
				if (nums[start] <= target&&target < nums[mid])
					end = mid;
				else
					start = mid + 1;
			}
			else
			{
				if (nums[mid] < target&&target <= nums[end - 1])
					start = mid + 1;
				else
					end = mid;
			}
		}
		return -1;
	}
};
//int main(void)
//{
//	Solution2 test;
//	vector<int> a({3,4,1,2 });
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
