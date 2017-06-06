//	152. Maximum Product Subarray
//------------------------------------------------------------------------------//
//	Find the contiguous subarray within an array (containing at least one		//
//	number) which has the largest product.										//
//	For example, given the array[2, 3, -2, 4],									//
//	the contiguous subarray[2, 3] has the largest product = 6.					//
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
//双端法，贪心的做法，对于乘来说，0是有害元素，遇到0重新置1
//偶数个负数的情况，两端出发的都一样，奇数个负数的情况则不一样
//从两边出发，取最大的
class Solution {
public:
	int maxProduct(vector<int>& nums) {
		int n = nums.size();
		if (n == 0) return 0;
		int front = 1, back = 1;
		int result = INT_MIN;
		for (int i = 0; i < n; ++i) {
			front = front*nums[i];
			back = back*nums[n - i - 1];
			result = max(result, max(front, back));
			if (front == 0) front = 1;
			if (back == 0) back = 1;
		}
		return result;
	}
};
//动态规划的思想，遇到负数，交换负值和正值记录
class Solution2 {
public:
	int maxProduct(vector<int>& nums) {
		int n = nums.size();
		if (n == 1) return nums[0];
		int pMax = 0, nMax = 0, result = INT_MIN;
		for (int i = 0; i < n; ++i) {
			if (nums[i] < 0) swap(pMax, nMax);
			pMax = max(pMax*nums[i], nums[i]);
			nMax = min(nMax*nums[i], nums[i]);
			result = max(result, pMax);
		}
		return result;
	}
};
//动态规划，一个变量记录到i时最大的乘积，由于有负数的存在，加一个变量记录到i时最小的乘积
class Solution3 {
public:
	int maxProduct(vector<int>& nums) {
		if (nums.size() == 0) return 0;
		long long curmax = nums[0], curmin = nums[0], res = nums[0];
		for (int i = 1; i<nums.size(); ++i) {
			long long premax = curmax;
			curmax = max(curmax*nums[i], max(curmin*nums[i], (long long)nums[i]));
			curmin = min(premax*nums[i], min(curmin*nums[i], (long long)nums[i]));
			res = max(res, curmax);
		}
		return int(res);
	}
};
//int main(void)
//{
//	Solution2 test;
//	vector<int> nums{ 2,3,-2,0,-1,1 };
//	cout << test.maxProduct(nums);
//	cout << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}