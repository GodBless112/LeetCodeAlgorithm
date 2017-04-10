//	18. 4Sum
//------------------------------------------------------------------------------//
//	Given an array S of n integers, are there elements a, b, c, and d in S such //
//	that a + b + c + d = target? Find all unique quadruplets in the array which //
//	gives the sum of target.													//	 
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<cctype>
#include<algorithm>
#include<set>
#include<unordered_map>
// constants
// function prototype
using namespace std;
//先排序，然后左右夹逼，O(n3)
class Solution 
{
public:
	vector<vector<int>> fourSum(vector<int>& nums, int target) 
	{
		vector<vector<int>> result;
		if (nums.size() < 4)
			return result;
		sort(nums.begin(), nums.end());
		for (int i = 0; i < nums.size() - 3; i++)
		{
			for (int j = i + 1; j < nums.size() - 2; j++)
			{
				int k = j + 1;
				int l = nums.size() - 1;
				while (k < l)
				{
					int sum = nums[i] + nums[j] + nums[k] + nums[l];
					if (sum == target)
					{
						result.push_back({ nums[i],nums[j],nums[k],nums[l] });
						k++; l--;
						while (nums[k] == nums[k - 1]) k++;
						while (nums[l] == nums[l + 1]) l--;
					}
					else if (sum < target)
					{
						k++;
						while (k < l&&nums[k] == nums[k - 1])
							k++;
					}
					else
					{
						l--;
						while (k < l&&nums[l] == nums[l + 1])
							l--;
					}
				}
				while (j + 2 < nums.size() && nums[j] == nums[j + 1])
					j++;
			}
			while (i + 3 < nums.size() && nums[i] == nums[i + 1])
				i++;
		}
		return result;
	}
};
//仍然是左右夹逼法，采用STL方法，时间会慢于方法1
class Solution2 {
public:
	vector<vector<int>> fourSum(vector<int>& nums, int target) {
		vector<vector<int>> result;
		if (nums.size() < 4) return result;
		sort(nums.begin(), nums.end());
		auto last = nums.end();
		for (auto a = nums.begin(); a < prev(last, 3);
			a = upper_bound(a, prev(last, 3), *a)) {
			for (auto b = next(a); b < prev(last, 2);
				b = upper_bound(b, prev(last, 2), *b)) {
				auto c = next(b);
				auto d = prev(last);
				while (c < d) {
					if (*a + *b + *c + *d < target) {
						c = upper_bound(c, d, *c);
					}
					else if (*a + *b + *c + *d > target) {
						d = prev(lower_bound(c, d, *d));
					}
					else {
						result.push_back({ *a, *b, *c, *d });
						c = upper_bound(c, d, *c);
						d = prev(lower_bound(c, d, *d));
					}
				}
			}
		}
		return result;
	}
};
//方法3，利用hashmap做一个缓存，存放两个数的和的表,理论上是O(n3)
class Solution3
{
public:
	vector<vector<int>> fourSum(vector<int>& nums, int target)
	{
		vector<vector<int>> result;
		if (nums.size() < 4)
			return result;
		sort(nums.begin(), nums.end());
		unordered_map<int, vector<pair<int, int>>> cache;
		for (int i = 0; i < nums.size(); i++)
			for (int j = i + 1; j < nums.size(); j++)
				cache[nums[i] + nums[j]].push_back(make_pair(i, j));
		for (int k = 0; k < nums.size(); k++)
		{
			for (int l = k + 1; l < nums.size(); l++)
			{
				int key = target - nums[k] - nums[l];
				if (cache.find(key) == cache.end())
					continue;
				const auto &rec = cache[key];
				for (int m = 0; m < rec.size(); m++)
				{
					if (k <= rec[m].second)
						continue;
					result.push_back({ nums[rec[m].first],nums[rec[m].second],nums[k],nums[l] });
				}
			}
		}
		sort(result.begin(), result.end());
		result.erase(unique(result.begin(), result.end()), result.end());
		return result;
	}
};
//方法4，multimap
class Solution4
{
public:
	vector<vector<int>> fourSum(vector<int>& nums, int target)
	{
		vector<vector<int>> result;
		if (nums.size() < 4)
			return result;
		sort(nums.begin(), nums.end());
		unordered_multimap<int, pair<int, int>> cache;
		for (size_t i = 0; i < nums.size(); i++)
			for (size_t j = i + 1; j < nums.size(); j++)
				cache.insert(make_pair(nums[i] + nums[j], make_pair(i, j)));
		for (auto i = cache.begin(); i != cache.end(); i++)
		{
			int gap = target - i->first;
			auto range = cache.equal_range(gap);
			for (auto j = range.first; j != range.second; j++)
			{
				auto a = i->second.first;
				auto b = i->second.second;
				auto c = j->second.first;
				auto d = j->second.second;
				if (a != c&&a != d&&b != c&&b != d)
				{
					vector<int> rec({ nums[a],nums[b],nums[c],nums[d] });
					sort(rec.begin(), rec.end());
					result.push_back(rec);
				}
			}
		}
		sort(result.begin(), result.end());
		result.erase(unique(result.begin(), result.end()), result.end());
		return result;
	}
};
//int main(void)
//{
//	Solution4 test;
//	vector<int> a({ 1,1,1,1,2,2,2,2 });
//	auto x = test.fourSum(a, 4);
//	
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}
