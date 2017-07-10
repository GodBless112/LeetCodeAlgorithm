//	220. Contains Duplicate III
//------------------------------------------------------------------------------//
//	Given an array of integers, find out whether there are two distinct indices //
//	i and j in the array such that the absolute difference between nums[i] and	//
//	nums[j] is at most t and the absolute difference between i and j is at most //
//	k.																			//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<set>
#include<map>
#include<unordered_map>
// constants
// function prototype
using namespace std;
//利用set的排序性，维持k个窗，利用lower_bound寻找边界|x-nums[i]|<=t,-t<=x-nums[i]<=t
//只要找到x>=nums[i]-t的下界即可
class Solution {
public:
	bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
		set<long long> dict;
		if (k <= 0 || t < 0) return false;
		for (int i = 0; i < nums.size(); ++i) {
			if (i > k) dict.erase(nums[i - k - 1]);
			auto pos = dict.lower_bound((long long)nums[i] - t);
			if (pos != dict.end() && (long long)*pos - nums[i] <= t)
				return true;
			dict.insert(nums[i]);
		}
		return false;
	}
};
//map
class Solution2 {
public:
	bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
		map<long long, int> M;
		int l = 0;
		for (int r = 0; r<nums.size(); r++) {
			if (r - l>k && M[nums[l]] == l)
				M.erase(nums[l++]);
			auto it = M.lower_bound((long long)nums[r] - t);
			if (it != M.end() && abs((long long)it->first - nums[r]) <= t)
				return true;
			M[nums[r]] = r;
		}
		return false;
	}
};
//桶排序
class Solution3 {
	long long getBucketId(long long i, long long w) {
		return i < 0 ? (i + 1) / w - 1 : i / w;
	}
public:
	bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
		int n = nums.size();
		if (n < 2 || k < 1 || t < 0)
		{
			return false;
		}

		unordered_map<long long, long long> buckets;
		long long width = (long long)t + 1;
		for (int i = 0; i < n; i++)
		{
			long long id = getBucketId(nums[i], width);

			// found the value in the same bucket
			if (buckets.find(id) != buckets.end())
			{
				return true;
			}

			// found the value in the adjacent bucket
			if ((buckets.find(id - 1) != buckets.end() && nums[i] - buckets[id - 1] < width) ||
				(buckets.find(id + 1) != buckets.end() && buckets[id + 1] - nums[i] < width))
			{
				return true;
			}

			// insert current value to buckets
			buckets[id] = nums[i];

			if (i >= k)    // remove out of range element
			{
				buckets.erase(getBucketId(nums[i - k], width));
			}
		}

		return false;
	}
};
//int main(void)
//{
//	Solution test;
//	vector<int> nums{ INT_MIN,-2147483647 };
//	cout << boolalpha << test.containsNearbyAlmostDuplicate(nums, 3, 3);
//	cout << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}