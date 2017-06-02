//	189. Rotate Array
//------------------------------------------------------------------------------//
//	Rotate an array of n elements to the right by k steps.						//
//	For example, with n = 7 and k = 3, the array[1, 2, 3, 4, 5, 6, 7] is rotated//
//	to[5, 6, 7, 1, 2, 3, 4].													//
//	Note:																		//
//	Try to come up as many solutions as you can, there are at least 3 different	//
//	ways to solve this problem.													//
//	Hint :																		//
//	Could you do it in - place with O(1) extra space ?							//
//	Related problem : Reverse Words in a String II 								//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<unordered_map>
#include<ctime>
// constants
// function prototype
using namespace std;
//利用一个中间数组缓存旋转点之后的值
class Solution {
public:
	void rotate(vector<int>& nums, int k) {
		k = k%nums.size();
		int m = nums.size() - k;
		vector<int> temp(nums.begin() + m, nums.end());
		for (int i = nums.size() - 1; i >= k; --i)
			nums[i] = nums[i - k];
		for (int i = 0; i < k; ++i)
			nums[i] = temp[i];
	}
};
//用一个中间数组缓存整个数组，时间复杂度O(n)，空间复杂度的O(n)
class Solution2 {
public:
	void rotate(vector<int>& nums, int k) {
		if (nums.empty() || k < 0) return;
		vector<int> temp(nums.begin(), nums.end());
		for (int i = 0; i < nums.size(); ++i)
			nums[(i + k) % nums.size()] = temp[i];
	}
};
//用循环移置的方法,时间复杂度O(n)，空间复杂度的O(1)
class Solution3 {
public:
	void rotate(vector<int>& nums, int k) {
		k = k % nums.size();
		int count = 0;
		for (int start = 0; count < nums.size(); start++) {
			int current = start;
			int prev = nums[start];
			do {
				int next = (current + k) % nums.size();
				int temp = nums[next];
				nums[next] = prev;
				prev = temp;
				current = next;
				count++;
			} while (current != start);
		}
	}
};
int main(void)
{
	Solution3 test;
	vector<int> nums{ 1,2,3,4,5 };
	test.rotate(nums, 4);
	for_each(nums.begin(), nums.end(), [](int x) {cout << x << " "; });
	cout << endl;
	cout << atoi("0x01") << endl;
	// code to keep window open for MSVC++
	cin.clear();
	while (cin.get() != '\n')
		continue;
	cin.get();
	
	return 0;
}