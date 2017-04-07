// Regular Expression Matching
//正则表达式匹配,采用迭代或者动态规划的方法来做
#include <iostream>
#include<vector>
#include<string>
#include<cctype>
// constants
// function prototype
using namespace std;
class Solution 
{
public:
	bool isMatch(const string& s, const string& p) {
		return isMatch(s.c_str(), p.c_str());
	}
private:
	bool isMatch(const char *s, const char *p)
	{
		if (*p == '\0') return *s == '\0';
		// next char is not '*', then must match current character
		if (*(p + 1) != '*') 
		{
			if (*p == *s || (*p == '.' && *s != '\0'))
				return isMatch(s + 1, p + 1);
			else
				return false;
		}
		else 
		{ // next char is '*'
			while (*p == *s || (*p == '.' && *s != '\0')) 
			{
				if (isMatch(s, p + 2))
					return true;
				s++;
			}
			return isMatch(s, p + 2);
		}
	}
};
//递归调用，纯string，效率会差于char*形式
class Solution2
{
public:
	bool isMatch(string s, string p)
	{
		if (p.empty())
			return s.empty();
		if (p[1] == '*')
			return (isMatch(s, p.substr(2)) || !s.empty() && (s[0] == p[0] || p[0] == '.') && isMatch(s.substr(1), p));
		else
			return (!s.empty() && (s[0] == p[0] || p[0] == '.') && isMatch(s.substr(1), p.substr(1)));
	}
};
class Solution3 {
public:
	bool isMatch(string s, string p) {
		/**
		* f[i][j]: if s[0..i-1] matches p[0..j-1]
		* if p[j - 1] != '*'
		*      f[i][j] = f[i - 1][j - 1] && s[i - 1] == p[j - 1]
		* if p[j - 1] == '*', denote p[j - 2] with x
		*      f[i][j] is true iff any of the following is true
		*      1) "x*" repeats 0 time and matches empty: f[i][j - 2]
		*      2) "x*" repeats >= 1 times and matches "x*x": s[i - 1] == x && f[i - 1][j]
		* '.' matches any single character
		*/
		int m = s.size(), n = p.size();
		vector<vector<bool>> f(m + 1, vector<bool>(n + 1, false));

		f[0][0] = true;
		for (int i = 1; i <= m; i++)
			f[i][0] = false;
		// p[0.., j - 3, j - 2, j - 1] matches empty iff p[j - 1] is '*' and p[0..j - 3] matches empty
		for (int j = 1; j <= n; j++)
			f[0][j] = j > 1 && '*' == p[j - 1] && f[0][j - 2];

		for (int i = 1; i <= m; i++)
			for (int j = 1; j <= n; j++)
				if (p[j - 1] != '*')
					f[i][j] = f[i - 1][j - 1] && (s[i - 1] == p[j - 1] || '.' == p[j - 1]);
				else
					// p[0] cannot be '*' so no need to check "j > 1" here
					f[i][j] = f[i][j - 2] || (s[i - 1] == p[j - 2] || '.' == p[j - 2]) && f[i - 1][j];

		return f[m][n];
	}
};
//int main(void)
//{
//	Solution3 test;
//	string a("abcdef");
//	string b(".*");
//	cout << test.isMatch(a, b) << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}
