//	345. Reverse Vowels of a String
//------------------------------------------------------------------------------//
//	Write a function that takes a string as input and reverse only the vowels	//
//	of a string.																//
//	Example 1:																	//
//	Given s = "hello", return "holle".											//
//	Example 2 :																	//
//	Given s = "leetcode", return "leotcede".									//
//	Note :																		//
//	The vowels does not include the letter "y".									//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<unordered_set>
// constants
// function prototype
using namespace std;
class Solution {
public:
	string reverseVowels(string s) {
		int start = 0, end = s.size() - 1;
		while (start < end) {
			while (start < end && dict.find(s[start]) == dict.end())
				start++;
			while (start < end && dict.find(s[end]) == dict.end())
				end--;
			swap(s[start++], s[end--]);
		}
		return s;
	}
private:
	unordered_set<char> dict = { 'a','e','i','o','u','A','E','I','O','U' };
};
//STL方法find_first_of，find_last_of
class Solution2 {
public:
	string reverseVowels(string s) {
		int i = 0, j = s.size() - 1;
		while (i < j) {
			i = s.find_first_of("aeiouAEIOU", i);
			j = s.find_last_of("aeiouAEIOU", j);
			if (i < j) {
				swap(s[i++], s[j--]);
			}
		}
		return s;
	}
};
//用char数组代替哈希表
class Solution3 {
public:
	string reverseVowels(string s) {
		int dict[256] = { 0 };
		dict['a'] = 1, dict['A'] = 1;
		dict['e'] = 1, dict['E'] = 1;
		dict['i'] = 1, dict['I'] = 1;
		dict['o'] = 1, dict['O'] = 1;
		dict['u'] = 1, dict['U'] = 1;
		int start = 0, end = (int)s.size() - 1;
		while (start < end) {
			while (start < end && dict[s[start]] == 0) start++;
			while (start < end && dict[s[end]] == 0) end--;
			swap(s[start], s[end]);
			start++; end--;
		}
		return s;
	}
};
class Solution4 {
public:
	string reverseVowels(string s) {
		auto p1 = s.begin(), p2 = s.end() - 1;
		string vowels = "aeiouAEIOU";
		while (p1 < p2) {
			while ((vowels.find(*p1) == string::npos) && (p1 < p2)) p1++;
			while ((vowels.find(*p2) == string::npos) && (p1 < p2)) p2--;
			if (p1 < p2) swap(*p1, *p2);
			p1++;
			p2--;
		}
		return s;
	}
};
//int main(void)
//{
//	Solution test;
//	cout << test.reverseVowels("lkktcode");
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