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
#include<list>
#include<ctime>
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
class Solution2 {
public:
	int strStr(const string& haystack, const string& needle) {
		return kmp(haystack.c_str(), needle.c_str());
	}
private:
	/*
	* @brief 计算部分匹配表，即next数组
	**
	@param[in] pattern 模式串
	* @param[out] next next 数组
	* @return 无
	*/
	static void compute_prefix(const char *pattern, int next[]) {
		int i;
		int j = -1;
		const int m = strlen(pattern);
		next[0] = j;
		for (i = 1; i < m; i++) {
			while (j > -1 && pattern[j + 1] != pattern[i]) j = next[j];
			if (pattern[i] == pattern[j + 1]) j++;
			next[i] = j;
		}
	}
	/*
	* @brief KMP 算法
	**
	@param[in] text 文本􁪶􁱛
	* @param[in] pattern 模式串 􁽐􁐾􀍡
	* @return 成功则返回第一次匹配的位置，否则返回-1
	*/
	static int kmp(const char *text, const char *pattern) {
		int i;
		int j = -1;
		const int n = strlen(text);
		const int m = strlen(pattern);
		if (n == 0 && m == 0) return 0; /* "","" */
		if (m == 0) return 0; /* "a","" */
		int *next = (int*)malloc(sizeof(int) * m);
		compute_prefix(pattern, next);
		for (i = 0; i < n; i++) {
			while (j > -1 && pattern[j + 1] != text[i]) j = next[j];
			if (text[i] == pattern[j + 1]) j++;
			if (j == m - 1) {
				free(next);
				return i - j;
			}
		}
		free(next);
		return -1;
	}
};
struct A
	 {
	int a;
	char c[0];
	 };
//int main(void)
//{
//	char *p[] = { "Shanghai","Beijing","Honkong" };
//	cout << *(p[1] + 3);
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}
