//	26. Remove Duplicates from Sorted Array
//------------------------------------------------------------------------------//
//	Given a sorted array, remove the duplicates in place such that each element	//
//	appear only once and return the new length.									//
//	Do not allocate extra space for another array, you must do this in place	//
//	with constant memory.														//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<cctype>
#include<algorithm>
#include<stack>
// constants
// function prototype
using namespace std;
//从前往后捋，如果遇到独特的记录下来，index++，O(n)时间，O(1)空间
class Solution 
{
public:
	int removeDuplicates(vector<int>& nums) 
	{
		const int n = nums.size();
		if (n < 2)
			return n;
		int index = 1;
		for (int i = 1; i < n; i++)
			if (nums[i] != nums[index - 1])
				nums[index++] = nums[i];
		return index;
	}
};
//STL方法
class Solution2
{
public:
	int removeDuplicates(vector<int>& nums)
	{
		return distance(nums.begin(), unique(nums.begin(), nums.end()));
	}
};
// STL方法,upper_bound
class Solution3
{
public:
	int removeDuplicates(vector<int>& nums)
	{
		return distance(nums.begin(), removeDuplicates(nums.begin(), nums.end(), nums.begin()));
	}
	template<typename InIt, typename OutIt>
	OutIt removeDuplicates(InIt first, InIt last, OutIt output)
	{
		while (first != last)
		{
			*output++ = *first;
			first = upper_bound(first, last, *first);
		}
		return output;
	}
};
//int main(void)
//{
//	Solution3 test;
//	vector<int> a({ 1,1,2,2 });
//	cout << test.removeDuplicates(a) << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}
