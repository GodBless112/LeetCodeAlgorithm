//	167. Two Sum II - Input array is sorted
//------------------------------------------------------------------------------//
//	Given an array of integers that is already sorted in ascending order, find	//
//	two numbers such that they add up to a specific target number.				//
//	The function twoSum should return indices of the two numbers such that they //
//	add up to the target, where index1 must be less than index2.Please note		//
//	that your returned answers(both index1 and index2) are not zero - based.	//
//	You may assume that each input would have exactly one solution and you may	//
//	not use the same element twice.												//
//	Input: numbers = { 2, 7, 11, 15 }, target = 9								//
//	Output : index1 = 1, index2 = 2												//
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

//双指针，左右夹逼法
class Solution {
public:
	vector<int> twoSum(vector<int>& numbers, int target) {
		int n = numbers.size();
		int i = 0, j = n - 1;
		while (i < j) {
			int gap = target - numbers[i];
			if (gap == numbers[j])
				return{ i + 1,j + 1 };
			else if (gap > numbers[j])
				i++;
			else
				j--;
		}
	}
};
//哈希表
class Solution2 {
public:
	vector<int> twoSum1(vector<int>& numbers, int target) {
		unordered_map<int, int> myMap;
		for (int i = 0; i < numbers.size(); i++) {
			if (myMap.find(target - numbers[i]) != myMap.end())
				return{ myMap[target - numbers[i]] + 1, i + 1 };
			myMap[numbers[i]] = i;
		}
	}
};
//二分搜索
class Solution3 {
public:
	vector<int> twoSum(vector<int>& numbers, int target) {
		for (int i = 0; i < numbers.size() - 1; i++) {
			int index = binarySearch(numbers, i + 1, numbers.size() - 1, target - numbers[i]);
			if (index != -1) return{ i + 1, index + 1 };
		}
	}

	int binarySearch(vector<int>& numbers, int begin, int end, int des) {
		int l = begin, r = end;
		while (l <= r) {
			int mid = (l + r) / 2;
			if (des == numbers[mid]) return mid;
			if (des < numbers[mid]) {
				r = mid - 1;
			}
			else {
				l = mid + 1;
			}
		}
		return -1;
	}
};
//int main(void)
//{
//	Solution3 test;
//	vector<int> numbers{ 2, 7, 11, 15 };
//	auto res = test.twoSum(numbers, 9);
//	cout << res[0] << " " << res[1] << endl;
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