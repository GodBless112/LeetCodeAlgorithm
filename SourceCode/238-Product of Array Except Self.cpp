//	238. Product of Array Except Self
//------------------------------------------------------------------------------//
//	Given an array of n integers where n > 1, nums, return an array output such //
//	that output[i] is equal to the product of all the elements of nums except	//
//	nums[i].																	//
//	Solve it without division and in O(n).										//
//	For example, given[1, 2, 3, 4], return[24, 12, 8, 6].						//
//	Follow up :																	//
//	Could you solve it with constant space complexity ? (Note : The output		//
//	array does not count as extra space for the purpose of space complexity		//
//	analysis.)																	//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<stack>

// constants
// function prototype
using namespace std;
//O(n)时间，O(n)空间的情况
class Solution {
public:
	vector<int> productExceptSelf(vector<int>& nums) {
		const int n = nums.size();
		vector<int> result(n);
		if (n == 0) return result;
		vector<int> FromBegin(n);
		vector<int> FromEnd(n);
		FromBegin[0] = FromEnd[0] = 1;
		for (int i = 1; i < n; ++i) {
			FromBegin[i] = FromBegin[i - 1] * nums[i - 1];
			FromEnd[i] = FromEnd[i - 1] * nums[n - i];
		}
		for (int i = 0; i < n; ++i)
			result[i] = FromBegin[i] * FromEnd[n - i - 1];
		return result;
	}
};
//O(n)时间，O(1)空间，由方案1变化得到，用两个整型代替数组
class Solution2 {
public:
	vector<int> productExceptSelf(vector<int>& nums) {
		const int n = nums.size();
		vector<int> result(n, 1);
		if (n == 0) return result;
		int FromBegin = 1, FromEnd = 1;
		for (int i = 0; i < n; ++i) {
			result[i] *= FromBegin;
			FromBegin *= nums[i];
			result[n - i - 1] *= FromEnd;
			FromEnd *= nums[n - i - 1];
		}
		return result;
	}
};
//int main(void)
//{
//	Solution2 test;
//	vector<int> nums{ 1,2,3,4 };
//	vector<int> output = test.productExceptSelf(nums);
//	for (auto x : nums)
//		cout << x << " ";
//	cout << endl;
//	for (auto x : output)
//		cout << x << " ";
//	cout << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}