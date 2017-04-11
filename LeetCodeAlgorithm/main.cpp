//	28. Implement strStr()
//------------------------------------------------------------------------------//
//	Implement strStr().
//	Returns the index of the first occurrence of needle in haystack, or -1 if	//
//	needle is not part of haystack.												//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<cctype>
#include<algorithm>
#include<stack>
// constants
// function prototype
using namespace std;
//暴力匹配，时间O(m*n)，空间O(1)
class Solution 
{
public:
	int strStr(string haystack, string needle) 
	{
		const int m = haystack.size();
		const int n = needle.size();
		if (n == 0)
			return 0;
		for (int i = 0; i < m - n + 1; i++)
		{
			int j;
			for (j = 0; j < n; j++)
				if (haystack[i + j] != needle[j])
					break;
			if (j == n)
				return i;
		}
		return -1;
	}
};
int main(void)
{
	Solution test;
	string a("abcd"), b("bcd");
	cout << test.strStr(a,b) << endl;
	// code to keep window open for MSVC++
	cin.clear();
	while (cin.get() != '\n')
		continue;
	cin.get();

	return 0;
}
