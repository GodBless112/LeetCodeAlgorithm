//	209. Minimum Size Subarray Sum
//------------------------------------------------------------------------------//
//	Given an array of n positive integers and a positive integer s, find the	//
//	minimal length of a contiguous subarray of which the sum ≥ s. If there		//
//	isn't one, return 0 instead.												//
//	For example, given the array[2, 3, 1, 2, 4, 3] and s = 7,					//
//	the subarray[4, 3] has the minimal length under the problem constraint.		//
//	More practice:																//
//	If you have figured out the O(n) solution, try coding another solution of	//
//	which the time complexity is O(n log n).									//
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
//时间复杂度O(n)的做法：双指针的方法
class Solution {
public:
	int minSubArrayLen(int s, vector<int>& nums) {
		int result = INT_MAX, n = nums.size(), sum = 0, start = 0;
		for (int i = 0; i < n; ++i) {
			sum += nums[i];
			while (sum >= s) {
				result = min(result, i - start + 1);
				sum -= nums[start++];
			}
		}
		return result == INT_MAX ? 0 : result;
	}
};
//双指针的另一种实现
class Solution2 {
public:
	int minSubArrayLen(int s, vector<int>& nums) {
		int n = nums.size(), left = 0, right = 0, sum = 0, result = INT_MAX;
		while (right < n) {
			do
				sum += nums[right++];
			while (right < n && sum < s);
			while (left < right && (sum - nums[left]) >= s)
				sum -= nums[left++];
			if (sum >= s) result = min(result, right - left);
		}
		return result == INT_MAX ? 0 : result;
	}
};
//时间复杂度O(nlogn)的做法，分而治之
//利用一个数组记录累加和，空间复杂度O(n)
class Solution3 {
public:
	int minSubArrayLen(int s, vector<int>& nums) {
		vector<int> sums = accumulate(nums);
		int n = nums.size(), minlen = INT_MAX;
		for (int i = 1; i <= n; i++) {
			if (sums[i] >= s) {
				int p = upper_bound(sums, 0, i, sums[i] - s);
				if (p != -1) minlen = min(minlen, i - p + 1);
			}
		}
		return minlen == INT_MAX ? 0 : minlen;
	}
private:
	vector<int> accumulate(vector<int>& nums) {
		int n = nums.size();
		vector<int> sums(n + 1, 0);
		for (int i = 1; i <= n; i++)
			sums[i] = nums[i - 1] + sums[i - 1];
		return sums;
	}
	int upper_bound(vector<int>& sums, int left, int right, int target) {
		int l = left, r = right;
		while (l < r) {
			int m = l + ((r - l) >> 1);
			if (sums[m] <= target) l = m + 1;
			else r = m;
		}
		return sums[r] > target ? r : -1;
	}
};
//时间复杂度O(nlogn)，空间复杂度O(1)的分而治之方法
class Solution4 {
public:
	int minSubArrayLen(int s, vector<int>& nums) {
		int i = 1, j = nums.size(), min = 0;
		while (i <= j) {
			int mid = (i + j) / 2;
			if (WindowExist(mid, nums, s)) {
				j = mid - 1;
				min = mid;
			}
			else i = mid + 1;
		}
		return min;
	}
private:
	//滑动窗，检测大小为size的窗口的和是否大于等于s
	bool WindowExist(int size, vector<int> &nums, int s) {
		int sum = 0;
		for (int i = 0; i < nums.size(); i++) {
			if (i >= size) sum -= nums[i - size];
			sum += nums[i];
			if (sum >= s) return true;
		}
		return false;
	}
};
//int main(void)
//{
//	Solution4 test;
//	vector<int> nums{ 12,28,83,4,25,26,25,2,25,25,25,12 };
//	cout << test.minSubArrayLen(213, nums);
//	cout << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}