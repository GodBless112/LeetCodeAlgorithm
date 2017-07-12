//	260. Single Number III
//------------------------------------------------------------------------------//
//	Given an array of numbers nums, in which exactly two elements appear only	//
//	once and all the other elements appear exactly twice. Find the two elements //
//	that appear only once.														//
//	For example :																//
//	Given nums = [1, 2, 1, 3, 2, 5], return[3, 5].								//
//	Note :																		//
//	1.The order of the result is not important.So in the above example, [5, 3]	//
//	is also correct.															//
//	2.Your algorithm should run in linear runtime complexity.Could you implement//
//	it using only constant space complexity ?									//
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
//哈希表，O(n)时间，O(n)空间
class Solution {
public:
	vector<int> singleNumber(vector<int>& nums) {
		unordered_map<int, int> dict;
		for (int i = 0; i < nums.size(); ++i)
			dict[nums[i]]++;
		vector<int> result;
		for (auto key : dict)
			if (key.second == 1)
				result.push_back(key.first);
		return result;
	}
};
//位运算：
//首先所有数异或，得到只出现一次的两数的异或值，由于两个数不同
//那么，异或结果即为他们不同位的组合，取最后一位bit，将nums划分为两组
//则得到结果
class Solution2 {
public:
	vector<int> singleNumber(vector<int>& nums) {
		int XorVal = 0;
		for (int i = 0; i < nums.size(); ++i)
			XorVal ^= nums[i];
		XorVal &= -XorVal;	//得到最后一bit
		//XorVal = (XorVal & (XorVal - 1)) ^ XorVal;	//另一种得到最后一bit的方法
		vector<int> result(2);
		for (int i = 0; i < nums.size(); ++i) {
			if ((XorVal & nums[i]) == 0)
				result[0] ^= nums[i];
			else
				result[1] ^= nums[i];
		}
		return result;
	}
};
//int main(void)
//{
//	Solution2 test;
//	vector<int> nums{ 1, 2, 1, 3, 2, 5 };
//	auto res = test.singleNumber(nums);
//	cout << res[0] << " " << res[1];
//	cout << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}