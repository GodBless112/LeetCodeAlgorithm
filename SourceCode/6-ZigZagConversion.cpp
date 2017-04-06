// ZigZag Convertion
//关键是找出规律，将Z型字符划分为多个块，包含竖直部分和斜对角部分，每个块一行有两个字符，第一行和最后一行没有
#include <iostream>
#include<vector>
#include<string>
// constants
// function prototype
using namespace std;
class Solution 
{
public:
	string convert(string s, int numRows) 
	{
		string result;
		if (s.size() <= 1 || numRows <= 1)
			return s;
		//i means row
		for (int i = 0; i < numRows; i++)
		{
			for (int j = 0, index = i; index < s.size(); j++, index = (numRows * 2 - 2)*j + i)
			{
				result += s[index];
				if (i == 0 || i == (numRows - 1))
					continue;
				if ((index + (numRows - 1 - i) * 2) < s.size())
					result += s[index + (numRows - 1 - i) * 2];
			}
		}
		return result;
	}
};
//int main(void)
//{
//	Solution test;
//	cout << test.convert("123", 1);
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}
