//	242. Valid Anagram
//------------------------------------------------------------------------------//
//	Given two strings s and t, write a function to determine if t is an anagram //
//	of s.																		//
//	For example,																//
//	s = "anagram", t = "nagaram", return true.									//
//	s = "rat", t = "car", return false.											//
//	Note:																		//
//	You may assume the string contains only lowercase alphabets.				//
//	Follow up :																	//
//	What if the inputs contain unicode characters ? How would you adapt your	//
//	solution to such case ?														//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<unordered_map>
// constants
// function prototype
using namespace std;
//两个字符排序后比较
class Solution {
public:
	bool isAnagram(string s, string t) {
		sort(s.begin(), s.end());
		sort(t.begin(), t.end());
		return s == t;
	}
};
//hash表，可以适应所有Unicode的情况
class Solution2 {
public:
	bool isAnagram(string s, string t) {
		if (s.size() != t.size()) return false;
		unordered_map<char, int> dict;
		for (int i = 0; i < s.size(); ++i) {
			dict[s[i]]++;
			dict[t[i]]--;
		}
		for (auto x : dict)
			if (x.second != 0)
				return false;
		return true;
	}
};
//hash表2，利用字符串的元素都为小写字母的事实
class Solution3 {
public:
	bool isAnagram(string s, string t) {
		int alp[26] = {};
		for (int i = 0; i < s.length(); i++)
			alp[s.at(i) - 'a']++;
		for (int i = 0; i < t.length(); i++)
			alp[t.at(i) - 'a']--;
		for (int i = 0; i<26; i++)
			if (alp[i] != 0)
				return false;
		return true;
	}
};
//int main(void)
//{
//	Solution3 test;
//	cout << boolalpha << test.isAnagram("ang", "gan");
//	cout << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}