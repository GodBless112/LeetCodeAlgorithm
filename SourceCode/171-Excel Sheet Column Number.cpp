//	171. Excel Sheet Column Number
//------------------------------------------------------------------------------//
//	Related to question Excel Sheet Column Title								//
//	Given a column title as appear in an Excel sheet, return its corresponding	//
//	column number.																//
//	For example :																//
//	A -> 1																		//
//	B -> 2																		//
//	C -> 3																		//
//	...																			//
//	Z -> 26																		//
//	AA -> 27																	//
//	AB -> 28 																	//
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
//迭代的方法
class Solution {
public:
	int titleToNumber(string s) {
		int n = s.size();
		int result = 0;
		for (int i = n - 1; i >= 0; --i)
			result += pow(26, n - i - 1)*(s[i] - 'A' + 1);
		return result;
	}
};
//递归的方法
class Solution2 {
public:
	int titleToNumber(string s) {
		return s != "" ? 26 * titleToNumber(s.substr(0, s.size() - 1)) + s[s.size() - 1] - 'A' + 1 : 0;
	}
};
//正向的迭代
class Solution3
{
public:
	int titleToNumber(string s)
	{
		int ret = 0;
		for (int i = 0; i<s.size(); i++)
		{
			ret *= 26;
			ret += s[i] - 'A' + 1;
		}
		return ret;
	}
};
//int main(void)
//{
//	Solution2 test;
//	cout << test.titleToNumber("ZZ");
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