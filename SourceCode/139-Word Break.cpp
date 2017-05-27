//	139. Word Break
//------------------------------------------------------------------------------//
//	Given a non-empty string s and a dictionary wordDict containing a list of	//
//	non-empty words, determine if s can be segmented into a space-separated		//
//	sequence of one or more dictionary words. You may assume the dictionary		//
//	does not contain duplicate words.											//
//	For example, given															//
//	s = "leetcode",																//
//	dict = ["leet", "code"].													//
//	Return true because "leetcode" can be segmented as "leet code".				//
//	UPDATE(2017 / 1 / 4) :														//
//		The wordDict parameter had been changed to a list of strings(instead of //
//	a set of strings).Please reload the code definition to get the latest		//
//	changes.																	//
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

//深度优先搜索，时间复杂度O(2^n)，会超时
class Solution {
public:
	bool wordBreak(string s, vector<string>& wordDict) {
		unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
		bool result = false;
		DFS(result, s, 0, wordSet);
		return result;
	}
private:
	void DFS(bool &status, string &s, int start, unordered_set<string> &wordSet) {
		if (status) return;
		if (start == s.size()) {
			status = true;
			return;
		}
		for (int i = start; i < s.size(); ++i) {
			if (wordSet.find(s.substr(start, i - start + 1))
				!= wordSet.end())
				DFS(status, s, i + 1, wordSet);
		}
	}
};
//动态规划，时间复杂度O(n^2)
//设状态为f[i]，表示s[0..i]能被分割与否，那么状态转移方程为
//f(i) = any_of(f(j) && s[j + 1,i] 属于 dict),0 <=j < i
class Solution2 {
public:
	bool wordBreak(string s, vector<string>& wordDict) {
		unordered_set<string> dict(wordDict.begin(), wordDict.end());
		vector<bool> canBreak(s.size() + 1, false);
		canBreak[0] = true;
		for (int i = 1; i < canBreak.size(); ++i) {
			for (int j = 0; j < i; ++j) {
				if (canBreak[j] && dict.find(s.substr(j, i - j)) != dict.end()) {
					canBreak[i] = true;
					break;
				}
			}
		}
		return canBreak.back();
	}
};
//int main(void)
//{
//	Solution2 test;
//	string s = "leetcode";
//	vector<string> wordDict{ "leet","code" };
//	cout << boolalpha << test.wordBreak(s, wordDict);
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