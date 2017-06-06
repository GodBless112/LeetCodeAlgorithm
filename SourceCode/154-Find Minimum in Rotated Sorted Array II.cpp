//	154. Find Minimum in Rotated Sorted Array II
//------------------------------------------------------------------------------//
//	Follow up for "Find Minimum in Rotated Sorted Array":						//
//	What if duplicates are allowed ?											//
//	Would this affect the run - time complexity ? How and why ?					//
//	Suppose an array sorted in ascending order is rotated at some pivot unknown //
//	to you beforehand.															//
//	(i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).							//
//	Find the minimum element.													//
//	The array may contain duplicates.											//
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
			if (nums[start] < nums[mid]) {
				result = min(result, nums[start]);
				start = mid + 1;
			}
			else if (nums[start] > nums[mid]) {
				result = min(result, nums[mid]);
				end = mid;
			}
			else {
				start++;
				result = min(result, nums[mid]);
			}		
		}
		return result;
	}
};
//二分搜索，有三种情况
//一、中间元素大于右边元素，说明最小值在中间元素和右边元素之间
//二、中间元素小于右边元素，说明最小值在左边元素和中间元素之间
//三、中间元素等于右边元素，说明左边元素和右边元素均相等，跳过这些元素
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
			else if (nums[mid] < nums[right])
				right = mid;
			else {
				left++;
				right--;
			}		
		}
		return nums[left];
	}
};

//int main(void)
//{
//	Solution2 test;
//	vector<int> nums{ 3,3,1,3 };
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