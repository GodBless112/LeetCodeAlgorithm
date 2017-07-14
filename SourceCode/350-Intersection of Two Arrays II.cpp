//	350. Intersection of Two Arrays II
//------------------------------------------------------------------------------//
//	Given two arrays, write a function to compute their intersection.			//
//	Example:																	//
//	Given nums1 = [1, 2, 2, 1], nums2 = [2, 2], return [2, 2]					//
//	Note :																		//
//	1.Each element in the result should appear as many times as it shows in		//
//	both arrays.																//
//	2.The result can be in any order.											//
//	Follow up:																	//
//	1.What if the given array is already sorted ? How would you optimize your	//
//	algorithm ?																	//
//	2.What if nums1's size is small compared to nums2's size ? Which algorithm	//
//	is better ?																	//
//	3.What if elements of nums2 are stored on disk, and the memory is limited	//
//	such that you cannot load all elements into the memory at once ?			//
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
//先排序，然后合并求交集，O(max(m, n) log(max(m, n))) Space: O(m + n)
class Solution {
public:
	vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
		vector<int> result;
		sort(nums1.begin(), nums1.end());
		sort(nums2.begin(), nums2.end());
		int n1 = nums1.size(), n2 = nums2.size();
		int i = 0, j = 0;
		while (i < n1 && j < n2) {
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
//利用一个map来记录，排除不同的，Time: O(m + n) Space: O(m + n)
class Solution2 {
public:
	vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
		unordered_map<int, int> m;
		for (auto x : nums1)
			m[x]++;
		vector<int> result;
		for (auto a : nums2)
			if (m[a] > 0) {
				result.push_back(a);
				m[a]--;
			}
		return result;
	}
};
//map的方法2，多一个find判断，避免不存在交集时的情况下多余的空间消耗，Time: O(m + n) Space: O(m)
class Solution3 {
public:
	vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
		unordered_map<int, int> dict;
		vector<int> res;
		for (int i = 0; i < (int)nums1.size(); i++) dict[nums1[i]]++;
		for (int i = 0; i < (int)nums2.size(); i++)
			if (dict.find(nums2[i]) != dict.end() && --dict[nums2[i]] >= 0) res.push_back(nums2[i]);
		return res;
	}
};
//int main(void)
//{
//	Solution3 test;
//	vector<int> nums1{ 1,2,2,2,1 };
//	vector<int> nums2{ 2,2 };
//	vector<int> res = test.intersect(nums1, nums2);
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