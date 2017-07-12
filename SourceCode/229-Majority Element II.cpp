//	229. Majority Element II
//------------------------------------------------------------------------------//
//	Given an integer array of size n, find all elements that appear more than	//
//	⌊ n/3 ⌋ times. The algorithm should run in linear time and in O(1) space.	//
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
//哈希表的方法，时间复杂度O(n)，但违背了O(1)空间复杂度的要求
class Solution {
public:
	vector<int> majorityElement(vector<int>& nums) {
		unordered_map<int, int> dict;
		vector<int> result;
		int m = nums.size() / 3;
		for (size_t i = 0; i < nums.size(); ++i) {
			dict[nums[i]]++;
			if (dict[nums[i]] == m + 1)
				result.push_back(nums[i]);
		}
		return result;
	}
};
//Boyer Moore voting algorithm，可适用于找出大于 n/k 的元素
class Solution2 {
public:
	vector<int> majorityElement(vector<int>& nums) {
		int major1 = 0, major2 = 1, count1 = 0, count2 = 0;
		for (auto x : nums) {
			if (x == major1) count1++;
			else if (x == major2) count2++;
			else if (count1 == 0) major1 = x, count1 = 1;
			else if (count2 == 0) major2 = x, count2 = 1;
			else count1--, count2--;
		}
		count1 = count2 = 0;
		vector<int> result;
		for (auto x : nums) {
			if (x == major1) count1++;
			else if (x == major2) count2++;
		}
		if (count1 > nums.size() / 3) result.push_back(major1);
		if (count2 > nums.size() / 3) result.push_back(major2);
		return result;
	}
};
//int main(void)
//{
//	Solution2 test;
//	vector<int> nums{ 1, 1, 1, 4, 4, 4 };
//	vector<int> major = test.majorityElement(nums);
//	for (auto x : major)
//		cout << x << " ";
//	cout << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}