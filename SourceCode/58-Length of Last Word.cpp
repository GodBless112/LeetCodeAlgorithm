//	58. Length of Last Word
//------------------------------------------------------------------------------//
//	Given a string s consists of upper/lower-case alphabets and empty space		//
//	characters ' ', return the length of last word in the string.				//
//	If the last word does not exist, return 0.									//
//	Note: A word is defined as a character sequence consists of non - space		//
//	characters only.															//
//	For example,																//
//		Given s = "Hello World",												//
//		return 5.																//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<functional>
#include<unordered_map>
// constants
// function prototype
using namespace std;
//从后往前，找到第一个不是空格的，然后在往前找到第一个是空格的，之间的字符就是last string
class Solution 
{
public:
	int lengthOfLastWord(string s) 
	{
		int n = s.size(), start, end;
		for (end = n - 1; end >= 0; --end)
			if (s[end] != ' ')
				break;
		if (end == -1)
			return 0;
		for (start = end - 1; start >= 0; --start)
			if (s[start] == ' ')
				break;
		return end - start;
	}
};
//STL方法
class Solution2
{
public:
	int lengthOfLastWord(string s)
	{
		auto first = find_if(s.rbegin(), s.rend(), ::isalpha);
		auto last = find_if_not(first, s.rend(), ::isalpha);
		return distance(first, last);
	}
};
//顺序扫描
class Solution3
{
public:
	int lengthOfLastWord(const string& s) {
		return lengthOfLastWord(s.c_str());
	}
private:
	int lengthOfLastWord(const char *s) {
		int len = 0;
		while (*s) {
			if (*s++ != ' ')
				++len;
			else if (*s && *s != ' ')
				len = 0;
		}
		return len;
	}
};
//int main(void)
//{
//	Solution3 test;
//	string a = " hello wor ";
//	cout << test.lengthOfLastWord(a) << endl;
//	
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}
