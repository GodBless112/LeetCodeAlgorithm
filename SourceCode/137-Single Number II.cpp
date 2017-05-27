//	137. Single Number II
//------------------------------------------------------------------------------//
//	Given an array of integers, every element appears three times except for	//
//	one, which appears exactly once. Find that single one.						//
//	Note:																		//
//	Your algorithm should have a linear runtime complexity.Could you implement	//
//	it without using extra memory ?												//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<unordered_map>
// constants
// function prototype
using namespace std;

//利用哈希表，时间复杂度O(N)，但是这使用了额外空间
class Solution {
public:
	int singleNumber(vector<int>& nums) {
		unordered_map<int, int> mp;
		for (int i = 0; i < nums.size(); ++i)
			mp[nums[i]]++;
		for (auto x : mp)
			if (x.second == 1)
				return x.first;
	}
};
//位运算
//用二进制模拟三进制的运算
//这里有三个标志，one，two，three,分别表示二进制位上1出现的次数（模3）
class Solution2 {
public:
	int singleNumber(vector<int>& nums) {
		int one = 0, two = 0, three = 0;
		for (auto i : nums) {
			two |= (one & i);		//二进制位上1出现的2次有哪些位，上一次one的结果遇上当前值，再或上上一次two结果
			one ^= i;				//二进制位上1出现的1次有哪些位
			three = ~(one & two);	//one和two相与的结果即为three，即one，two某一位同时为1时说明出现了三次
			one &= three;			//清空出现了三次的情况
			two &= three;
		}
		return one;
	}
};
//利用一个32位数组记录每一位出现的情况
class Solution3 {
public:
	int singleNumber(vector<int>& nums) {
		const int W = sizeof(int) * 8; 
		int count[W]; 
		fill_n(&count[0], W, 0);
		for (int i = 0; i < nums.size(); i++) {
			for (int j = 0; j < W; j++) {
				count[j] += (nums[i] >> j) & 1;
				count[j] %= 3;
			}
		}
		int result = 0;
		for (int i = 0; i < W; i++) {
			result += (count[i] << i);
		}
		return result;
	}
};
//方法2的改进版
class Solution4 {
public:
	int singleNumber(vector<int>& nums) {
		int ones = 0, twos = 0;
		for (int i = 0; i < nums.size(); ++i) {
			ones = (ones^nums[i])&(~twos);
			twos = (twos^nums[i])&(~ones);
		}
		return ones;
	}
};
//int main(void)
//{
//	Solution4 test;
//	vector<int> nums{ 1,2,1,-3,2,1,2 };
//	cout << test.singleNumber(nums);
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