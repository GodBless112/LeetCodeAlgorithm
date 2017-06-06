//	151. Reverse Words in a String
//------------------------------------------------------------------------------//
//	Given an input string, reverse the string word by word.						//
//	For example,																//
//	Given s = "the sky is blue",												//
//	return "blue is sky the".													//
//	Update(2015 - 02 - 12) :													//
//	For C programmers : Try to solve it in - place in O(1) space.				//
//	Clarification:																//
//	What constitutes a word ?													//
//	A sequence of non - space characters constitutes a word.					//
//	Could the input string contain leading or trailing spaces ?					//
//	Yes.However, your reversed string should not contain leading or trailing	//
//	spaces.																		//
//	How about multiple spaces between two words ?								//
//	Reduce them to a single space in the reversed string.						//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<sstream>
// constants
// function prototype
using namespace std;
//利用字符串划分函数，划分从字符串数组，然后重构
class Solution {
public:
	void reverseWords(string &s) {
		auto sp = split(s, " ");
		string str;
		s = accumulate(sp.rbegin(), sp.rend(), str, [](string &str, string &t) {
			return str += t + " ";
		});
		s.erase(s.end() - 1);
	}
private:
	vector<string> split(string &s, string type) {
		vector<string> result;
		if (s.empty()) return result;
		size_t start = 0, index = s.find_first_of(type, 0);
		while (index != s.npos) {
			if (start != index)
				result.push_back(s.substr(start, index - start));
			start = index + 1;
			index = s.find_first_of(type, start);
		}
		if (!s.substr(start).empty())
			result.push_back(s.substr(start));
		return result;
	}
};
//双指针法，用一个index记录反向存储的位置，利用reverse函数，inplace的算法
class Solution2 {
public:
	void reverseWords(string &s) {
		reverse(s.begin(), s.end());
		int storeIndex = 0;
		for (int i = 0; i < s.size(); i++) {
			if (s[i] != ' ') {
				if (storeIndex != 0) s[storeIndex++] = ' ';
				int j = i;
				while (j < s.size() && s[j] != ' ') { s[storeIndex++] = s[j++]; }
				reverse(s.begin() + storeIndex - (j - i), s.begin() + storeIndex);
				i = j;
			}
		}
		s.erase(s.begin() + storeIndex, s.end());
	}
};
//利用stringstream
class Solution3 {
public:
	void reverseWords(string &s) {
		istringstream is(s);
		string tmp;
		is >> s;
		while (is >> tmp) s = tmp + " " + s;
		if (s[0] == ' ') s = "";
	}
};
//双指针法，用一个index记录反向存储的位置，利用reverse函数，inplace的算法
class Solution4 {
public:
	void reverseWords(string &s) {

		int i = 0, j = 0;
		int l = 0;
		int len = s.length();
		int wordcount = 0;

		while (true) {
			while (i<len && s[i] == ' ') i++;  // skip spaces in front of the word
			if (i == len) break;
			if (wordcount) s[j++] = ' ';
			l = j;
			while (i<len && s[i] != ' ') { s[j] = s[i]; j++; i++; }
			reverse(s.begin() + l, s.begin() + j);                // reverse word in place
			wordcount++;

		}

		s.resize(j);                           // resize result string
		reverse(s.begin(),s.end());                  // reverse whole string
	}
};
//int main(void)
//{
//	Solution4 test;
//	string s = "   the  sky  is   blue   ";
//	cout << s << endl;
//	test.reverseWords(s);
//	cout << s;
//	cout << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//	
//	return 0;
//}