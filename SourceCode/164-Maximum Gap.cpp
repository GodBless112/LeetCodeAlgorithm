//	164. Maximum Gap
//------------------------------------------------------------------------------//
//	Given an unsorted array, find the maximum difference between the successive //
//	elements in its sorted form.												//
//	Try to solve it in linear time / space.										//
//	Return 0 if the array contains less than 2 elements.						//
//	You may assume all elements in the array are non - negative integers and fit//
//	in the 32 - bit signed integer range.										//
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
//先STL排序再搜索一遍，不满足线性时间空间的条件
//时间复杂度O(log2n)，空间复杂度：不需额外空间
class Solution {
public:
	int maximumGap(vector<int>& nums) {
		if (nums.empty() || nums.size() < 2)            // check if array is empty or small sized
			return 0;
		sort(nums.begin(), nums.end());
		int result = 0;
		for (int i = 1; i < nums.size(); ++i) {
			result = max(nums[i] - nums[i - 1], result);
		}
		return result;
	}
};
//基数排序，时间复杂度O(d⋅(n+k))≈O(n)，空间复杂度O(n+k)≈O(n)
class Solution2 {
public:
	int maximumGap(vector<int>& nums) {
		if (nums.empty() || nums.size() < 2)           // check if array is empty or small sized
			return 0;
		int maxVal = *max_element(nums.begin(), nums.end());
		int exp = 1;                                 // 1, 10, 100, 1000 ...
		int radix = 10;                              // base 10 system
		vector<int> aux(nums.size());
		/* LSD Radix Sort */
		while (maxVal / exp > 0) {
			vector<int> count(radix, 0);

			for (int i = 0; i < nums.size(); i++)    // Counting sort
				count[(nums[i] / exp) % 10]++;

			for (int i = 1; i < count.size(); i++)   // you could also use partial_sum()
				count[i] += count[i - 1];

			for (int i = nums.size() - 1; i >= 0; i--)
				aux[--count[(nums[i] / exp) % 10]] = nums[i];

			for (int i = 0; i < nums.size(); i++)
				nums[i] = aux[i];

			exp *= 10;
		}
		int result = 0;

		for (int i = 0; i < nums.size() - 1; i++)
			result = max(nums[i + 1] - nums[i], result);


		return result;
	}
};
//桶排序，Buckets and The Pigeonhole Principle
class Solution3 {
public:
	class Bucket {
	public:
		bool used = false;
		int minval = numeric_limits<int>::max();        // same as INT_MAX
		int maxval = numeric_limits<int>::min();        // same as INT_MIN
	};

	int maximumGap(vector<int>& nums)
	{
		if (nums.empty() || nums.size() < 2)
			return 0;

		int mini = *min_element(nums.begin(), nums.end()),
			maxi = *max_element(nums.begin(), nums.end());

		int bucketSize = max(1, (maxi - mini) / ((int)nums.size() - 1));        // bucket size or capacity
		int bucketNum = (maxi - mini) / bucketSize + 1;                         // number of buckets
		vector<Bucket> buckets(bucketNum);

		for (auto&& num : nums) {
			int bucketIdx = (num - mini) / bucketSize;                          // locating correct bucket
			buckets[bucketIdx].used = true;
			buckets[bucketIdx].minval = min(num, buckets[bucketIdx].minval);
			buckets[bucketIdx].maxval = max(num, buckets[bucketIdx].maxval);
		}

		int prevBucketMax = mini, maxGap = 0;
		for (auto&& bucket : buckets) {
			if (!bucket.used)
				continue;

			maxGap = max(maxGap, bucket.minval - prevBucketMax);
			prevBucketMax = bucket.maxval;
		}

		return maxGap;
	}
};
//int main(void)
//{
//	Solution2 test;
//	vector<int> nums{ 1, 2, 13, 1 };
//	cout << test.maximumGap(nums);
//	cout << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//	
//	return 0;
//}