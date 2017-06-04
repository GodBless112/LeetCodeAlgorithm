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
//交换法，每次用后k个元素与前k个元素交换，然后更新n和k
class Solution4 {
public:
	void rotate(vector<int>& nums, int k) {
		int n = nums.size();
		auto start = nums.begin();
		for (; k = k % n; n -= k)
		{
			// Swap the last k elements with the first k elements. 
			// The last k elements will be in the correct positions
			// but we need to rotate the remaining (n - k) elements 
			// to the right by k steps.
			for (int i = 0; i < k; i++)
			{
				swap(*start, *(start + (n - k)));
				start++;
			}
		}
	}
};
//不断交换两个子数组
class Solution5 {
public:
	void rotate(vector<int>& nums, int k) {
		int n = nums.size();
		if ((n == 0) || (k <= 0) || (k%n == 0))
		{
			return;
		}

		k = k%n;
		// Rotation to the right by k steps is equivalent to swapping 
		// the two subarrays nums[0,...,n - k - 1] and nums[n - k,...,n - 1].
		int start = 0;
		int tmp = 0;
		while (k > 0)
		{
			if (n - k >= k)
			{
				// The left subarray with size n - k is longer than 
				// the right subarray with size k. Exchange 
				// nums[n - 2*k,...,n - k - 1] with nums[n - k,...,n - 1].
				for (int i = 0; i < k; i++)
				{
					tmp = nums[start + n - 2 * k + i];
					nums[start + n - 2 * k + i] = nums[start + n - k + i];
					nums[start + n - k + i] = tmp;
				}

				// nums[n - 2*k,...,n - k - 1] are in their correct positions now.
				// Need to rotate the elements of nums[0,...,n - k - 1] to the right 
				// by k%n steps.
				n = n - k;
				k = k%n;
			}
			else
			{
				// The left subarray with size n - k is shorter than 
				// the right subarray with size k. Exchange 
				// nums[0,...,n - k - 1] with nums[n - k,...,2*(n - k) - 1].
				for (int i = 0; i < n - k; i++)
				{
					tmp = nums[start + i];
					nums[start + i] = nums[start + n - k + i];
					nums[start + n - k + i] = tmp;
				}

				// nums[n - k,...,2*(n - k) - 1] are in their correct positions now.
				// Need to rotate the elements of nums[n - k,...,n - 1] to the right 
				// by k - (n - k) steps.
				tmp = n - k;
				n = k;
				k -= tmp;
				start += tmp;
			}
		}
	}
};
//int main(void)
//{
//	Solution5 test;
//	vector<int> nums{ 1,2,3,4,5 };
//	test.rotate(nums, 4);
//	for_each(nums.begin(), nums.end(), [](int x) {cout << x << " "; });
//	cout << endl;
//	cout << atoi("0x01") << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//	
//	return 0;
//}