//	38. Count and Say
//------------------------------------------------------------------------------//
//	The count-and-say sequence is the sequence of integers beginning as follows://
//	1, 11, 21, 1211, 111221, ...												//
//	1 is read off as "one 1" or 11.												//
//	11 is read off as "two 1s" or 21.											//
//	21 is read off as "one 2, then one 1" or 1211.								//
//	Given an integer n, generate the nth sequence.								//
//	Note: The sequence of integers will be represented as a string.				//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<functional>
#include<sstream>
// constants
// function prototype
using namespace std;
class Solution 
{
public:
	string countAndSay(int n) 
	{
		string result = "1";
		for (int i = 0; i < n - 1; i++)
		{
			string temp;
			int start = 0;
			int count = 0;
			for (int j = 0; j <= result.size(); j++)
			{
				if (result[start] == result[j])
					count++;
				else
				{
					temp += '0' + count;
					temp += result[start];
					count = 1;
					start = j;
				}
			}
			result = temp;
		}
		return result;
	}
};
//STL，没有第一个快
class Solution2 {
public:
	string countAndSay(int n) {
		string s("1");
		while (--n)
			s = getNext(s);
		return s;
	}
	string getNext(const string &s) {
		stringstream ss;
		for (auto i = s.begin(); i != s.end(); ) {
			auto j = find_if(i, s.end(), bind1st(not_equal_to<char>(), *i));
			ss << distance(i, j) << *i;
			i = j;
		}
		return ss.str();
	}
};
//int main(void)
//{
//	Solution2 test;
//	cout << test.countAndSay(5) << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}
