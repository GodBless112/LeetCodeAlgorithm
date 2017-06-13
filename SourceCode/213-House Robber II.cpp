//	213. House Robber II
//------------------------------------------------------------------------------//
//	Note: This is an extension of House Robber.									//
//	After robbing those houses on that street, the thief has found himself a	//
//	new place for his thievery so that he will not get too much attention.This	//
//	time, all houses at this place are arranged in a circle.That means the		//
//	first house is the neighbor of the last one.Meanwhile, the security system	//
//	for these houses remain the same as for those in the previous street.		//
//	Given a list of non - negative integers representing the amount of money of //
//	each house, determine the maximum amount of money you can rob tonight		//
//	without alerting the police.												//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<unordered_set>
// constants
// function prototype
using namespace std;
//类似于House Robber I，动态规划的思想
//由于房子成环状，那么第一个房子和最后一个房子肯定不能同时抢，即可以不抢第一个或不抢最后一个
//可以对前n-1个房子和后n-1个房子分别计算一次
class Solution {
public:
	int rob(vector<int>& nums) {
		int result = INT_MIN;
		int prev = 0, cur = 0;
		int n = nums.size();
		if (n == 1)
			return nums[0];
		for (int i = 0; i < n - 1; ++i) {
			prev = max(prev + nums[i], cur);
			swap(prev, cur);
		}
		result = max(cur, result);
		prev = cur = 0;
		for (int i = 1; i < n; ++i) {
			prev = max(prev + nums[i], cur);
			swap(prev, cur);
		}
		return max(result, cur);
	}
};
//上述方法的优化
class Solution2 {
public:
	int rob(vector<int>& nums) {
		int n = nums.size();
		if (n < 2) return n ? nums[0] : 0;
		return max(robber(nums, 0, n - 2), robber(nums, 1, n - 1));
	}
private:
	int robber(vector<int>& nums, int l, int r) {
		int pre = 0, cur = 0;
		for (int i = l; i <= r; i++) {
			int temp = max(pre + nums[i], cur);
			pre = cur;
			cur = temp;
		}
		return cur;
	}
};
//int main(void)
//{
//	Solution2 test;
//	vector<int> nums{ 1 };
//	cout << test.rob(nums);
//	cout << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}