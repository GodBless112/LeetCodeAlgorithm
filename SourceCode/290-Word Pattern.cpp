//	290. Word Pattern
//------------------------------------------------------------------------------//
//	Given a pattern and a string str, find if str follows the same pattern.		//
//	Here follow means a full match, such that there is a bijection between a	//
//	letter in pattern and a non - empty word in str.							//
//	Examples:																	//
//	pattern = "abba", str = "dog cat cat dog" should return true.				//
//	pattern = "abba", str = "dog cat cat fish" should return false.				//
//	pattern = "aaaa", str = "dog cat cat dog" should return false.				//
//	pattern = "abba", str = "dog dog dog dog" should return false.				//
//	Notes :																		//
//		You may assume pattern contains only lowercase letters, and str			//
//	contains lowercase letters separated by a single space.						//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<sstream>
#include<unordered_map>
#include<unordered_set>
#include<map>
// constants
// function prototype
using namespace std;
//哈希表，一个hashmap记录变换对，一个hashset记录是否变换过
class Solution {
public:
	bool wordPattern(string pattern, string str) {
		stringstream ss(str);
		vector<string> strs;
		string s;
		while (ss >> s)
			strs.push_back(s);
		unordered_map<char, string> dict;
		unordered_set<string> trans;
		if (pattern.size() != strs.size()) return false;
		for (int i = 0; i < pattern.size(); ++i) {
			if (dict.find(pattern[i]) == dict.end()) {
				if (trans.find(strs[i]) != trans.end())
					return false;
				dict[pattern[i]] = strs[i];
				trans.insert(strs[i]);
			}			
			else if (dict[pattern[i]] != strs[i])
				return false;		
		}
		return true;
	}
};
//直接istringstream输出，不放到vector里
class Solution2 {
public:
	bool wordPattern(string pattern, string str) {
		map<char, int> p2i;
		map<string, int> w2i;
		istringstream in(str);
		int i = 0, n = pattern.size();
		for (string word; in >> word; ++i) {
			if (i == n || p2i[pattern[i]] != w2i[word])
				return false;
			p2i[pattern[i]] = w2i[word] = i + 1;
		}
		return i == n;
	}
};
//int main(void)
//{
//	Solution2 test;
//	string pattern = "abba";
//	string str = "dog cat cat fish";
//	cout << boolalpha << test.wordPattern(pattern, str);
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