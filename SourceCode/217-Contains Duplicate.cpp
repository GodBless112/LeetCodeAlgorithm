//	217. Contains Duplicate
//------------------------------------------------------------------------------//
//	Given an array of integers, find if the array contains any duplicates. Your //
//	function should return true if any value appears at least twice in the		//
//	array, and it should return false if every element is distinct.				//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<set>
#include<unordered_set>
// constants
// function prototype
using namespace std;
//利用hash表
class Solution {
public:
	bool containsDuplicate(vector<int>& nums) {
		unordered_set<int> dict;
		for (int i = 0; i < nums.size(); ++i) {
			if (dict.find(nums[i]) != dict.end())
				return true;
			dict.insert(nums[i]);
		}
		return false;
	}
};
//利用set
class Solution2 {
public:
	bool containsDuplicate(vector<int>& nums) {
		return set<int>(nums.begin(), nums.end()).size() < nums.size();
	}
};
//排序
class Solution3 {
public:
	bool containsDuplicate(vector<int>& nums) {
		if (nums.empty()) return false;
		sort(nums.begin(), nums.end());
		for (int i = 0; i < nums.size() - 1; ++i)
			if (nums[i] == nums[i + 1])
				return true;
		return false;
	}
};
//int main(void)
//{
//	Solution3 test;
//	vector<int> nums{ 1,3,5,7 };
//	cout << boolalpha << test.containsDuplicate(nums);
//	cout << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}