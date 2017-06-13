//	211. Add and Search Word - Data structure design
//------------------------------------------------------------------------------//
//	Design a data structure that supports the following two operations:			//
//	void addWord(word)															//
//	bool search(word)															//
//	search(word) can search a literal word or a regular expression string		//
//	containing only letters a - z or ..A.means it can represent any one letter.	//
//	For example :																//
//	addWord("bad")																//
//	addWord("dad")																//
//	addWord("mad")																//
//	search("pad") -> false														//
//	search("bad") -> true														//
//	search(".ad") -> true														//
//	search("b..") -> true														//
//	Note:																		//
//	You may assume that all words are consist of lowercase letters a - z.		//
//	You should be familiar with how a Trie works. If not, please work on this	//
//	problem: Implement Trie (Prefix Tree) first.								//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
#include<unordered_set>
#include<queue>
#include<stack>
// constants
// function prototype
using namespace std;
//采用字典树（前缀树）的方法，完善的版本
class WordDictionary {
public:
	/** Initialize your data structure here. */
	WordDictionary() {
		root = new TrieNode;
	}

	/** Adds a word into the data structure. */
	void addWord(string word) {
		if (search(word)) return;
		TrieNode *node = root;
		for (auto ch : word) {
			TrieNode* child = node->subNode(ch);
			if (child != nullptr) {
				node = child;
			}
			else {
				TrieNode *newNode = new TrieNode(ch);
				node->children.push_back(newNode);
				node = newNode;
			}
			++node->shared;
		}
		node->isend = true;
	}

	/** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
	bool search(string word) {
		return search(root, word);
	}
private:
	class TrieNode {
	public:
		char content;
		bool isend;
		int shared;
		vector<TrieNode*> children;
		TrieNode() :content(' '), isend(false), shared(0) {}
		TrieNode(char ch) :content(ch), isend(false), shared(0) {}
		TrieNode *subNode(char ch) {
			if (!children.empty())
				for (auto child : children)
					if (child->content == ch)
						return child;
			return nullptr;
		}
		~TrieNode() {
			for (auto child : children)
				delete child;
		}
	};
	bool search(TrieNode* root, string word) {
		TrieNode* curr = root;
		for (int i = 0; i < word.size(); ++i) {
			if (word[i] == '.') {
				int j;
				for (j = 0; j < curr->children.size(); ++j)
					if (search(curr->children[j], word.substr(i + 1)))
						return true;
				return false;
			}
			else {
				curr = curr->subNode(word[i]);
				if (curr == nullptr)
					return false;
			}
		}
		return curr->isend == true;
	}
	TrieNode *root;
};
//字典树简化版
class WordDictionary2 {
public:
	/** Initialize your data structure here. */
	WordDictionary2() {
		root = new TrieNode;
	}

	/** Adds a word into the data structure. */
	void addWord(string word) {
		TrieNode *node = root;
		for (auto ch : word) {
			if (nullptr == node->children[ch - 'a'])
				node->children[ch - 'a'] = new TrieNode;
			node = node->children[ch - 'a'];
		}
		node->isKey = true;
	}

	/** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
	bool search(string word) {
		return search(root, word.c_str());
	}
private:
	class TrieNode {
	public:
		bool isKey;
		TrieNode* children[26];
		TrieNode() : isKey(false) {
			memset(children, NULL, sizeof(TrieNode*) * 26);
		}
	};
	bool search(TrieNode* root, const char* word) {
		TrieNode* curr = root;
		for (int i = 0; word[i]; i++) {
			if (curr && word[i] != '.')
				curr = curr->children[word[i] - 'a'];
			else if (curr && word[i] == '.') {
				TrieNode *tmp = curr;
				for (int j = 0; j < 26; ++j) {
					curr = tmp->children[j];
					if (search(curr, word + i + 1))
						return true;
				}
			}
			else break;
		}
		return curr && curr->isKey;
	}
	TrieNode *root;
};
/**
* Your WordDictionary object will be instantiated and called as such:
* WordDictionary obj = new WordDictionary();
* obj.addWord(word);
* bool param_2 = obj.search(word);
*/
//int main(void)
//{
//	WordDictionary2 obj;
//	obj.addWord("bad");
//	cout<<boolalpha << obj.search("b..");
//	cout << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}