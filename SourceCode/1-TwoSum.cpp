// static.cpp -- using a static local variable
#include <iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>
// constants
// function prototype
using namespace std;
class Solution 
{
public:
	vector<int> twoSum(vector<int>& nums, int target)
	{
		int min = nums[0], max = min;
		// first loop to find max and min integers
		for (int i = 0; i < nums.size(); i++)
		{
			if (nums[i] < min)
				min = nums[i];
			if (nums[i] > max)
				max = nums[i];
		}
		// valid range for input integers relative to target
		int sMin;
		int sMax;
		if (min < target - max)
			sMin = min;
		else
			sMin = target - max;

		if (max > target - min)
			sMax = max;
		else
			sMax = target - min;

		// array to keep indices of valid input integers
		// initialize with -1
		int size = 1 + sMax - sMin;
		int *arr;
		arr = new int[size];
		// for (int i = 0; i < arr.length;i++)
		//     arr[i] = -1;
		fill(arr, arr + size, -1);
		// second loop
		int offset = -sMin;
		for (int i = 0; i < nums.size(); i++)
		{
			// Skip if integer is not from a valid range
			if (nums[i] > sMax || nums[i] < sMin)
				continue;
			// if found valid X1 and corresponding element of indices array is still -1
			// then mark its pair X2 = target - X1 in indices array
			if (arr[nums[i] + offset] == -1)
				arr[target - nums[i] + offset] = i;
			else
			{
				//delete[] arr;
				return{ arr[nums[i] + offset],i };
			}		
		}
		//delete[] arr;
		return{ 0,0 };
	}
};
class Solution2
{
public:
	vector<int> TwoSum(vector<int> & num, int target)
	{
		vector<int> result;
		unordered_map<int, int> mapping;
		for (int i = 0; i < num.size(); i++)
			mapping[num[i]] = i;
		for (int i = 0; i < num.size(); i++)
		{
			const int temp = target - num[i];
			if (mapping.find(temp) != mapping.end() && mapping[temp] != i)
			{
				result.push_back(i);
				result.push_back(mapping[temp]);
				sort(result.begin(), result.end());
				break;
			}
		}
		return result;
	}
};
class Solution3
{
	struct node
	{
		int val;
		int index;
	};

public:
	static bool ComPare(const node & n1, const node & n2)
	{
		if (n1.val < n2.val)
			return true;
		else
			return false;
	}
	vector<int> TwoSum(vector<int> & num, int target)
	{
		vector<node> nodes(num.size());
		vector<int> result;
		for (int i = 0; i < num.size(); i++)
		{
			nodes[i].index = i;
			nodes[i].val = num[i];
		}
		sort(nodes.begin(), nodes.end(), ComPare);
		int i = 0, j = num.size() - 1;
		while (i < j)
		{
			int gap = target - nodes[i].val;
			if (nodes[j].val == gap)
			{
				result.push_back(nodes[i].index);
				result.push_back(nodes[j].index);
				break;
			}
			else if (nodes[j].val < gap)
				i++;
			else
				j--;
		}
		sort(result.begin(), result.end());
		return result;
	}
};
//int main(void)
//{
//	vector<int> nums = { 3, 2, 4, -3, 12, 0, 9, 7, 1, 4, 5 };
//	vector<int> result;
//	Solution a;
//	result = a.twoSum(nums,10);
//	int b=result.size();
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}
