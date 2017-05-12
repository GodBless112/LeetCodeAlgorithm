//	80. Remove Duplicates from Sorted Array II
//------------------------------------------------------------------------------//
//	Follow up for "Remove Duplicates":											//
//	What if duplicates are allowed at most twice ?								//
//	For example,																//
//	Given sorted array nums = [1, 1, 1, 2, 2, 3],								//
//	Your function should return length = 5, with the first five elements of		//
//	nums being 1, 1, 2, 2 and 3. It doesn't matter what you leave beyond the	//
//	new length.																	//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
// constants
// function prototype
using namespace std;
//加入一个count，记录出现的次数
class Solution 
{
public:
	int removeDuplicates(vector<int>& nums) 
	{
		const int n = nums.size();
		if (n < 3)
			return n;
		int index = 1;
		int count = 1;
		for (int i = 1; i < n; i++)
			if (nums[i] != nums[index - 1]) {
				nums[index++] = nums[i];
				count = 1;
			}	
			else {
				if (count == 1) {
					nums[index++] = nums[i];
					count++;
				}
			}
		return index;
	}
};
//间隔变成2，每次比较间隔为2的两个数
class Solution2 {
public:
	int removeDuplicates(vector<int>& nums) {
		if (nums.size() <= 2) return nums.size();
		int index = 2;
		for (int i = 2; i < nums.size(); i++) {
			if (nums[i] != nums[index - 2])
				nums[index++] = nums[i];
		}
		return index;
	}
};
class Solution3 {
public:
	int removeDuplicates(vector<int>& nums) {
		const int n = nums.size();
		int index = 0;
		for (int i = 0; i < n; ++i) {
			if (i > 0 && i < n - 1 && nums[i] == nums[i - 1] && nums[i] == nums[i + 1])
				continue;
			nums[index++] = nums[i];
		}
		return index;
	}
};
//int main(void)
//{
//	Solution test;
//	vector<int> nums{ 1,1,1,2,2,3 };
//	cout << test.removeDuplicates(nums) << endl;
//	for_each(nums.begin(), nums.begin() + test.removeDuplicates(nums), [](int a) {
//		cout << a << " ";
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
