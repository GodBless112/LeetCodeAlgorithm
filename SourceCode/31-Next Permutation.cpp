//	31. Next Permutation
//------------------------------------------------------------------------------//
//	Implement next permutation, which rearranges numbers into the				//
//	lexicographically next greater permutation of numbers.						//	
//	If such arrangement is not possible, it must rearrange it as the lowest		//
//	possible order(ie, sorted in ascending order).								//
//	The replacement must be in - place, do not allocate extra memory.			//
//	Here are some examples.Inputs are in the left - hand column and its			//
//	corresponding outputs are in the right - hand column.						//
//	1, 2, 3 → 1, 3, 2															//
//	3, 2, 1 → 1, 2, 3															//
//	1, 1, 5 → 1, 5, 1															//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<cctype>
#include<algorithm>
#include<stack>
#include<list>
#include<functional>
// constants
// function prototype
using namespace std;
//思想，寻找到第一个逆序对，将逆序对后面数中最小的且大于逆序对第一个元素的值想交换，后面的逆序
class Solution 
{
public:
	void nextPermutation(vector<int>& nums) 
	{
		int size = nums.size();
		if (size < 2)
			return;
		int i, j, k;
		for (i = size - 1; i > 0; i--)
		{
			if (nums[i - 1] < nums[i])
				break;
		}
		if (i == 0)
		{
			reverse(nums.begin() + i, nums.end());
			return;
		}
		for (j = i; j < size; j++)
		{
			if (nums[j] <= nums[i - 1])
			{
				break;
			}
		}
		swap(nums[i - 1], nums[j - 1]);
		reverse(nums.begin() + i, nums.end());
	}
};
//STL实现
class Solution2 {
public:
	void nextPermutation(vector<int> &nums) {
		next_permutation(nums.begin(), nums.end());
	}
	template<typename BidiIt>
	bool next_permutation(BidiIt first, BidiIt last) {
		// Get a reversed range to simplify reversed traversal.
		const auto rfirst = reverse_iterator<BidiIt>(last);
		const auto rlast = reverse_iterator<BidiIt>(first);
		// Begin from the second last element to the first element.
		auto pivot = next(rfirst);
		// Find `pivot`, which is the first element that is no less than its
		// successor. `Prev` is used since `pivort` is a `reversed_iterator`.
		while (pivot != rlast && *pivot >= *prev(pivot))
			++pivot;
		// No such elemenet found, current sequence is already the largest
		// permutation, then rearrange to the first permutation and return false.
		if (pivot == rlast) {
			reverse(rfirst, rlast);
			return false;
		}
		// Scan from right to left, find the first element that is greater than
		// `pivot`.
		auto change = find_if(rfirst, pivot, bind1st(less<int>(), *pivot));
		swap(*change, *pivot);
		reverse(rfirst, pivot);
		return true;
	}
};
//int main(void)
//{
//	Solution2 test;
//	vector<int> a({ 1,2,3 });
//	
//	while(1)
//		test.nextPermutation(a);
//
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}
