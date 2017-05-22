//	127. Word Ladder
//------------------------------------------------------------------------------//
//	Given two words (beginWord and endWord), and a dictionary's word list, find //
//	the length of shortest transformation sequence from beginWord to endWord,	//
//	such that:																	//
//	Only one letter can be changed at a time.									//
//	Each transformed word must exist in the word list.Note that beginWord is	//
//	not a transformed word.														//
//	For example,																//
//	Given:																		//
//	beginWord = "hit"															//
//	endWord = "cog"																//
//	wordList = ["hot", "dot", "dog", "lot", "log", "cog"]						//
//	As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",//
//	return its length 5.														//
//	Note :																		//
//		Return 0 if there is no such transformation sequence.					//
//		All words have the same length.											//
//		All words contain only lowercase alphabetic characters.					//
//		You may assume no duplicates in the word list.							//
//		You may assume beginWord and endWord are non - empty and are not the	//
//	same.																		//
//		UPDATE(2017 / 1 / 20) :													//
//		The wordList parameter had been changed to a list of strings(instead of //
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
#include<unordered_map>
#include<queue>
// constants
// function prototype
using namespace std;
//单源最短路径的思路，单队列，广度优先搜索
class Solution {
public:
	int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
		unordered_set<string> wordDict(wordList.begin(), wordList.end());
		queue<string> toVisit;
		addNextWords(beginWord, wordDict, toVisit);
		int ladderLen = 2;
		while (!toVisit.empty()) {
			int num = toVisit.size();
			for (int i = 0; i < num; ++i) {
				string word = toVisit.front();
				toVisit.pop();
				if (word == endWord) return ladderLen;
				addNextWords(word, wordDict, toVisit);
			}
			ladderLen++;
		}
		return 0;
	}
private:
	void addNextWords(string word, unordered_set<string>& wordDict, queue<string>& toVisit) {
		for (int i = 0; i < word.size(); ++i) {
			wordDict.erase(word);
			char letter = word[i];
			for (char ch = 'a'; ch <= 'z'; ++ch) {
				if (ch == letter) continue;
				word[i] = ch;
				if (wordDict.find(word) != wordDict.end()) {
					toVisit.push(word);
					wordDict.erase(word);
				}
			}
			word[i] = letter;
		}
	}
};
//单源最短路径的思路，单队列，广度优先搜索，邻接表的形式
class Solution2 {
public:
	int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
		unordered_set<string> wordDict(wordList.begin(), wordList.end());
		unordered_map<string, int> pathlen;
		queue<string> toVisit;
		pathlen[beginWord] = 1;
		toVisit.push(beginWord);
		
		while (!toVisit.empty()) {
			string word = toVisit.front();
			toVisit.pop();
			vector<string> adj = getAdjacent(word, wordDict);
			for (int i = 0; i < adj.size(); ++i) {
				if (pathlen.find(adj[i]) == pathlen.end()) {
					pathlen[adj[i]] = pathlen[word] + 1;
					toVisit.push(adj[i]);
				}
				if (adj[i] == endWord) return pathlen[adj[i]];
			}
		}
		return 0;
	}
private:
	//寻找一个单词的邻接表
	vector<string> getAdjacent(string word, unordered_set<string>& wordDict) {
		vector<string> result;
		for (int i = 0; i < word.size(); ++i) {
			char letter = word[i];
			for (char ch = 'a'; ch <= 'z'; ++ch) {
				if (ch == letter) continue;
				word[i] = ch;
				if (wordDict.find(word) != wordDict.end())
					result.push_back(word);
			}
			word[i] = letter;
		}
		return result;
	}
};
//双端法，从起始和结束同时开始，遇到相同的元素时则找到路径，此法最优
class Solution3 {
public:
	int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
		unordered_set<string> wordDict(wordList.begin(), wordList.end());
		if (wordDict.find(endWord) == wordDict.end()) return 0;
		unordered_set<string> head, tail, *phead, *ptail;
		head.insert(beginWord);
		tail.insert(endWord);
		int dist = 2;
		//选择较小的一个往下进行
		while (!head.empty() && !tail.empty()) {
			if (head.size() < tail.size()) {
				phead = &head;
				ptail = &tail;
			}
			else {
				phead = &tail;
				ptail = &head;
			}
			unordered_set<string> temp;
			for (auto itr = phead->begin(); itr != phead->end(); itr++) {
				string word = *itr;
				wordDict.erase(word);
				for (int p = 0; p < (int)word.length(); p++) {
					char letter = word[p];
					for (int k = 0; k < 26; k++) {
						word[p] = 'a' + k;
						if (ptail->find(word) != ptail->end())
							return dist;
						if (wordDict.find(word) != wordDict.end()) {
							temp.insert(word);
							wordDict.erase(word);
						}
					}
					word[p] = letter;
				}
			}
			dist++;
			swap(*phead, temp);
		}
		return 0;
	}
};
//双队列法
class Solution4 {
public:
	int ladderLength(const string& start, const string &end,
		vector<string>& wordList) {
		unordered_set<string> dict(wordList.begin(), wordList.end());
		if (dict.find(end) == dict.end()) return 0;
		queue<string> current, next; //当前层，下一层
		unordered_set<string> visited; //判重
		int level = -1; //层次
		auto state_is_valid = [&](const string& s) {
			return dict.find(s) != dict.end() || s == end;
		};
		auto state_is_target = [&](const string &s) {return s == end; };
		auto state_extend = [&](const string &s) {
			unordered_set<string> result;
			for (size_t i = 0; i < s.size(); ++i) {
				string new_word(s);
				for (char c = 'a'; c <= 'z'; c++) {
					//防止同字母替换
					if (c == new_word[i]) continue;
					swap(c, new_word[i]);
					if (state_is_valid(new_word) &&
						visited.find(new_word) == visited.end()) {
						result.insert(new_word);
					}
					swap(c, new_word[i]); //恢复该单词
				}
			}
			return result;
		};
		current.push(start);
		visited.insert(start);
		while (!current.empty()) {
			++level;
			while (!current.empty()) {
				//千万不能用const auto&pop()会删除元素
				//引用就变成了悬空引用
				const auto state = current.front();
				current.pop();
				if (state_is_target(state)) {
					return level + 1;
				}
				const auto& new_states = state_extend(state);
				for (const auto& new_state : new_states) {
					next.push(new_state);
					visited.insert(new_state);
				}
			}
			swap(next, current);
		}
		return 0;
	}
};
//int main(void)
//{
//	Solution3 test;
//	vector<string> wordList{ "hot", "dot", "dog", "lot", "log", "cog" };
//	cout << test.ladderLength("hit", "ceg", wordList);
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