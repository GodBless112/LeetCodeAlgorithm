//	228. Summary Ranges
//------------------------------------------------------------------------------//
//	Given a sorted integer array without duplicates, return the summary of its	//
//	ranges.																		//
//	For example, given[0, 1, 2, 4, 5, 7], return["0->2", "4->5", "7"].			//
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
class Solution {
public:
	vector<string> summaryRanges(vector<int>& nums) {
		vector<string> range;
		if (nums.size() == 0) return range;
		int start = 0, end = -1;
		for (int i = 0; i <= nums.size(); ++i) {
			if (i < nums.size() && nums[i] - nums[start] == i - start)
				end++;
			else {
				if (end > start) {
					string tmp = to_string(nums[start]) + "->" + to_string(nums[end]);
					range.push_back(tmp);
				}
				else {
					string tmp = to_string(nums[start]);
					range.push_back(tmp);
				}
				start = end = i;
			}
		}
		return range;
	}
};
//双指针，1的简化
class Solution2 {
public:
	vector<string> summaryRanges(vector<int>& nums) {
		const int size_n = nums.size();
		vector<string> res;
		if (0 == size_n) return res;
		for (int i = 0; i < size_n;) {
			int start = i, end = i;
			while (end + 1 < size_n && nums[end + 1] == nums[end] + 1) end++;
			if (end > start) res.push_back(to_string(nums[start]) + "->" + to_string(nums[end]));
			else res.push_back(to_string(nums[start]));
			i = end + 1;
		}
		return res;
	}
};
class Solution3 {
public:
	vector<string> summaryRanges(vector<int>& nums) {
		vector<string> ret;
		int s = 0;
		for (int i = 0; i < nums.size(); i++) {
			if (i + 1 == nums.size() || nums[i] + 1 != nums[i + 1]) {
				string tmp = to_string(nums[s]);
				if (i != s) tmp += "->" + to_string(nums[i]);
				ret.push_back(tmp);
				s = i + 1;
			}
		}

		return ret;
	}
};
//int main(void)
//{
//	Solution test;
//	vector<int> nums{ -1 };// { 0, 1, 2, 4, 5, 7 };
//	vector<string> range = test.summaryRanges(nums);
//	for (auto s : range)
//		cout << s << " ";
//	cout << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}