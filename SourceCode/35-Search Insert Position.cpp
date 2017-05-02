//	35. Search Insert Position
//------------------------------------------------------------------------------//
//	Given a sorted array and a target value, return the index if the target is	//
//	found. If not, return the index where it would be if it were inserted in	//
//	order.																		//
//	You may assume no duplicates in the array.									//
//	Here are few examples.														//
//	[1, 3, 5, 6], 5 → 2														//
//	[1, 3, 5, 6], 2 → 1														//
//	[1, 3, 5, 6], 7 → 4														//
//	[1, 3, 5, 6], 0 → 0														//
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
//STL lower_bound
class Solution 
{
public:
	int searchInsert(vector<int>& nums, int target) 
	{
		return distance(nums.begin(), lower_bound(nums.begin(), nums.end(), target));
	}
	template<typename ForwardIterator, typename T>
	ForwardIterator lower_bound(ForwardIterator first,
		ForwardIterator last, T value) 
	{
		while (first != last) 
		{
			auto mid = next(first, distance(first, last) / 2);
			if (value > *mid) first = ++mid;
			else last = mid;
		}
		return first;
	}
};
//target位于start和end之间[start,end)
class Solution2
{
public:
	int searchInsert(vector<int>& nums, int target) 
	{
		int start = 0, end = nums.size();
		while (start < end)
		{
			int mid = (start + end) / 2 ;

			if (nums[mid] == target)
				return mid;
			else if (nums[mid] > target)
				end = mid;
			else
				start = mid + 1;
		}
		return start;
	}
};
class Solution3 {
public:
	int searchInsert(vector<int>& nums, int target) {
		int low = 0, high = nums.size() - 1;

		// Invariant: the desired index is between [low, high+1]
		while (low <= high) {
			int mid = low + (high - low) / 2;

			if (nums[mid] < target)
				low = mid + 1;
			else
				high = mid - 1;
		}

		// (1) At this point, low > high. That is, low >= high+1
		// (2) From the invariant, we know that the index is between [low, high+1], so low <= high+1. Follwing from (1), now we know low == high+1.
		// (3) Following from (2), the index is between [low, high+1] = [low, low], which means that low is the desired index
		//     Therefore, we return low as the answer. You can also return high+1 as the result, since low == high+1
		return low;
	}
};
//int main(void)
//{
//	Solution2 test;
//	vector<int> a({ 1,2});
//	auto x = test.searchInsert(a, 0);
//	cout << x;
//
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}
