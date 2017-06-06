//	205. Isomorphic Strings
//------------------------------------------------------------------------------//
//	Given two strings s and t, determine if they are isomorphic.				//
//	Two strings are isomorphic if the characters in s can be replaced to get t.	//
//	All occurrences of a character must be replaced with another character		//
//	while preserving the order of characters.No two characters may map to the	//
//	same character but a character may map to itself.							//
//	For example,																//
//	Given "egg", "add", return true.											//
//	Given "foo", "bar", return false.											//
//	Given "paper", "title", return true.										//
//	Note:																		//
//	You may assume both s and t have the same length.							//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<unordered_map>
#include<unordered_set>
// constants
// function prototype
using namespace std;
//利用hash表记录，一个hashmap记录变换对，一个hashset记录是否变换过
class Solution {
public:
	bool isIsomorphic(string s, string t) {
		unordered_map<char, char> dict;
		unordered_set<char> trans;
		for (int i = 0; i < s.size(); ++i) {
			if (dict.find(s[i]) == dict.end()) {
				if (trans.find(t[i]) != trans.end())
					return false;
				dict[s[i]] = t[i];
				trans.insert(t[i]);
			}			
			else if (dict[s[i]] != t[i])
				return false;
		}
		return true;
	}
};
//不用hash表，用两个256大小的数组记录s和t字符出现的位置，
//如果对应位上的值不一样，则说明出现了两种可能的变换
class Solution2 {
public:
	bool isIsomorphic(string s, string t) {
		int m1[256] = { 0 }, m2[256] = { 0 }, n = s.size();
		for (int i = 0; i < n; ++i) {
			if (m1[s[i]] != m2[t[i]]) return false;
			m1[s[i]] = i + 1;
			m2[t[i]] = i + 1;
		}
		return true;
	}
};
//利用char数组记录对应字符
class Solution3 {
public:
	bool isIsomorphic(string s, string t) {
		char charArrS[256] = { 0 };
		char charArrT[256] = { 0 };
		int i = 0;
		while (s[i] != 0)
		{
			if (charArrS[s[i]] == 0 && charArrT[t[i]] == 0)
			{
				charArrS[s[i]] = t[i];
				charArrT[t[i]] = s[i];
			}
			else
				if (charArrS[s[i]] != t[i] || charArrT[t[i]] != s[i])
					return false;
			i++;
		}

		return true;
	}
};
//int main(void)
//{
//	Solution3 test;
//	cout << boolalpha << test.isIsomorphic("egg", "add");
//	cout << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//	
//	return 0;
//}