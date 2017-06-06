//	162. Find Peak Element
//------------------------------------------------------------------------------//
//	A peak element is an element that is greater than its neighbors.			//
//	Given an input array where nums[i] ≠ nums[i + 1], find a peak element and	//
//	return its index.															//
//	The array may contain multiple peaks, in that case return the index to any	//
//	one of the peaks is fine.													//
//	You may imagine that nums[-1] = nums[n] = -∞.								//
//	For example, in array[1, 2, 3, 1], 3 is a peak element and your function	//
//	should return the index number 2.											//
//	Note:																		//
//	Your solution should be in logarithmic complexity.							//
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
//线性搜索，时间复杂度O(n)，空间复杂度O(1)，有三种情况
//1.纯升序，则返回最后一个元素为峰值
//2.纯降序，则返回第一个元素为峰值，我们不需要比较nums[i]和nums[i-1]，因为随着前面的处理可以保证是处在升序中
//3.有升有降，则返回中间元素
class Solution {
public:
	int findPeakElement(vector<int>& nums) {
		for (int i = 0; i < nums.size() - 1; i++) {
			if (nums[i] > nums[i + 1])
				return i;
		}
		return nums.size() - 1;
	}
};
//迭代版的二分搜索，时间复杂度O(log​2​​(n))，空间复杂度O(1)
//这个方法是判断中间元素比两边都大则为峰值，可以优化
class Solution2 {
public:
	int findPeakElement(vector<int>& nums) {
		int low = 0, high = nums.size() - 1;
		while (low < high - 1) {
			int mid = (low + high) / 2;
			if (nums[mid] > nums[mid - 1] && nums[mid] > nums[mid + 1])
				return mid;
			else if (nums[mid] > nums[mid + 1])
				high = mid - 1;
			else
				low = mid + 1;
		}
		return nums[low] > nums[high] ? low : high;
	}
};
//迭代版的优化，同1，不需要比较nums[i]和nums[i-1]
class Solution3 {
public:
	int findPeakElement(vector<int>& nums) {
		int left = 0, right = nums.size() - 1;
		while (left < right) {
			int mid = left + (right - left) / 2;
			if (nums[mid] > nums[mid + 1])
				right = mid;
			else
				left = mid + 1;
		}
		return left;
	}
};
//递归二分搜索
class Solution4 {
public:
	int findPeakElement(vector<int>& nums) {
		return findPeakElement(nums, 0, nums.size() - 1);
	}
private:
	int findPeakElement(vector<int> &nums, int l, int r) {
		if (l == r) return l;
		int mid = (l + r) / 2;
		if (nums[mid] > nums[mid + 1])
			return findPeakElement(nums, l, mid);
		return findPeakElement(nums, mid + 1, r);
	}
};
//int main(void)
//{
//	Solution4 test;
//	vector<int> nums{ 1, 2, 3, 1 };
//	cout << test.findPeakElement(nums);
//	cout << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//	
//	return 0;
//}