//	212. Word Search II
//------------------------------------------------------------------------------//
//	Given a 2D board and a list of words from the dictionary, find all words in //
//	the board.																	//
//	Each word must be constructed from letters of sequentially adjacent cell,	//
//	where "adjacent" cells are those horizontally or vertically neighboring.The	//
//	same letter cell may not be used more than once in a word.					//
//	For example,																//
//	Given words = ["oath", "pea", "eat", "rain"] and board =					//
//	[																			//
//		['o', 'a', 'a', 'n'],													//
//		['e', 't', 'a', 'e'],													//
//		['i', 'h', 'k', 'r'],													//
//		['i', 'f', 'l', 'v']													//
//	]																			//
//	Return["eat", "oath"].														//
//	Note:																		//
//	You may assume that all inputs are consist of lowercase letters a - z.		//
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

//利用深度优先搜索，直接用79题的代码，时间复杂度较高，会超时
class Solution {
public:
	vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
		vector<string> result;
		unordered_set<string> worddict(words.begin(), words.end());
		for (auto ele : worddict)
			if (exist(board, ele))
				result.push_back(ele);
		return result;
	}
private:
	bool exist(vector<vector<char>>& board, string word) {
		const int m = board.size();
		const int n = board[0].size();
		vector<vector<bool> > status(m, vector<bool>(n, false));
		for (int i = 0; i < m; ++i)
			for (int j = 0; j < n; ++j)
				if (WordSearch(0, i, j, status, board, word))
					return true;
		return false;
	}
	bool WordSearch(int deep, int i, int j, vector<vector<bool>>& status, vector<vector<char>>& board, string word) {
		if (i < 0 || j < 0 || i >= board.size() || j >= board[0].size())
			return false;
		if (word[deep] != board[i][j])
			return false;
		if (status[i][j])
			return false;
		if (word.size() - 1 == deep)
			return true;
		status[i][j] = true;
		if (WordSearch(deep + 1, i + 1, j, status, board, word) 
			|| WordSearch(deep + 1, i, j + 1, status, board, word)
			|| WordSearch(deep + 1, i - 1, j, status, board, word)
			|| WordSearch(deep + 1, i, j - 1, status, board, word))
			return true;
		status[i][j] = false;
		return false;
	}
};
//由于单词集比较大，可以事先将其整合，采用trie树
class Solution2 {
public:
	vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
		Trie trie;
		for (auto s : words)
			trie.insert(s);
		vector<string> result;
		string sofar;
		for (int i = 0; i < board.size(); ++i)
			for (int j = 0; j < board[0].size(); ++j)
				DFS(board, result, sofar, trie.root, i, j);
		return result;
	}
private:
	class Trie {
	public:
		Trie() {
			root = new TrieNode();
		}

		// Inserts a word into the trie.
		void insert(string s) {
			if (search(s)) return;
			TrieNode* curr = root;
			for (auto ch : s) {
				TrieNode* child = curr->subNode(ch);
				if (child != nullptr) {
					curr = child;
				}
				else {
					TrieNode *newNode = new TrieNode(ch);
					curr->children.push_back(newNode);
					curr = newNode;
				}
				++curr->shared;
			}
			curr->isend = true;
		}

		// Returns if the word is in the trie.
		bool search(string key) {
			TrieNode* curr = root;
			for (auto ch : key) {
				curr = curr->subNode(ch);
				if (curr == nullptr)
					return false;
			}
			return curr->isend == true;
		}

		// Returns if there is any word in the trie
		// that starts with the given prefix.
		bool startsWith(string prefix) {
			TrieNode* curr = root;
			for (auto ch : prefix) {
				curr = curr->subNode(ch);
				if (curr == nullptr)
					return false;
			}
			return true;
		}
		~Trie() {
			delete root;
		}
	public:
		class TrieNode {
		public:
			char content;   // the character included
			bool isend;     // if the node is the end of a word
			int shared;     // the number of the node shared ,convenient to implement delete(string key), not necessary in this problem
			vector<TrieNode*> children; // the children of the node
										// Initialize your data structure here.
			TrieNode() :content(' '), isend(false), shared(0) {}
			TrieNode(char ch) :content(ch), isend(false), shared(0) {}
			TrieNode* subNode(char ch) {
				if (!children.empty()) {
					for (auto child : children) {
						if (child->content == ch)
							return child;
					}
				}
				return nullptr;
			}
			~TrieNode() {
				for (auto child : children)
					delete child;
			}
		};
		TrieNode* root;
	};
	void DFS(vector<vector<char>> &board, vector<string> &ret, string &sofar, Trie::TrieNode *root, int i, int j) {
		if (i < 0 || j < 0 || i >= board.size() || j >= board[0].size())
			return;
		if (root->subNode(board[i][j]) == nullptr)
			return;
		root = root->subNode(board[i][j]);
		char t = '\0';
		swap(t, board[i][j]);
		sofar.push_back(t);
		if (root->isend) {
			root->isend = false;
			ret.push_back(sofar);
		}
		DFS(board, ret, sofar, root, i, j + 1);
		DFS(board, ret, sofar, root, i + 1, j);
		DFS(board, ret, sofar, root, i - 1, j);
		DFS(board, ret, sofar, root, i, j - 1);
		swap(t, board[i][j]);
		sofar.pop_back();
	}
};
//针对此题，使用trie树可以优化
class Solution3 {
public:
	int m, n;
	class Trie {
	public:
		Trie *next[26];
		bool exist;

