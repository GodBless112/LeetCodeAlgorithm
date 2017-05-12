//	91. Decode Ways
//------------------------------------------------------------------------------//
//	A message containing letters from A-Z is being encoded to numbers using the //
//	following mapping:															//
//	'A' -> 1																	//
//	'B' -> 2																	//
//	'Z' -> 26																	//
//	Given an encoded message containing digits, determine the total number of	//
//	ways to decode it.															//
//	For example,																//
//	Given encoded message "12", it could be decoded as "AB" (1 2) or "L" (12).	//
//	The number of ways decoding "12" is 2.										//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<unordered_map>
#include<set>
#include<iterator>
// constants
// function prototype
using namespace std;
//类似于Climbing Stairs，对于前k个字符组成的字符串，它的解法等于
//前k-1个的解法加上前k-2个的解法（k-2k-1合法的情况）
class Solution
{
public:
	int numDecodings(string s) 
	{
		if (s.empty() || s[0] == '0')
			return 0;
		int prev = 0;
		int cur = 1;
		for (size_t i = 1; i <= s.size(); i++)
		{
			if (s[i - 1] == '0') cur = 0;
			if (i < 2 || !(s[i - 2] == '1' || (s[i - 2] == '2'&&s[i - 1] <= '6')))
				prev = 0;
			int temp = cur;
			cur = prev + cur;
			prev = temp;
		}
		return cur;
	}
};
//int main(void)
//{
//	Solution test;
//	string s = "110";
//	cout << test.numDecodings(s);
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