//	349. Intersection of Two Arrays
//------------------------------------------------------------------------------//
//	Given two arrays, write a function to compute their intersection.			//
//	Example:																	//
//	Given nums1 = [1, 2, 2, 1], nums2 = [2, 2], return[2].						//
//	Note :																		//
//	1.Each element in the result must be unique.								//
//	2.The result can be in any order.											//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<unordered_set>
// constants
// function prototype
using namespace std;
//先排序，然后合并求交集
class Solution {
public:
	vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
		vector<int> result;
		sort(nums1.begin(), nums1.end());
		sort(nums2.begin(), nums2.end());
		int n1 = nums1.size(), n2 = nums2.size();
		int i = 0, j = 0;
		while (i < n1 && j < n2) {
			while (i < n1 - 1 && nums1[i] == nums1[i + 1]) i++;
			while (j < n2 - 1 && nums2[j] == nums2[j + 1]) j++;
			if (nums1[i] == nums2[j]) {
				result.push_back(nums1[i]);
				i++; j++;
			}
			else if (nums1[i] > nums2[j])
				j++;
			else
				i++;	
		}
		return result;
	}
};
//利用一个set来排除不同的
class Solution2 {
public:
	vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
		unordered_set<int> m(nums1.begin(), nums1.end());
		vector<int> res;
		for (auto a : nums2)
			if (m.count(a)) {
				res.push_back(a);
				m.erase(a);
			}
		return res;
	}
};
//int main(void)
//{
//	Solution2 test;
//	vector<int> nums1{ 1,2,2,1 };
//	vector<int> nums2{ 2,1,2 };
//	vector<int> res = test.intersection(nums1, nums2);
//	for (auto x : res)
//		cout << x << " ";
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