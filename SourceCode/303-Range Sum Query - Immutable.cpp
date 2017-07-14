//	303. Range Sum Query - Immutable
//------------------------------------------------------------------------------//
//	Given an integer array nums, find the sum of the elements between indices i //
//	and j (i ≤ j), inclusive.													//
//	Example:																	//
//	Given nums = [-2, 0, 3, -5, 2, -1]											//
//	sumRange(0, 2) -> 1															//
//	sumRange(2, 5) -> - 1														//
//	sumRange(0, 5) -> - 3														//
//	Note :																		//
//		1.You may assume that the array does not change.						//
//		2.There are many calls to sumRange function.							//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<unordered_map>
// constants
// function prototype
using namespace std;
class NumArray {
public:
	NumArray(vector<int> nums) :range(nums.size() + 1) {
		for (int i = 1; i <= nums.size(); ++i)
			range[i] = range[i - 1] + nums[i - 1];
	}

	int sumRange(int i, int j) {
		return range[j + 1] - range[i];
	}
private:
	vector<int> range;
};
//缓存所有值
class NumArray2 {
public:
	NumArray2(vector<int> nums) :range(nums.size(), vector<int>(nums.size())) {
		for (int i = 0; i < nums.size(); ++i) {
			int sum = 0;
			for (int j = i; j < nums.size(); ++j) {
				sum += nums[j];
				range[i][j] = sum;
			}
		}
	}

	int sumRange(int i, int j) {
		return range[i][j];
	}
private:
	vector<vector<int>> range;
};

//STL求部分和方法
class NumArray3 {
public:
	NumArray3(vector<int> &nums) : psum(nums.size() + 1, 0) {
		partial_sum(nums.begin(), nums.end(), psum.begin() + 1);
	}

	int sumRange(int i, int j) {
		return psum[j + 1] - psum[i];
	}
private:
	vector<int> psum;
};
//方案1的变形，初始点不是0
class NumArray4 {
public:
	NumArray4(vector<int> nums) {
		int sum = 0;
		for (int i = 0; i<nums.size(); i++)
		{
			sum += nums[i];
			data.push_back(sum);
		}
	}

	int sumRange(int i, int j) {
		if (i == 0)
			return data[j];
		else
			return data[j] - data[i - 1];
	}
private:
	vector<int> data;
};
/**
* Your NumArray object will be instantiated and called as such:
* NumArray obj = new NumArray(nums);
* int param_1 = obj.sumRange(i,j);
*/
//int main(void)
//{
//	vector<int> nums{ -2, 0, 3, -5, 2, -1 };
//	NumArray2 test(nums);
//	for (int i = 0; i < nums.size(); ++i)
//		for (int j = i; j < nums.size(); ++j)
//			cout << test.sumRange(i, j) << " ";
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