		Trie() {
			fill_n(next, 26, nullptr);
			exist = false;
		}

		~Trie() {
			for (int i = 0; i < 26; ++i)
				delete next[i];
		}

		void insert(const string &t) {
			Trie *iter = this;
			for (int i = 0; i < t.size(); ++i) {
				if (iter->next[t[i] - 'a'] == nullptr)
					iter->next[t[i] - 'a'] = new Trie();
				iter = iter->next[t[i] - 'a'];
			}
			iter->exist = true;
		}
	};
	vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
		Trie *trie = new Trie();
		for (auto &s : words)
			trie->insert(s);
		m = board.size();
		n = board[0].size();

		vector<string> ret;
		string sofar;
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				bc(board, ret, sofar, trie, i, j);
			}
		}
		return ret;
	}

	void bc(vector<vector<char>> &board, vector<string> &ret, string &sofar, Trie *root, int x, int y) {
		if (x < 0 || y < 0 || x >= m || y >= n || board[x][y] == '\0' || root == nullptr)
			return;
		if (root->next[board[x][y] - 'a'] == nullptr)
			return;
		root = root->next[board[x][y] - 'a'];
		char t = '\0';
		swap(t, board[x][y]);
		sofar.push_back(t);
		if (root->exist) {
			root->exist = false;
			ret.push_back(sofar);
		}
		bc(board, ret, sofar, root, x, y + 1);
		bc(board, ret, sofar, root, x + 1, y);
		bc(board, ret, sofar, root, x - 1, y);
		bc(board, ret, sofar, root, x, y - 1);
		swap(t, board[x][y]);
		sofar.pop_back();
	}
};
//优化2
class Solution4 {
	class Trie {
	public:
		Trie *children[26]; // pointers to its substrings starting with 'a' to 'z'
		bool leaf; // if the node is a leaf, or if there is a word stopping at here
		int idx; // if it is a leaf, the string index of the array words
		Trie()
		{
			this->leaf = false;
			this->idx = 0;
			fill_n(this->children, 26, nullptr);
		}
	};

public:
	void insertWords(Trie *root, vector<string>& words, int idx)
	{
		int pos = 0, len = words[idx].size();
		while (pos<len)
		{
			if (nullptr == root->children[words[idx][pos] - 'a']) root->children[words[idx][pos] - 'a'] = new Trie();
			root = root->children[words[idx][pos++] - 'a'];
		}
		root->leaf = true;
		root->idx = idx;
	}

	Trie *buildTrie(vector<string>& words)
	{
		Trie *root = new Trie();
		int i;
		for (i = 0; i<words.size(); i++) insertWords(root, words, i);
		return root;
	}

	void checkWords(vector<vector<char>>& board, int i, int j, int row, int col, Trie *root, vector<string> &res, vector<string>& words)
	{
		char temp;
		if (board[i][j] == 'X') return; // visited before;
		if (nullptr == root->children[board[i][j] - 'a']) return; // no string with such prefix
		else
		{
			temp = board[i][j];
			if (root->children[temp - 'a']->leaf)  // if it is a leaf
			{
				res.push_back(words[root->children[temp - 'a']->idx]);
				root->children[temp - 'a']->leaf = false; // set to false to indicate that we found it already
			}
			board[i][j] = 'X'; //mark the current position as visited
							   // check all the possible neighbors
			if (i>0) checkWords(board, i - 1, j, row, col, root->children[temp - 'a'], res, words);
			if ((i + 1)<row) checkWords(board, i + 1, j, row, col, root->children[temp - 'a'], res, words);
			if (j>0) checkWords(board, i, j - 1, row, col, root->children[temp - 'a'], res, words);
			if ((j + 1)<col)  checkWords(board, i, j + 1, row, col, root->children[temp - 'a'], res, words);
			board[i][j] = temp; // recover the current position
		}
	}

	vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
		vector<string> res;
		int row = board.size();
		if (0 == row) return res;
		int col = board[0].size();
		if (0 == col) return res;
		int wordCount = words.size();
		if (0 == wordCount) return res;

		Trie *root = buildTrie(words);

		int i, j;
		for (i = 0; i<row; i++)
		{
			for (j = 0; j<col && wordCount > res.size(); j++)
			{
				checkWords(board, i, j, row, col, root, res, words);
			}
		}
		return res;
	}
};
//int main(void)
//{
//	Solution4 test;
//	vector<vector<char>> board = {  { 'o', 'a', 'a', 'n' },
//									{ 'e', 't', 'a', 'e' },
//									{ 'i', 'h', 'k', 'r' },
//									{ 'i', 'f', 'l', 'v' } };
//	vector<string> words{ "oath", "pea", "eat", "rain" };
//	auto res = test.findWords(board, words);
//	for (auto s : res)
//		cout << s << " ";
//	cout << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}