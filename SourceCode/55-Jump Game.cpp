//	55. Jump Game
//------------------------------------------------------------------------------//
//	Given an array of non-negative integers, you are initially positioned at	//
//	the first index of the array.												//
//	Each element in the array represents your maximum jump length at that		//
//	position.																	//
//	Determine if you are able to reach the last index.							//
//	For example :																//
//	A = [2, 3, 1, 1, 4], return true.											//
//	A = [3, 2, 1, 0, 4], return false.											//
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
//贪心算法：由于是最大可以跳多远，也就是说如果能到最后一点，则每一层都可以到
//所以只需判断最远能到第几层
class Solution 
{
public:
	bool canJump(vector<int>& nums) 
	{
		int reach = 0;
		for (int i = 0; i <= reach && reach < nums.size(); ++i)
		{
			reach = max(reach, i + nums[i]);
		}
		return reach >= (nums.size() - 1);
	}
};
//贪心算法，逆向走，看最多下降到第几层，跟正向走有区别
class Solution2
{
public:
	bool canJump(vector<int>& nums)
	{
		if (nums.empty())
			return true;
		int n = nums.size() - 1;
		for (int i = n - 1; i >= 0; --i)
			if ((i + nums[i]) >= n)
				n = i;
		return n == 0;
	}
};
//动态规划：F[i]表示从0层出发，走到i时剩余的最大步数
//则状态转移方程为：F[i]=max{F[i-1],A[i-1]}-1
class Solution3 {
public:
	bool canJump(const vector<int>& nums) 
	{
		vector<int> f(nums.size(), 0);
		f[0] = 0;
		for (int i = 1; i < nums.size(); i++) 
		{
			f[i] = max(f[i - 1], nums[i - 1]) - 1;
			if (f[i] < 0) return false;;
		}
		return f[nums.size() - 1] >= 0;
	}
};
//int main(void)
//{
//	Solution3 test;
//	vector<int> a = { 2,2, 0,1 };
//	cout << boolalpha << test.canJump(a);
//	cout << endl;
//	
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}
