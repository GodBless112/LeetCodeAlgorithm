//	300. Longest Increasing Subsequence
//------------------------------------------------------------------------------//
//	Given an unsorted array of integers, find the length of longest increasing	//
//	subsequence.																//
//	For example,																//
//	Given[10, 9, 2, 5, 3, 7, 101, 18],											//
//	The longest increasing subsequence is[2, 3, 7, 101], therefore the length	//
//	is 4. Note that there may be more than one LIS combination, it is only		//
//	necessary for you to return the length.										//
//	Your algorithm should run in O(n2) complexity.								//
//	Follow up : Could you improve it to O(n log n) time complexity ?			//
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
//动态规划，用record[i]表示以i结束的最长升序子序列
//那么record[i]=max(record[i],record[j]+1)，对所有的j<i且nums[j]<nums[i]
class Solution {
public:
	int lengthOfLIS(vector<int>& nums) {
		int n = nums.size();
		if (n == 0) return 0;
		vector<int> record(n, 1);
		for (int i = 1; i < n; ++i)
			for (int j = 0; j < i; ++j)
				if (nums[j] < nums[i])
					record[i] = max(record[i], record[j] + 1);
		return *max_element(record.begin(), record.end());
	}
};

//二分搜索
class Solution2 {
public:
	int lengthOfLIS(vector<int>& nums) {
		if (nums.empty()) { return 0; }
		vector<int> tail;  // keep tail value of each possible len
		tail.push_back(nums[0]);
		for (auto n : nums) {
			if (n <= tail[0]) {
				tail[0] = n;
			}
			else if (n > tail.back()) { // large than the tail of current largest len 
				tail.push_back(n);
			}
			else {  // find smallest one which is >= n
				int left = 0;
				int right = tail.size() - 1;
				int res = left;
				while (left <= right) {
					int mid = left + (right - left) / 2;
					if (tail[mid] >= n) {
						res = mid;
						right = mid - 1;
					}
					else { // tail[mid] < n
						left = mid + 1;
					}
				}
				tail[res] = n;
			}
		}
		return tail.size();
	}
};
class Solution3 {
public:
	int lengthOfLIS(vector<int>& nums) {
		vector<int> res;
		for (int i = 0; i<nums.size(); i++) {
			auto it = std::lower_bound(res.begin(), res.end(), nums[i]);
			if (it == res.end()) res.push_back(nums[i]);
			else *it = nums[i];
		}
		return res.size();
	}
};
//int main(void)
//{
//	Solution3 test;
//	vector<int> nums{ 4,10,4,3,8,9 };
//	cout << test.lengthOfLIS(nums);
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