//11. Container With Most Water
#include <iostream>
#include<vector>
#include<string>
#include<cctype>
#include<algorithm>
// constants
// function prototype
using namespace std;
//����������٣�O(n2),�ᳬʱ
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
//O(n)�������߿�ʼ���أ��̰�ЧӦ����ͬ����һ����ӵ�����£�����ԽԶ���Խ�����д����߿�ʼ��
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
//O(n)������2�Ľ�һ���Ż�
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
