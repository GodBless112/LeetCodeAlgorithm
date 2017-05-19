//	136. Single Number
//------------------------------------------------------------------------------//
//	Given an array of integers, every element appears twice except for one.		//
//	Find that single one.														//
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

//利用哈希表
class Solution {
public:
	int singleNumber(vector<int>& nums) {
		unordered_map<int, int> numsCount;
		for (int i = 0; i < nums.size(); ++i)
			numsCount[nums[i]]++;
		for (auto i = numsCount.begin(); i != numsCount.end(); ++i)
			if (i->second == 1)
				return i->first;
	}
};
//利用异或，偶数次同元素异或之后仍为0
class Solution2 {
public:
	int singleNumber(vector<int>& nums) {
		int res = 0;
		for (auto i : nums)
			res ^= i;
		return res;
	}
};
//STL的异或方法
class Solution3 {
public:
	int singleNumber(vector<int>& nums) {
		return accumulate(nums.begin(), nums.end(), 0, bit_xor<int>());
	}
};
//int main(void)
//{
//	Solution3 test;
//	vector<int> nums({ 1,2,3,1,2,3,4 });
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