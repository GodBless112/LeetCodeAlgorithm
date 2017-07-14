//	283. Move Zeroes
//------------------------------------------------------------------------------//
//	Given an array nums, write a function to move all 0's to the end of it		//
//	while maintaining the relative order of the non-zero elements.				//
//	For example, given nums = [0, 1, 0, 3, 12], after calling your function,	//
//	nums should be[1, 3, 12, 0, 0].												//
//	Note:																		//
//	1.You must do this in - place without making a copy of the array.			//
//	2.Minimize the total number of operations.									//
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
//双指针，操作不是最优
class Solution {
public:
	void moveZeroes(vector<int>& nums) {
		int nonzeroIndex = 0;
		for (int i = 0; i < nums.size(); ++i)
			if (nums[i] != 0)
				nums[nonzeroIndex++] = nums[i];
		for (int i = nonzeroIndex; i < nums.size(); ++i)
			nums[i] = 0;
	}
};
//双指针，时间空间最优
class Solution2 {
public:
	void moveZeroes(vector<int>& nums) {
		int zeroIndex = 0;
		for (int i = 0; i < nums.size(); ++i)
			if (nums[i] != 0)
				swap(nums[zeroIndex++], nums[i]);
	}
};
//STL方法
class Solution3 {
public:
	void moveZeroes(vector<int>& nums) {
		fill(remove(nums.begin(), nums.end(), 0), nums.end(), 0);
	}
};
//int main(void)
//{
//	Solution2 test;
//	vector<int> nums{ 0, 1, 0, 3, 12 };
//	test.moveZeroes(nums);
//	for (auto x : nums)
//		cout << x << " ";
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