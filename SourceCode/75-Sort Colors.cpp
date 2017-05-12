//	75. Sort Colors
//------------------------------------------------------------------------------//
//	Given an array with n objects colored red, white or blue, sort them so that //
//	objects of the same color are adjacent, with the colors in the order red,	//
//	white and blue.																//
//	Here, we will use the integers 0, 1, and 2 to represent the color red, white//
//	, and blue respectively.													//
//	Note:																		//
//	You are not suppose to use the library's sort function for this problem.	//
//	Follow up :																	//
//	A rather straight forward solution is a two - pass algorithm using counting	//
//	sort.																		//
//	First, iterate the array counting number of 0's, 1's, and 2's, then			//
//	overwrite array with total number of 0's, then 1's and followed by 2's.		//
//	Could you come up with an one - pass algorithm using only constant space ?	//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<sstream>
#include<algorithm>
#include<functional>
// constants
// function prototype
using namespace std;
//计数排序，但需要走两趟，不满足一趟排序的要求
class Solution 
{
public:
	void sortColors(vector<int>& nums) 
	{
		int colorCount[3] = { 0 };
		for (size_t i = 0; i < nums.size(); ++i)
			colorCount[nums[i]]++;
		int index = 0;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < colorCount[i]; j++)
				nums[index++] = i;
	}
};
//三指针，https://discuss.leetcode.com/topic/36832/sharing-c-solution-with-good-explanation/2
//思想是，把0放到最前面，2放到最后面，利用三个指针指向0,1,2的分界
class Solution2 {
public:
	void sortColors(vector<int>& nums)
	{
		int tmp = 0, low = 0, mid = 0, high = nums.size() - 1;

		while (mid <= high)
		{
			if (nums[mid] == 0)
			{
				tmp = nums[low];
				nums[low] = nums[mid];
				nums[mid] = tmp;
				low++;
				mid++;
			}
			else if (nums[mid] == 1)
			{
				mid++;
			}
			else if (nums[mid] == 2)
			{
				tmp = nums[high];
				nums[high] = nums[mid];
				nums[mid] = tmp;
				high--;
			}
		}
	}
};
//思想同2
class Solution3 {
public:
	void sortColors(vector<int>& A) {
		int red = 0, blue = A.size() - 1;
		for (int i = 0; i < blue + 1;) {
			if (A[i] == 0)
				swap(A[i++], A[red++]);
			else if (A[i] == 2)
				swap(A[i], A[blue--]);
			else
				i++;
		}
	}
};
//类似于快速排序，划分算法，利用STL::partition，划分成两组，返回第二组不满足的第一个元素
class Solution4 {
public:
	void sortColors(vector<int>& nums) {
		partition(partition(nums.begin(), nums.end(), bind1st(equal_to<int>(), 0)),
			nums.end(), bind1st(equal_to<int>(), 1));
	}
};
//自己实现的partition
class Solution5 {
public:
	void sortColors(vector<int>& nums) {
		partition(partition(nums.begin(), nums.end(), bind1st(equal_to<int>(), 0)),
			nums.end(), bind1st(equal_to<int>(), 1));
	}
private:
	template<typename ForwardIterator, typename UnaryPredicate>
	ForwardIterator partition(ForwardIterator first, ForwardIterator last,
		UnaryPredicate pred) {
		auto pos = first;
		for (; first != last; ++first)
			if (pred(*first))
				swap(*first, *pos++);
		return pos;
	}
};
//int main(void)
//{
//	Solution5 test;
//	vector<int> a = { 1,2,0,1,1,2,2,0,0 };
//	test.sortColors(a);
//	for_each(a.begin(), a.end(), [](int x) {
//		cout << x << " ";
//	});
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
