//	14. Longest Common Prefix
#include <iostream>
#include<vector>
#include<string>
#include<cctype>
#include<algorithm>
// constants
// function prototype
using namespace std;
//从第一个字符开始，对每一个字符串比较，直至遇到不满足的结束
class Solution 
{
public:
	string longestCommonPrefix(vector<string>& strs) 
	{
		int i = 0, j;
		string ret = "";
		if (strs.empty())
			return ret;
		while (i < strs[0].size())
		{
			for (j = 1; j < strs.size(); j++)
			{
				if (strs[j][i]=='\0'||strs[j][i] != strs[j - 1][i])
					break;
			}
			if (j == strs.size())
				ret += strs[0].substr(i++, 1);
			else
				break;
		}
		return ret;
	}
};
class Solution2
{
public:
	string longestCommonPrefix(vector<string>& strs)
	{
		int i = 0, j = 1;
		if (strs.empty())
			return "";
		while (i < strs[0].size())
		{
			for (j = 1; j < strs.size(); j++)
			{
				if (strs[j][i] != strs[0][i])
					return strs[0].substr(0, i);
			}
			i++;
		}
		return strs[0];
	}
};
class Solution3 
{
public:
	string longestCommonPrefix(vector<string>& strs) 
	{
		string prefix = "";
		for (int idx = 0; strs.size()>0; prefix += strs[0][idx], idx++)
			for (int i = 0; i<strs.size(); i++)
				if (idx >= strs[i].size() || (i > 0 && strs[i][idx] != strs[i - 1][idx]))
					return prefix;
		return prefix;
	}
};
//int main(void)
//{
//	Solution2 test;
//	vector<string> a({});
//	cout << test.longestCommonPrefix(a) << endl;
//	
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}
