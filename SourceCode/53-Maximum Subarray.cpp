//	53. Maximum Subarray
//------------------------------------------------------------------------------//
//	Find the contiguous subarray within an array (containing at least one		//
//	number) which has the largest sum.											//
//	For example, given the array[-2, 1, -3, 4, -1, 2, 1, -5, 4],				//
//	the contiguous subarray[4, -1, 2, 1] has the largest sum = 6.				//
//	click to show more practice.												//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<functional>
#include<unordered_map>
// constants
// function prototype
using namespace std;
//贪心算法
class Solution 
{
public:
	int maxSubArray(vector<int>& nums) 
	{
		int result = INT_MIN;
		int sum = 0;
		for (int i = 0; i < nums.size(); i++)
		{
			sum += nums[i];
			if (sum > result)
				result = sum;
			if (sum < 0)
				sum = 0;
		}
		return result;
	}
};
class Solution2 {
public:
	int maxSubArray(vector<int> &num) {
		if (num.empty())
			return INT_MIN;
		int ans = num[0], i, j, sum = 0;
		for (i = 0; i<num.size(); i++) {
			sum += num[i];
			ans = max(sum, ans);
			sum = max(sum, 0);
		}
		return ans;
	}
};
//动态规划：考虑状态转移，对于i处之后的子字符串，前面的字符串是否有用取决于其是否大于0
//则状态转移方程为：F[i]=max{F[j-1]+S[j],S[j]}，F[j]是以S[j]结尾的最大子序列和
//target=max{F[i]}i=0...n
class Solution3
{
public:
	int maxSubArray(vector<int> &nums)
	{
		int result = INT_MIN, F = 0;
		for (int i = 0; i < nums.size(); i++)
		{
			F = max(F + nums[i], nums[i]);
			result = max(result, F);
		}
		return result;
	}
};
//分而治之
class Solution4 {
public:
	void maxSubArray(vector<int>& nums, int l, int r, int& mx, int& lmx, int& rmx, int& sum) {
		if (l == r) {
			mx = lmx = rmx = sum = nums[l];
		}
		else {
			int m = (l + r) / 2;
			int mx1, lmx1, rmx1, sum1;
			int mx2, lmx2, rmx2, sum2;
			maxSubArray(nums, l, m, mx1, lmx1, rmx1, sum1);
			maxSubArray(nums, m + 1, r, mx2, lmx2, rmx2, sum2);
			mx = max(max(mx1, mx2), rmx1 + lmx2);
			lmx = max(lmx1, sum1 + lmx2);
			rmx = max(rmx2, sum2 + rmx1);
			sum = sum1 + sum2;
		}
	}
	int maxSubArray(vector<int>& nums) {
		if (nums.size() == 0) {
			return 0;
		}
		int mx, lmx, rmx, sum;
		maxSubArray(nums, 0, nums.size() - 1, mx, lmx, rmx, sum);
		return mx;
	}
};
//int main(void)
//{
//	Solution3 test;
//	vector<int> a({-2});
//	cout << test.maxSubArray(a) << endl;
//	
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}
