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
int main(void)
{
	Solution test;
	vector<int> nums{ 1,3,4,5,6 };
	cout << test.rob(nums);
	// code to keep window open for MSVC++
	cin.clear();
	while (cin.get() != '\n')
		continue;
	cin.get();
	
	return 0;
}