//	219. Contains Duplicate II
//------------------------------------------------------------------------------//
//	Given an array of integers and an integer k, find out whether there are two //
//	distinct indices i and j in the array such that nums[i] = nums[j] and the	//
//	absolute difference between i and j is at most k.							//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<set>
#include<unordered_map>
#include<unordered_set>
// constants
// function prototype
using namespace std;
//利用hashmap
class Solution {
public:
	bool containsNearbyDuplicate(vector<int>& nums, int k) {
		unordered_map<int, int> dict;
		for (int i = 0; i < nums.size(); ++i) {
			if (dict.find(nums[i]) != dict.end()		//如果出现过该元素并且距离小于k则返回true
				&& abs(dict[nums[i]] - i) <= k)
				return true;
			dict[nums[i]] = i;		//距离超过了或者没有这个元素都更新其位置
		}
		return false;
	}
};
//利用set，维持k个大小的set
class Solution2 {
public:
	bool containsNearbyDuplicate(vector<int>& nums, int k) {
		unordered_set<int> dict;
		if (k <= 0) return false;
		if (k >= nums.size()) k = nums.size() - 1;
		for (int i = 0; i < nums.size(); ++i) {
			if (i > k) dict.erase(nums[i - k - 1]);
			if (dict.find(nums[i]) != dict.end())
				return true;
			dict.insert(nums[i]);
		}
		return false;
	}
};
//类似于2，不过是利用set，维持k大小的set，如果插入失败时，则返回true
class Solution3 {
public:
	bool containsNearbyDuplicate(vector<int>& nums, int k) {
		set<int> cand;
		for (int i = 0; i < nums.size(); i++) {
			if (i > k) cand.erase(nums[i - k - 1]);
			if (!cand.insert(nums[i]).second) return true;
		}
		return false;
	}
};
//int main(void)
//{
//	Solution3 test;
//	vector<int> nums{ 1,3,5,7,1,1 };
//	cout << boolalpha << test.containsNearbyDuplicate(nums, 3);
//	cout << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}