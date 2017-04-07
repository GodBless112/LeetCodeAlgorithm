//11. Container With Most Water
#include <iostream>
#include<vector>
#include<string>
#include<cctype>
#include<algorithm>
// constants
// function prototype
using namespace std;
//暴力法，穷举，O(n2),会超时
class Solution {
public:
    int maxArea(vector<int>& height) 
	{
		int ret = 0;
		for (int i = 0; i < height.size(); i++)
		{
			for (int j = i; j < height.size(); j++)
			{
				int area = min(height[i], height[j])*(j - i);
				ret = (area > ret) ? area : ret;
			}
		}
		return ret;
    }
};
//O(n)，从两边开始搜素，短板效应决定同样有一块板子的情况下，距离越远面积越大，所有从两边开始搜
class Solution2 
{
public:
	int maxArea(vector<int>& height)
	{
		int start = 0;
		int end = height.size() - 1;
		int ret = 0;
		while (start < end)
		{
			int area = min(height[start], height[end])*(end - start);
			ret = max(ret, area);
			if (height[start] <= height[end])
				start++;
			else
				end--;
		}
		return ret;
	}
};
//O(n)，方法2的进一步优化
class Solution3
{
public:
	int maxArea(vector<int>& height)
	{
		int start = 0;
		int end = height.size() - 1;
		int ret = 0;
		while (start < end)
		{
			int h = min(height[start], height[end]);
			ret = max(ret, h*(end - start));
			while (start < end&&height[start] <= h)
				start++;
			while (start < end&&height[end] <= h)
				end--;
		}
		return ret;
	}
};
//int main(void)
//{
//	Solution3 test;
//	vector<int> a({ 1,1 });
//	cout << test.maxArea(a) << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}
