//	274. H-Index
//------------------------------------------------------------------------------//
//	Given an array of citations (each citation is a non-negative integer) of a	//
//	researcher, write a function to compute the researcher's h-index.			//
//	According to the definition of h - index on Wikipedia : "A scientist has	//
//	index h if h of his/her N papers have at least h citations each, and the	//
//	other N − h papers have no more than h citations each."						//
//	For example, given citations = [3, 0, 6, 1, 5], which means the researcher	//
//	has 5 papers in total and each of them had received 3, 0, 6, 1, 5 citations //
//	respectively.Since the researcher has 3 papers with at least 3 citations	//
//	each and the remaining two with no more than 3 citations each, his			//
//	h - index is 3.																//
//	Note : If there are several possible values for h, the maximum one is taken //
//	as the h - index.															//
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
//先排序，然后从后往前
class Solution {
public:
	int hIndex(vector<int>& citations) {
		sort(citations.begin(), citations.end());
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
//先排序，然后正向走
class Solution2 {
public:
	int hIndex(vector<int>& citations) {
		if (citations.empty())
			return 0;
		sort(citations.begin(), citations.end());
		int n = citations.size();
		int i = 0;
		while (i<n && citations[i]<(n - i)) i++;
		return n - i;
	}
};
//哈希表/bucket sort
class Solution3 {
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
//int main(void)
//{
//	Solution3 test;
//	vector<int> citations{ 100 };
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