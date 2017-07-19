//	275. H-Index II
//------------------------------------------------------------------------------//
//	Follow up for H-Index: What if the citations array is sorted in ascending	//
//	order? Could you optimize your algorithm?									//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<unordered_set>
#include<unordered_map>
// constants
// function prototype
using namespace std;
//从后往前
class Solution {
public:
	int hIndex(vector<int>& citations) {
		int n = citations.size();
		int h = 1;
		for (int i = n - 1; i >= 0; --i, ++h)
			if (citations[i] == h)
				return h;
			else if (citations[i] < h)
				return h - 1;
		return h - 1;
	}
};
//正向走，还可以优化
class Solution2 {
public:
	int hIndex(vector<int>& citations) {
		if (citations.empty())
			return 0;
		int n = citations.size();
		int i = 0;
		while (i<n && citations[i]<(n - i)) i++;
		return n - i;
	}
};
//针对1,2优化，二分搜索，找最小的index满足citations[i]>=n-index
class Solution3 {
public:
	int hIndex(vector<int>& citations) {
		int start = 0, len = citations.size(), end = len - 1;
		int mid;
		while (start <= end) {
			mid = start + (end - start) / 2;
			if (citations[mid] == len - mid) return len - mid;
			else if (citations[mid] > len - mid)
				end = mid - 1;
			else start = mid + 1;
		}
		return len - start;
	}
};

//哈希表/bucket sort,对于已经排序的不好
class Solution4 {
public:
	int hIndex(vector<int>& citations) {
		if (citations.empty())
			return 0;
		int n = citations.size();
		vector<int> hash(n + 1, 0);
		for (int i = 0; i < n; ++i) {
			if (citations[i] >= n)
				hash[n]++;
			else
				hash[citations[i]]++;
		}
		int paper = 0;
		for (int i = n; i >= 0; --i) {
			paper += hash[i];
			if (paper >= i)
				return i;
		}
	}
};
//不同形式的二分
class Solution5 {
public:
	int hIndex(vector<int>& citations) {
		int left = 0, len = citations.size(), right = len - 1, mid;
		while (left <= right)
		{
			mid = left + (right - left) / 2;
			if (citations[mid] >= (len - mid)) right = mid - 1;
			else left = mid + 1;
		}
		return len - left;
	}
};
class Solution6 {
public:
	int hIndex(vector<int>& citations) {
		int size = citations.size();

		int first = 0;
		int mid;
		int count = size;
		int step;

		while (count > 0) {
			step = count / 2;
			mid = first + step;
			if (citations[mid] < size - mid) {
				first = mid + 1;
				count -= (step + 1);
			}
			else {
				count = step;
			}
		}

		return size - first;
	}
};
//int main(void)
//{
//	Solution test;
//	vector<int> citations{ 0,1,3,5,6 };
//	cout << test.hIndex(citations);
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