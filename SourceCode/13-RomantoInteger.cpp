//	13. Roman to Integer
#include <iostream>
#include<vector>
#include<string>
#include<cctype>
#include<algorithm>
// constants
// function prototype
using namespace std;
//寻找法
class Solution 
{
public:
	int romanToInt(string s) 
	{
		const int radix[] = { 1000,900,500,400,100,90,50,40,10,9,5,4,1 };
		string RomanTable[] = { "M", "CM", "D", "CD", "C", "XC",
			"L", "XL", "X", "IX", "V", "IV", "I" };
		int ret = 0;
		string temp = s;
		for (int i = 0; !temp.empty(); i++)
		{
			size_t a = temp.find(RomanTable[i]);
			if (a != temp.npos)
			{
				while (temp.substr(0, RomanTable[i].size()) == RomanTable[i])
				{
					ret += radix[i];
					temp = temp.substr(RomanTable[i].size());
				}
			}
		}
		return ret;
	}
};
//查表法，时间复杂度O(n)，空间复杂度O(1),分段运算，如果后面出现的数字大于前一个，则需要减去该值，否则加上
class Solution2
{
public:
	inline int map(const char c)
	{
		switch (c)
		{
		case 'I':
			return 1;
		case 'V':
			return 5;
		case 'X':
			return 10;
		case 'L':
			return 50;
		case 'C':
			return 100;
		case 'D':
			return 500;
		case 'M':
			return 1000;
		}
	}
	int romanToInt(string s)
	{
		int ret = 0;
		for (int i = 0; i < s.size(); i++)
		{
			if (i > 0 && map(s[i]) > map(s[i - 1]))
				ret += map(s[i]) - 2 * map(s[i - 1]);
			else
				ret += map(s[i]);
		}
		return ret;
	}
};
//int main(void)
//{
//	Solution2 test;
//	cout << test.romanToInt("MCMXCVI") << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}
