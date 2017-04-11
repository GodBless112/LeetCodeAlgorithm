//	27. Remove Element
//------------------------------------------------------------------------------//
//	Given an array and a value, remove all instances of that value in place and //
//	return the new length. Do not allocate extra space for another array, you	//
//	must do this in place with constant memory. The order of elements can be	//
//	changed.It doesn't matter what you leave beyond the new length.				//
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
//双指针，O(n)，从前往后，依次交换
class Solution 
{
public:
	int removeElement(vector<int>& nums, int val) 
	{
		if (nums.empty())
			return 0;
		int index = 0;
		for (int i = 0; i < nums.size(); i++)
		{
			if (nums[i] != val)
				nums[index++] = nums[i];
		}
		return index;
	}
};
//遇到匹配的，让它与最后一个元素交换
class Solution2
{
public:
	int removeElement(vector<int>& nums, int val)
	{
		if (nums.empty())
			return 0;
		int n = nums.size();
		int i = 0;
		while (i < n)
		{
			if (nums[i] == val)
			{
				nums[i] = nums[n - 1];
				n--;
			}
			else
				i++;
		}
		return i;
	}
};
//STL remove方法
class Solution3 
{
public:
	int removeElement(vector<int>& nums, int val)
	{
		return distance(nums.begin(), remove(nums.begin(), nums.end(), val));
	}
};
//int main(void)
//{
//	Solution2 test;
//	vector<int> a({ 3,1,1,2,2,4,4 });
//	cout << test.removeElement(a,1) << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}
