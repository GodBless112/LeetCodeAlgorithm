//	88. Merge Sorted Array
//------------------------------------------------------------------------------//
//	Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as	//
//	one sorted array.															//
//	Note:																		//
//	You may assume that nums1 has enough space(size that is greater or equal to //
//	m + n) to hold additional elements from nums2.The number of elements		//
//	initialized in nums1 and nums2 are m and n respectively.					//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<functional>
// constants
// function prototype
using namespace std;
//双指针，从后往前
class Solution 
{
public:
	void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) 
	{
		int ia = m - 1, ib = n - 1, icur = m + n - 1;
		while (ia >= 0 && ib >= 0)
			nums1[icur--] = (nums1[ia] >= nums2[ib]) ? nums1[ia--] : nums2[ib--];
		while (ib >= 0)
			nums1[icur--] = nums2[ib--];
	}
};
//int main(void)
//{
//	Solution test;
//	vector<int > a = { 1,0,0 };
//	vector<int> b = { 1,2 };
//	test.merge(a,1, b, 2);
//	for (auto x : a)
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
