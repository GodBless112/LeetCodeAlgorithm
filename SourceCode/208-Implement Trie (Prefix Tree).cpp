//	208. Implement Trie (Prefix Tree)
//------------------------------------------------------------------------------//
//	Implement a trie with insert, search, and startsWith methods.				//
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
//字典树，核心思想是空间换时间。利用字符串的公共前缀来降低查询时间的开销以达到提高效率的目的
//Trie树的基本性质可以归纳为： 
//（1）根节点不包含字符，除根节点意外每个节点只包含一个字符。
//（2）从根节点到某一个节点，路径上经过的字符连接起来，为该节点对应的字符串。
//（3）每个节点的所有子节点包含的字符串不相同。
//Trie树有一些特性：
//1）根节点不包含字符，除根节点外每一个节点都只包含一个字符。
//2）从根节点到某一节点，路径上经过的字符连接起来，为该节点对应的字符串。
//3）每个节点的所有子节点包含的字符都不相同。
//4）如果字符的种数为n，则每个结点的出度为n，这也是空间换时间的体现，浪费了很多的空间。
//5）插入查找的复杂度为O(n)，n为字符串长度。
//基本思想（以字母树为例）：
//1、插入过程
//对于一个单词，从根开始，沿着单词的各个字母所对应的树中的节点分支向下走，直到单词遍历完，将最后
//的节点标记为红色，表示该单词已插入Trie树。
//2、查询过程
//同样的，从根开始按照单词的字母顺序向下遍历trie树，一旦发现某个节点标记不存在或者单词遍历完成而
//最后的节点未标记为红色，则表示该单词不存在，若最后的节点标记为红色，表示该单词存在。
class Trie {
public:
	/** Initialize your data structure here. */
	Trie() {
		root = new TrieNode;
	}

	/** Inserts a word into the trie. */
	void insert(string word) {
		TrieNode *node = root;
		for (int i = 0; i < word.size(); ++i) {
			int id = word[i] - 'a';
			if (nullptr == node->next[id])
				node->next[id] = new TrieNode;
			node = node->next[id];
			node->count++;
		}
		node->exit = true;
	}

	/** Returns if the word is in the trie. */
	bool search(string word) {
		TrieNode *node = root;
		for (int i = 0; i < word.size(); ++i) {
			int id = word[i] - 'a';
			if (nullptr == node->next[id])
				return false;
			node = node->next[id];
		}
		return node->exit;
	}

	/** Returns if there is any word in the trie that starts with the given prefix. */
	bool startsWith(string prefix) {
		TrieNode *node = root;
		for (int i = 0; i < prefix.size(); ++i) {
			int id = prefix[i] - 'a';
			if (nullptr == node->next[id])
				return false;
			node = node->next[id];
		}
		return node->count;
	}
private:
	struct TrieNode
	{
		int count;				//统计单词前缀出现的次数
		TrieNode * next[26];	//指向下面的节点
		bool exit;				//该节点是否构成单词
		TrieNode() :count(0), exit(false) {
			memset(next, 0, sizeof(next));
		}
	};
	TrieNode *root;
};
//更普遍完善的实现
class Trie2 {
public:
	Trie2() {
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
	~Trie2() {
		delete root;
	}
private:
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
/**
* Your Trie object will be instantiated and called as such:
* Trie obj = new Trie();
* obj.insert(word);
* bool param_2 = obj.search(word);
* bool param_3 = obj.startsWith(prefix);
*/
//int main(void)
//{
//	Trie2 obj;
//	obj.insert("my");
//	obj.insert("luck");
//	cout << boolalpha << obj.search("my") << endl;
//	cout << boolalpha << obj.startsWith("lu");
//	cout << endl;
//	// code to keep window open for MSVC++
//	cin.clear();
//	while (cin.get() != '\n')
//		continue;
//	cin.get();
//
//	return 0;
//}