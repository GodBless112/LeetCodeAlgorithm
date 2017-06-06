//	198. House Robber
//------------------------------------------------------------------------------//
//	You are a professional robber planning to rob houses along a street. Each	//
//	house has a certain amount of money stashed, the only constraint stopping	//
//	you from robbing each of them is that adjacent houses have security system	//
//	connected and it will automatically contact the police if two adjacent		//
//	houses were broken into on the same night.									//
//	Given a list of non - negative integers representing the amount of money of //
//	each house, determine the maximum amount of money you can rob tonight		//
//	without alerting the police. 												//
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
//动态规划，从奇数出发和从偶数出发两个状态
//对于奇数位只能是上次在奇数位抢到的加上本次的或者偶数位抢到的，这次不抢，偶数位同理
//空间复杂度O(1)，时间复杂度O(n)
class Solution {
public:
	int rob(vector<int>& nums) {
		int a = 0, b = 0;
		for (int i = 0; i < nums.size(); ++i) {
			if (i % 2)
				a = max(b, a + nums[i]);
			else
				b = max(a, b + nums[i]);
		}
		return max(a, b);
	}
};
//动态规划：对于每一栋房子有两种情况，不抢或抢，则状态转移为，前一栋不抢到这一栋抢
//前一栋抢这一栋不抢，空间复杂度O(1)，时间复杂度O(n)
class Solution2 {
public:
	int rob(vector<int>& nums) {
		int exclude = 0, include = 0;	//不抢当前房子和抢当前房子
		for (int i = 0; i < nums.size(); ++i) {
			int tmp = include;
			include = exclude + nums[i];
			exclude = max(tmp, exclude);
		}
		return max(include, exclude);
	}
};
//利用一个数组记录，f(j) = max(f(j-1),f(j-2)+nums[i])，空间复杂度O(n)，时间复杂度O(n)
class Solution3 {
public:
	int rob(vector<int>& nums) {
		const int n = nums.size();
		if (n == 0) return 0;
		if (n == 1) return nums[0];
		if (n == 2) return max(nums[0], nums[1]);
		vector<int> f(n, 0);
		f[0] = nums[0];
		f[1] = max(nums[0], nums[1]);
		for (int i = 2; i < n; ++i)
			f[i] = max(f[i - 2] + nums[i], f[i - 1]);
		return f[n - 1];
	}
};
//方法3的优化，f(j) = max(f(j-1),f(j-2)+nums[i])，空间复杂度O(1)，时间复杂度O(n)
class Solution4 {
public:
	int rob(vector<int>& nums) {
		int it1 = 0, it2 = 0;
		for (int i = 0; i < nums.size(); i++) {
			it1 = max(it1 + nums[i], it2);
			swap(it1, it2);
		}
		return it2;
	}
};
//int main(void)
//{
//	Solution4 test;
//	vector<int> nums{ 1,3,4,20,6 };
//	cout << test.rob(nums);
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//	
//	return 0;
//}