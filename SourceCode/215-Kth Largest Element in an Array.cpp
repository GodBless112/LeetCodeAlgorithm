//	215. Kth Largest Element in an Array
//------------------------------------------------------------------------------//
//	Find the kth largest element in an unsorted array. Note that it is the kth	//
//	largest element in the sorted order, not the kth distinct element.			//
//	For example,																//
//	Given[3, 2, 1, 5, 6, 4] and k = 2, return 5.								//
//	Note:																		//
//	You may assume k is always valid, 1 ≤ k ≤ array's length.					//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<queue>
#include<set>
#include<ctime>
#include<stdlib.h>
// constants
// function prototype
using namespace std;
//利用优先队列，即最大堆，先建立堆，然后弹出k-1个元素，O(N lg K) 时间 + O(K) 空间
class Solution {
public:
	int findKthLargest(vector<int>& nums, int k) {
		priority_queue<int> q(nums.begin(), nums.end());
		for (int i = 0; i < k - 1; ++i) {
			q.pop();
		}
		return q.top();
	}
};
//先排序，O(N lg N) 时间 + O(N) 空间
class Solution2 {
public:
	int findKthLargest(vector<int>& nums, int k) {
		sort(nums.begin(), nums.end());
		return nums[nums.size() - k];
	}
};
//利用最小堆，O(N lg K) 时间 + O(K) 空间
class Solution3 {
public:
	int findKthLargest(vector<int>& nums, int k) {
		priority_queue<int, vector<int>, greater<int>> q;
		for (int i = 0; i < nums.size(); ++i) {
			q.push(nums[i]);
			if (q.size() > k)
				q.pop();
		}
		return q.top();
	}
};
//类似于最小堆，可以用multiset，O(N lg K) 时间 + O(K) 空间
class Solution4 {
public:
	int findKthLargest(vector<int>& nums, int k) {
		multiset<int> mset;
		int n = nums.size();
		for (int i = 0; i < n; i++) {
			mset.insert(nums[i]);
			if (mset.size() > k)
				mset.erase(mset.begin());
		}
		return *mset.begin();
	}
};
//利用快速排序的划分算法，O(N)最好情况 / O(N^2) 最坏情况时间复杂度 + O(1) 空间
class Solution5 {
public:
	int findKthLargest(vector<int>& nums, int k) {
		int left = 0, right = nums.size() - 1;
		while (true) {
			int pos = partition(nums, left, right);
			if (pos == k - 1) return nums[pos];
			if (pos > k - 1) right = pos - 1;
			else left = pos + 1;
		}
	}
private:
	int partition(vector<int>& nums, int left, int right) {
		int pivot = nums[left];
		int low = left, high = right;
		while (low < high) {
			while (low < high && nums[high] < pivot)
				high--;
			nums[low] = nums[high];
			while (low < high && nums[low] >= pivot)
				low++;
			nums[high] = nums[low];
		}
		nums[low] = pivot;
		return low;
	}
};
//另一种划分写法
class Solution6 { 
public:
	int partition(vector<int>& nums, int left, int right) {
		int pivot = nums[left];
		int l = left + 1, r = right;
		while (l <= r) {
			if (nums[l] < pivot && nums[r] > pivot)
				swap(nums[l++], nums[r--]);
			if (nums[l] >= pivot) l++;
			if (nums[r] <= pivot) r--;
		}
		swap(nums[left], nums[r]);
		return r;
	}

	int findKthLargest(vector<int>& nums, int k) {
		int left = 0, right = nums.size() - 1;
		while (true) {
			int pos = partition(nums, left, right);
			if (pos == k - 1) return nums[pos];
			if (pos > k - 1) right = pos - 1;
			else left = pos + 1;
		}
	}
};
//改进的划分算法，随机化算法，平均O(N)时间，O(1)空间
class Solution7 {
public:
	int partition(vector<int>& nums, int left, int right) {
		int pivot = nums[left];
		int l = left + 1, r = right;
		while (l <= r) {
			if (nums[l] < pivot && nums[r] > pivot)
				swap(nums[l++], nums[r--]);
			if (nums[l] >= pivot) l++;
			if (nums[r] <= pivot) r--;
		}
		swap(nums[left], nums[r]);
		return r;
	}

	int findKthLargest(vector<int>& nums, int k) {
		shuffle(nums);
		int left = 0, right = nums.size() - 1;
		while (true) {
			int pos = partition(nums, left, right);
			if (pos == k - 1) return nums[pos];
			if (pos > k - 1) right = pos - 1;
			else left = pos + 1;
		}
	}
	void shuffle(vector<int>& nums) {
		srand(time(0));
		for (int ind = 1; ind < nums.size(); ind++) {
			int r = rand() % (ind + 1);
			swap(nums[ind], nums[r]);
		}
	}
};
//int main(void)
//{
//	Solution7 test;
//	vector<int> nums{ 3, 2, 1, 5, 6, 4 };
//	cout << test.findKthLargest(nums, 2);
//	cout << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}