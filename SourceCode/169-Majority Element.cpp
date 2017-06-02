//	169. Majority Element
//------------------------------------------------------------------------------//
//	Given an array of size n, find the majority element. The majority element	//
//	is the element that appears more than ⌊ n/2 ⌋ times.						//
//	You may assume that the array is non - empty and the majority element always//
//	exist in the array. 														//
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

//哈希表的方法，时间空间都是O(n)
class Solution {
public:
	int majorityElement(vector<int>& nums) {
		unordered_map<int, int> map;
		int size = nums.size();
		for (int i = 0; i < size; ++i) {
			map[nums[i]]++;
			if (map[nums[i]] > size / 2) return nums[i];
		}
	}
};
//排序后找中间元素，时间复杂度O(nlogn)
class Solution2 {
public:
	int majorityElement(vector<int>& nums) {
		sort(nums.begin(), nums.end());
		return nums[nums.size() / 2];
	}
};
//Moore voting algorithm,O(n)time,O(1)space
//每次都找出一对不同的元素，从数组中删掉，直到数组为空或只有一种元素。 
//不难证明，如果存在元素e出现频率超过半数，那么数组中最后剩下的就只有e。
class Solution3 {
public:
	int majorityElement(vector<int>& nums) {
		int major = nums[0], count = 1;
		for (int i = 1; i < nums.size(); ++i) {
			if (count == 0) {
				major = nums[i];
				count = 1;
			}
			else if (nums[i] == major)
				count++;
			else
				count--;
		}
		return major;
	}
};
//随机化的算法，随机选取一个元素，看是否个数大于一半
class Solution4 {
public:
	int majorityElement(vector<int>& nums) {
		int n = nums.size();
		srand(unsigned(time(NULL)));
		while (true) {
			int idx = rand() % n;
			int candidate = nums[idx];
			int counts = 0;
			for (int i = 0; i < n; i++)
				if (nums[i] == candidate)
					counts++;
			if (counts > n / 2) return candidate;
		}
	}
};
//分而治之的算法
class Solution5 {
public:
    int majorityElement(vector<int>& nums) {
        return majority(nums, 0, nums.size() - 1);
    }
private:
    int majority(vector<int>& nums, int left, int right) {
        if (left == right) return nums[left];
        int mid = left + ((right - left) >> 1);
        int lm = majority(nums, left, mid);
        int rm = majority(nums, mid + 1, right);
        if (lm == rm) return lm;
		return count(nums.begin() + left, nums.begin() + right + 1, lm)
		> count(nums.begin() + left, nums.begin() + right + 1, rm) ? lm : rm;
    }
};
//位运算的方法1
//计算特定一位上1出现的次数
//利用一个mask来表示第i位上为1，其余为为0的标志
class Solution6 {
public:
	int majorityElement(vector<int>& nums) {
		int major = 0, n = nums.size();
		for (int i = 0, mask = 1; i < 32; i++, mask <<= 1) {
			int bitCounts = 0;
			for (int j = 0; j < n; j++) {
				if (nums[j] & mask) bitCounts++;
				if (bitCounts > n / 2) {
					major |= mask;
					break;
				}
			}
		}
		return major;
	}
};
//位运算方法2，利用一个数组存
class Solution7 {
public:
	int majorityElement(vector<int>& nums) {
		int major = 0, n = nums.size();
		vector<int> bit(32);
		for (int num : nums)
			for (int i = 0; i < 32; i++)
				if ((num >> (31 - i) & 1) == 1)
					bit[i]++;
		for (int i = 0; i<32; i++) {
			bit[i] = bit[i] > n / 2 ? 1 : 0;
			major += bit[i] * (1 << (31 - i));
		}
		return major;
	}
};
//int main(void)
//{
//	Solution7 test;
//	vector<int> nums{ -1,-1,-1,2,2,2,2,-1,-1 };
//	cout << test.majorityElement(nums);
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