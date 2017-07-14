//	268. Missing Number
//------------------------------------------------------------------------------//
//	Given an array containing n distinct numbers taken from 0, 1, 2, ..., n,	//
//	find the one that is missing from the array.								//
//	For example,																//
//	Given nums = [0, 1, 3] return 2.											//
//	Note:																		//
//	Your algorithm should run in linear runtime complexity.Could you implement	//
//	it using only constant extra space complexity ?								//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<queue>
// constants
// function prototype
using namespace std;
//位运算的方法，原本应是[0,n],现在缺一个，利用异或，同时异或下标，最后结果就是缺的值
//时间复杂度O(n)，空间O(1)
class Solution {
public:
	int missingNumber(vector<int>& nums) {
		int Xor = nums.size();
		for (int i = 0; i < nums.size(); ++i)
			Xor ^= nums[i] ^ i;
		return Xor;
	}
};
//二分搜索
class Solution2 {
public:
	int missingNumber(vector<int>& nums) {
		sort(nums.begin(), nums.end());
		int left = 0, right = nums.size(), mid;
		while (left < right) {
			mid = left + (right - left) / 2;
			if (nums[mid] > mid) right = mid;
			else left++;
		}
		return left;
	}
};
//求和的方法
class Solution3 {
public:
	int missingNumber(vector<int>& nums) {
		long long sum = (long long)(nums.size() + 1)*nums.size() / 2;
		for (int i = 0; i < nums.size(); ++i)
			sum -= nums[i];
		return sum;
	}
};
//int main(void)
//{
//	Solution3 test;
//	vector<int> nums{ 0,1,2,3,5,6 };
//	cout << test.missingNumber(nums);
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