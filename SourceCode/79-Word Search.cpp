//	79. Word Search
//------------------------------------------------------------------------------//
//	Given a 2D board and a word, find if the word exists in the grid.			//
//	The word can be constructed from letters of sequentially adjacent cell,		//
//	where "adjacent" cells are those horizontally or vertically neighboring.The //
//	same letter cell may not be used more than once.							//
//	For example,																//
//	Given board =																//
//	[																			//
//		['A', 'B', 'C', 'E'],													//
//		['S', 'F', 'C', 'S'],													//
//		['A', 'D', 'E', 'E']													//
//	]																			//
//	word = "ABCCED", ->returns true,											//
//	word = "SEE", ->returns true,												//
//	word = "ABCB", ->returns false.												//
//------------------------------------------------------------------------------//
#include <iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include<functional>
// constants
// function prototype
using namespace std;
//回溯加递归深搜
class Solution 
{
public:
	bool exist(vector<vector<char>>& board, string word) 
	{
		const int m = board.size();
		const int n = board[0].size();
		vector<vector<bool> > status(m, vector<bool>(n, false));
		for (int i = 0; i < m; ++i)
			for (int j = 0; j < n; ++j)
				if (WordSearch(0, i, j, status, board, word))
					return true;
		return false;
	}
private:
	bool WordSearch(int deep, int i, int j, vector<vector<bool>>& status, vector<vector<char>>& board, string word)
	{
		if (i < 0 || i >= board.size() || j < 0 || j >= board[0].size())
			return false;
		if (board[i][j] != word[deep])
			return false;
		if (status[i][j] == true)
			return false;
		if (deep == word.size() - 1)
			return true;
		status[i][j] = true;
		if (WordSearch(deep + 1, i - 1, j, status, board, word)
			|| WordSearch(deep + 1, i + 1, j, status, board, word)
			|| WordSearch(deep + 1, i, j - 1, status, board, word)
			|| WordSearch(deep + 1, i, j + 1, status, board, word))
			return true;
		status[i][j] = false;
		return false;
	}
};
//利用board来记录是否访问过该节点，会破坏原始数据
class Solution2 {
public:
	bool exist(vector<vector<char> > &board, string word) {
		m = board.size();
		n = board[0].size();
		for (int x = 0; x<m; x++)
			for (int y = 0; y<n; y++)
			{
				if (isFound(board, word.c_str(), x, y))
					return true;
			}
		return false;
	}
private:
	int m;
	int n;
	bool isFound(vector<vector<char> > &board, const char* w, int x, int y)
	{
		if (x<0 || y<0 || x >= m || y >= n || board[x][y] == '\0' || *w != board[x][y])
			return false;
		if (*(w + 1) == '\0')
			return true;
		char t = board[x][y];
		board[x][y] = '\0';
		if (isFound(board, w + 1, x - 1, y) || isFound(board, w + 1, x + 1, y) || isFound(board, w + 1, x, y - 1) || isFound(board, w + 1, x, y + 1))
			return true;
		board[x][y] = t;
		return false;
	}
};
//int main(void)
//{
//	Solution test;
//	vector<vector<char>> board = { {'A', 'B', 'C', 'E' },{'S', 'F', 'C', 'S' },{'A', 'D', 'E', 'E' } };
//	cout << test.exist(board, "ABCB");
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
