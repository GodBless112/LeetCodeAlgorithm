//	153. Find Minimum in Rotated Sorted Array
//------------------------------------------------------------------------------//
//	Suppose an array sorted in ascending order is rotated at some pivot unknown //
//	to you beforehand.															//
//	(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).							//
//	Find the minimum element.													//
//	You may assume no duplicate exists in the array.							//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<sstream>
// constants
// function prototype
using namespace std;
//二分搜索
class Solution {
public:
	int findMin(vector<int>& nums) {
		int start = 0, end = nums.size();
		int result = INT_MAX;
		while (start != end) {
			int mid = start + (end - start) / 2;
			if (nums[start] <= nums[mid]) {
				result = min(result, nums[start]);
				start = mid + 1;
			}
			else {
				result = min(result, nums[mid]);
				end = mid;
			}
		}
		return result;
	}
};
//另一种二分搜索，有三种情况
//Case 1. The leftmost value is less than the rightmost value in the list: This means that the list is not rotated.
//e.g>[1 2 3 4 5 6 7]
//Case 2. The value in the middle of the list is greater than the leftmost and rightmost values in the list.
//e.g>[4 5 6 7 0 1 2 3]
//Case 3. The value in the middle of the list is less than the leftmost and rightmost values in the list.
//e.g>[5 6 7 0 1 2 3 4]
class Solution2 {
public:
	int findMin(vector<int>& nums) {
		int left = 0, right = nums.size() - 1;
		while (left < right) {
			if (nums[left] < nums[right])
				return nums[left];

			int mid = (left + right) / 2;
			if (nums[mid] > nums[right])
				left = mid + 1;
			else
				right = mid;
		}

		return nums[left];
	}
};
//int main(void)
//{
//	Solution2 test;
//	vector<int> nums{ 4, 5, 6, 7, 0, 1, 2 };
//	cout << test.findMin(nums);
//	cout << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}