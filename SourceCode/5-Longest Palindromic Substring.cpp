/// Longest Palindromic Substring
//最长回文子串
//
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<cmath>
#include<ctime>
#include<iomanip>
#include<stdio.h>
#include<exception>
#include<cstdlib>
#include<fstream>
#include<cstdio>
#include<set>
#include<map>
#include<vector>
#include<stack>
#include<list>
#include<queue>
#include<algorithm>
#include<functional>
#include<numeric>
#include<iterator>
#include<unordered_map>
#include<Windows.h>
// constants
using namespace std;
// function prototype
//暴力法，O(n2)，从一个字符左右两边开始搜
class Solution {
public:
	string longestPalindrome(string s) 
	{
		int i, j;
		int len;
		int max_index;
		int max_Count = 0;
		int start = 0;
		for (i = 0; i < s.size(); i++)
		{
			len = min(i - 0, s.size() - i);
			for (j = 0; j < len; j++)
			{
				if (s[i - j] != s[i + j])
					break;
			}
			j--;
			if ((j+1) == len&&s[i - j-1] == s[i + j+1])
				j++;
			if (2 * j + 1 > max_Count)
			{
				max_Count = 2*j+1;
				max_index = i - j;
			}
		}
		for (i = 0; i < s.size(); i++)
		{
			if (s[i] != s[start])
			{
				j = i - start;
				if (j > max_Count)
				{
					max_Count = j;
					max_index = start;
				}
				start = i;
			}
		}

		if (s[s.size()-1] == s[start])
		{
			j = s.size() - start;
			if (j > max_Count)
			{
				max_Count = j;
				max_index = start;
			}
		}
		return s.substr(max_index, max_Count);
	}
};
//备忘录法，O(n2)，此处哈希函数还有问题
typedef string::const_iterator Iterator;
namespace std {
	template<>
	struct hash<pair<Iterator, Iterator>> {
		size_t operator()(pair<Iterator, Iterator> const& p) const {
			return ((size_t) &(*p.first)) ^ ((size_t) &(*p.second));
		}
	};
}
class Solution2 {
public:
	string longestPalindrome(string const& s) {
		cache.clear();
		return cachedLongestPalindrome(s.begin(), s.end());
	}
private:
	unordered_map<pair<Iterator, Iterator>, string> cache;
	string longestPalindrome(Iterator first, Iterator last) {
		size_t length = distance(first, last);
		if (length < 2) return string(first, last);
		auto s = cachedLongestPalindrome(next(first), prev(last));
		if (s.length() == length - 2 && *first == *prev(last))
			return string(first, last);
		auto s1 = cachedLongestPalindrome(next(first), last);
		auto s2 = cachedLongestPalindrome(first, prev(last));
		// return max(s, s1, s2)
		if (s.size() > s1.size()) return s.size() > s2.size() ? s : s2;
		else return s1.size() > s2.size() ? s1 : s2;
	}
	string cachedLongestPalindrome(Iterator first, Iterator last) {
		auto key = make_pair(first, last);
		auto pos = cache.find(key);
		if (pos != cache.end()) return pos->second;
		else return cache[key] = longestPalindrome(first, last);
	}
};
//动态规划，O(n2),用f(j,i)表示从j到i的字符串是否是回文。
//状态转移方程可以表示为：f(j,i)=s[j] == s[i] && (i - j < 2 || f[(j + 1), i - 1])
class Solution3
{
public:
	string longestPalindrome(string const& s) 
	{
		const int n = s.size();
		bool *f;
		size_t maxLen = 1, start = 0;
		f = new bool[n*n];
		fill(f, f + n*n, false);
		for (size_t i = 0; i < s.size(); i++)
		{
			f[i*n + i] = true;
			for (size_t j = 0; j < i; j++)
			{
				f[j*n + i] = (s[j] == s[i] && (i - j < 2 || f[(j + 1)*n + i - 1]));
				if (f[j*n + i] && (i - j + 1) > maxLen)
				{
					maxLen = i - j + 1;
					start = j;
				}
			}
		}
		delete f;
		return s.substr(start, maxLen);
	}
};
//Manacher算法
class Solution4 
{
public:
	// Transform S into T.
	// For example, S = "abba", T = "^#a#b#b#a#$".
	// ^ and $ signs are sentinels appended to each end to avoid bounds checking
	string preProcess(const string& s) {
		int n = s.length();
		if (n == 0) return "^$";
		string ret = "^";
		for (int i = 0; i < n; i++) ret += "#" + s.substr(i, 1);
		ret += "#$";
		return ret;
	}
	string longestPalindrome(string s) {
		string T = preProcess(s);
		const int n = T.length();
		// 􀐔 T[i] 􀍩􀍜􁓲􅖌􀥀􁌕/􀤢􁞘􁑏􂮳􄪮􁏕􅖌􀌼􀠴􀥚 T[i] 􃜙􁌠􅖌
		// 􀰏􂂓 P[i] 􁭞􂎿􁂆􃁕􀍡􀍜􀰍􁪶􀍡􂮳􄪮􁏕
		int *P=new int[n];
		int C = 0, R = 0;
		for (int i = 1; i < n - 1; i++) {
			int i_mirror = 2 * C - i; // equals to i' = C - (i-C)
			P[i] = (R > i) ? min(R - i, P[i_mirror]) : 0;
			// Attempt to expand palindrome centered at i
			while (T[i + 1 + P[i]] == T[i - 1 - P[i]])
				P[i]++;
			// If palindrome centered at i expand past R,
			// adjust center based on expanded palindrome.
			if (i + P[i] > R) {
				C = i;
				R = i + P[i];
			}
		}
		// Find the maximum element in P.
		int max_len = 0;
		int center_index = 0;
		for (int i = 1; i < n - 1; i++) {
			if (P[i] > max_len) {
				max_len = P[i];
				center_index = i;
			}
		}
		delete P;
		return s.substr((center_index - 1 - max_len) / 2, max_len);
	}
};
////Manacher算法，自己实现，大致思想：空间换时间，时间复杂度O(N)，将输入字符串构造成#a#b#b#b....的形式，
////并且可以再头尾出加上标志以避免额外的判断。给定一个ID和MAXEDGE，MAXEDGE代表在ID处的回文子串的右边界
////则在处理一个新的i时，可以判断i是否在MAXEDGE覆盖范围内，再加上i关于ID对称的j，(1)如果i在MAXEDGE内，j
////处的回文子串长度在ID的覆盖范围，则i的回文子串长度和j处相等，不用更新，(2)如果i在MAXEDGE内，但是j处的
////回文子串长度超出ID范围，则i的回文长度至少是MAXEDGE-i，在继续搜索，(3)i不在ID范围内，从0开始搜索
class Solution5
{
public:
	string longestPalindrome(string const& s)
	{
		string T = ManacherPreProcess(s);
		int n = T.length();
		int ID = 0, MAXEDGE = 0;	//ID为现最大覆盖区域的中心，MAXEDGE为边界
		int *P = new int[n];		//记录以每个点为中心的回文子串长度
		int Max_Center = 0, Max_Len = 0;	//最长回文子串出现的中心点和长度
		for (int i = 1; i < n - 1; i++)
		{
			P[i] = (MAXEDGE > i) ? min(P[2 * ID - i], MAXEDGE - i) : 0;
			while (T[i + P[i] + 1] == T[i - P[i] - 1])	//继续匹配
				P[i]++;
			if ((i + P[i]) > MAXEDGE)
			{
				MAXEDGE = i + P[i];
				ID = i;
			}
			if (P[i] > Max_Len)
			{
				Max_Len = P[i];
				Max_Center = i;
			}
		}
		delete P;
		return s.substr((Max_Center - Max_Len - 1) / 2, Max_Len);
	}
private:
	string ManacherPreProcess(const string & s)
	{
		int n = s.length();
		if (n == 0)
			return "^$";
		string T = "^";
		for (int i = 0; i < n; i++)
			T += "#" + s.substr(i, 1);
		T += "#$";
		return T;
	}
};
//中心展开法
class Solution6 {
public:
	std::string longestPalindrome(std::string s) {
		if (s.empty() || 1 == s.size())
			return s;
		int i, a, b, mark, sz = s.size();
		int maxlen = 1;
		for (i = 0; i < sz && 2 * (sz - i) > maxlen;)
		{
			a = b = i;
			for (; b + 1 < sz && s[b] == s[b + 1]; ++b);
			i = b + 1; //the key step, rather than ++i, i could skip duplicate characters.
			for (; a > 0 && b + 1 < sz && s[a - 1] == s[b + 1]; --a, ++b);
			if (b - a + 1 > maxlen)
			{
				mark = a;
				maxlen = b - a + 1;
			}
		}
		return s.substr(mark, maxlen);
	}
};
//int main()
//{
//	Solution5 test;
//	cout << test.longestPalindrome("babadada") << endl;
//	cout << "Done.\n";
//	// code to keep window open for MSVC++
//	std::cin.clear();
//	while (std::cin.get() != '\n')
//		continue;
//	std::cin.get();
//	return 0;
//}


